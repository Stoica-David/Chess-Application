#pragma once

#include <thread>
#include <chrono>

using Thread = std::thread;

class Timer
{
public:
	Timer();

	void Start(int seconds);
	void Stop();

	int GetTimeLeft() const;

private:
	void Run();

	Thread timerThread;
	bool running;
	int timeLeft;
};