#pragma once

#include<utility>
#include<vector>

using Position = std::pair<int, int>;
using PositionList = std::vector<Position>;
using MoveVector = std::vector<std::pair<Position, Position>>;

static bool Pawn2Forward(Position p1, Position p2)
{
	return std::abs(p2.first - p1.first) == 2 && std::abs(p2.second - p1.second);
}