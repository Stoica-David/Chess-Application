#include "Timer.h"

Timer::Timer() : running(false), timeLeft(600)
{
}

Timer::~Timer()
{
	running = false;

	cv.notify_one();

	if (thread.joinable()) {
		thread.join();
	}
}

void Timer::StartTimer()
{
	start_time = std::chrono::steady_clock::now();
}

void Timer::StopTimer()
{
	end_time = std::chrono::steady_clock::now();
	remaining_time -= std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);
}

bool Timer::IsTimeExpired() const
{
	return remaining_time <= std::chrono::seconds(0);
}

int Timer::GetSeconds() const
{
	return remaining_time.count() % 60;
}

int Timer::GetMinutes() const
{
	return remaining_time.count() / 60;
}

void Timer::Run()
{
	while (running)
	{
		std::unique_lock lk(mutex);
		cv.wait_for(lk, 200ms, [&] { return !running; });

		// Notify time update
	}
}
