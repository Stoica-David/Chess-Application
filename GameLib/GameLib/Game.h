#pragma once

#include "IGame.h"
#include "Board.h"
#include "Piece.h"

#include<vector>
#include<memory>



class Game:public IGame
{
public:
	//Getters
	ChessBoard GetBoard();

	//Other methods
	bool Move(Position p1, Position p2) override;

private:
	Board m_gameboard;
	std::vector<PiecesPtr> m_pieces;
};