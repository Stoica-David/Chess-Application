#pragma once

#include <chrono>
#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <functional>

using namespace std::chrono_literals;

class Timer
{
public:
	Timer(int total_minutes);
	Timer(const Timer&) = default;

	~Timer();

	void StartTimer();
	void StopTimer();

	void SetNotifyChange(std::function<void()> newFunc);

	bool IsTimeExpired() const;

	int GetSeconds() const;
	int GetMinutes() const;

private:
	void Run();

private:
	std::thread thread;
	std::atomic<bool> running;
	std::condition_variable cv;
	std::mutex mutex;

	std::chrono::steady_clock::time_point start_time;
	std::chrono::duration<int> remaining_time;
	std::chrono::steady_clock::time_point end_time;
	std::function<void()> notifyChange;
};
