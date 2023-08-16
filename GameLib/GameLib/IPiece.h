#pragma once

#include "Position.h"
#include "EPieceType.h"
#include "EColor.h"
#include <utility>
#include <vector>

using PositionMatrix = std::vector<PositionList>;

class IPiece
{
public:
	/**
	 * Determines whether or not a given piece from a position can go to a different position
	 *
	 * @param p1 initial position
	 * @param p2 new position
	 *
	 * @return bool true if p2 is a position where the piece can go
	 */
	virtual bool IsMoveRegular(Position p1, Position p2) const = 0;

	/**
	 * Determines all positions a piece has to travel until p2 in reached
	 *
	 * @param p1 initial position
	 * @param p2 new position
	 *
	 * @return vector of positions the piece travels to until p2 in reached
	 */
	virtual PositionList DeterminePattern(Position p1, Position p2) const = 0;

	/**
	 * Determines all squares a piece can go from a given position
	 * Doesn't take into account other pieces that may be on the board
	 *
	 * @param position of piece
	 *
	 * @return matrix of position vectors for every direction in which the piece can go
	 */
	virtual PositionMatrix AllMoves(Position p) const = 0;
};
