#pragma once

class IGame
{
	virtual bool MovePiece(int, int) = 0;
	virtual ~IGame() = default;
};