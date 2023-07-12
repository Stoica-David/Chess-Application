#pragma once

#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "King.h"
#include "Queen.h"
#include "Pawn.h"
#include<array>

class Board
{
public:
	// Constructors
	Board();

	// Getters
	std::array<std::array<PiecesPtr, 8>, 8> GetGameboard() const;

	//Functions
	bool PositionExists(int x, int y);
	bool VerifyTheWay(int x_curr, int y_curr);

private:
	std::array<std::array<PiecesPtr, 8>, 8> m_gameboard;
};