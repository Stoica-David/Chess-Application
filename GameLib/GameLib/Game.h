#pragma once

#include "Board.h"
#include "Piece.h"

#include<vector>
#include<memory>



class Game
{
public:

	//Getters
	ChessBoard GetBoard();

	//Other methods
	bool Move(Position p1, Position p2);

public:
	Board m_gameboard;

	std::vector<PiecesPtr> m_pieces;
};