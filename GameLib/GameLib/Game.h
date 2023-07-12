#pragma once
#include "Board.h"
#include "Piece.h"
#include<vector>
#include<memory>

class Game
{
public:

private:
	Board m_gameboard;
	std::vector<PiecesPtr> m_pieces;
};