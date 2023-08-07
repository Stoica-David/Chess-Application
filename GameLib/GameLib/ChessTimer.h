#pragma once
#include <chrono>

class ChessTimer
{
public:

	ChessTimer(int total_minutes);

	void startTurn();
	void endTurn();

	bool isTimeExpired() const;
	bool isGameOver() const;

	std::chrono::duration<int> getRemainingTime() const;

private:
	std::chrono::steady_clock::time_point start_time;
	std::chrono::steady_clock::time_point end_time;
	std::chrono::duration<int> total_time;
	std::chrono::duration<int> remaining_time;
};

