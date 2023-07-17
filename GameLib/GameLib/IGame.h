#pragma once
#include "IPiece.h"
#include "PieceInfo.h"

using IGamePtr = std::shared_ptr<class IGame>;

class IGame
{
public:
	static IGamePtr Produce();

	virtual IPiecePtr GetPieceInfo(Position) const = 0;
	virtual bool Move(Position, Position) = 0;

	virtual ~IGame() = default;
};
