#include "IGame.h"
#include "BoardExceptions.h"
#include "GameExceptions.h"

#include<gtest/gtest.h>

class IGameTest : public testing::Test
{
protected:
	void SetUp() override
	{
		myInstance = IGame::Produce();
	}

	void TearDown() override
	{
	}

	IGamePtr myInstance;
};

TEST_F(IGameTest, MoveTest)
{
	EXPECT_NO_THROW(myInstance->Move({6,0}, {4,0}));
	EXPECT_THROW(myInstance->Move({6,1}, {5,1}), TurnException);
	EXPECT_NO_THROW(myInstance->Move({1,0}, {3,0}));
	EXPECT_THROW(myInstance->Move({4,0}, {3,0}), InTheWayException);
	EXPECT_NO_THROW(myInstance->Move({6,2}, {5,2}));
	EXPECT_NO_THROW(myInstance->Move({1,3}, {2,3}));
	EXPECT_THROW(myInstance->Move({6,0}, {5,2}), DoesntExistException);
	EXPECT_THROW(myInstance->Move({5,2}, {2,2}), MoveException);
	EXPECT_THROW(myInstance->Move({-5,2}, {2,2}), PositionException);
}