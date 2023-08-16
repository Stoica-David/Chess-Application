#pragma once

#include "Position.h"
#include "IPieceInfo.h"

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
	 * returns number of moves
	 * 
	 * @return int number of moves
	 */
	virtual int GetNrMoves() const = 0;

	/**
* Returns color of player
*/
	virtual EColor GetTurn() const = 0;
	
	/**
 * Obtains information about a piece on a given position
 *
 * @param position on board
 * @return pointer to PieceInfo
 */
	virtual IPieceInfoPtr GetPieceInfo(Position) const = 0;

	/**
* Determines positions where a piece can move depending on surroundings
* @param p position inside board
* @return vector of possible positions where a piece can go
*/
	virtual PositionList GetMoves(Position p) const = 0;
	
	/**
 * Obtains past moves
 *
 * @return vector of positions
 */
	virtual MoveVector GetHistory() const = 0;

	/**
 * Determine left pieces from the board
 *
 * @param color of pieces
 * @return vector of pieces and their apparitions
 */
	virtual PiecesLeftVector GetPiecesLeft(EColor) const = 0;
};