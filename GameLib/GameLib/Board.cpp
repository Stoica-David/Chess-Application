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

bool Board::VerifyTheWay(Position p1, Position p2) const
{
	PositionList piecePattern = m_board[p1.first][p1.second]->DeterminePattern(p1, p2);

	for (const auto& currPos : piecePattern)
	{
		if (m_board[currPos.first][currPos.second])
		{
			if ((currPos != p2) || (currPos == p2 && m_board[currPos.first][currPos.second]))
			{
				return false;
			}
		}
	}

	return true;
}

// Delete later
void Board::printBoard()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (m_board[i][j])
			{
				switch (m_board[i][j]->GetType())
				{
				case EPieceType::King:
				{
					std::cout << "K ";
					break;
				}
				case EPieceType::Rook:
				{
					std::cout << "R ";
					break;
				}
				case EPieceType::Knight:
				{
					std::cout << "Kn ";
					break;
				}

				case EPieceType::Bishop:
				{
					std::cout << "B ";
					break;
				}
				case EPieceType::Pawn:
				{
					std::cout << "P ";
					break;
				}
				case EPieceType::Queen:
				{
					std::cout << "Q ";
					break;
				}
				}
			}
			else
			{
				std::cout << "- ";
				break;
			}
			
		}
		std::cout << std::endl;
	}
}

bool Board::PositionExists(Position p) const
{
	return (p.first >= 0 && p.first < 8) && (p.second >= 0 && p.second < 8);
}
