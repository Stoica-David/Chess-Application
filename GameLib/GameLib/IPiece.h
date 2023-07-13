#pragma once

#include <utility>
#include <vector>

using Position = std::pair<int, int>;
using PositionList = std::vector<Position>;

class IPiece
{
public:
	virtual bool IsMoveRegular(Position p1, Position p2)=0;
	virtual PositionList DeterminePattern(Position p1, Position p2)=0;
};