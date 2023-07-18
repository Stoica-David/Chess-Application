#pragma once

#include "IGame.h"
#include "Board.h"
#include "Piece.h"

#include<vector>
#include<memory>

class Game : public IGame
{
public:
	// Constructor
	Game();

	//Other methods
	bool Move(Position p1, Position p2) override;
	IPieceInfoPtr GetPieceInfo(Position) const override;
	PiecesPtr GetPiece(Position) const;

private:
	bool PawnGoesDiagonally(Position p1, Position p2) const;
	bool SameColor(Position p1, Position p2) const;

private:
	Board m_gameboard;
	EColor m_turn;
};