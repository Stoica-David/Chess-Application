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
	for (auto curr : v)
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

bool Board::IsOver(EColor color) const
{
	Position whiteKingPos = FindKing(color);

	return (IsCheckMate(whiteKingPos, color));
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

bool Board::VerifyTheWay(Position p1, Position p2) const
{
	int x1 = p1.first, y1 = p1.second, x2 = p2.first, y2 = p2.second;

	PositionList piecePattern = m_board[x1][y1]->DeterminePattern(p1, p2);

	for (const auto& currPos : piecePattern)
	{
		int currX = currPos.first,
			currY = currPos.second;
		if (m_board[currX][currY])
		{
			if ((currPos != p2) || (currPos == p2 && m_board[currX][currY] && SameColor(m_board[x1][y1]->GetColor(), m_board[currX][currY]->GetColor())))
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
			if ((!m_board[i][j]) || SameColor(m_board[i][j]->GetColor(), color))
			{
				continue;
			}
			else
			{
				moves = GetMoves({ i, j });
			}

			for (int k = 0; k < moves.size(); k++)
			{
				if (moves[k] == p)
					return true;
			}
		}
	}
	return false;
}

bool Board::IsSameWay(Position p1, Position p2, EColor color) const
{
	Position checkPos = FindCheck(p1, color);

	PositionList checkList = m_board[checkPos.first][checkPos.second]->DeterminePattern(checkPos, p1);

	Position pos1 = checkPos, pos2 = checkList[0];
	int xp1 = pos1.first,
		yp1 = pos1.second,
		xp2 = pos2.first,
		yp2 = pos2.second;

	int d1 = xp2 - xp1;
	int d2 = yp2 - yp1;

	int x1 = p1.first,
		y1 = p1.second,
		x2 = p2.first,
		y2 = p2.second;

	int d3 = x2 - x1;
	int d4 = y2 - y1;

	return ((d1 == d3) && (d2 == d4));
}

bool Board::IsCheckMate(Position p, EColor color) const
{
	if (!m_board[p.first][p.second])
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
			EColor notColor;

			if (color == EColor::Black)
				notColor = EColor::White;
			else
				notColor = EColor::Black;

			if (!IsDefended(currMoves[i], notColor))
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
		if (Find(remaining, EPieceType::Queen) == 1)
		{
			return true;
		}

		if (Find(remaining, EPieceType::Rook) == 1)
		{
			return true;
		}

		if (Find(remaining, EPieceType::Pawn) == 1)
		{
			return true;
		}

		if (Find(remaining, EPieceType::Knight) == 1)
		{
			return true;
		}

		if ((Find(remaining, EPieceType::Bishop) == 2 && !SameBishop()) || Find(remaining, EPieceType::Bishop) == 1)
		{
			return true;
		}
	}

	return false;
}

Position Board::FindCheck(Position p, EColor color) const
{
	PositionList currList;
	Position checkPos;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if ((!m_board[i][j]) || SameColor(m_board[i][j]->GetColor(), color))
			{
				continue;
			}

			currList = GetMoves({ i,j });

			for (int k = 0; k < currList.size(); k++)
			{
				if (currList[k] == p)
				{
					return { i, j };
				}
			}
		}
	}

	return {};
}

Position Board::FindKing(EColor color) const
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
			if (m_board[i][j] && m_board[i][j]->GetType() == EPieceType::King && SameColor(m_board[i][j]->GetColor(), color))
				return { i, j };
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
			if (m_board[i][j])
				newList.push_back(m_board[i][j]);
		}
	}
	return newList;
}

void Board::Move(Position p1, Position p2)
{
	PiecesPtr currPiece = GetPiece(p1);
	PiecesPtr nextPiece = GetPiece(p2);

	if (!currPiece->IsMoveRegular(p1, p2))
		throw MoveException("The move cannot be done by the piece!");

	if (!VerifyTheWay(p1, p2))
	{
		throw InTheWayException("There is a piece in the way");
	}

	if (nextPiece && currPiece->SameColor(nextPiece))
	{
		throw SameColorException("The pieces have the same color");
	}

	if (currPiece->Is(EPieceType::Pawn) && PawnGoesDiagonally(p1, p2) && (!nextPiece))
	{
		throw PawnDiagonallyException("The pawn cannot go diagonally!");
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
	int x1 = p1.first, y1 = p1.second, x2 = p2.first, y2 = p2.second;

	return (std::abs(x2 - x1) == 1 && std::abs(y2 - y1) == 1);
}


bool Board::FindHelp(Position p, EColor color) const
{
	PositionList attackMoves;
	PositionList helpMoves;
	PositionList kingMoves = GetMoves(p);
	PiecesPtr attackPiece;
	Position attackPos;

	int x = p.first, y = p.second;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (!m_board[i][j] || SameColor(m_board[i][j]->GetColor(), color))
				continue;
			attackMoves = GetMoves({ i, j });
			for (int k = 0; k < attackMoves.size(); k++)
				if (attackMoves[k] == p)
				{
					attackPiece = m_board[i][j];
					attackPos = { i, j };
				}
		}
	}

	PositionList attackPattern = attackPiece->DeterminePattern(attackPos, p);

	for (auto currPos : attackPattern)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (!m_board[i][j] || (m_board[i][j]->GetColor() != color) || (m_board[i][j]->GetType() == EPieceType::King))
				{
					continue;
				}

				helpMoves = GetMoves({ i, j });

				for (int k = 0; k < helpMoves.size(); k++)
				{
					if (currPos == helpMoves[k])
					{
						if (m_board[i][j]->GetType() == EPieceType::Pawn && !m_board[helpMoves[k].first][helpMoves[k].second])
						{
							break;
						}

						return true;

					}
				}
			}
		}
	}
	return false;
}

bool Board::KillCheck(Position p, EColor color) const
{
	Position toKill;
	int x = p.first, y = p.second;

	if (!m_board[x][y])
	{
		return false;
	}

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (m_board[i][j] && !SameColor(m_board[i][j]->GetColor(), color))
			{
				PositionList moves = GetMoves({ i, j });
				for (int k = 0; k < moves.size(); k++)
					if (moves[k] == p)
					{
						toKill = std::make_pair(i, j);
						break;
					}
			}
		}
	}

	int killX = toKill.first, killY = toKill.second;
	EColor notColor = m_board[toKill.first][toKill.second]->GetColor();

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (m_board[i][j] && !SameColor(m_board[i][j]->GetColor(), m_board[killX][killY]->GetColor()))
			{
				PositionList moves = GetMoves({ i, j });
				for (int k = 0; k < moves.size(); k++)
				{
					if (moves[k] == toKill)
					{
						if (m_board[i][j]->GetType() == EPieceType::King && IsDefended(toKill, notColor))
						{
							break;
						}

						if (m_board[i][j]->GetType() == EPieceType::Pawn && !PawnGoesDiagonally({ i,j }, moves[0]))
						{
							break;
						}

						return true;
					}
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
			if (!m_board[i][j] || !SameColor(m_board[i][j]->GetColor(), color))
				continue;

			currList = DefendedPositions({ i, j }, color);

			for (int k = 0; k < currList.size(); k++)
			{
				if (currList[k] == p)
					return true;
			}
		}
	}

	return false;
}

bool Board::SameColor(EColor color1, EColor color2) const
{
	return (color1 == color2);
}

bool Board::SameBishop() const
{
	Piece* firstBishop = nullptr;
	Piece* secondBishop = nullptr;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (m_board[i][j] && m_board[i][j]->Is(EPieceType::Bishop))
			{
				if (!firstBishop)
					firstBishop = GetPiece({ i, j }).get();
				else
					secondBishop = GetPiece({ i, j }).get();
			}
		}
	}

	return firstBishop && secondBishop && firstBishop->GetColor() == secondBishop->GetColor();
}

PositionList Board::DefendedPositions(Position p, EColor color) const
{
	PositionList newList = {};

	if (!m_board[p.first][p.second])
		return {};

	PositionMatrix m = m_board[p.first][p.second]->AllMoves(p);

	for (int i = 0; i < m.size(); i++)
	{
		for (int j = 0; j < m[i].size(); j++)
		{
			int currX = m[i][j].first;
			int currY = m[i][j].second;

			if (!m_board[currX][currY] || !SameColor(m_board[currX][currY]->GetColor(), color))
				continue;

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
				if (currPiece && !SameColor(currPiece->GetColor(), initialPiece->GetColor()))
					newList.push_back({ x , y });
				break;
			}

			newList.push_back({ x , y });
		}
	}

	return newList;
}

int Board::Find(PieceVector v, EPieceType Piece) const
{
	int cnt = 0;
	for (const auto& x : v)
		if (x->GetType() == Piece)
			cnt++;
	return cnt;
}
