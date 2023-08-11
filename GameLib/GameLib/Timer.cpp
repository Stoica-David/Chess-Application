#include "Timer.h"

Timer::Timer(int totalMinutes) 
	: running(false)
	, remaining_time(totalMinutes * 60000)
	, m_bSuspended( false )
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
	m_bSuspended = false;

	cv.notify_all();

	if (!thread.joinable())
	{
		thread = std::thread(&Timer::Run, this);
	}
}

void Timer::StopTimer()
{
	m_bSuspended = true;
}

void Timer::PauseTimer()
{
	running = false;

	cv.notify_one();
}

void Timer::RestartTimer()
{
	//600000
	remaining_time = std::chrono::milliseconds(600000);
}

void Timer::SetNotifyChange(std::function<void()> newFunc)
{
	notifyChange = newFunc;
}

bool Timer::IsTimeExpired()
{
	return remaining_time <= std::chrono::milliseconds(0);
}

int Timer::GetMs() const
{
	return (remaining_time).count();
}

void Timer::Run()
{
	while (running)
	{
		auto initial_time = std::chrono::steady_clock::now();

		std::unique_lock lk(mutex);
		cv.wait_for(lk, 10ms, [&] { return !running; });

		if (m_bSuspended)
			continue;

		auto current_time = std::chrono::steady_clock::now();

		remaining_time -= std::chrono::duration_cast<std::chrono::milliseconds>(current_time - initial_time);

		if (remaining_time < std::chrono::milliseconds(0))
			remaining_time = std::chrono::milliseconds(0);

		if (IsTimeExpired())
		{
			StopTimer();
		}

		// Notify time update
		notifyChange();
	}
}
