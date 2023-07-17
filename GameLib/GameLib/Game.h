#pragma once

#include "IGame.h"
#include "Board.h"
#include "Piece.h"

#include<vector>
#include<memory>

using PieceVector = std::vector<PiecesPtr>;

class Game:public IGame
{
public:
	// Constructor
	Game();

	//Getters
	ChessBoard GetBoard() const;

	//Other methods
	bool Move(Position p1, Position p2) override;
	IPiecePtr GetPieceInfo(Position) const override;

private:
	Board m_gameboard;
};