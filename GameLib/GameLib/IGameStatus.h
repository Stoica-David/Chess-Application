#pragma once

#include "Position.h"
#include "IPieceInfo.h"

#include <unordered_map>
#include <chrono>

/**
 * Vector of pieces left on the board
 */
using PiecesLeftVector = std::vector < std::pair<EPieceType, int>>;

class IGameStatus
{
public:
	virtual ~IGameStatus() = default;

	/**
	 * Checks if the game is in draw state
	 */
	virtual bool IsDraw() const = 0;
	/**
	* Checks if the game is in over state
	*/
	virtual bool IsOver() const = 0;
	/**
	* Checks if the game is in draw proposed state
	*/
	virtual bool IsDrawProposed() const = 0;
	/**
	* Checks if the game is in check state
	*/
	virtual bool IsCheck() const = 0;
	/**
	* Checks if the game is in choose piece state
	*/
	virtual bool IsPromoting() const = 0;
	/**
	* Checks if the game is in pause state
	*/
	virtual bool IsFrozen() const = 0;
	/**
	* Checks if the game is in playing state
	*/
	virtual bool IsPlaying() const = 0;

	/**
	 * Returns color of player
	 */
	virtual EColor GetTurn() const = 0;
	virtual PositionList GetMoves(Position p) const = 0;
	virtual MoveVector GetHistory() const = 0;
	virtual IPieceInfoPtr GetPieceInfo(Position) const = 0;

	virtual int GetMs(EColor color) const = 0;

	virtual PiecesLeftVector GetPiecesLeft(EColor) const = 0;
};