#include "Board.h"

Board::Board()
{
	for (int i = 2; i < 6; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			this->m_gameboard[i][j] = std::make_shared<Piece>();
		}
	}

	this->m_gameboard[0][0] = std::make_shared<Rook>(EColor::white);
	this->m_gameboard[0][1] = std::make_shared<Knight>(EColor::white);
	this->m_gameboard[0][2] = std::make_shared<Bishop>(EColor::white);
	this->m_gameboard[0][3] = std::make_shared<King>(EColor::white);
	this->m_gameboard[0][4] = std::make_shared<Queen>(EColor::white);
	this->m_gameboard[0][5] = std::make_shared<Bishop>(EColor::white);
	this->m_gameboard[0][6] = std::make_shared<Knight>(EColor::white);
	this->m_gameboard[0][7] = std::make_shared<Rook>(EColor::white);

	this->m_gameboard[7][0] = std::make_shared<Rook>(EColor::black);
	this->m_gameboard[7][1] = std::make_shared<Knight>(EColor::black);
	this->m_gameboard[7][2] = std::make_shared<Bishop>(EColor::black);
	this->m_gameboard[7][3] = std::make_shared<King>(EColor::black);
	this->m_gameboard[7][4] = std::make_shared<Queen>(EColor::black);
	this->m_gameboard[7][5] = std::make_shared<Bishop>(EColor::black);
	this->m_gameboard[7][6] = std::make_shared<Knight>(EColor::black);
	this->m_gameboard[7][7] = std::make_shared<Rook>(EColor::black);

	for (int i = 0; i < 8; i++)
	{
		this->m_gameboard[1][i] = std::make_shared<Pawn>(EColor::white);
		this->m_gameboard[6][i] = std::make_shared<Pawn>(EColor::black);
	}
}

std::array<std::array<PiecesPtr, 8>, 8> Board::GetGameboard()
{
	return this->m_gameboard;
}


bool Board::PositionExists(int x, int y)
{
	if ((x > -1 && x < 8) && (y > -1 && y < 8))
		return true;
	return false;
}
