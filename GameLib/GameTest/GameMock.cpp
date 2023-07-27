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


	myGame.Move({ 1,0 }, { 2,0 });
	myGame.Move({ 6,0 }, { 5,0 });
	myGame.Move({ 2,0 }, { 3,0 });
	EXPECT_THROW(myGame.Move({ 5,0 }, { 4,0 }), InTheWayException);
	myGame.Move({ 6,1 }, { 5,1 });

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

TEST(MoveMock, MultipleListeners)
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

	auto mock1 = std::make_shared<MockGame>(),
		 mock2 = std::make_shared<MockGame>(),
		 mock3 = std::make_shared<MockGame>();

	myGame.AddListener(mock1);
	myGame.AddListener(mock2);
	myGame.AddListener(mock3);

	EXPECT_CALL(*mock1, OnMove());
	EXPECT_CALL(*mock2, OnMove());
	EXPECT_CALL(*mock3, OnMove());
	
	myGame.Move({ 6,0 }, { 5,0 });

	myGame.RemoveListener(mock1.get());
	myGame.RemoveListener(mock2.get());
	myGame.RemoveListener(mock3.get());
}

TEST(MoveMock, AfterRemove)
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

	auto mock1 = std::make_shared<MockGame>(),
		mock2 = std::make_shared<MockGame>(),
		mock3 = std::make_shared<MockGame>();

	myGame.AddListener(mock1);
	myGame.AddListener(mock2);
	myGame.AddListener(mock3);

	EXPECT_CALL(*mock1, OnMove());
	EXPECT_CALL(*mock2, OnMove());
	EXPECT_CALL(*mock3, OnMove());

	myGame.Move({ 6,0 }, { 5,0 });

	myGame.RemoveListener(mock2.get());
	myGame.RemoveListener(mock3.get());
	
	EXPECT_CALL(*mock1, OnMove());

	myGame.Move({ 1,0 }, { 2,0 });

	myGame.RemoveListener(mock1.get());
}

TEST(MoveMock, ImbricateTest)
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

	auto mock1 = std::make_shared<MockGame>(),
		mock2 = std::make_shared<MockGame>(),
		mock3 = std::make_shared<MockGame>();

	myGame.AddListener(mock1);
	myGame.AddListener(mock2);
	myGame.AddListener(mock3);

	EXPECT_CALL(*mock1, OnMove());
	EXPECT_CALL(*mock2, OnMove());
	EXPECT_CALL(*mock3, OnMove()).Times(0);

	myGame.RemoveListener(mock3.get());

	myGame.Move({ 6,0 }, { 5,0 });

	myGame.RemoveListener(mock2.get());
	myGame.RemoveListener(mock1.get());
}

TEST(MoveMock, InTheWayExceptionMove)
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
	EXPECT_THROW(myGame.Move({ 7,0 }, { 6,0 }), InTheWayException);
	EXPECT_THROW(myGame.Move({ 7,0 }, { 7,1 }), InTheWayException);
	EXPECT_THROW(myGame.Move({ 7,2 }, { 6,1 }), InTheWayException);

	myGame.RemoveListener(mock.get());
}

TEST(MoveMock, MoveExceptionTest)
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
	EXPECT_THROW(myGame.Move({ 7,0 }, { 4,2 }), MoveException);
	EXPECT_THROW(myGame.Move({ 7,1 }, { 6,6 }), MoveException);
	EXPECT_THROW(myGame.Move({ 6,1 }, { 3,1 }), MoveException);
	EXPECT_THROW(myGame.Move({ 7,5 }, { 6,5 }), MoveException);

	myGame.RemoveListener(mock.get());
}

TEST(MoveMock, PositionExceptionTest)
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
	EXPECT_THROW(myGame.Move({ 7,0 }, { 4,-3242342 }), PositionException);
	EXPECT_THROW(myGame.Move({ 192,1 }, { 6,6 }), PositionException);

	myGame.RemoveListener(mock.get());
}

TEST(MoveMock, DoesntExistExceptionTest)
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
	EXPECT_THROW(myGame.Move({ 2,0 }, { 2,0 }), DoesntExistException);
	EXPECT_THROW(myGame.Move({ 2,1 }, { 6,6 }), DoesntExistException);
	EXPECT_THROW(myGame.Move({ 5,1 }, { 6,6 }), DoesntExistException);
	EXPECT_THROW(myGame.Move({ 7,3 }, { 3,6 }), DoesntExistException);

	myGame.RemoveListener(mock.get());
}

TEST(MoveMock, PromoteExceptionTest)
{
	CharMatrix m = { {
	{'k', '-', '-', '-', '-', '-', '-', '-',},
	{'-', '-', '-', 'P', '-', 'R', '-', '-',},
	{'-', '-', '-', '-', '-', '-', '-', '-',},
	{'-', '-', '-', '-', '-', '-', '-', '-',},
	{'-', '-', 'P', '-', '-', '-', '-', '-',},
	{'-', '-', '-', '-', '-', '-', '-', '-',},
	{'P', 'P', 'P', 'P', '-', '-', 'P', 'P',},
	{'R', 'H', 'B', 'Q', 'K', 'B', 'H', 'R',},
	} };

	Game myGame(m, EColor::White, EState::Playing);

	auto mock = std::make_shared<MockGame>();

	myGame.AddListener(mock);

	EXPECT_CALL(*mock, OnMove()).Times(0);
	EXPECT_THROW(myGame.PromoteTo(EPieceType::Queen), PromoteException);

	myGame.RemoveListener(mock.get());
}

TEST(MoveMock, TurnExceptionTest1)
{
	CharMatrix m = { {
	{'k', '-', '-', '-', '-', '-', '-', '-',},
	{'-', '-', '-', 'P', '-', 'R', '-', '-',},
	{'-', '-', '-', '-', '-', '-', '-', '-',},
	{'-', '-', '-', '-', '-', '-', '-', '-',},
	{'-', '-', 'P', '-', '-', '-', '-', '-',},
	{'-', '-', '-', '-', '-', '-', '-', '-',},
	{'P', 'P', 'P', 'P', '-', '-', 'P', 'P',},
	{'R', 'H', 'B', 'Q', 'K', 'B', 'H', 'R',},
	} };

	Game myGame(m, EColor::White, EState::Playing);

	auto mock = std::make_shared<MockGame>();

	myGame.AddListener(mock);

	EXPECT_CALL(*mock, OnMove()).Times(0);
	EXPECT_THROW(myGame.Move({0, 0}, {0,1}), TurnException);

	myGame.RemoveListener(mock.get());
}

TEST(MoveMock, TurnExceptionTest2)
{
	CharMatrix m = { {
	{'k', '-', '-', '-', '-', '-', '-', '-',},
	{'-', '-', '-', 'P', '-', 'R', '-', '-',},
	{'-', '-', '-', '-', '-', '-', '-', '-',},
	{'-', '-', '-', '-', '-', '-', '-', '-',},
	{'-', '-', 'P', '-', '-', '-', '-', '-',},
	{'-', '-', '-', '-', '-', '-', '-', '-',},
	{'P', 'P', 'P', 'P', '-', '-', 'P', 'P',},
	{'R', 'H', 'B', 'Q', 'K', 'B', 'H', 'R',},
	} };

	Game myGame(m, EColor::White, EState::Playing);

	auto mock = std::make_shared<MockGame>();

	myGame.AddListener(mock);

	EXPECT_CALL(*mock, OnMove()).Times(1);
	EXPECT_THROW(myGame.Move({ 0, 0 }, { 0,1 }), TurnException);
	EXPECT_NO_THROW(myGame.Move({ 6, 0 }, { 5,0 }));
	EXPECT_THROW(myGame.Move({ 5, 0 }, { 4,0 }), TurnException);

	myGame.RemoveListener(mock.get());
}

TEST(MoveMock, StillCheckExceptionTest)
{
	CharMatrix m = { {
	{'k', '-', '-', '-', '-', 'R', '-', '-',},
	{'-', '-', '-', 'P', '-', '-', '-', '-',},
	{'-', '-', '-', '-', '-', '-', '-', 'b',},
	{'-', '-', '-', '-', '-', 'q', '-', '-',},
	{'-', '-', 'P', '-', '-', '-', '-', '-',},
	{'-', '-', '-', '-', '-', '-', '-', '-',},
	{'P', 'P', 'P', 'P', '-', '-', 'P', 'P',},
	{'R', 'H', 'B', 'Q', 'K', 'B', 'H', 'R',},
	} };

	Game myGame(m, EColor::Black, EState::Playing);

	auto mock = std::make_shared<MockGame>();

	myGame.AddListener(mock);

	EXPECT_CALL(*mock, OnMove()).Times(0);
	EXPECT_THROW(myGame.Move({ 3, 5 }, { 3,6 }), StillCheckException);
	EXPECT_THROW(myGame.Move({ 3, 5 }, { 4,6 }), StillCheckException);
	EXPECT_THROW(myGame.Move({ 2, 7 }, { 3,6 }), StillCheckException);

	myGame.RemoveListener(mock.get());
}


TEST(CheckMateMock, CheckMate1)
{
	CharMatrix m = { {
	{'r', 'h', 'b', 'q', 'k', 'b', 'h', 'r',},
	{'p', 'p', 'p', 'p', '-', 'p', 'p', 'p',},
	{'-', '-', '-', '-', '-', '-', '-', '-',},
	{'-', '-', '-', '-', 'p', '-', '-', '-',},
	{'-', '-', 'P', '-', '-', '-', 'P', '-',},
	{'-', '-', '-', '-', '-', 'P', '-', '-',},
	{'P', 'P', 'P', 'P', 'P', '-', 'P', 'P',},
	{'R', 'H', 'B', 'Q', 'K', 'B', 'H', 'R',},
	} };

	Game myGame(m, EColor::Black, EState::Playing);

	auto mock = std::make_shared<MockGame>();

	myGame.AddListener(mock);

	EXPECT_CALL(*mock, OnGameOver(EOverState::BlackWon));
	EXPECT_CALL(*mock, OnMove());

	myGame.Move({ 0,3 }, { 4,7 });

	myGame.RemoveListener(mock.get());
}

TEST(CheckMock, Check1)
{
	CharMatrix m = { {
	{'r', 'h', 'b', 'q', 'k', 'b', 'h', 'r',},
	{'p', 'p', 'p', 'p', '-', 'p', 'p', 'p',},
	{'-', '-', '-', '-', '-', '-', '-', '-',},
	{'r', '-', '-', '-', '-', '-', '-', '-',},
	{'-', '-', 'P', '-', '-', '-', 'P', '-',},
	{'-', '-', '-', '-', '-', 'P', '-', '-',},
	{'P', 'P', 'P', 'P', '-', '-', 'P', 'P',},
	{'R', 'H', 'B', 'Q', 'K', 'B', 'H', 'R',},
	} };

	Game myGame(m, EColor::Black, EState::Playing);

	auto mock = std::make_shared<MockGame>();

	myGame.AddListener(mock);

	EXPECT_CALL(*mock, OnCheck());
	EXPECT_CALL(*mock, OnMove());

	myGame.Move({ 3,0 }, { 3,4 });

	myGame.RemoveListener(mock.get());
}

TEST(ChoosePieceMock, Choose1)
{
	CharMatrix m = { {
	{'r', 'h', 'b', 'q', 'k', 'b', 'h', '-',},
	{'p', 'p', 'p', 'p', '-', 'p', 'p', 'P',},
	{'-', '-', '-', '-', '-', '-', '-', '-',},
	{'r', '-', '-', '-', '-', '-', '-', '-',},
	{'-', '-', 'P', '-', '-', '-', 'P', '-',},
	{'-', '-', '-', '-', '-', 'P', '-', '-',},
	{'P', 'P', 'P', 'P', '-', '-', 'P', 'P',},
	{'R', 'H', 'B', 'Q', 'K', 'B', 'H', 'R',},
	} };

	Game myGame(m, EColor::White, EState::Playing);

	auto mock = std::make_shared<MockGame>();

	myGame.AddListener(mock);

	EXPECT_CALL(*mock, OnChoosePiece(_));
	EXPECT_CALL(*mock, OnMove());

	myGame.Move({ 1,7 }, { 0,7 });

	myGame.RemoveListener(mock.get());
}

TEST(ChoosePieceMock, Choose2)
{
	CharMatrix m = { {
	{'r', '-', '-', '-', '-', '-', '-', '-',},
	{'-', '-', '-', 'P', '-', 'P', '-', '-',},
	{'-', '-', '-', '-', '-', '-', '-', '-',},
	{'k', '-', '-', '-', '-', '-', '-', '-',},
	{'-', '-', 'P', '-', '-', '-', '-', '-',},
	{'-', '-', '-', '-', '-', '-', '-', '-',},
	{'P', 'P', 'P', 'P', '-', '-', 'P', 'P',},
	{'R', 'H', 'B', 'Q', 'K', 'B', 'H', 'R',},
	} };

	Game myGame(m, EColor::White, EState::Playing);

	auto mock = std::make_shared<MockGame>();

	myGame.AddListener(mock);

	EXPECT_CALL(*mock, OnChoosePiece(_));
	EXPECT_CALL(*mock, OnMove());

	myGame.Move({ 1,3 }, { 0,3 });
	myGame.Move({ 1,5 }, { 0,5 });

	myGame.RemoveListener(mock.get());
}

TEST(ChoosePieceMock, Choose3)
{
	CharMatrix m = { {
	{'k', '-', '-', '-', '-', '-', '-', '-',},
	{'-', '-', '-', 'P', '-', 'R', '-', '-',},
	{'-', '-', '-', '-', '-', '-', '-', '-',},
	{'-', '-', '-', '-', '-', '-', '-', '-',},
	{'-', '-', 'P', '-', '-', '-', '-', '-',},
	{'-', '-', '-', '-', '-', '-', '-', '-',},
	{'P', 'P', 'P', 'P', '-', '-', 'P', 'P',},
	{'R', 'H', 'B', 'Q', 'K', 'B', 'H', 'R',},
	} };

	Game myGame(m, EColor::White, EState::Playing);

	auto mock = std::make_shared<MockGame>();

	myGame.AddListener(mock);

	EXPECT_CALL(*mock, OnChoosePiece(_));
	EXPECT_CALL(*mock, OnMove());
	EXPECT_CALL(*mock, OnGameOver(EOverState::WhiteWon));

	myGame.Move({ 1,3 }, { 0,3 });
	myGame.PromoteTo(EPieceType::Queen);

	myGame.RemoveListener(mock.get());
}

TEST(RestartMock, RestartDefault)
{
	CharMatrix m = { {
	{'r', 'h', 'b', 'q', 'k', 'b', 'h', '-',},
	{'p', 'p', 'p', 'p', '-', 'p', 'p', 'P',},
	{'-', '-', '-', '-', '-', '-', '-', '-',},
	{'r', '-', '-', '-', '-', '-', '-', '-',},
	{'-', '-', 'P', '-', '-', '-', 'P', '-',},
	{'-', '-', '-', '-', '-', 'P', '-', '-',},
	{'P', 'P', 'P', 'P', '-', '-', 'P', 'P',},
	{'R', 'H', 'B', 'Q', 'K', 'B', 'H', 'R',},
	} };

	Game myGame(m, EColor::White, EState::Playing);

	auto mock = std::make_shared<MockGame>();

	myGame.AddListener(mock);

	EXPECT_CALL(*mock, OnRestart);

	myGame.Restart();

	myGame.RemoveListener(mock.get());
}