#pragma once

#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "King.h"
#include "Queen.h"
#include "Pawn.h"
#include<array>

using ChessBoard = std::array<std::array<PiecesPtr, 8>, 8>;

class Board
{
public:
	// Constructors
	Board();

	// Getters
	ChessBoard GetGameboard() const;

	// Functions
	bool PositionExists(Position p) const;
	bool VerifyTheWay(Position p1, Position p2) const;

	// Temporary
	void printBoard();

private:
	ChessBoard m_board;
};