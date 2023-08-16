#pragma once

#include <chrono>
#include <functional>

#include "EColor.h"
#include "Thread.h"

using namespace std::chrono_literals;
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
	
	// Flow of the timer
	void StartTimer();
	void StopTimer();
	void ResetTimer();

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

	std::chrono::milliseconds m_initial_time;
	std::chrono::milliseconds m_white_remaining_time;
	std::chrono::milliseconds m_black_remaining_time;

	EColor m_color;

	bool m_bSuspended;

	TimerCallback m_notifyChange;
};
