#pragma once

#include "Position.h"
#include "IPieceInfo.h"

#include <unordered_map>
#include <chrono>

using PieceMap = std::unordered_map <EPieceType, int>;

class IGameStatus
{
public:
	virtual ~IGameStatus() = default;

	virtual bool IsDraw() const = 0;
	virtual bool IsOver() const = 0;
	virtual bool IsDrawProposed() const = 0;
	virtual bool IsCheck() const = 0;
	virtual bool IsPromoting() const = 0;
	virtual bool IsFrozen() const = 0;
	virtual bool IsPlaying() const = 0;

	virtual EColor GetTurn() const = 0;
	virtual PositionList GetMoves(Position p) const = 0;
	virtual MoveVector GetHistory() const = 0;
	virtual IPieceInfoPtr GetPieceInfo(Position) const = 0;
	virtual PieceMap GetPiecesLeft(EColor) const = 0;
	virtual int GetMs(EColor color) const = 0;
};