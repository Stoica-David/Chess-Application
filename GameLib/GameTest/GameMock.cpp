#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "Game.h"
#include "BoardExceptions.h"
#include "GameExceptions.h"

using ::testing::_;
using ::testing::Throw;

class MockGame : public IGameListener
{
public:
	MOCK_METHOD(void, OnMove, (), (override));
	MOCK_METHOD(void, OnGameOver, (EOverState state), (override));
	MOCK_METHOD(void, OnChoosePiece, (Position pos), (override));
	MOCK_METHOD(void, OnCheck, (), (override));
	MOCK_METHOD(void, OnRestart, (), (override));
};


TEST(MoveMock, RegularMove1)
{
	auto mock = std::make_shared<MockGame>();
	Game myGame;
	
	myGame.AddListener(mock);

	EXPECT_CALL(*mock, OnMove());

	myGame.Move({ 6,1 }, { 5,1 });

	myGame.RemoveListener(mock.get());
}

TEST(MoveMock, RegularMove2)
{
	auto mock = std::make_shared<MockGame>();
	Game myGame;

	myGame.AddListener(mock);

	EXPECT_CALL(*mock, OnMove()).Times(3);

	myGame.Move({ 6,1 }, { 5,1 });
	myGame.Move({ 1,1 }, { 2,1 });
	myGame.Move({ 5,1 }, { 4,1 });

	myGame.RemoveListener(mock.get());
}

TEST(MoveMock, RegularMove3)
{
	CharMatrix m = { {
	{'r', 'r', 'b', 'q', 'k', 'b', 'r', 'r',},
	{'p', 'p', 'p', 'p', '-', '-', 'p', 'p',},
	{'-', '-', '-', '-', '-', 'p', '-', '-',},
	{'-', '-', '-', '-', 'p', '-', '-', '-',},
	{'Q', '-', 'P', '-', '-', '-', '-', '-',},
	{'-', '-', '-', '-', '-', 'P', '-', '-',},
	{'P', 'P', '-', 'P', 'P', '-', 'P', 'P',},
	{'R', 'H', 'B', '-', 'K', 'B', 'H', 'R',},
	} };

	Game myGame(m, EColor::Black, EState::Playing);

	auto mock = std::make_shared<MockGame>();

	myGame.AddListener(mock);
	
	EXPECT_CALL(*mock, OnMove()).Times(4);
	

	myGame.Move({1,0}, {2,0});
	myGame.Move({6,0}, {5,0});
	myGame.Move({2,0}, {3,0});
	EXPECT_THROW(myGame.Move({ 5,0 }, { 4,0 }), InTheWayException);
	myGame.Move({6,1}, {5,1});
	
	myGame.RemoveListener(mock.get());
}

TEST(MoveMock, RegularMove4)
{
	CharMatrix m = { {
	{'r', 'r', 'b', 'q', 'k', 'b', 'r', 'r',},
	{'p', 'p', 'p', 'p', '-', '-', 'p', 'p',},
	{'-', '-', '-', '-', '-', 'p', '-', '-',},
	{'-', '-', '-', '-', 'p', '-', '-', '-',},
	{'Q', '-', 'P', '-', '-', '-', '-', '-',},
	{'-', '-', '-', '-', '-', 'P', '-', '-',},
	{'P', 'P', '-', 'P', 'P', '-', 'P', 'P',},
	{'R', 'H', 'B', '-', 'K', 'B', 'H', 'R',},
	} };

	Game myGame(m, EColor::White, EState::Playing);

	auto mock = std::make_shared<MockGame>();

	myGame.AddListener(mock);

	EXPECT_CALL(*mock, OnMove()).Times(0);
	EXPECT_THROW(myGame.Move({ 6,0 }, { 4,0 }), InTheWayException);

	myGame.RemoveListener(mock.get());
}