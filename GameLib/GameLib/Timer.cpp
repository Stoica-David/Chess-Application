#include "Timer.h"

using namespace std::chrono_literals;

Timer::Timer(int seconds, bool)
	: m_running(false)
	, m_initial_time(seconds * 1000)
	, m_white_remaining_time(m_initial_time)
	, m_black_remaining_time(m_initial_time)
	, m_timer_resolution(1ms)
	, m_white_thinking_time(0ms)
	, m_black_thinking_time(0ms)
	, m_toDecrease_time(0ms)
	, m_bSuspended(false)
	, m_color(EColor::White)
{
}

Timer::Timer(int totalMinutes)
	: Timer(totalMinutes * 60, true)
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

void Timer::SetColor(EColor color)
{
	color == EColor::White ? m_white_thinking_time += m_toDecrease_time : m_black_thinking_time += m_toDecrease_time;

	m_thinking_times.push_back(m_toDecrease_time);

	m_toDecrease_time = 0ms;

	m_color = color;
}

void Timer::SetNotifyChange(TimerCallback newFunc)
{
	m_notifyChange = newFunc;
}

void Timer::SetTimerResolution(int ms)
{
	m_timer_resolution = static_cast<std::chrono::milliseconds>(ms);
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

void Timer::ResetTimer()
{
	m_white_remaining_time = std::chrono::milliseconds(m_initial_time);
	m_black_remaining_time = std::chrono::milliseconds(m_initial_time);
}

bool Timer::IsTimeExpired()
{
	return m_white_remaining_time <= std::chrono::milliseconds(0) || m_black_remaining_time <= std::chrono::milliseconds(0);
}

int Timer::GetInitialTime() const
{
	return m_initial_time.count();
}

int Timer::GetRemainingTime(EColor color) const
{
	return color == EColor::White ? (m_white_remaining_time).count() : (m_black_remaining_time).count();
}

int Timer::GetTimeForMove(EColor color) const
{
	return color == EColor::White ? m_white_thinking_time.count() : m_black_thinking_time.count();
}

int Timer::GetThinkingTimes(int nrMove) const
{
	return m_thinking_times[nrMove].count();
}

int Timer::GetTimerResolution() const
{
	return m_timer_resolution.count();
}

static std::chrono::milliseconds TimeInMillis(const std::chrono::steady_clock::time_point& initial_time)
{
	auto current_time = std::chrono::steady_clock::now();
	return std::chrono::duration_cast<std::chrono::milliseconds>(current_time - initial_time);
}

void Timer::Run()
{
	while (m_running)
	{
		auto initial_time = std::chrono::steady_clock::now();

		std::unique_lock lk(m_mutex);
		m_cv.wait_for(lk, m_timer_resolution, [&] { return !m_running; });

		if (m_bSuspended)
			continue;

		auto elapsed_time = TimeInMillis(initial_time);
		m_toDecrease_time += elapsed_time;

		initial_time = std::chrono::steady_clock::now();

		auto& remainingTime = m_color == EColor::White ? m_white_remaining_time : m_black_remaining_time;
		remainingTime = elapsed_time < remainingTime ? remainingTime - elapsed_time : 0ms;

		if (IsTimeExpired())
		{
			StopTimer();
		}

		m_notifyChange();
	}
}
