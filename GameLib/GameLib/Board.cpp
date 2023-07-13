#include "Board.h"

Board::Board()
{
	for (int i = 2; i < 6; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			this->m_gameboard[i][j] = {};
		}
	}

	this->m_gameboard[0][0] = std::make_shared<Rook>(EColor::White);
	this->m_gameboard[0][1] = std::make_shared<Knight>(EColor::White);
	this->m_gameboard[0][2] = std::make_shared<Bishop>(EColor::White);
	this->m_gameboard[0][3] = std::make_shared<King>(EColor::White);
	this->m_gameboard[0][4] = std::make_shared<Queen>(EColor::White);
	this->m_gameboard[0][5] = std::make_shared<Bishop>(EColor::White);
	this->m_gameboard[0][6] = std::make_shared<Knight>(EColor::White);
	this->m_gameboard[0][7] = std::make_shared<Rook>(EColor::White);

	this->m_gameboard[7][0] = std::make_shared<Rook>(EColor::Black);
	this->m_gameboard[7][1] = std::make_shared<Knight>(EColor::Black);
	this->m_gameboard[7][2] = std::make_shared<Bishop>(EColor::Black);
	this->m_gameboard[7][3] = std::make_shared<King>(EColor::Black);
	this->m_gameboard[7][4] = std::make_shared<Queen>(EColor::Black);
	this->m_gameboard[7][5] = std::make_shared<Bishop>(EColor::Black);
	this->m_gameboard[7][6] = std::make_shared<Knight>(EColor::Black);
	this->m_gameboard[7][7] = std::make_shared<Rook>(EColor::Black);

	for (int i = 0; i < 8; i++)
	{
		this->m_gameboard[1][i] = std::make_shared<Pawn>(EColor::White);
		this->m_gameboard[6][i] = std::make_shared<Pawn>(EColor::Black);
	}
}

std::array<std::array<PiecesPtr, 8>, 8> Board::GetGameboard() const
{
	return this->m_gameboard;
}

bool Board::VerifyTheWay(int x_curr, int y_curr)
{
	return false;
}


bool Board::PositionExists(int x, int y)
{
	if ((x > -1 && x < 8) && (y > -1 && y < 8))
		return true;
	return false;
}
