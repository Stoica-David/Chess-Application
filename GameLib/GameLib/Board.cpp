#include "Board.h"

//#include "Rook.h"
//#include "Knight.h"
//#include "Bishop.h"
//#include "King.h"
//#include "Queen.h"
//#include "Pawn.h"
//
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
Board::Board(const PieceVector& v)
{
	for (auto curr : v)
	{
		int x = curr.first.first;
		int y = curr.first.second;
		PiecesPtr currPiece = curr.second;

		m_board[x][y] = currPiece;
	}
}

ChessBoard Board::GetGameboard() const
{
	return m_board;
}

void Board::SetGameboard(Position p, PiecesPtr newPiece)
{
	m_board[p.first][p.second] = newPiece;
}

bool Board::VerifyTheWay(Position p1, Position p2) const
{
	int x1 = p1.first, y1 = p1.second, x2 = p2.first, y2 = p2.second;

	PositionList piecePattern = m_board[x1][y1]->DeterminePattern(p1, p2);

	for (const auto& currPos : piecePattern)
	{
		if (m_board[currPos.first][currPos.second])
		{
			if ((currPos != p2) || (currPos == p2 && m_board[currPos.first][currPos.second] && m_board[x1][y1]->GetColor() == m_board[currPos.first][currPos.second]->GetColor()))
			{
				return false;
			}
		}
	}

	return true;
}

PositionList Board::GetMoves(Position p) const
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
				if (currPiece && (currPiece->GetColor() != initialPiece->GetColor()))
					newList.push_back({ x , y });
				break;
			}

			newList.push_back({ x , y });
		}
	}

	return newList;
}

bool Board::IsCheck(Position p, EColor color) const
{
	PositionList moves;

	for (int i = 0; i < m_board.size(); i++)
	{
		for (int j = 0; j < m_board[i].size(); j++)
		{
			if ((!m_board[i][j]) || (m_board[i][j]->GetColor() == color))
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

PiecesPtr Board::GetPiece(Position p) const
{
	return m_board[p.first][p.second];
}

//bool Board::IsCheckMate(Position p) const
//{
//	PositionList currMoves = GetMoves(p);
//
//	if (!IsCheck(p))
//		return false;
//
//	for (int i = 0; i < currMoves.size(); i++)
//	{
//		if (!IsCheck(currMoves[i]))
//			return false;
//	}
//
//	if (FindHelp(p))
//	{
//		return false;
//	}
//
//	if (!KillCheck(p))
//		return false;
//
//	return true;
//}

//bool Board::FindHelp(Position p)
//{
//	PositionList currMoves;
//	PositionList kingMoves = GetMoves(p);
//
//	int x = p.first, y = p.second;
//
//	for (int i = 0; i < 8; i++)
//	{
//		for (int j = 0; j < 8; j++)
//		{
//			if (m_board[i][j] && m_board[i][j]->GetColor() == m_board[x][y]->GetColor())
//				currMoves = GetMoves({ i, j });
//
//			for (int k = 0; k < currMoves.size(); k++)
//			{
//				int currX = currMoves[k].first;
//				int currY = currMoves[k].second;
//
//				m_board[currX][currY] = m_board[i][j];
//				m_board[i][j] = {};
//
//				if (!IsCheck(p))
//				{
//					m_board[i][j] = m_board[currX][currY];
//					m_board[currX][currY] = {};
//					return true;
//				}
//
//				m_board[i][j] = m_board[currX][currY];
//				m_board[currX][currY] = {};
//			}
//		}
//	}
//	return false;
//}
//
//bool Board::KillCheck(Position p)
//{
//	Position toKill;
//	int x = p.first, y = p.second;
//
//	for (int i = 0; i < 8; i++)
//	{
//		for (int j = 0; j < 8; j++)
//		{
//			if (m_board[i][j] && m_board[i][j]->GetColor() != m_board[x][y]->GetColor())
//			{
//				PositionList moves = GetMoves({ i, j });
//				for (int k = 0; k < moves.size(); k++)
//					if (moves[k] == p)
//						toKill = { i, j };
//			}
//		}
//	}
//	int killX = toKill.first, killY = toKill.second;
//
//	for (int i = 0; i < 8; i++)
//	{
//		for (int j = 0; j < 8; j++)
//		{
//			if (m_board[i][j] && m_board[i][j]->GetColor() != m_board[killX][killY]->GetColor())
//			{
//				PositionList moves = GetMoves({ i, j });
//				for (int k = 0; k < moves.size(); k++)
//					if (moves[k] == p)
//						return true;
//			}
//		}
//	}
//	return false;
//}

Position Board::FindKing(EColor color) const
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
			if (m_board[i][j] && m_board[i][j]->GetType() == EPieceType::King && m_board[i][j]->GetColor() == color)
				return { i, j };
	}
	return { -1, -1 };
}

bool Board::PositionExists(Position p) const
{
	return (p.first >= 0 && p.first < 8) && (p.second >= 0 && p.second < 8);
}
