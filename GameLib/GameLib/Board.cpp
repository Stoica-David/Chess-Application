#include "Board.h"
#include "PieceInfo.h"
#include "BoardExceptions.h"

Board::Board()
{
	std::vector<EPieceType> TYPES = {
		EPieceType::Rook,
		EPieceType::Knight,
		EPieceType::Bishop,
		EPieceType::Queen,
		EPieceType::King,
		EPieceType::Bishop,
		EPieceType::Knight,
		EPieceType::Rook
	};

	for (int i = 0; i < TYPES.size(); i++)
	{
		m_board[0][i] = Piece::Produce(TYPES[i], EColor::Black);
		m_board[7][i] = Piece::Produce(TYPES[i], EColor::White);
	}

	for (int i = 0; i < 8; i++)
	{
		m_board[1][i] = Piece::Produce(EPieceType::Pawn, EColor::Black);
		m_board[6][i] = Piece::Produce(EPieceType::Pawn, EColor::White);
	}
}

// For creating different type of boards for testing
Board::Board(const PiecePairVector& v)
{
	for (const auto& curr : v)
	{
		int x = curr.first.first;
		int y = curr.first.second;
		PiecesPtr currPiece = curr.second;

		m_board[x][y] = currPiece;
	}
}

PiecesPtr& Board::operator[](Position p)
{
	return m_board[p.first][p.second];
}

IPieceInfoPtr Board::GetPieceInfo(Position p) const
{
	if (auto piece = GetPiece(p))
	{
		return PieceInfo::Produce(piece->GetType(), piece->GetColor());
	}

	return {};
}

PiecesPtr Board::GetPiece(Position p) const
{
	return m_board[p.first][p.second];
}

bool Board::IsOver(EColor color) const
{
	Position KingPos = FindKing(color);

	return (IsCheckMate(KingPos, color));
}

bool Board::VerifyTheWay(Position p1, Position p2) const
{
	int x1 = p1.first,
		y1 = p1.second,
		x2 = p2.first,
		y2 = p2.second;

	PiecesPtr initialPiece = m_board[x1][y1];

	PositionList piecePattern = initialPiece->DeterminePattern(p1, p2);

	for (const auto& currPos : piecePattern)
	{
		int currX = currPos.first,
			currY = currPos.second;

		PiecesPtr currPiece = m_board[currX][currY];

		if (currPiece)
		{
			if ((currPos != p2) || (currPos == p2 && (initialPiece->GetColor() == currPiece->GetColor())))
			{
				return false;
			}
		}
	}

	return true;
}

bool Board::IsCheck(Position p, EColor color) const
{
	PositionList moves;

	for (int i = 0; i < m_board.size(); i++)
	{
		for (int j = 0; j < m_board[i].size(); j++)
		{
			PiecesPtr currPiece = m_board[i][j];

			if ((!currPiece) || (currPiece->GetColor() == color))
			{
				continue;
			}
			else
			{
				moves = GetMoves({ i, j });
			}

			auto it = std::find(moves.begin(), moves.end(), p);

			if (it != moves.end())
			{
				return true;
			}
		}
	}
	return false;
}

bool Board::IsSameWay(Position p1, Position p2, EColor color) const
{
	Position checkPos = FindCheck(p1, color);

	PiecesPtr attackPiece = m_board[checkPos.first][checkPos.second];

	PositionList checkList = attackPiece->DeterminePattern(checkPos, p1);

	Position pos1 = checkPos, pos2 = checkList[0];
	int x1Check = pos1.first,
		y1Check = pos1.second,
		x2Check = pos2.first,
		y2Check = pos2.second;

	int d1 = x2Check - x1Check;
	int d2 = y2Check - y1Check;

	int x1King = p1.first,
		y1King = p1.second,
		x2King = p2.first,
		y2King = p2.second;

	int d3 = x2King - x1King;
	int d4 = y2King - y1King;

	return ((d1 == d3) && (d2 == d4));
}

bool Board::IsCheckMate(Position p, EColor color) const
{
	PiecesPtr King = m_board[p.first][p.second];

	if (!King)
	{
		return false;
	}

	PositionList currMoves = GetMoves(p);

	if (!IsCheck(p, color))
	{
		return false;
	}

	for (int i = 0; i < currMoves.size(); i++)
	{
		if (!IsCheck(currMoves[i], color))
		{
			if (!IsDefended(currMoves[i], OppositeColor(color)))
			{
				if (!IsSameWay(p, currMoves[i], color))
				{
					return false;
				}
			}
		}
	}

	if (FindHelp(p, color))
	{
		return false;
	}

	if (KillCheck(p, color))
	{
		return false;
	}

	return true;
}

bool Board::IsDraw() const
{
	PieceVector remaining = RemainingPieces();

	if (remaining.size() == 2)
	{
		return true;
	}

	if (remaining.size() <= 4)
	{
		if (Find(remaining, EPieceType::Rook) == 1)
		{
			return true;
		}

		if (Find(remaining, EPieceType::Knight) == 1)
		{
			return true;
		}

		if ((Find(remaining, EPieceType::Bishop) == 2 && !SameBishop()) || (Find(remaining, EPieceType::Bishop) == 1))
		{
			return true;
		}
	}

	return false;
}

bool Board::Stalemate(EColor color) const
{
	Position kingPos = FindKing(color);

	if (!OnlyKing(color))
	{
		return false;
	}

	if (IsCheck(kingPos, color))
	{
		return false;
	}

	PositionList kingMoves = GetMoves(kingPos);

	for (const auto& currMove : kingMoves)
	{
		if (!IsCheck(currMove, color))
		{
			return false;
		}
	}

	return true;
}

Position Board::FindCheck(Position p, EColor color) const
{
	PositionList currMoves;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			PiecesPtr currPiece = m_board[i][j];

			if ((!currPiece) || (currPiece->GetColor() == color))
			{
				continue;
			}

			currMoves = GetMoves({ i,j });

			auto it = std::find(currMoves.begin(), currMoves.end(), p);

			if (it != currMoves.end())
			{
				return { i, j };
			}
		}
	}

	return {-1, -1};
}

Position Board::FindKing(EColor color) const
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			PiecesPtr currPiece = m_board[i][j];

			if (currPiece && (currPiece->GetType() == EPieceType::King) && (currPiece->GetColor() == color))
			{
				return { i, j };
			}
		}
	}
	return { -1, -1 };
}

PieceVector Board::RemainingPieces() const
{
	PieceVector newList;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			PiecesPtr currPiece = m_board[i][j];

			if (currPiece)
			{
				newList.push_back(currPiece);
			}
		}
	}
	return newList;
}

void Board::PromoteTo(const std::string& string, Position p, EColor color) 
{
	Position prevPos;

	if (p.first == 0)
	{
		prevPos.first = p.first + 1;
	}
	else if (p.first == 7)
	{
		prevPos.first = p.first - 1;
	}
	else
	{
		throw PromoteException("Can't promote!\n");
	}

	prevPos.second = p.second;

	if (!m_board[p.first][p.second]->Is(EPieceType::Pawn))
	{
		throw PromoteException("Can't Promote yet!");
	}

	m_board[prevPos.first][prevPos.second] = {};

	if (string == "Queen")
	{
		UpdatePiece(EPieceType::Queen, p, color);
	}
	if (string == "Rook")
	{
		UpdatePiece(EPieceType::Rook, p, color);
	}
	if (string == "Bishop")
	{
		UpdatePiece(EPieceType::Bishop, p, color);
	}
	if (string == "Knight")
	{
		UpdatePiece(EPieceType::Knight, p, color);
	}
}

void Board::UpdatePiece(EPieceType type, Position p, EColor color)
{
	m_board[p.first][p.second] = Piece::Produce(type, color);
}

void Board::Move(Position p1, Position p2)
{
	PiecesPtr currPiece = GetPiece(p1);
	PiecesPtr nextPiece = GetPiece(p2);

	if (!currPiece->IsMoveRegular(p1, p2))
	{
		if (!currPiece->Is(EPieceType::Pawn) || PawnException(p1, p2))
		{
			throw MoveException("The move cannot be done by the piece!");
		}
	}

	if (!VerifyTheWay(p1, p2))
	{
		throw InTheWayException("There is a piece in the way");
	}

	if (nextPiece && currPiece->SameColor(nextPiece))
	{
		throw SameColorException("The pieces have the same color");
	}

	(*this)[p2] = currPiece;
	(*this)[p1] = {};

	Position kingPos = FindKing(currPiece->GetColor());

	if (IsCheck(kingPos, currPiece->GetColor()))
	{
		(*this)[p1] = currPiece;
		(*this)[p2] = nextPiece;

		throw StillCheckException("The king is still in check!");
	}

}

bool Board::PawnGoesDiagonally(Position p1, Position p2)
{
	int x1 = p1.first,
		y1 = p1.second,
		x2 = p2.first,
		y2 = p2.second;

	return (std::abs(x2 - x1) == 1 && std::abs(y2 - y1) == 1);
}

bool Board::OnlyKing(EColor color) const
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			PiecesPtr currPiece = m_board[i][j];

			if (currPiece && currPiece->GetColor() == color && !currPiece->Is(EPieceType::King))
			{
				return false;
			}
		}
	}

	return true;
}

bool Board::FindHelp(Position p, EColor color) const
{
	PositionList kingMoves = GetMoves(p);

	PositionList attackMoves;
	PiecesPtr attackPiece;
	Position attackPos;

	int x = p.first,
		y = p.second;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			PiecesPtr currPiece = m_board[i][j];

			if (!currPiece || (currPiece->GetColor() == color))
			{
				continue;
			}

			attackMoves = GetMoves({ i, j });

			auto it = std::find(attackMoves.begin(), attackMoves.end(), p);

			if (it != attackMoves.end())
			{
				attackPiece = currPiece;
				attackPos = { i, j };
			}
		}
	}

	PositionList attackPattern = attackPiece->DeterminePattern(attackPos, p);

	PositionList helpMoves;
	for (auto currPos : attackPattern)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				PiecesPtr currPiece = m_board[i][j];

				if (!currPiece || (currPiece->GetColor() != color) || (currPiece->GetType() == EPieceType::King))
				{
					continue;
				}

				helpMoves = GetMoves({ i, j });

				auto it = std::find(helpMoves.begin(), helpMoves.end(), currPos);

				if (it != helpMoves.end())
				{
					if (currPiece->GetType() == EPieceType::Pawn && !m_board[(*it).first][(*it).second])
					{
						break;
					}

					return true;
				}
			}
		}
	}

	return false;
}

bool Board::KillCheck(Position p, EColor color) const
{
	int x = p.first,
		y = p.second;

	Position toKill;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			PiecesPtr currPiece = m_board[i][j];

			if (currPiece && (currPiece->GetColor() != color))
			{
				PositionList moves = GetMoves({ i, j });

				auto it = std::find(moves.begin(), moves.end(), p);

				if (it != moves.end())
				{
					toKill = { i, j };
					break;
				}
			}
		}
	}

	int killX = toKill.first, killY = toKill.second;

	EColor notColor = m_board[killX][killY]->GetColor();

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			PiecesPtr currPiece = m_board[i][j];

			if (currPiece && (currPiece->GetColor() != m_board[killX][killY]->GetColor()))
			{
				PositionList moves = GetMoves({ i, j });

				auto it = std::find(moves.begin(), moves.end(), toKill);

				if (it != moves.end())
				{
					if (currPiece->GetType() == EPieceType::King && IsDefended(toKill, notColor))
					{
						break;
					}

					if (currPiece->GetType() == EPieceType::Pawn && !PawnGoesDiagonally({ i,j }, moves[0]))
					{
						break;
					}

					return true;
				}
			}
		}
	}
	return false;
}

bool Board::IsDefended(Position p, EColor color) const
{
	PositionList currList;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			PiecesPtr currPiece = m_board[i][j];

			if (!currPiece || (currPiece->GetColor() != color))
			{
				continue;
			}

			currList = DefendedPositions({ i, j }, color);

			auto it = std::find(currList.begin(), currList.end(), p);

			if (it != currList.end())
			{
				return true;
			}
		}
	}

	return false;
}

bool Board::SameBishop() const
{
	Piece* firstBishop = nullptr;
	Piece* secondBishop = nullptr;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			PiecesPtr currPiece = m_board[i][j];

			if (currPiece && currPiece->Is(EPieceType::Bishop))
			{
				if (!firstBishop)
				{
					firstBishop = GetPiece({ i, j }).get();
				}
				else
				{
					secondBishop = GetPiece({ i, j }).get();
				}
			}
		}
	}

	return (firstBishop && secondBishop && firstBishop->GetColor() == secondBishop->GetColor());
}

bool Board::PawnException(Position p1, Position p2) const
{
	PiecesPtr currPiece = m_board[p1.first][p1.second];
	PiecesPtr nextPiece = m_board[p2.first][p2.second];

	return (currPiece->Is(EPieceType::Pawn) && (!PawnGoesDiagonally(p1, p2) || (PawnGoesDiagonally(p1, p2) && (!nextPiece))));
}

PositionList Board::DefendedPositions(Position p, EColor color) const
{
	PositionList newList;
	PiecesPtr initialPiece = m_board[p.first][p.second];
	if (!initialPiece)
	{
		return {};
	}

	PositionMatrix m = initialPiece->AllMoves(p);

	for (int i = 0; i < m.size(); i++)
	{
		for (int j = 0; j < m[i].size(); j++)
		{
			int currX = m[i][j].first;
			int currY = m[i][j].second;

			PiecesPtr currPiece = m_board[currX][currY];

			if (!currPiece || (currPiece->GetColor() != color))
			{
				continue;
			}

			newList.push_back({ currX, currY });
		}
	}

	return newList;
}

PositionList Board::GetMoves(Position p) const
{
	auto initialPiece = m_board[p.first][p.second];

	if (!initialPiece)
	{
		return {};
	}

	PositionMatrix currMoves = initialPiece->AllMoves(p);

	PositionList newList;

	for (int i = 0; i < currMoves.size(); i++)
	{
		for (int j = 0; j < currMoves[i].size(); j++)
		{
			int x = currMoves[i][j].first;
			int y = currMoves[i][j].second;

			if (auto currPiece = m_board[x][y])
			{
				if (currPiece->GetColor() != initialPiece->GetColor())
				{
					if (!initialPiece->Is(EPieceType::Pawn) || (PawnGoesDiagonally(p, {x,y})))
					{
						newList.push_back({ x , y });
					}
				}

				break;
			}

			newList.push_back({ x , y });
		}
	}

	return newList;
}

int Board::Find(PieceVector v, EPieceType Piece) const
{
	int tmp = 0;

	for (const auto& x : v)
	{
		if (x->GetType() == Piece)
		{
			tmp++;
		}
	}

	return tmp;
}
