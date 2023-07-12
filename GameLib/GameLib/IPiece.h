#pragma once

class IPiece
{
public:
	virtual bool IsMoveRegular(int x_curr, int y_curr, int x_next, int y_next)=0;
	virtual void DeterminePattern(int x_curr, int y_curr) = 0;
};