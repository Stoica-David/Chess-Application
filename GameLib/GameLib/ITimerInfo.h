#pragma once

#include "EColor.h"

class ITimerInfo
{
public:

	/**
	 * Obtains total time allocated for a player
	 * 
	 * @return int milliseconds 
	 */
	virtual int GetTotalTime() const = 0;

	/**
	 * Obtains left time
	 * 
	 * @return int milliseconds 
	 */
	virtual int GetRemainingTime(EColor color) const = 0;

	/**
	 * Obtain time spent between moves
	 * 
	 * @return int milliseconds between moves 
	 */
	virtual int GetThinkingTime(int nrMove) const = 0;


	/**
	 * Obtain time after turn was switched
	 * 
	 * @return int milliseconds 
	 */
	virtual int GetCurrentMoveTime() const = 0;

	/**
	 * Sets how fast you want the timer to update
	 */
	virtual void SetTimerResolution(int ms) = 0;

	/**
	 * Obtain milliseconds between updates
	 * 
	 * @return int milliseconds
	 */
	virtual int GetTimerResolution() const = 0;
};