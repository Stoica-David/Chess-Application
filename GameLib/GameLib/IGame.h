#pragma once

#include "IPieceInfo.h"
#include "Position.h"

using IGamePtr = std::shared_ptr<class IGame>;

class IGame
{
public:
	static IGamePtr Produce();

	virtual IPieceInfoPtr GetPieceInfo(Position) const = 0;
	
	virtual bool Move(Position, Position) = 0;
	
	virtual EColor GetTurn() const = 0;
	
	virtual bool IsDraw() const = 0;
	virtual bool IsOver() const = 0;

	virtual ~IGame() = default;
};
