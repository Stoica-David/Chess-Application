#include <iostream>
#include "Board.h"

Board::Board()
{
	for (int i = 2; i < 6; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			m_gameboard[i][j] = {};
		}
	}

	m_gameboard[0][0] = std::make_shared<Rook>(EColor::Black);
	m_gameboard[0][1] = std::make_shared<Knight>(EColor::Black);
	m_gameboard[0][2] = std::make_shared<Bishop>(EColor::Black);
	m_gameboard[0][3] = std::make_shared<Queen>(EColor::Black);
	m_gameboard[0][4] = std::make_shared<King>(EColor::Black);
	m_gameboard[0][5] = std::make_shared<Bishop>(EColor::Black);
	m_gameboard[0][6] = std::make_shared<Knight>(EColor::Black);
	m_gameboard[0][7] = std::make_shared<Rook>(EColor::Black);

	m_gameboard[7][0] = std::make_shared<Rook>(EColor::White);
	m_gameboard[7][1] = std::make_shared<Knight>(EColor::White);
	m_gameboard[7][2] = std::make_shared<Bishop>(EColor::White);
	m_gameboard[7][3] = std::make_shared<Queen>(EColor::White);
	m_gameboard[7][4] = std::make_shared<King>(EColor::White);
	m_gameboard[7][5] = std::make_shared<Bishop>(EColor::White);
	m_gameboard[7][6] = std::make_shared<Knight>(EColor::White);
	m_gameboard[7][7] = std::make_shared<Rook>(EColor::White);

	for (int i = 0; i < 8; i++)
	{
		m_gameboard[1][i] = std::make_shared<Pawn>(EColor::Black);
		m_gameboard[6][i] = std::make_shared<Pawn>(EColor::White);
	}
}

ChessBoard Board::GetGameboard() const
{
	return m_gameboard;
}

bool Board::VerifyTheWay(Position p1, Position p2) const
{
	PositionList piecePattern = m_gameboard[p1.first][p1.second]->DeterminePattern(p1, p2);

	for (const auto& currPos : piecePattern)
	{
		if (m_gameboard[currPos.first][currPos.second])
		{
			return false;
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
			if (m_gameboard[i][j])
			{
				switch (m_gameboard[i][j]->GetType())
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
				default:
					std::cout << "- ";
					break;

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
