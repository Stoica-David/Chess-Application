#pragma once

#include <chrono>
#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <functional>

#include "EColor.h"

using namespace std::chrono_literals;

class Timer
{
public:
	Timer(int total_minutes);
	Timer(const Timer&) = default;

	~Timer();

	void StartTimer();
	void StopTimer();
	void RestartTimer();
	void SetNotifyChange(std::function<void()> newFunc);
	void SetColor(EColor);

	bool IsTimeExpired();

	int GetMs(EColor)const;

private:
	void Run();

private:
	std::thread m_thread;
	std::atomic<bool> m_running;
	std::condition_variable m_cv;
	std::mutex m_mutex;

	std::chrono::milliseconds m_white_remaining_time;
	std::chrono::milliseconds m_black_remaining_time;
	std::function<void()> m_notifyChange;

	bool m_bSuspended;
	EColor m_color;
};
