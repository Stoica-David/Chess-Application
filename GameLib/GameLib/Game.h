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

	//Getters
	ChessBoard GetBoard() const;

	//Other methods
	bool Move(Position p1, Position p2) override;
	IPieceInfoPtr GetPieceInfo(Position) const override;

private:
	Board m_gameboard;
};