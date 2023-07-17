#pragma once
#include "IPiece.h"
#include "IPieceInfo.h"

using IGamePtr = std::shared_ptr<class IGame>;

class IGame
{
public:
	static IGamePtr Produce();

	virtual bool Move(Position, Position) = 0;
	virtual ~IGame() = default;
};
