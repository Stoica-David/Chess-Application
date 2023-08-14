#include "Timer.h"

Timer::Timer(int totalMinutes)
	: m_running(false)
	, m_white_remaining_time(totalMinutes * 60000)
	, m_black_remaining_time(totalMinutes * 60000)
	, m_bSuspended(false)
	, m_color(EColor::White)
{
}

Timer::~Timer()
{
	m_running = false;

	m_cv.notify_one();

	if (m_thread.joinable())
	{
		m_thread.join();
	}
}

void Timer::StartTimer()
{
	m_running = true;
	m_bSuspended = false;

	m_cv.notify_all();

	if (!m_thread.joinable())
	{
		m_thread = std::thread(&Timer::Run, this);
	}
}

void Timer::StopTimer()
{
	m_bSuspended = true;

	m_cv.notify_all();
}

void Timer::RestartTimer()
{
	//600000
	m_white_remaining_time = std::chrono::milliseconds(600000);
	m_black_remaining_time = std::chrono::milliseconds(600000);
}

void Timer::SetNotifyChange(std::function<void()> newFunc)
{
	m_notifyChange = newFunc;
}

void Timer::SetColor(EColor color)
{
	m_color = color;
}

bool Timer::IsTimeExpired()
{
	return m_white_remaining_time <= std::chrono::milliseconds(0) || m_black_remaining_time <= std::chrono::milliseconds(0);
}

int Timer::GetMs(EColor color) const
{
	if (color == EColor::White)
		return (m_white_remaining_time).count();
	else
		return (m_black_remaining_time).count();
}

void Timer::Run()
{
	while (m_running)
	{
		auto initial_time = std::chrono::steady_clock::now();

		std::unique_lock lk(m_mutex);
		m_cv.wait_for(lk, 10ms, [&] { return !m_running; });

		if (m_bSuspended)
			continue;

		auto current_time = std::chrono::steady_clock::now();

		if (m_color == EColor::White)
			m_white_remaining_time -= std::chrono::duration_cast<std::chrono::milliseconds>(current_time - initial_time);
		else
			m_black_remaining_time -= std::chrono::duration_cast<std::chrono::milliseconds>(current_time - initial_time);

		if (m_white_remaining_time < std::chrono::milliseconds(0))
			m_white_remaining_time = std::chrono::milliseconds(0);

		if (m_black_remaining_time < std::chrono::milliseconds(0))
			m_black_remaining_time = std::chrono::milliseconds(0);

		if (IsTimeExpired())
		{
			StopTimer();
		}

		// Notify time update
		m_notifyChange();
	}
}
