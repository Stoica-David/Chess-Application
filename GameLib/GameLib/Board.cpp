#include "Board.h"
#include "PieceInfo.h"
#include "BoardExceptions.h"

#include <algorithm>

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
	: m_board(newBoard.m_board)
	, m_moves(newBoard.m_moves)
	, m_PGN(newBoard.m_PGN)
	, m_prevPositions(newBoard.m_prevPositions)
	, m_nrMove(newBoard.m_nrMove)
{

}

void Board::Set(const ChessBoard& board)
{
	m_board = board;
}

void Board::Reset()
{
	for ( auto& row : m_board )
	{
		row.fill( {} );
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

	for (int i = 0; i < 8; i++)
	{
		m_board[0][i] = Piece::Produce(TYPES[i], EColor::Black);
		m_board[1][i] = Piece::Produce( EPieceType::Pawn, EColor::Black );
		m_board[6][i] = Piece::Produce( EPieceType::Pawn, EColor::White );
		m_board[7][i] = Piece::Produce(TYPES[i], EColor::White);
	}

	m_prevPositions = { };
	m_moves = { };
	m_PGN = { };
}

IPieceInfoPtr Board::GetPieceInfo(Position p) const
{
	if (auto piece = at(p))
	{
		return std::make_shared<PieceInfo>(piece->GetType(), piece->GetColor());
	}

	return {};
}

String Board::GetCurrPGN() const
{
	return m_PGN;
}

BitMatrix Board::GetPrevPositions() const
{
	return m_prevPositions;
}

MoveVector Board::GetHistory() const
{
	return m_moves;
}

PiecesPtr& Board::at(Position p)
{
	return m_board.at(p.x).at(p.y);
}

const PiecesPtr& Board::at(Position p) const
{
	return m_board.at(p.x).at(p.y);
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

bool Board::IsCheckMate(EColor color) const
{
	Position kingPos = FindKing(color);

	try
	{
		PiecesPtr King = at(kingPos);

		if ( !King || !IsCheck( kingPos, color ) )
		{
			return false;
		}
	}
	catch (...)
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

bool Board::IsPinned(Position p) const
{
	EColor currColor = at(p)->GetColor();

	Position checkPos = FindCheck(p, currColor);

	if (!checkPos.IsValid())
	{
		return false;
	}

	Position kingPos = FindKing(currColor);
	PositionList behindCurr = at(checkPos)->DeterminePattern(p, kingPos);

	if (std::find(behindCurr.begin(), behindCurr.end(), kingPos) == behindCurr.end())
	{
		return false;
	}

	PositionList checkPattern = at(checkPos)->DeterminePattern(checkPos, kingPos);

	bool kingFound = std::find(checkPattern.begin(), checkPattern.end(), kingPos) != checkPattern.end() ? true : false, 
		 currFound = std::find(checkPattern.begin(), checkPattern.end(), p) != checkPattern.end() ? true : false;

	return kingFound && currFound;
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

bool Board::IsOver(EColor color) const
{
	return (IsCheckMate(color));
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

bool Board::IsEnPassant(Position p1, Position p2) const
{
	PiecesPtr currPiece = at(p1);
	PiecesPtr nextPiece = at(p2);

	if (!currPiece || !currPiece->Is(EPieceType::Pawn) || nextPiece)
	{
		return false;
	}

	if ((!currPiece->GetLeftPassant() && !currPiece->GetRightPassant()) || !PawnGoesDiagonally(p1, p2))
	{
		return false;
	}

	return true;
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

			if (std::find(currMoves.begin(), currMoves.end(), p2) != currMoves.end())
			{
				return true;
			}
		}
	}

	return false;
}

bool Board::PawnException(Position p1, Position p2) const
{
	PiecesPtr currPiece = at(p1);
	PiecesPtr nextPiece = at(p2);

	return (currPiece->Is(EPieceType::Pawn) && (!PawnGoesDiagonally(p1, p2) || (PawnGoesDiagonally(p1, p2) && (!nextPiece))));
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
	return Position::INVALID;
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

	if (!currPiece->IsMoveRegular(p1, p2) && !IsCastle1(p1, p2) && !IsCastle2(p1, p2))
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

	bool currPiecePrevMoved = false;

	if (currPiece)
	{ 
		currPiecePrevMoved = currPiece->GetHasMoved();
	}

	if (IsCastle1(p1, p2))
	{
		Castle1(p1, p2);
	}
	else if (IsCastle2(p1, p2))
	{
		Castle2(p1, p2);
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

void Board::PromoteTo(EPieceType pieceType, EColor color)
{
	int row = ( color == EColor::White ? 0 : 7 );

	for (int i = 0; i < 8; i++)
	{
		if (m_board[row][i] && m_board[row][i]->Is(EPieceType::Pawn))
		{
			at( { row, i } ) = Piece::Produce( pieceType, color );
			return;
		}
	}

	throw PromoteException( "Can't promote!\n" );
}

PositionList Board::GetMoves(Position p) const
{
	PiecesPtr currPiece = at(p);

	PositionList newList;

	if (currPiece)
	{
		if (IsCheck(FindKing(currPiece->GetColor()), currPiece->GetColor()))
		{
			newList = GetMovesCheck(p);
		}
		else if (IsPinned(p))
		{
			newList = GetMovesPinned(p);
		}
		else if (at(p)->GetType() == EPieceType::King)
		{
			newList = GetMovesKing(p);
		}
		else
		{
			newList = GetMovesNormal(p);
		}

		if (currPiece->Is(EPieceType::Pawn))
		{
			PositionList enPassantMoves = GetPassantMoves(p);

			for (const auto& position : enPassantMoves )
			{
				newList.push_back(position);
			}
		}
	}

	return newList;
}

PositionList Board::GetMovesCheck(Position p) const
{
	PiecesPtr currPiece = at(p);

	return currPiece->Is(EPieceType::King) ? GetMovesCheckKing(p) : GetMovesCheckOther(p);
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
			PGNCastleCase1(initialBoard, color);

			nrMove++;
			continue;
		}
		else if (moveString == "O-O")
		{
			PGNCastleCase2(initialBoard, color);

			nrMove++;
			continue;
		}

		type = isupper(moveString[0]) ? moveString.erase(moveString.begin()), GetPieceType(moveString[0]) : EPieceType::Pawn;

		bool toPromote = false;

		if (strchr("RNBQK", moveString.back()))
		{
			promoteType = GetPieceType(moveString.back());
			toPromote = true;
			moveString.pop_back();
			moveString.pop_back();
		}

		int toX = -1, toY = -1, fromX = -1, fromY = -1;

		if (moveString.size() == 4)
		{
			fromX = 8 - (moveString[1] - '0');
			fromY = moveString[0] - 'a';

			toX = 8 - (moveString[3] - '0');
			toY = moveString[2] - 'a';
		}
		else if (moveString.size() == 3)
		{
			isdigit(moveString[0]) ? fromX = 8 - (moveString[0] - '0') : fromY = moveString[0] - 'a';

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

String Board::GenerateInitial(EPieceType pieceType)
{
	switch (pieceType)
	{
	case EPieceType::Rook:
	{
		return "=R";
	}
	case EPieceType::Knight:
	{
		return "=N";
	}
	case EPieceType::Bishop:
	{
		return "=B";
	}
	case EPieceType::Queen:
	{
		return "=Q";
	}
	default:
		throw PromoteException("Can't promote!\n");
	}
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

Position Board::IntermediatePosition(Position p) const
{
	PiecesPtr currPiece = at(p);
	Position intermediate = Position::INVALID;

	if (currPiece->Is(EPieceType::Pawn))
	{
		Position pair1 = { 5, p.y };
		Position pair2 = { 2, p.y };

		intermediate = currPiece->GetColor() == EColor::White ? pair1 : pair2;
	}

	return intermediate;
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

bool Board::SameBishop() const
{
	PiecesPtr firstBishop;
	PiecesPtr secondBishop;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			PiecesPtr currPiece = m_board[i][j];

			if (currPiece && currPiece->Is(EPieceType::Bishop))
			{
				!firstBishop ? firstBishop = at({ i, j }) : secondBishop = at({ i, j });
			}
		}
	}

	return (firstBishop && secondBishop && firstBishop->GetColor() == secondBishop->GetColor());
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
	Position toKill = Position::INVALID;

	for (int i = 0; i < 8 && !toKill.IsValid(); i++)
	{
		for (int j = 0; j < 8 && !toKill.IsValid(); j++)
		{
			PiecesPtr currPiece = m_board[i][j];

			if (currPiece && (currPiece->GetColor() != color))
			{
				PositionList moves = GetMovesNormal({ i, j });

				if ( std::find( moves.begin(), moves.end(), p ) != moves.end())
				{
					toKill = { i, j };
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
					if (currPiece->GetType() == EPieceType::King && (IsDefended(toKill, notColor) || !PawnGoesDiagonally({ i,j }, moves[0])))
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

bool Board::FindOnSameLine(Position p1, Position p2) const
{
	int i = p1.x;
	for (int j = 0; j < 8; j++)
	{
		PiecesPtr currPiece = m_board[i][j];

		if (Position(i, j) != p1 && currPiece && currPiece->SameColor(at(p1)) && currPiece->GetType() == at(p1)->GetType())
		{
			PositionList currMoves = GetMoves({ i, j });

			if (std::find(currMoves.begin(), currMoves.end(), p2) != currMoves.end())
			{
				return true;
			}
		}
	}

	return false;
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

int Board::Find(PieceVector v, EPieceType type) const
{
	auto IsType = [type](PiecesPtr& p) {
		return p->GetType() == type;
	};

	return std::count_if(v.begin(), v.end(), IsType);
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

void Board::UpdatePrevPositions()
{
	m_prevPositions.push_back(GetCurrentPosition());
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

bool Board::IsCastle1(Position p1, Position p2) const
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

	if (p1.x != p2.x || (p1.y - p2.y != 4 && p2.y - p1.y != 3))
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

bool Board::IsCastle2(Position p1, Position p2) const
{
	PiecesPtr initialPiece = at(p1);
	PiecesPtr finalPiece = at(p2);

	Position rookPos1 = { p2.x, p2.y + 1 };
	Position rookPos2 = { p2.x, p2.y - 2 };

	if (!rookPos1.IsValid() && !rookPos2.IsValid())
	{
		return false;
	}

	PiecesPtr rook1;
	PiecesPtr rook2;

	if (rookPos1.IsValid())
		rook1 = at(rookPos1);

	if (rookPos2.IsValid())
		rook2 = at(rookPos2);

	if (!initialPiece || finalPiece || (!rook1 && !rook2))
	{
		return false;
	}

	if (!initialPiece->Is(EPieceType::King) || ((rook1 && !rook1->Is(EPieceType::Rook)) && (rook2 && !rook2->Is(EPieceType::Rook))))
	{
		return false;
	}

	if (initialPiece->GetHasMoved() || (rook1 && at(rookPos1)->GetHasMoved()) && rook2 && at(rookPos2)->GetHasMoved())
	{
		return false;
	}

	if ((rook1 && initialPiece->GetColor() != at(rookPos1)->GetColor()) && (rook2 && initialPiece->GetColor() != at(rookPos2)->GetColor()))
	{
		return false;
	}

	if ((p1.x != 0 && p1.x != 7) || (rookPos1.x != 0 && rookPos1.x != 7) || (rookPos2.x != 0 && rookPos2.x != 7))
	{
		return false;
	}

	if (p1.x != p2.x || (p1.y - p2.y != 2 && p2.y - p1.y != 2))
	{
		return false;
	}

	PositionList castleTiles = rook1 && rook1->Is(EPieceType::Rook) ? rook1->DeterminePattern(rookPos1, p1) : rook2->DeterminePattern(rookPos2, p1);

	for (int i = 0; i < castleTiles.size(); i++)
	{
		if (IsCheck(castleTiles[i], m_board[p1.x][p1.y]->GetColor()))
		{
			return false;
		}
	}

	return true;
}

bool Board::CastleVerifyWay(Position p1, Position p2) const
{
	if (IsCastle1(p1, p2))
	{
		Position nextPos = p1.y > p2.y ? Position(p2.x, p2.y + 2) : Position(p2.x, p2.y - 1);

		return VerifyTheWay(p1, nextPos);
	}

	return false;
}

void Board::Castle1(Position p1, Position p2)
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

void Board::Castle2(Position p1, Position p2)
{
	PiecesPtr currPiece = at(p1);
	PiecesPtr nextPiece;

	if (m_board[p2.x][p2.y + 1])
	{
		nextPiece = at({ p2.x, p2.y + 1 });
		at({ p2.x, p2.y + 1 }) = {};
	}
	else
	{
		nextPiece = at({ p2.x, p2.y - 2 });
		at({ p2.x, p2.y - 2 }) = {};
	}

	int newSecondKing, newSecondRook;

	newSecondKing = p2.y;
	newSecondRook = p1.y > p2.y ? p2.y + 1 : p2.y - 1;

	m_board[p2.x][newSecondKing] = currPiece;
	m_board[p2.x][newSecondRook] = nextPiece;

	currPiece->SetHasMoved(true);
	nextPiece->SetHasMoved(true);

	at(p1) = {};

	if (IsCheck({ p2.x, newSecondKing }, m_board[p2.x][newSecondKing]->GetColor()))
	{
		m_board[p2.x][newSecondKing] = {};
		m_board[p2.x][newSecondRook] = {};

		at(p1) = currPiece;
		at(p2) = nextPiece;

		currPiece->SetHasMoved(false);
		nextPiece->SetHasMoved(false);
	}
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

bool Board::IsLeftPassantPossible(Position p1, Position p2) const
{
	return p2.y < p1.y&& at(p1)->GetLeftPassant();
}

bool Board::IsRightPassantPossible(Position p1, Position p2) const
{
	return p2.y > p1.y && at(p1)->GetRightPassant();
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

PositionList Board::GetMovesKing(Position p) const
{
	PositionList kingMoves = GetMovesNormal(p);

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (!at(Position(i, j)) || at(p)->GetColor() == at(Position(i, j))->GetColor())
			{
				continue;
			}

			PositionList currMoves = GetMovesNormal({ i, j });

			for (const auto& currMove : currMoves)
			{
				for (int j = 0; j < kingMoves.size(); j++)
				{
					if (kingMoves[j] == currMove)
					{
						kingMoves.erase(kingMoves.begin() + j);
					}
				}
			}
		}
	}

	if (IsCastle1(p, Position(p.x, 0)) && VerifyTheWay(p, { p.x, 0 }))
	{
		kingMoves.push_back({ p.x, 0 });
		kingMoves.push_back({ p.x, 2 });
	}

	if (IsCastle1(p, Position(p.x, 7)) && VerifyTheWay(p, { p.x, 7 }))
	{
		kingMoves.push_back({ p.x, 7 });
		kingMoves.push_back({ p.x, 6 });
	}

	return kingMoves;
}

PositionList Board::GetPassantMoves(Position p) const
{
	PositionList enPassantMoves;

	auto leftPos = { p.x, p.y - 1 };

	if (at(p)->GetLeftPassant() == true)
	{
		if (LeftPawnCheck(p))
		{
			enPassantMoves.push_back(at(p)->GetColor() == EColor::White ? Position(p.x - 1, p.y - 1) : Position(p.x + 1, p.y - 1));
		}
	}
	else if (at(p)->GetRightPassant() == true)
	{
		if (RightPawnCheck(p))
		{
			enPassantMoves.push_back(at(p)->GetColor() == EColor::White ? Position(p.x - 1, p.y + 1) : Position(p.x + 1, p.y + 1));
		}
	}

	return enPassantMoves;
}

PositionList Board::GetMovesCheckKing(Position p) const
{
	PiecesPtr currPiece = at(p);

	PositionList newList = GetMovesNormal(p);

	for (int i = 0; i < newList.size(); i++)
	{
		if (IsCheck(newList[i], currPiece->GetColor()) || IsSameWay(p, newList[i], currPiece->GetColor()))
		{
			if (!currPiece->Is(EPieceType::Pawn) || PawnGoesDiagonally(p, newList[i]))
			{
				newList.erase(newList.begin() + i);
				i--;
			}
		}
	}

	return newList;
}

PositionList Board::GetMovesCheckOther(Position p) const
{
	Position kingPos = FindKing(at(p)->GetColor());
	PiecesPtr king = at(kingPos);

	Position checkPos = FindCheck(kingPos, at(p)->GetColor());
	PiecesPtr checkPiece = at(checkPos);

	PositionList checkPattern = checkPiece->DeterminePattern(checkPos, kingPos);
	PositionList currMoves = GetMovesNormal(p);
	PositionList newList;

	for (const auto& move : currMoves)
	{
		if (std::find(checkPattern.begin(), checkPattern.end(), move) != checkPattern.end())
		{
			newList.push_back(move);
		}
	}

	if (std::find(currMoves.begin(), currMoves.end(), checkPos) != currMoves.end())
	{
		newList.push_back(checkPos);
	}

	return newList;
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

		if (std::find(moves.begin(), moves.end(), nextPos) != moves.end())
		{
			return true;
		}
	}

	return false;
}

void Board::PGNCastleCase1(Board initialBoard, EColor color)
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
}

void Board::PGNCastleCase2(Board initialBoard, EColor color)
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

		if (toReturnPos == Position::INVALID)
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

String Board::ConvertMove(Position p1, Position p2) const
{
	String convertedMove;

	if (IsCastle1(p1, p2))
	{
		convertedMove += p1.y > p2.y ? "O-O-O" : "O-O";
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
		}

		if (FindOnSameLine(p1, p2) && !at(p1)->Is(EPieceType::Pawn))
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
}

EColor Board::OppositeColor(EColor color)
{
	return color == EColor::White ? EColor::Black : EColor::White;
}