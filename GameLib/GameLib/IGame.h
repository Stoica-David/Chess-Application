#pragma once

#include "IPieceInfo.h"
#include "Position.h"
#include "IGameListener.h"
#include <string>

using IGamePtr = std::shared_ptr<class IGame>;
using CharMatrix = std::array<std::array<char, 8>, 8>;
using IGameListenerWeakPtr = std::weak_ptr<IGameListener>;
using IGameListenerSharedPtr = std::shared_ptr<IGameListener>;

class IGame
{
public:
	static IGamePtr Produce();

	virtual IPieceInfoPtr GetPieceInfo(Position) const = 0;
	
	virtual void Move(Position, Position) = 0;
	
	virtual EColor GetTurn() const = 0;

	virtual bool IsOver() const = 0;
	virtual bool IsDraw() = 0;
	virtual bool IsCheck() = 0;

	virtual void ProposeDraw() = 0;
	virtual bool IsDrawProposed()const = 0;
	virtual void DrawResponse(bool) = 0;

	virtual bool ChoosePiece()const = 0;
	virtual void PromoteTo(const std::string&, Position) = 0;

	virtual PositionList GetMoves(Position p) = 0;

	virtual void Restart() = 0;

	virtual void AddListener(IGameListenerSharedPtr) = 0;
	virtual void RemoveListener(IGameListener*) = 0;
	
	virtual void NotifyMove() = 0;
	virtual void NotifyGameOver() = 0;
	virtual void NotifyDraw() = 0;
	virtual void NotifyChoosePiece(Position) = 0;
	virtual void NotifyCheck() = 0;

	virtual ~IGame() = default;
};
