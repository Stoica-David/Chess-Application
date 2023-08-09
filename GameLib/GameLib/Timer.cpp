#include "Timer.h"

Timer::Timer() : running(false), timeLeft(600)
{
}

void Timer::Start(int seconds)
{
	if (!running)
	{
		running = true;
		timeLeft = seconds;
		timerThread = Thread(&Timer::Run, this);
	}
}

void Timer::Stop()
{
	if (running)
	{
		running = false;
		timerThread.join();
	}
}

int Timer::GetTimeLeft() const
{
	return timeLeft;
}

void Timer::Run()
{
	while (running && timeLeft > 0)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
		--timeLeft;
	}

	running = false;
}
