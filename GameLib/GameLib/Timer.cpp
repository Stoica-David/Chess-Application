#include "Timer.h"

Timer::Timer(int totalMinutes) : running(false), remaining_time(totalMinutes * 60)
{
}

Timer::~Timer()
{
	running = false;

	cv.notify_one();

	if (thread.joinable())
	{
		thread.join();
	}
}

void Timer::StartTimer()
{
	running = true;

	cv.notify_all();

	if(!thread.joinable())
		thread = std::thread(&Timer::Run, this);
}

void Timer::StopTimer()
{
	running = false;

	cv.notify_all();

	if (thread.joinable())
	{
		thread.join();
	}
}

void Timer::RestartTimer()
{
	remaining_time = std::chrono::seconds(600);
}

void Timer::SetNotifyChange(std::function<void()> newFunc)
{
	notifyChange = newFunc;
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
		cv.wait_for(lk, 1s, [&] { return !running; });

		remaining_time -= std::chrono::seconds(1);

		// Notify time update
		notifyChange();
	}
}
