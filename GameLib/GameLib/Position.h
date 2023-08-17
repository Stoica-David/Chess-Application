#pragma once

#include<vector>

struct Position
{
	int x;
	int y;

	Position(int x = -1, int y = -1);

	bool operator==(const Position& other) const;
	bool operator!=(const Position& other) const;

	bool IsValid() const;

	static const Position INVALID;
};

using PositionList = std::vector<Position>;
using MoveVector = std::vector<std::pair<Position, Position>>;

static bool Pawn2Forward(Position p1, Position p2)
{
	return std::abs(p2.x - p1.x) == 2 && std::abs(p2.y - p1.y) == 0;
}
