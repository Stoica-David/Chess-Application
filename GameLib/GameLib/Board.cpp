#include "Board.h"
#include "PieceInfo.h"
#include "BoardExceptions.h"

Board::Board()
{
	Reset();
}

Board::Board(const CharMatrix& matrix)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (matrix[i][j] == '-')
			{
				m_board[i][j] = {};
			}
			else if (isupper(matrix[i][j]))
			{
				InitializeWhite(matrix[i][j], { i,j });
			}
			else if (islower(matrix[i][j]))
			{
				InitializeBlack(matrix[i][j], { i,j });
			}
		}
	}
	
	m_whiteDead = { };
	m_blackDead = { };
	m_prevPositions = { };
}

PiecesPtr& Board::operator[](Position p)
{
	return m_board[p.first][p.second];
}

IPieceInfoPtr Board::GetPieceInfo(Position p) const
{
	if (auto piece = GetPiece(p))
	{
		return std::make_shared<PieceInfo>(piece->GetType(), piece->GetColor());
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

	return (IsCheckMate(color));
}

bool Board::VerifyTheWay(Position p1, Position p2) const
{
	if (IsCastle(p1, p2))
	{
		if (p1.second > p2.second)
		{
			return VerifyTheWay(p1, { p2.first, p2.second + 2 });
		}
		else
		{
			return VerifyTheWay(p1, { p2.first, p2.second - 1 });
		}
	}

	int x1 = p1.first,
		y1 = p1.second,
		x2 = p2.first,
		y2 = p2.second;

	PiecesPtr initialPiece = m_board[x1][y1];

	PositionList piecePattern = initialPiece->DeterminePattern(p1, p2);

	for (const auto& currPos : piecePattern)
	{
		if (auto currPiece = m_board[currPos.first][currPos.second])
		{
			if ((currPos != p2) || (currPos == p2 && (initialPiece->GetColor() == currPiece->GetColor())) || (initialPiece->Is(EPieceType::Pawn) && !PawnGoesDiagonally(p1, p2)))
			{
				return false;
			}
		}
		else
		{
			if (initialPiece->Is(EPieceType::Pawn) && (GetPiece(IntermediatePosition(p1))) && std::abs(x1 - x2) == 2)
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
				moves = GetMovesNormal({ i, j });
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

bool Board::IsCheckMate(EColor color) const
{
	Position p = FindKing(color);

	PiecesPtr King = m_board[p.first][p.second];

	if (!King)
	{
		return false;
	}

	PositionList currMoves = GetMovesNormal(p);

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

	if (Is3Fold(GetCurrentPosition()))
	{
		return true;
	}

	return false;
}

bool Board::IsStalemate(EColor color) const
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

	PositionList kingMoves = GetMovesNormal(kingPos);

	auto NotInCheck = [&](const Position& p)
	{
		return !IsCheck(p, color);
	};

	return std::find_if(kingMoves.begin(), kingMoves.end(), NotInCheck) == kingMoves.end();
}

bool Board::Is3Fold(const Bitset& bitset) const
{
	int nrAppearences = 0;

	for (int i = 0; i < m_prevPositions.size(); i++)
	{
		if (m_prevPositions[i] == bitset)
		{
			nrAppearences++;
		}
	}

	return (nrAppearences == 3);
}

bool Board::IsPromotePossible(Position p) const
{
	return (m_board[p.first][p.second] && m_board[p.first][p.second]->Is(EPieceType::Pawn) && (p.first == 0 || p.first == 7));
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

			currMoves = GetMovesNormal({ i,j });

			auto it = std::find(currMoves.begin(), currMoves.end(), p);

			if (it != currMoves.end())
			{
				return { i, j };
			}
		}
	}

	return { -1, -1 };
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

void Board::PromoteTo(EPieceType pieceType, EColor color)
{
	Position p;
	Position prevPos;

	bool found = false;

	for (int i = 0; i < 8; i++)
	{
		if (m_board[0][i] && m_board[0][i]->Is(EPieceType::Pawn))
		{
			found = true;
			p = { 0, i };
		}

		if (m_board[7][i] && m_board[7][i]->Is(EPieceType::Pawn))
		{
			p = { 7, i };
			found = true;
		}
	}

	if (!found)
	{
		throw PromoteException("Can't promote!\n");
	}

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

	switch (pieceType)
	{
	case EPieceType::Rook:
		UpdatePiece(EPieceType::Rook, p, color);
		break;
	case EPieceType::Knight:
		UpdatePiece(EPieceType::Knight, p, color);
		break;
	case EPieceType::Bishop:
		UpdatePiece(EPieceType::Bishop, p, color);
		break;
	case EPieceType::Queen:
		UpdatePiece(EPieceType::Queen, p, color);
		break;
	default:
		break;
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

	if (!currPiece->IsMoveRegular(p1, p2) && !IsCastle(p1, p2))
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

	if (!IsCastle(p1, p2))
	{
		if ((*this)[p2])
		{
			IPieceInfoPtr ip = GetPieceInfo(p2);

			if ((*this)[p2]->GetColor() == EColor::White)
			{
				m_whiteDead.push_back(ip);
			}
			else
			{
				m_blackDead.push_back(ip);
			}
		}

		(*this)[p2] = currPiece;
		(*this)[p1] = {};
		(*this)[p2]->SetHasMoved(true);

	}
	else
	{
		Castle(p1, p2);
	}

	Position kingPos = FindKing(currPiece->GetColor());

	if (IsCheck(kingPos, currPiece->GetColor()))
	{
		(*this)[p1] = currPiece;
		(*this)[p2] = nextPiece;

		if ((*this)[p2] && (*this)[p2]->GetColor() == EColor::White)
		{
			if (m_whiteDead.size())
			{
				m_whiteDead.pop_back();
			}
		}
		else
		{
			if (m_blackDead.size())
			{
				m_blackDead.pop_back();
			}
		}

		currPiece->SetHasMoved(false);

		throw StillCheckException("The king is still in check!");
	}

	if (currPiece->GetColor() == EColor::Black)
	{
		UpdatePrevPositions();
	}
}

void Board::Reset()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			m_board[i][j] = {};
		}
	}

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

	m_whiteDead = { };
	m_blackDead = { };
	m_prevPositions = { };
}

PositionList Board::GetMoves(Position p) const
{
	PiecesPtr currPiece = m_board[p.first][p.second];

	PositionList newList;

	if (!currPiece)
	{
		return {};
	}

	if (IsCheck(FindKing(currPiece->GetColor()), currPiece->GetColor()))
	{
		newList = GetMovesCheck(p);
	}
	else
	{
		newList = GetMovesNormal(p);
	}

	return newList;
}

PositionList Board::GetMovesNormal(Position p) const
{
	auto initialPiece = m_board[p.first][p.second];

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
					if (!initialPiece->Is(EPieceType::Pawn) || (PawnGoesDiagonally(p, { x,y })))
					{
						newList.push_back({ x , y });
					}
				}

				break;
			}

			if (initialPiece->Is(EPieceType::Pawn) && std::abs(p.first - x) == 2)
			{
				int intermediateX = IntermediatePosition(p).first;
				int intermediateY = IntermediatePosition(p).second;

				if (m_board[intermediateX][intermediateY])
				{
					break;
				}
			}

			if ((!initialPiece->Is(EPieceType::Pawn) || (!PawnGoesDiagonally(p, { x,y }))))
			{
				newList.push_back({ x , y });
			}
		}
	}

	return newList;
}

PositionList Board::GetMovesCheck(Position p) const
{
	PiecesPtr currPiece = m_board[p.first][p.second];
	EColor currColor = m_board[p.first][p.second]->GetColor();
	PositionList newList;

	if (currPiece->Is(EPieceType::King))
	{
		newList = GetMovesNormal(p);

		for (int i = 0; i < newList.size(); i++)
		{
			if (IsCheck(newList[i], currColor))
			{
				newList.erase(newList.begin() + i);
			}
		}
	}
	else
	{
		Position kingPos = FindKing(currColor);
		PiecesPtr king = m_board[kingPos.first][kingPos.second];

		Position checkPos = FindCheck(kingPos, currColor);
		PiecesPtr checkPiece = m_board[checkPos.first][checkPos.second];

		PositionList checkPattern = checkPiece->DeterminePattern(checkPos, kingPos);

		PositionList currMoves = GetMovesNormal(p);

		for (int i = 0; i < currMoves.size(); i++)
		{
			for (int j = 0; j < checkPattern.size(); j++)
			{
				if (currMoves[i] == checkPattern[j])
				{
					newList.push_back(currMoves[i]);
				}
			}
		}

		for (int i = 0; i < currMoves.size(); i++)
		{
			if (checkPos == currMoves[i])
			{
				newList.push_back(currMoves[i]);
			}
		}
	}

	return newList;
}

const IPieceInfoVector& Board::GetWhiteDead() const
{
	return m_whiteDead;
}

const IPieceInfoVector& Board::GetBlackDead() const
{
	return m_blackDead;
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
	PositionList kingMoves = GetMovesNormal(p);

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

			attackMoves = GetMovesNormal({ i, j });

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

				helpMoves = GetMovesNormal({ i, j });

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
				PositionList moves = GetMovesNormal({ i, j });

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
				PositionList moves = GetMovesNormal({ i, j });

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

bool Board::IsCastle(Position p1, Position p2) const
{
	PiecesPtr initialPiece = m_board[p1.first][p1.second];
	PiecesPtr finalPiece = m_board[p2.first][p2.second];

	if (!initialPiece || !finalPiece)
	{
		return false;
	}

	if (!initialPiece->Is(EPieceType::King) || !finalPiece->Is(EPieceType::Rook))
	{
		return false;
	}

	if (initialPiece->GetHasMoved() || finalPiece->GetHasMoved())
	{
		return false;
	}

	if (initialPiece->GetColor() != finalPiece->GetColor())
	{
		return false;
	}

	if ((p1.first != 0 && p1.first != 7) || (p2.first != 0 && p2.first != 7))
	{
		return false;
	}

	if (p1.first != p2.first)
	{
		return false;
	}

	if (p1.second - p2.second != 4 && p2.second - p1.second != 3)
	{
		return false;
	}

	PositionList castleTiles = finalPiece->DeterminePattern(p2, p1);

	for (int i = 0; i < castleTiles.size(); i++)
	{
		if (IsCheck(castleTiles[i], m_board[p1.first][p1.second]->GetColor()))
		{
			return false;
		}
	}

	return true;
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

Bitset Board::GetCurrentPosition() const
{
	Bitset newBitset;

	int k = 0;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (!m_board[i][j])
			{
				for (int l = 0; l < 4; l++)
				{
					newBitset[4 * k + l] = 1;
				}
			}
			else
			{
				EPieceType currType = m_board[i][j]->GetType();

				newBitset[4 * k] = (int)m_board[i][j]->GetColor();

				newBitset[4 * k + 1] = ((int)currType % 2);

				newBitset[4 * k + 2] = ((int)currType / 2) % 2;

				newBitset[4 * k + 3] = ((int)currType / 4) % 2;

			}
			k++;
		}
	}

	return newBitset;
}

void Board::Castle(Position p1, Position p2)
{
	PiecesPtr currPiece = m_board[p1.first][p1.second];
	PiecesPtr nextPiece = m_board[p2.first][p2.second];

	int newSecondKing, newSecondRook;

	if (p1.second > p2.second)
	{
		newSecondKing = p2.second + 2;
		newSecondRook = p1.second - 1;
	}
	else
	{
		newSecondKing = p2.second - 1;
		newSecondRook = p1.second + 1;
	}

	m_board[p2.first][newSecondKing] = currPiece;
	m_board[p2.first][newSecondRook] = nextPiece;

	currPiece->SetHasMoved(true);
	nextPiece->SetHasMoved(true);

	(*this)[p1] = {};
	(*this)[p2] = {};

	if (IsCheck({ p2.first, newSecondKing }, m_board[p2.first][newSecondKing]->GetColor()))
	{
		m_board[p2.first][newSecondKing] = {};
		m_board[p2.first][newSecondRook] = {};

		(*this)[p1] = currPiece;
		(*this)[p2] = nextPiece;
	}
}

void Board::UpdatePrevPositions()
{
	m_prevPositions.push_back(GetCurrentPosition());
}

void Board::InitializeWhite(char c, Position p)
{
	int i = p.first, j = p.second;

	switch (c)
	{
	case 'P':
	{
		m_board[i][j] = Piece::Produce(EPieceType::Pawn, EColor::White);
		break;
	}
	case 'R':
	{
		m_board[i][j] = Piece::Produce(EPieceType::Rook, EColor::White);
		break;
	}
	case 'B':
	{
		m_board[i][j] = Piece::Produce(EPieceType::Bishop, EColor::White);
		break;
	}
	case 'H':
	{
		m_board[i][j] = Piece::Produce(EPieceType::Knight, EColor::White);
		break;
	}
	case 'Q':
	{
		m_board[i][j] = Piece::Produce(EPieceType::Queen, EColor::White);
		break;
	}
	case 'K':
	{
		m_board[i][j] = Piece::Produce(EPieceType::King, EColor::White);
		break;
	}
	}
}

void Board::InitializeBlack(char c, Position p)
{
	int i = p.first, j = p.second;

	switch (c)
	{
	case 'p':
	{
		m_board[i][j] = Piece::Produce(EPieceType::Pawn, EColor::Black);
		break;
	}
	case 'r':
	{
		m_board[i][j] = Piece::Produce(EPieceType::Rook, EColor::Black);
		break;
	}
	case 'b':
	{
		m_board[i][j] = Piece::Produce(EPieceType::Bishop, EColor::Black);
		break;
	}
	case 'h':
	{
		m_board[i][j] = Piece::Produce(EPieceType::Knight, EColor::Black);
		break;
	}
	case 'q':
	{
		m_board[i][j] = Piece::Produce(EPieceType::Queen, EColor::Black);
		break;
	}
	case 'k':
	{
		m_board[i][j] = Piece::Produce(EPieceType::King, EColor::Black);
		break;
	}
	}
}

Position Board::IntermediatePosition(Position p) const
{
	PiecesPtr currPiece = m_board[p.first][p.second];
	Position intermediate = { -1, -1 };

	if (!currPiece->Is(EPieceType::Pawn))
	{
		return intermediate;
	}

	if (currPiece->GetColor() == EColor::White)
	{
		intermediate = { 5, p.second };
	}
	else
	{
		intermediate = { 2, p.second };
	}

	return intermediate;
}
