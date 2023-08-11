#include "Board.h"
#include "PieceInfo.h"
#include "BoardExceptions.h"

#include <sstream>
#include <algorithm>
#include <cstdint>

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

	m_prevPositions = { };
	m_moves = { };
	m_PGN = { };
}

Board::Board(const Board& newBoard)
{
	m_board = newBoard.m_board;
	m_moves = newBoard.m_moves;
	m_PGN = newBoard.m_PGN;
	m_prevPositions = newBoard.m_prevPositions;
}

PiecesPtr& Board::at(Position p)
{
	return m_board.at(p.x).at(p.y);
}

const PiecesPtr& Board::at(Position p) const
{
	return m_board.at(p.x).at(p.y);
}

void Board::Set(const ChessBoard& board)
{
	m_board = board;
}

IPieceInfoPtr Board::GetPieceInfo(Position p) const
{
	if (auto piece = at(p))
	{
		return std::make_shared<PieceInfo>(piece->GetType(), piece->GetColor());
	}

	return {};
}

MoveVector Board::GetHistory() const
{
	return m_moves;
}

String Board::GetCurrPGN() const
{
	return m_PGN;
}

BitMatrix Board::GetPrevPositions() const
{
	return m_prevPositions;
}

bool Board::IsOver(EColor color) const
{
	return (IsCheckMate(color));
}

bool Board::CastleVerifyWay(Position p1, Position p2) const
{
	if (IsCastle(p1, p2))
	{
		Position nextPos = p1.y > p2.y ? Position(p2.x, p2.y + 2) : Position(p2.x, p2.y - 1);

		return VerifyTheWay(p1, nextPos);
	}

	return false;
}

bool Board::VerifyTheWay(Position p1, Position p2) const
{
	if (CastleVerifyWay(p1, p2))
		return true;

	int x1 = p1.x,
		y1 = p1.y,
		x2 = p2.x,
		y2 = p2.y;

	PiecesPtr initialPiece = m_board[x1][y1];

	PositionList piecePattern = initialPiece->DeterminePattern(p1, p2);

	for (const auto& currPos : piecePattern)
	{
		if (auto currPiece = at(currPos))
		{
			if ((currPos != p2) || (currPos == p2 && (initialPiece->SameColor(currPiece))) || (initialPiece->Is(EPieceType::Pawn) && !PawnGoesDiagonally(p1, p2)))
			{
				return false;
			}
		}
		else if (initialPiece->Is(EPieceType::Pawn) && CanMoveTwoForward(p1, p2))
		{
			return false;
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

			if ((!currPiece) || (currPiece->Is(color)))
			{
				continue;
			}

			PositionList moves = GetMovesNormal({ i, j });

			if (currPiece->Is(EPieceType::Pawn) && PawnGoesDiagonally({ i, j }, p))
				return true;

			if (std::find(moves.begin(), moves.end(), p) != moves.end())
			{
				if (!currPiece->Is(EPieceType::Pawn) || PawnGoesDiagonally({ i,j }, p))
				{
					return true;
				}
			}
		}
	}

	return false;
}

bool Board::IsSameWay(Position p1, Position p2, EColor color) const
{
	Position checkPos = FindCheck(p1, color);

	PiecesPtr attackPiece = at(checkPos);

	PositionList checkList = attackPiece->DeterminePattern(checkPos, p1);

	Position pos1 = checkPos, pos2 = checkList[0];
	int x1Check = pos1.x,
		y1Check = pos1.y,
		x2Check = pos2.x,
		y2Check = pos2.y;

	int d1 = x2Check - x1Check;
	int d2 = y2Check - y1Check;

	int x1King = p1.x,
		y1King = p1.y,
		x2King = p2.x,
		y2King = p2.y;

	int d3 = x2King - x1King;
	int d4 = y2King - y1King;

	return ((d1 == d3) && (d2 == d4));
}

bool Board::IsCheckMate(EColor color) const
{
	Position kingPos = FindKing(color);
	PiecesPtr King = at(kingPos);

	if (!King || !IsCheck(kingPos, color))
	{
		return false;
	}

	PositionList currMoves = GetMovesNormal(kingPos);
	for (auto& pos : currMoves)
	{
		if (!IsCheck(pos, color))
		{
			if (!IsDefended(pos, OppositeColor(color)))
			{
				if (!IsSameWay(kingPos, pos, color))
				{
					return false;
				}
			}
		}
	}

	return !FindHelp(kingPos, color) && !KillCheck(kingPos, color);
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
		if (Find(remaining, EPieceType::Rook) == 1 || Find(remaining, EPieceType::Knight) == 1 || (Find(remaining, EPieceType::Bishop) == 1))
		{
			return true;
		}

		if ((Find(remaining, EPieceType::Bishop) == 2 && !SameBishop()))
		{
			return true;
		}
	}

	return Is3Fold();
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
	if (m_prevPositions.empty())
		return false;

	return std::count(m_prevPositions.begin(), m_prevPositions.end(), m_prevPositions.back()) == 3;
}

bool Board::IsPromotePossible(Position p) const
{
	PiecesPtr currPiece = at(p);

	return (currPiece && currPiece->Is(EPieceType::Pawn) && (p.x == 0 || p.x == 7));
}

bool Board::IsPinned(Position p) const
{
	EColor currColor = at(p)->GetColor();

	Position checkPos = FindCheck(p, currColor);

	if (checkPos == Position(-1, -1))
	{
		return false;
	}

	Position kingPos = FindKing(currColor);
	PositionList behindCurr = at(checkPos)->DeterminePattern(p, kingPos);

	for (int i = 0; i < behindCurr.size(); i++)
	{
		if (at(behindCurr[i]) && behindCurr[i] != kingPos)
		{
			return false;
		}
	}

	//PositionMatrix checkMoves = at(checkPos)->AllMoves(checkPos);

	PositionList checkPattern = at(checkPos)->DeterminePattern(checkPos, kingPos);

	bool kingFound = false, currFound = false;

	for (auto position : checkPattern)
	{
		if (position == kingPos)
		{
			kingFound = true;
		}

		if (position == p)
		{
			currFound = true;
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

			if (currPiece && (currPiece->Is(EPieceType::King, color)))
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
			if (PiecesPtr currPiece = m_board[i][j])
			{
				newList.push_back(currPiece);
			}
		}
	}

	return newList;
}

void Board::PromoteTo(EPieceType pieceType, EColor color)
{
	Position pieceToPromote;

	bool found = false;
	for (int i = 0; i < 8; i++)
	{
		if (m_board[0][i] && m_board[0][i]->Is(EPieceType::Pawn))
		{
			found = true;
			pieceToPromote = { 0, i };
		}

		if (m_board[7][i] && m_board[7][i]->Is(EPieceType::Pawn))
		{
			pieceToPromote = { 7, i };
			found = true;
		}
	}

	if (!found)
	{
		throw PromoteException("Can't promote!\n");
	}

	at(pieceToPromote) = Piece::Produce(pieceType, color);
}

void Board::Move(Position p1, Position p2)
{
	m_PGN.clear();

	PiecesPtr currPiece;
	PiecesPtr nextPiece;

	try
	{
		currPiece = at(p1);
		nextPiece = at(p2);
	}
	catch (...)
	{
		throw MoveException("");
	}

	if (!currPiece)
	{
		throw MoveException("The move cannot be done by the piece!");
	}

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

	m_PGN += ConvertMove(p1, p2);

	bool currPiecePrevMoved = currPiece->GetHasMoved();

	if (IsCastle(p1, p2))
	{
		Castle(p1, p2);
	}
	else if (IsEnPassant(p1, p2))
	{
		EnPassant(p1, p2);
	}
	else
	{
		at(p2) = currPiece;
		at(p1) = {};
		currPiece->SetHasMoved(true);
	}

	m_moves.push_back({ p1, p2 });

	Position kingPos = FindKing(currPiece->GetColor());

	if (IsCheck(kingPos, currPiece->GetColor()))
	{
		at(p1) = currPiece;
		at(p2) = nextPiece;

		currPiece->SetHasMoved(currPiecePrevMoved);

		m_PGN.clear();
		m_moves.pop_back();

		throw StillCheckException("The king is still in check!");
	}
	else
	{
		UpdatePrevPositions();
	}

	ResetEnPassant();

	if (at(p2) && at(p2)->Is(EPieceType::Pawn) && Pawn2Forward(p1, p2))
	{
		if (p2.y > 0)
		{
			Position leftPos = { p2.x, p2.y - 1 };

			if (LeftPawnCheck(p2))
			{
				at(leftPos)->SetRightPassant(true);
			}
		}

		if (p2.y < 7)
		{
			Position rightPos = { p2.x, p2.y + 1 };

			if (RightPawnCheck(p2))
			{
				at(rightPos)->SetLeftPassant(true);
			}
		}
	}

	Position otherKingPos = FindKing(OppositeColor(currPiece->GetColor()));

	if (!m_PGN.empty())
	{
		if (IsCheckMate(OppositeColor(currPiece->GetColor())))
		{
			m_PGN += "# ";
		}
		else if (IsCheck(otherKingPos, OppositeColor(currPiece->GetColor())))
		{
			m_PGN += "+ ";
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

	m_prevPositions = { };
	m_moves = { };
	m_PGN = { };
}

PositionList Board::GetMoves(Position p) const
{
	PiecesPtr currPiece = at(p);

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

	if (currPiece->Is(EPieceType::Pawn))
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
	auto initialPiece = at(p);

	PositionMatrix currMoves = initialPiece->AllMoves(p);

	PositionList newList;

	for (int i = 0; i < currMoves.size(); i++)
	{
		for (int j = 0; j < currMoves[i].size(); j++)
		{
			auto currMove = currMoves[i][j];

			if (auto currPiece = at(currMove))
			{
				if (currPiece->GetColor() != initialPiece->GetColor())
				{
					if (!initialPiece->Is(EPieceType::Pawn) || (PawnGoesDiagonally(p, currMove)))
					{
						newList.push_back(currMove);
					}
				}

				break;
			}

			if (initialPiece->Is(EPieceType::Pawn) && std::abs(p.x - currMove.x) == 2)
			{
				if (at(IntermediatePosition(p)))
				{
					break;
				}
			}

			if ((!initialPiece->Is(EPieceType::Pawn) || (!PawnGoesDiagonally(p, currMove))))
			{
				newList.push_back(currMove);
			}
		}
	}

	return newList;
}

PositionList Board::GetMovesCheck(Position p) const
{
	PiecesPtr currPiece = at(p);
	EColor currColor = currPiece->GetColor();

	PositionList newList;

	if (currPiece->Is(EPieceType::King))
	{
		newList = GetMovesNormal(p);

		for (int i = 0; i < newList.size(); i++)
		{
			if (IsCheck(newList[i], currColor) || IsSameWay(p, newList[i], currColor))
			{
				if (!currPiece->Is(EPieceType::Pawn) || PawnGoesDiagonally(p, newList[i]))
				{
					newList.erase(newList.begin() + i);
					i--;
				}
			}
		}
	}
	else
	{
		Position kingPos = FindKing(currColor);
		PiecesPtr king = at(kingPos);

		Position checkPos = FindCheck(kingPos, currColor);
		PiecesPtr checkPiece = at(checkPos);

		PositionList checkPattern = checkPiece->DeterminePattern(checkPos, kingPos);

		PositionList currMoves = GetMovesNormal(p);

		for (const auto& move : currMoves)
		{
			if (std::find(checkPattern.begin(), checkPattern.end(), move) != checkPattern.end())
				newList.push_back(move);
		}

		if (std::find(currMoves.begin(), currMoves.end(), checkPos) != currMoves.end())
			newList.push_back(checkPos);
	}

	return newList;
}

PositionList Board::GetMovesPinned(Position p) const
{
	EColor currColor = at(p)->GetColor();

	PositionList newList;

	Position kingPos = FindKing(currColor);
	Position checkPos = FindCheck(p, currColor);

	PositionList checkPattern = at(checkPos)->DeterminePattern(checkPos, p);

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

String Board::GetFEN() const
{
	String FEN;	int ws = 0;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (!m_board[i][j])
			{
				ws++;
			}
			else
			{
				if (ws)
				{
					FEN.push_back('0' + ws);

					ws = 0;
				}

				FEN.push_back(m_board[i][j]->ConvertPiece());
			}
		}

		if (ws)
		{
			FEN.push_back('0' + ws);

			ws = 0;
		}

		if (i != 7)
		{
			FEN.push_back('/');
		}
	}

	return FEN + ' ';
}

String Board::GenerateInitial(EPieceType pieceType)
{
	String last;

	switch (pieceType)
	{
	case EPieceType::Rook:
	{
		last += "=R";
		break;
	}
	case EPieceType::Knight:
	{
		last += "=N";
		break;
	}
	case EPieceType::Bishop:
	{
		last += "=B";
		break;
	}
	case EPieceType::Queen:
	{
		last += "=Q";
		break;
	}
	default:
		throw PromoteException("Can't promote!\n");
	}

	return last;
}

void Board::LoadFEN(const String& string)
{
	Board initialBord(*this);
	Reset();
	int line = 0, col = 0;
	try
	{

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

			string[i] == '/' ? line++, col = 0 : col++;
		}
	}
	catch (ChessException exc)
	{
		throw FENException("Can't save properly!");
	}
}

void Board::ParsePGN(StringVector Moves)
{
	Board initialBoard(*this);
	Reset();

	int nrMove = 1;
	for (int i = 0; i < Moves.size(); i++)
	{
		String moveString = Moves[i];
		EPieceType type, promoteType;
		EColor color = nrMove % 2 == 0 ? EColor::Black : EColor::White;

		if (moveString == "O-O-O")
		{
			try
			{
				if (color == EColor::Black)
				{
					Move({ 0,4 }, { 0,0 });
				}
				else
				{
					Move({ 7,4 }, { 7,0 });
				}
			}
			catch (ChessException exc)
			{
				Reset();
				(*this) = initialBoard;
				throw PGNException("Can't load PGN properly!");
			}

			nrMove++;
			continue;
		}
		else if (moveString == "O-O")
		{
			try
			{
				if (color == EColor::Black)
				{
					Move({ 0,4 }, { 0,7 });
				}
				else
				{
					Move({ 7,4 }, { 7,7 });
				}
			}
			catch (ChessException exc)
			{
				Reset();
				(*this) = initialBoard;
				throw PGNException("Can't load PGN properly!");
			}

			nrMove++;
			continue;
		}

		if (isupper(moveString[0]))
		{
			type = GetPieceType(moveString[0]);
			moveString.erase(moveString.begin());
		}
		else
		{
			type = EPieceType::Pawn;
		}

		bool toPromote = false;

		if (strchr("RNBQK", moveString.back()))
		{
			promoteType = GetPieceType(moveString.back());
			toPromote = true;
			moveString.pop_back();
			moveString.pop_back();
		}

		int toX, toY, fromX = -1, fromY = -1;

		if (moveString.size() == 4)
		{
			fromX = 8 - (moveString[1] - '0');
			fromY = moveString[0] - 'a';

			toX = 8 - (moveString[3] - '0');
			toY = moveString[2] - 'a';
		}
		else if (moveString.size() == 3)
		{
			if (isdigit(moveString[0]))
			{
				fromX = 8 - (moveString[0] - '0');
			}
			else
			{
				fromY = moveString[0] - 'a';
			}

			toX = 8 - (moveString[2] - '0');
			toY = moveString[1] - 'a';
		}
		else if (moveString.size() == 2)
		{
			toX = 8 - (moveString[1] - '0');
			toY = moveString[0] - 'a';
		}

		Position prevPos(fromX, fromY);
		Position nextPos(toX, toY);

		try
		{
			prevPos = FindPrevPos(nextPos, type, color, prevPos);
		}
		catch (ChessException exc)
		{
			throw PGNException("Can't load PGN properly!");
		}

		try
		{
			Move(prevPos, nextPos);
		}
		catch (ChessException exc)
		{
			Reset();
			(*this) = initialBoard;
			throw PGNException("Can't load PGN properly!");
		}

		if (toPromote == true)
		{
			PromoteTo(promoteType, color);
		}

		nrMove++;
	}
}

String Board::ConvertMove(Position p1, Position p2) const
{
	String convertedMove;

	if (IsCastle(p1, p2))
	{
		if (p1.y > p2.y)
		{
			convertedMove += "O-O-O";
		}
		else
		{
			convertedMove += "O-O";
		}
	}
	else
	{
		switch (at(p1)->GetType())
		{
		case EPieceType::Rook:
			convertedMove.push_back('R');
			break;
		case EPieceType::Knight:
			convertedMove.push_back('N');
			break;
		case EPieceType::Bishop:
			convertedMove.push_back('B');
			break;
		case EPieceType::Queen:
			convertedMove.push_back('Q');
			break;
		case EPieceType::King:
			convertedMove.push_back('K');
			break;
		default:
			break;
		}

		if (FindOnSameLine(p1, p2))
		{
			convertedMove.push_back('a' + p1.y);
		}

		if (FindOnSameColumn(p1, p2) && !at(p1)->Is(EPieceType::Pawn))
		{
			convertedMove.push_back('1' + p1.x);
		}

		if (at(p2))
		{
			if (at(p1)->Is(EPieceType::Pawn))
			{
				convertedMove.push_back('a' + p1.y);
			}

			convertedMove.push_back('x');
		}

		convertedMove.push_back('a' + p2.y);
		convertedMove.push_back('0' + (8 - p2.x));
	}

	return convertedMove;
}

bool Board::PawnGoesDiagonally(Position p1, Position p2) const
{
	int x1 = p1.x,
		y1 = p1.y,
		x2 = p2.x,
		y2 = p2.y;

	PiecesPtr currPiece = at(p1);

	return (std::abs(y2 - y1) == 1 && ((currPiece->GetColor() == EColor::White && x2 - x1 == -1) || (currPiece->GetColor() == EColor::Black && x2 - x1 == 1)));
}

bool Board::GoesTwoForward(int x1, int x2) const
{
	return std::abs(x1 - x2) == 2;
}

bool Board::CanMoveTwoForward(Position p1, Position p2) const
{
	return ((at(IntermediatePosition(p1))) && GoesTwoForward(p1.x, p2.x));
}

bool Board::LeftPawnCheck(Position p) const
{
	PiecesPtr otherPiece = m_board[p.x][p.y - 1];
	PiecesPtr currPiece = at(p);

	return (p.y - 1 >= 0 && otherPiece && otherPiece->Is(EPieceType::Pawn) && otherPiece->GetColor() != currPiece->GetColor());
}

bool Board::RightPawnCheck(Position p) const
{
	PiecesPtr otherPiece = m_board[p.x][p.y + 1];
	PiecesPtr currPiece = at(p);

	return (p.y + 1 <= 7 && otherPiece && otherPiece->Is(EPieceType::Pawn) && otherPiece->GetColor() != currPiece->GetColor());
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
					if (currPiece->Is(EPieceType::Pawn) && !at(*it))
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
	Position toKill = { -1, -1 };

	for (int i = 0; i < 8; i++)
	{
		if (toKill != Position(-1, -1))
		{
			break;
		}

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

	EColor notColor = at(toKill)->GetColor();

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			PiecesPtr currPiece = m_board[i][j];

			if (currPiece && (currPiece->GetColor() != at(toKill)->GetColor()))
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
					firstBishop = at({ i, j }).get();
				}
				else
				{
					secondBishop = at({ i, j }).get();
				}
			}
		}
	}

	return (firstBishop && secondBishop && firstBishop->GetColor() == secondBishop->GetColor());
}

bool Board::PawnException(Position p1, Position p2) const
{
	PiecesPtr currPiece = at(p1);
	PiecesPtr nextPiece = at(p2);

	return (currPiece->Is(EPieceType::Pawn) && (!PawnGoesDiagonally(p1, p2) || (PawnGoesDiagonally(p1, p2) && (!nextPiece))));
}

bool Board::IsCastle(Position p1, Position p2) const
{
	PiecesPtr initialPiece = at(p1);
	PiecesPtr finalPiece = at(p2);

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

	if ((p1.x != 0 && p1.x != 7) || (p2.x != 0 && p2.x != 7))
	{
		return false;
	}

	if (p1.x != p2.x)
	{
		return false;
	}

	if (p1.y - p2.y != 4 && p2.y - p1.y != 3)
	{
		return false;
	}

	PositionList castleTiles = finalPiece->DeterminePattern(p2, p1);

	for (int i = 0; i < castleTiles.size(); i++)
	{
		if (IsCheck(castleTiles[i], m_board[p1.x][p1.y]->GetColor()))
		{
			return false;
		}
	}

	return true;
}

bool Board::IsEnPassant(Position p1, Position p2) const
{
	PiecesPtr currPiece = at(p1);
	PiecesPtr nextPiece = at(p2);

	if (!currPiece || !currPiece->Is(EPieceType::Pawn) || nextPiece)
	{
		return false;
	}

	if (!currPiece->GetLeftPassant() && !currPiece->GetRightPassant())
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
	PiecesPtr initialPiece = at(p);

	if (!initialPiece)
	{
		return {};
	}

	PositionMatrix m = initialPiece->AllMoves(p);

	for (int i = 0; i < m.size(); i++)
	{
		for (int j = 0; j < m[i].size(); j++)
		{
			PiecesPtr currPiece = at(m[i][j]);

			if (!currPiece)
			{
				continue;
			}

			if (currPiece->GetColor() != initialPiece->GetColor())
			{
				break;
			}

			newList.push_back(m[i][j]);
		}
	}

	return newList;
}

PositionList Board::GetPassantMoves(Position p) const
{
	PositionList enPassantMoves;

	auto leftPos = { p.x, p.y - 1 };

	if (at(p)->GetLeftPassant() == true)
	{
		if (LeftPawnCheck(p))
		{
			if (at(p)->GetColor() == EColor::White)
			{
				enPassantMoves.push_back({ p.x - 1, p.y - 1 });
			}
			else
			{
				enPassantMoves.push_back({ p.x + 1, p.y - 1 });
			}
		}
	}
	else if (at(p)->GetRightPassant() == true)
	{
		if (RightPawnCheck(p))
		{
			if (at(p)->GetColor() == EColor::White)
			{
				enPassantMoves.push_back({ p.x - 1, p.y + 1 });
			}
			else
			{
				enPassantMoves.push_back({ p.x + 1, p.y + 1 });
			}
		}
	}

	return enPassantMoves;
}

int Board::Find(PieceVector v, EPieceType type) const
{
	auto IsType = [type](PiecesPtr& p) {
		return p->GetType() == type;
	};

	return std::count_if(v.begin(), v.end(), IsType);
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
	PiecesPtr currPiece = at(p1);
	PiecesPtr nextPiece = at(p2);

	int newSecondKing, newSecondRook;

	newSecondKing = p1.y > p2.y ? p2.y + 2 : p2.y - 1;
	newSecondRook = p1.y > p2.y ? p1.y - 1 : p1.y + 1;

	m_board[p2.x][newSecondKing] = currPiece;
	m_board[p2.x][newSecondRook] = nextPiece;

	currPiece->SetHasMoved(true);
	nextPiece->SetHasMoved(true);

	at(p1) = {};
	at(p2) = {};

	if (IsCheck({ p2.x, newSecondKing }, m_board[p2.x][newSecondKing]->GetColor()))
	{
		m_board[p2.x][newSecondKing] = {};
		m_board[p2.x][newSecondRook] = {};

		at(p1) = currPiece;
		at(p2) = nextPiece;
	}
}

void Board::UpdatePrevPositions()
{
	m_prevPositions.push_back(GetCurrentPosition());
}

void Board::EnPassant(Position p1, Position p2)
{
	if (IsRightPassantPossible(p1, p2) || IsLeftPassantPossible(p1, p2))
	{
		Position otherPawnPos;

		otherPawnPos = at(p1)->Is(EColor::White) ? Position(p2.x + 1, p2.y) : Position(p2.x - 1, p2.y);

		at(p2) = at(p1);
		at(otherPawnPos) = {};
		at(p1) = {};

		at(p2)->SetLeftPassant(false);
		at(p2)->SetRightPassant(false);
	}
	else
		throw MoveException("The piece can't do this move!");
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

bool Board::IsLeftPassantPossible(Position p1, Position p2) const
{
	return p2.y < p1.y&& at(p1)->GetLeftPassant();
}

bool Board::IsRightPassantPossible(Position p1, Position p2) const
{
	return p2.y > p1.y && at(p1)->GetRightPassant();
}

Position Board::IntermediatePosition(Position p) const
{
	PiecesPtr currPiece = at(p);
	Position intermediate = { -1, -1 };

	if (currPiece->Is(EPieceType::Pawn))
	{
		Position pair1 = { 5, p.y };
		Position pair2 = { 2, p.y };

		intermediate = currPiece->GetColor() == EColor::White ? pair1 : pair2;
	}

	return intermediate;
}

bool Board::FindOnSameLine(Position p1, Position p2) const
{
	int i = p1.x;
	for (int j = 0; j < 8; j++)
	{
		PiecesPtr currPiece = m_board[i][j];

		if (Position(i, j) != p1 && currPiece && currPiece->SameColor(at(p1)) && currPiece->GetType() == at(p1)->GetType())
		{
			PositionList currMoves = GetMoves({ i, j });

			for (int k = 0; k < currMoves.size(); k++)
			{
				if (currMoves[k] == p2)
				{
					return true;
				}
			}
		}
	}

	return false;
}

bool Board::FindOnSameColumn(Position p1, Position p2) const
{
	int j = p1.y;
	for (int i = 0; i < 8; i++)
	{
		PiecesPtr currPiece = m_board[i][j];

		if (Position(i, j) != p1 && currPiece && currPiece->SameColor(at(p1)) && currPiece->GetType() == at(p1)->GetType())
		{
			PositionList currMoves = GetMoves({ i, j });

			for (int k = 0; k < currMoves.size(); k++)
			{
				if (currMoves[k] == p2)
				{
					return true;
				}
			}
		}
	}

	return false;
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
	default:
		throw FENException("");
	}

	return {};
}

Position Board::FindPrevPos(Position nextPos, EPieceType type, EColor color, Position prevPos) const
{
	Position toReturnPos = { -1, -1 };

	if (prevPos.x != -1 && prevPos.y != -1)
	{
		return prevPos;
	}
	else if (prevPos.x != -1)
	{
		toReturnPos.x = prevPos.x;
	}
	else if (prevPos.y != -1)
	{
		toReturnPos.y = prevPos.y;
	}

	for (int i = 0; i < 8; i++)
	{
		Position currPos; PiecesPtr currPiece;

		if (toReturnPos == Position(-1, -1))
		{
			for (int j = 0; j < 8; j++)
			{
				if (IsPrevPos(Position(i, j), nextPos, type, color))
				{
					return { i,j };
				}
			}

			continue;
		}
		else if (toReturnPos.x != -1)
		{
			currPos = { prevPos.x, i };
		}
		else if (toReturnPos.y != -1)
		{
			currPos = { i, prevPos.y };
		}

		if (IsPrevPos(currPos, nextPos, type, color))
		{
			return currPos;
		}
	}

	return toReturnPos;
}

ChessBoard Board::ConvertBitset(int bitsetNr) const
{
	if (bitsetNr > m_prevPositions.size())
	{
		throw ChessException("Bitset not available!");
	}

	ChessBoard chessBoard;

	Bitset currBitset = m_prevPositions[bitsetNr];

	for (int i = 0; i < 256; i += 4)
	{
		int line = (i / 4) / 8;
		int column = (i / 4) % 8;

		int value = currBitset[i + 3] * 4 + currBitset[i + 2] * 2 + currBitset[i + 1];

		if (value == 7)
		{
			chessBoard[line][column] = {};
		}
		else
		{
			EPieceType type = static_cast<EPieceType>(value);
			EColor color = currBitset[i] == 0 ? EColor::White : EColor::Black;

			chessBoard[line][column] = Piece::Produce(type, color);
		}
	}

	return chessBoard;
}

bool Board::IsPrevPos(Position currPos, Position nextPos, EPieceType type, EColor color) const
{
	PiecesPtr piece;

	try
	{
		piece = at(currPos);
	}
	catch (...)
	{
		throw PGNException("");
	}

	if (piece && piece->Is(type) && piece->GetColor() == color)
	{
		PositionList moves = GetMoves(currPos);

		for (const auto& currMove : moves)
		{
			if (currMove == nextPos)
			{
				return true;
			}
		}
	}

	return false;
}