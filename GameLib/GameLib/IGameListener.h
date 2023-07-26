#pragma once

class IGameListener
{
public:
	virtual void OnMove() = 0;
	virtual void OnGameOver() = 0;
	virtual void OnDraw() = 0;
	virtual void OnChoosePiece(Position) = 0;
	virtual void OnCheck() = 0;

	virtual ~IGameListener() = default;
};