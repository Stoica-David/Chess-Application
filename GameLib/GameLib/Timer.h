#pragma once

#include <chrono>
#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>

using namespace std::chrono_literals;

class Timer
{
public:
	Timer();
	~Timer();

	/*
	void Reset() {
		start_time = std::chrono::high_resolution_clock::now();
	}

	double ElapsedMilliseconds() const {
		auto end_time = std::chrono::high_resolution_clock::now();
		auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
		return static_cast<double>(elapsed_time.count());
	}

	double ElapsedSeconds() const {
		return ElapsedMilliseconds() / 1000.0;
	}
	*/

	void StartTimer();
	void StopTimer();

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
};
