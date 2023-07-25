#pragma once

#include "IPieceInfo.h"
#include "Position.h"
#include <string>
#include "EState.h"

using IGamePtr = std::shared_ptr<class IGame>;
using CharMatrix = std::array<std::array<char, 8>, 8>;

class IGame
{
public:
	static IGamePtr Produce();

	virtual IPieceInfoPtr GetPieceInfo(Position) const = 0;
	
	virtual void Move(Position, Position) = 0;
	
	virtual EColor GetTurn() const = 0;

	virtual bool IsOver() const = 0;
	virtual bool IsDraw() = 0;

	virtual void ProposeDraw() = 0;
	virtual bool IsDrawProposed()const = 0;
	virtual void DrawResponse(bool) = 0;

	virtual bool ChoosePiece()const = 0;
	virtual void PromoteTo(const std::string&, Position) = 0;

	virtual PositionList GetMoves(Position p) = 0;

	virtual ~IGame() = default;
};
