#include <iostream>
#include "Board.h"

Board::Board()
{
	for (int i = 2; i < 6; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			m_board[i][j] = {};
		}
	}

	m_board[0][0] = std::make_shared<Rook>(EColor::Black);
	m_board[0][1] = std::make_shared<Knight>(EColor::Black);
	m_board[0][2] = std::make_shared<Bishop>(EColor::Black);
	m_board[0][3] = std::make_shared<Queen>(EColor::Black);
	m_board[0][4] = std::make_shared<King>(EColor::Black);
	m_board[0][5] = std::make_shared<Bishop>(EColor::Black);
	m_board[0][6] = std::make_shared<Knight>(EColor::Black);
	m_board[0][7] = std::make_shared<Rook>(EColor::Black);

	m_board[7][0] = std::make_shared<Rook>(EColor::White);
	m_board[7][1] = std::make_shared<Knight>(EColor::White);
	m_board[7][2] = std::make_shared<Bishop>(EColor::White);
	m_board[7][3] = std::make_shared<Queen>(EColor::White);
	m_board[7][4] = std::make_shared<King>(EColor::White);
	m_board[7][5] = std::make_shared<Bishop>(EColor::White);
	m_board[7][6] = std::make_shared<Knight>(EColor::White);
	m_board[7][7] = std::make_shared<Rook>(EColor::White);

	for (int i = 0; i < 8; i++)
	{
		m_board[1][i] = std::make_shared<Pawn>(EColor::Black);
		m_board[6][i] = std::make_shared<Pawn>(EColor::White);
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

void Board::FreePosition(Position p)
{
	m_board[p.first][p.second] = {};
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
				if (currPiece->GetColor() != initialPiece->GetColor())
					newList.push_back({ x , y });
				break;
			}

			newList.push_back({ x , y });
		}
	}

	return newList;
}

bool Board::IsCheck(Position p) const
{
	PositionList moves;

	for (int i = 0; i < m_board.size(); i++)
	{
		for (int j = 0; j < m_board[i].size(); j++)
		{
			if ((!m_board[i][j]) || (m_board[i][j]->GetColor() == m_board[p.first][p.second]->GetColor()))
			{
				break;
			}
			else
			{
				moves = GetMoves({ i, j });
			}

			for (int k = 0; k < moves.size(); k ++)
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

bool Board::IsCheckMate(Position p) const
{
	PositionList currMoves = GetMoves(p);

	if (!IsCheck(p))
		return false;

	for (int i = 0; i < currMoves.size(); i++)
	{
		if (!IsCheck(currMoves[i]))
			return false;
	}

	return true;
}

bool Board::PositionExists(Position p) const
{
	return (p.first >= 0 && p.first < 8) && (p.second >= 0 && p.second < 8);
}
