#pragma once

#include "EOverState.h"

class IGameListener
{
public:
	virtual void OnMove() = 0;

	virtual void OnGameOver(EOverState) = 0;
	
	virtual void OnChoosePiece() = 0;
	
	virtual void OnCheck() = 0;

	virtual void OnRestart() = 0;

	virtual void OnPieceCapture(EPieceType, EColor) = 0;

	virtual void OnTimerChange() = 0;

	virtual ~IGameListener() = default;
};

using IGameListenerWeakPtr = std::weak_ptr<IGameListener>;
using IGameListenerPtr = std::shared_ptr<IGameListener>;