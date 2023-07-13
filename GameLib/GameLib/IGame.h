#pragma once
#include "IPiece.h"

class IGame
{
	virtual bool Move(Position, Position) = 0;
	virtual ~IGame() = default;
};