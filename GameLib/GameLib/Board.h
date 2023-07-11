#pragma once
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "King.h"
#include "Queen.h"
#include "Pawn.h"
#include<array>

enum class EPieceType
{
	Rook,
	Knight,
	Bishop,
	King,
	Queen,
	Pawn
};

class Board
{
public:
	// Constructors
	Board();

	// Getters
	std::array<std::array<PiecesPtr, 8>, 8> GetGameboard();
private:
	std::array<std::array<PiecesPtr, 8>, 8> gameboard;
};