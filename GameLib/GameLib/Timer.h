#pragma once

#include <chrono>
#include <functional>

#include "EColor.h"
#include "Thread.h"

using namespace std::chrono_literals;
using namespace std::chrono;

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
	void SetNotifyChange(std::function<void()> newFunc);
	
	// Flow of the timer
	void StartTimer();
	void StopTimer();
	void RestartTimer();

	// Time related
	bool IsTimeExpired();

	int GetMs(EColor)const;

private:
	void Run();

private:
	Thread m_thread;

	Mutex m_mutex;
	
	ConditionVariable m_cv;
	
	AtomicBool m_running;

	milliseconds m_white_remaining_time;
	milliseconds m_black_remaining_time;

	EColor m_color;

	bool m_bSuspended;

	std::function<void()> m_notifyChange;
};
