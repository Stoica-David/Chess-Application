#include "Timer.h"
#include "Game.h"

#include<windows.h>

#include "gtest/gtest.h"

TEST(TimeRanOutTest, RanOut1)
{
	auto nothing = []() {
	
	};

	std::mutex m_mutex;
	Timer t(1);

	t.SetNotifyChange(nothing);

	t.StartTimer();

	std::this_thread::sleep_for(std::chrono::milliseconds(500));

	t.StopTimer();

	EXPECT_EQ(t.IsTimeExpired(), false);
}

TEST(TimeRanOutTest, RanOut2)
{
	auto nothing = []() {

	};

	Timer t(1, true);

	t.SetNotifyChange(nothing);

	t.StartTimer();

	std::this_thread::sleep_for(std::chrono::milliseconds(1100));

	t.StopTimer();

	EXPECT_EQ(t.IsTimeExpired(), true);
}