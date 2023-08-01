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
			m_board[i][j] = ProducePiece(matrix[i][j]);
		}
	}

	m_whiteDead = { };
	m_blackDead = { };
	m_prevPositions = { };
	m_moves = { };
}

PiecesPtr& Board::operator[](Position p)
{
	return m_board[p.first][p.second];
}

void Board::SetHistory(const MoveVector& v)
{
	m_moves = v;
}

void Board::SetBoard(const String& string)
{
	Reset();

	if (string[1] != '.')
	{
		int line = 0, col = 0;

		for (int i = 0; i < string.size() - 2; i++)
		{
			if (isalpha(string[i]))
			{
				m_board[line][col] = ProducePiece(string[i]);
			}
			else if (isdigit(string[i]))
			{
				int ws = string[i] - '0';

				for (int j = 0; j < ws; j++)
				{
					m_board[line][col] = {};
					col++;
				}

				col--;
			}
			else if (string[i] == '/')
			{
				line++;
				col = 0;
			}
			else
			{
				col++;
			}
		}
	}/*
	else
	{

	}*/
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

MoveVector Board::GetHistory() const
{
	return m_moves;
}

bool Board::IsOver(EColor color) const
{
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
	for (int i = 0; i < m_board.size(); i++)
	{
		for (int j = 0; j < m_board[i].size(); j++)
		{
			PiecesPtr currPiece = m_board[i][j];

			if ((!currPiece) || (currPiece->GetColor() == color))
			{
				continue;
			}

			PositionList moves = GetMovesNormal({ i, j });

			if (std::find(moves.begin(), moves.end(), p) != moves.end())
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

	if (!IsCheck(p, color))
	{
		return false;
	}

	PositionList currMoves = GetMovesNormal(p);
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

	if (Is3Fold())
	{
		return true;
	}

	return false;
}

bool Board::IsStalemate(EColor color) const
{
	if (!OnlyKing(color))
	{
		return false;
	}

	Position kingPos = FindKing(color);

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

bool Board::Is3Fold() const
{
	if (!m_prevPositions.size())
	{
		return false;
	}

	int nrAppearences = 0;
	for (int i = 0; i < m_prevPositions.size(); i++)
	{
		if (m_prevPositions[i] == m_prevPositions[m_prevPositions.size() - 1])
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

bool Board::IsPinned(Position p) const
{
	EColor currColor = m_board[p.first][p.second]->GetColor();

	Position checkPos = FindCheck(p, currColor);

	if (checkPos == Position(-1, -1))
	{
		return false;
	}

	Position kingPos = FindKing(currColor);
	PositionList behindCurr = m_board[checkPos.first][checkPos.second]->DeterminePattern(p, kingPos);

	for (int i = 0; i < behindCurr.size(); i++)
	{
		auto [currX, currY] = behindCurr[i];

		if (m_board[currX][currY] && behindCurr[i] != kingPos)
		{
			return false;
		}
	}

	PositionMatrix checkMoves = m_board[checkPos.first][checkPos.second]->AllMoves(checkPos);

	bool kingFound = false, currFound = false;

	for (int i = 0; i < checkMoves.size(); i++)
	{
		for (int j = 0; j < checkMoves[i].size(); j++)
		{
			if (checkMoves[i][j] == kingPos)
			{
				kingFound = true;
			}

			if (checkMoves[i][j] == p)
			{
				currFound = true;
			}
		}
	}

	return kingFound && currFound;
}

Position Board::FindCheck(Position p, EColor color) const
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			PiecesPtr currPiece = m_board[i][j];

			if ((!currPiece) || (currPiece->GetColor() == color))
			{
				continue;
			}

			PositionList currMoves = GetMovesNormal({ i,j });

			if (std::find(currMoves.begin(), currMoves.end(), p) != currMoves.end())
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

	switch (pieceType)
	{
	case EPieceType::Rook:
	case EPieceType::Knight:
	case EPieceType::Bishop:
	case EPieceType::Queen:
		m_board[p.first][p.second] = Piece::Produce(pieceType, color);
		break;
	default:
		throw PromoteException("Can't promote!\n");
	}
}

void Board::Move(Position p1, Position p2)
{
	PiecesPtr currPiece = GetPiece(p1);
	PiecesPtr nextPiece = GetPiece(p2);

	if (!currPiece->IsMoveRegular(p1, p2) && !IsCastle(p1, p2))
	{
		if (!currPiece->Is(EPieceType::Pawn) || (PawnException(p1, p2) && !IsEnPassant(p1, p2)))
		{
			throw MoveException("The move cannot be done by the piece!");
		}
	}

	if (!VerifyTheWay(p1, p2))
	{
		throw InTheWayException("There is a piece in the way");
	}

	if (!IsCastle(p1, p2) && !IsEnPassant(p1, p2))
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
	else if (IsEnPassant(p1, p2))
	{
		EnPassant(p1, p2);
	}
	else
	{
		Castle(p1, p2);
	}

	m_moves.push_back({ p1, p2 });

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

		m_moves.pop_back();

		throw StillCheckException("The king is still in check!");
	}
	else if (currPiece->GetColor() == EColor::Black)
	{
		UpdatePrevPositions();
	}

	ResetEnPassant();

	if ((*this)[p2] && (*this)[p2]->Is(EPieceType::Pawn) && std::abs(p2.first - p1.first) == 2 && std::abs(p2.second - p1.second) == 0)
	{
		Position leftPos = { p2.first, p2.second - 1 };
		Position rightPos = { p2.first, p2.second + 1 };

		if (leftPos.second >= 0 && (*this)[leftPos] && (*this)[leftPos]->Is(EPieceType::Pawn) && (*this)[leftPos]->GetColor() != (*this)[p2]->GetColor())
		{
			(*this)[leftPos]->SetRightPassant(true);
		}

		if (rightPos.second <= 7 && (*this)[rightPos] && (*this)[rightPos]->Is(EPieceType::Pawn) && (*this)[rightPos]->GetColor() != (*this)[p2]->GetColor())
		{
			(*this)[rightPos]->SetLeftPassant(true);
		}
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
	m_moves = { };
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
	else if (IsPinned(p))
	{
		newList = GetMovesPinned(p);
	}
	else
	{
		newList = GetMovesNormal(p);
	}

	if (m_board[p.first][p.second]->Is(EPieceType::Pawn))
	{
		PositionList enPassantMoves = GetPassantMoves(p);

		for (int i = 0; i < enPassantMoves.size(); i++)
		{
			newList.push_back(enPassantMoves[i]);
		}
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

PositionList Board::GetMovesPinned(Position p) const
{
	EColor currColor = m_board[p.first][p.second]->GetColor();

	PositionList newList;

	Position kingPos = FindKing(currColor);
	Position checkPos = FindCheck(p, currColor);

	PositionList checkPattern = m_board[checkPos.first][checkPos.second]->DeterminePattern(checkPos, p);

	PositionList currMoves = GetMovesNormal(p);

	for (int i = 0; i < currMoves.size(); i++)
	{
		for (int j = 0; j < checkPattern.size(); j++)
		{
			if (currMoves[i] == checkPattern[j] || currMoves[i] == checkPos)
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

String Board::GenerateFEN() const
{
	String FEN;	int tmp = 0;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (!m_board[i][j])
			{
				tmp++;
			}
			else
			{
				if (tmp)
				{
					FEN.push_back('0' + tmp);

					tmp = 0;
				}

				FEN.push_back(m_board[i][j]->ConvertPiece());
			}
		}

		if (tmp)
		{
			FEN.push_back('0' + tmp);

			tmp = 0;
		}

		if (i != 7)
		{
			FEN.push_back('/');
		}
	}

	return FEN;
}

String Board::GeneratePGN() const
{
	return "";
}

bool Board::PawnGoesDiagonally(Position p1, Position p2)
{
	int x1 = p1.first,
		y1 = p1.second,
		x2 = p2.first,
		y2 = p2.second;

	return (std::abs(x2 - x1) == 1 && std::abs(y2 - y1) == 1);
}

bool Board::LeftPawnCheck(Position p) const
{
	PiecesPtr otherPiece = m_board[p.first][p.second - 1];
	PiecesPtr currPiece = m_board[p.first][p.second];

	return (p.second - 1 > 0 && otherPiece && otherPiece->Is(EPieceType::Pawn) && otherPiece->GetColor() != currPiece->GetColor());
}

bool Board::RightPawnCheck(Position p) const
{
	PiecesPtr otherPiece = m_board[p.first][p.second + 1];
	PiecesPtr currPiece = m_board[p.first][p.second];

	return (p.second + 1 < 7 && otherPiece && otherPiece->Is(EPieceType::Pawn) && otherPiece->GetColor() != currPiece->GetColor());
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

				if (!currPiece || (currPiece->GetColor() != color) || (currPiece->Is(EPieceType::King)))
				{
					continue;
				}

				helpMoves = GetMovesNormal({ i, j });

				auto it = std::find(helpMoves.begin(), helpMoves.end(), currPos);

				if (it != helpMoves.end())
				{
					if (currPiece->Is(EPieceType::Pawn) && !m_board[(*it).first][(*it).second])
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

bool Board::IsEnPassant(Position p1, Position p2) const
{
	PiecesPtr currPiece = m_board[p1.first][p1.second];
	PiecesPtr nextPiece = m_board[p2.first][p2.second];

	if (!currPiece || !currPiece->Is(EPieceType::Pawn) || nextPiece)
	{
		return false;
	}

	if (!m_board[p1.first][p1.second]->GetLeftPassant() && !m_board[p1.first][p1.second]->GetRightPassant())
	{
		return false;
	}

	if (!PawnGoesDiagonally(p1, p2))
	{
		return false;
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

PositionList Board::GetPassantMoves(Position p) const
{
	PositionList enPassantMoves;

	auto leftPos = { p.first, p.second - 1 };

	if (m_board[p.first][p.second]->GetLeftPassant() == true)
	{
		if (LeftPawnCheck(p))
		{
			if (m_board[p.first][p.second]->GetColor() == EColor::White)
			{
				enPassantMoves.push_back({ p.first - 1, p.second - 1 });
			}
			else
			{
				enPassantMoves.push_back({ p.first + 1, p.second - 1 });
			}
		}
	}
	else if (m_board[p.first][p.second]->GetRightPassant() == true)
	{
		if (RightPawnCheck(p))
		{
			if (m_board[p.first][p.second]->GetColor() == EColor::White)
			{
				enPassantMoves.push_back({ p.first - 1, p.second + 1 });
			}
			else
			{
				enPassantMoves.push_back({ p.first + 1, p.second + 1 });
			}
		}
	}

	return enPassantMoves;
	{

	};
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

EColor Board::OppositeColor(EColor color)
{
	return color == EColor::White ? EColor::Black : EColor::White;
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

void Board::EnPassant(Position p1, Position p2)
{
	if ((p2.second > p1.second && (*this)[p1]->GetRightPassant() == false) || (p2.second < p1.second && (*this)[p1]->GetLeftPassant() == false))
	{
		throw MoveException("The piece can't do this move!");
	}

	Position otherPawnPos;

	if ((*this)[p1]->GetColor() == EColor::White)
	{
		otherPawnPos = { p2.first + 1, p2.second };

		(*this)[p2] = GetPiece(p1);
		(*this)[otherPawnPos] = {};
		(*this)[p1] = {};

		IPieceInfoPtr ip = GetPieceInfo(p2);

		m_blackDead.push_back(ip);
	}
	else
	{
		otherPawnPos = { p2.first - 1, p2.second };

		(*this)[p2] = GetPiece(p1);
		(*this)[otherPawnPos] = {};
		(*this)[p1] = {};

		IPieceInfoPtr ip = GetPieceInfo(p2);

		m_whiteDead.push_back(ip);
	}

	(*this)[p2]->SetLeftPassant(false);
	(*this)[p2]->SetRightPassant(false);
}

void Board::ResetEnPassant()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (m_board[i][j])
			{
				m_board[i][j]->SetLeftPassant(false);
				m_board[i][j]->SetRightPassant(false);
			}
		}
	}
}

Position Board::IntermediatePosition(Position p) const
{
	PiecesPtr currPiece = m_board[p.first][p.second];
	Position intermediate = { -1, -1 };

	if (currPiece->Is(EPieceType::Pawn))
	{
		Position pair1 = { 5, p.second };
		Position pair2 = { 2, p.second };

		intermediate = currPiece->GetColor() == EColor::White ? pair1 : pair2;
	}

	return intermediate;
}

PiecesPtr Board::ProducePiece(char c)
{
	if (c == '-')
		return {};

	auto type = GetPieceType(c);
	auto color = isupper(c) ? EColor::White : EColor::Black;

	return Piece::Produce(type, color);
}

EPieceType Board::GetPieceType(char c)
{
	switch (tolower(c))
	{
	case 'p':
	{
		return EPieceType::Pawn;
	}
	case 'h':
	{
		return EPieceType::Knight;
	}
	case 'r':
	{
		return EPieceType::Rook;
	}
	case 'q':
	{
		return EPieceType::Queen;
	}
	case 'b':
	{
		return EPieceType::Bishop;
	}
	case 'k':
	{
		return EPieceType::King;
	}
	case 'n':
	{
		return EPieceType::Knight;
	}
	}
}
