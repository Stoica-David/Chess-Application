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

	// Functions
	bool PositionExists(Position p);
	bool VerifyTheWay(Position p1, Position p2);

	// Temporary
	void printBoard();

private:
	std::array<std::array<PiecesPtr, 8>, 8> m_gameboard;
};