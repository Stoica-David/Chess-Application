#pragma once

#include "EColor.h"

class ITimerInfo
{
public:
	virtual int GetTotalTime() const = 0;

	virtual int GetRemainingTime(EColor color) const = 0;

	virtual int GetThinkingTime(int nrMove) const = 0;

	//virtual int GetCurrentMoveTime() const = 0;

	virtual void SetTimerResolution(int ms) = 0;
	virtual int GetTimerResolution() const = 0;
};