#pragma once

#include "EOverState.h"

class IGameListener
{
public:
	/**
	 * Updates board every on every time a move is made
	 */
	virtual void OnMove() = 0;

	/**
	 * Updates the Ui depending of state
	 * 
	 * @param EOverState state to update the board to
	 */
	virtual void OnGameOver(EOverState) = 0;
	
	/**
	 * Updates the Ui to display promote options when needed
	 */
	virtual void OnChoosePiece() = 0;
	
	/**
	 * Updates the Ui to display check state
	 */
	virtual void OnCheck() = 0;

	/**
	 * Resets timers
	 * Clears captured pieces, previous moves
	 * Starts a new game
	 */
	virtual void OnRestart() = 0;

	/**
	 * Updates the Ui when a specified piece is captured
	 * Displays captured pieces
	 * 
	 * @param EPieceType type of piece captured
	 * @param EColor color of piece captured
	 */
	virtual void OnPieceCapture(EPieceType, EColor) = 0;


	/**
	 * Updates timer
	 */
	virtual void OnTimerChange() = 0;

	/**
	 * Necessary virtual destructor
	 */
	virtual ~IGameListener() = default;
};

using IGameListenerWeakPtr = std::weak_ptr<IGameListener>;
using IGameListenerPtr = std::shared_ptr<IGameListener>;