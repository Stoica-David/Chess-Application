#include "Board.h"

Board::Board()
{
	for (int i = 2; i < 6; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			this->gameboard[i][j] = std::make_shared<Piece>();
		}
	}

	this->gameboard[0][0] = std::make_shared<Rook>(EColor::white);
	this->gameboard[0][1] = std::make_shared<Knight>(EColor::white);
	this->gameboard[0][2] = std::make_shared<Bishop>(EColor::white);
	this->gameboard[0][3] = std::make_shared<King>(EColor::white);
	this->gameboard[0][4] = std::make_shared<Queen>(EColor::white);
	this->gameboard[0][5] = std::make_shared<Bishop>(EColor::white);
	this->gameboard[0][6] = std::make_shared<Knight>(EColor::white);
	this->gameboard[0][7] = std::make_shared<Rook>(EColor::white);

	this->gameboard[7][0] = std::make_shared<Rook>(EColor::black);
	this->gameboard[7][1] = std::make_shared<Knight>(EColor::black);
	this->gameboard[7][2] = std::make_shared<Bishop>(EColor::black);
	this->gameboard[7][3] = std::make_shared<King>(EColor::black);
	this->gameboard[7][4] = std::make_shared<Queen>(EColor::black);
	this->gameboard[7][5] = std::make_shared<Bishop>(EColor::black);
	this->gameboard[7][6] = std::make_shared<Knight>(EColor::black);
	this->gameboard[7][7] = std::make_shared<Rook>(EColor::black);

	for (int i = 0; i < 8; i++)
	{
		this->gameboard[1][i] = std::make_shared<Pawn>();
		this->gameboard[6][i] = std::make_shared<Pawn>();
	}
}

std::array<std::array<PiecesPtr, 8>, 8> Board::GetGameboard()
{
	return this->gameboard;
}

