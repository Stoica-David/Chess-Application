#pragma once

#include <chrono>
#include <functional>
#include <vector>

#include "EColor.h"
#include "Thread.h"

using TimerCallback = std::function<void()>;

class Timer
{
public:
	// Constructors
	Timer(int total_minutes);
	Timer(int, bool);
	Timer(const Timer&) = default;

	// Destructor
	~Timer();

	// Setters
	void SetColor(EColor);
	void SetNotifyChange(TimerCallback newFunc);
	void SetTimerResolution(int ms);
	
	// Flow of the timer
	void StartTimer();
	void StopTimer();
	void ResetTimer();

	// Time related
	bool IsTimeExpired();

	int GetInitialTime() const;
	int GetRemainingTime(EColor) const;
	int GetTimeForMove(EColor) const;
	int GetThinkingTimes(int nrMove) const;
	int GetTimerResolution() const;

private:
	void Run();

private:
	Thread m_thread;

	Mutex m_mutex;
	
	ConditionVariable m_cv;
	
	AtomicBool m_running;

	std::chrono::milliseconds m_initial_time;
	std::chrono::milliseconds m_white_remaining_time;
	std::chrono::milliseconds m_black_remaining_time;
	std::chrono::milliseconds m_timer_resolution;
	std::chrono::milliseconds m_white_thinking_time;
	std::chrono::milliseconds m_black_thinking_time;
	std::chrono::milliseconds m_toDecrease_time;

	std::vector<std::chrono::milliseconds> m_thinking_times;

	EColor m_color;

	bool m_bSuspended;

	TimerCallback m_notifyChange;
};
