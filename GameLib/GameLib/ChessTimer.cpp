#include "ChessTimer.h"

ChessTimer::ChessTimer(int total_minutes) : total_time(total_minutes * 60), remaining_time(total_minutes * 60)
{
}

void ChessTimer::startTurn()
{
	start_time = std::chrono::steady_clock::now();
}

void ChessTimer::endTurn()
{
	end_time = std::chrono::steady_clock::now();
	remaining_time -= std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);
}

bool ChessTimer::isTimeExpired() const
{
	return remaining_time <= std::chrono::seconds(0);
}

bool ChessTimer::isGameOver() const
{
	return remaining_time <= std::chrono::seconds(0);
}

std::chrono::duration<int> ChessTimer::getRemainingTime() const
{
	return remaining_time;
}
