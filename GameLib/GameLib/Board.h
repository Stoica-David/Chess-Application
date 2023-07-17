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
	Board(bool);

	// Getters
	ChessBoard GetGameboard() const;

	// Setters
	void SetGameboard(Position p, PiecesPtr newPiece);

	// Functions
	bool PositionExists(Position p) const;
	bool VerifyTheWay(Position p1, Position p2) const;
	void FreePosition(Position p);
	PositionList GetMoves(Position p) const;
	bool IsCheck(Position p) const;
	PiecesPtr GetPiece(Position p) const;
	bool IsCheckMate(Position p);
private:

	bool FindHelp(Position p);
	bool KillCheck(Position p);
	Position FindKing(EColor) const;

private:
	ChessBoard m_board;
};