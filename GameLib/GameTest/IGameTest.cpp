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
		myStatus = myInstance->GetStatus();
	}

	void TearDown() override
	{
	}

	IGamePtr myInstance;
	const IGameStatus* myStatus;
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

TEST_F(IGameTest, RestartTest)
{
	myInstance->Restart();

	EXPECT_EQ(myStatus->GetTurn(), EColor::White);
	EXPECT_EQ(myStatus->GetPieceInfo({ 6,0 })->GetColor(), EColor::White);
	EXPECT_EQ(myStatus->GetPieceInfo({ 6,0 })->GetType(), EPieceType::Pawn);
	EXPECT_EQ(myStatus->GetPieceInfo({ 1,0 })->GetColor(), EColor::Black);
	EXPECT_EQ(myStatus->GetPieceInfo({ 1,0 })->GetType(), EPieceType::Pawn);
	EXPECT_EQ(myStatus->GetPieceInfo({ 2,0 }), nullptr);
}

TEST_F(IGameTest, ProposeDrawTest)
{
	EXPECT_EQ(myStatus->IsDrawProposed(), false);
	EXPECT_NO_THROW(myInstance->ProposeDraw());
	EXPECT_EQ(myStatus->IsDrawProposed(), true);
}

TEST_F(IGameTest, DrawResponseTest1)
{
	EXPECT_NO_THROW(myInstance->DrawResponse(false));
	EXPECT_EQ(myStatus->IsDraw(), false);
}

TEST_F(IGameTest, DrawResponseTest2)
{
	EXPECT_NO_THROW(myInstance->DrawResponse(true));
	EXPECT_EQ(myStatus->IsDraw(), true);
	EXPECT_EQ(myStatus->IsOver(), true);
}

TEST_F(IGameTest, PromoteToTest1)
{
	EXPECT_THROW(myInstance->PromoteTo(EPieceType::Queen), PromoteException);
	EXPECT_THROW(myInstance->PromoteTo(EPieceType::Bishop), PromoteException);
	EXPECT_THROW(myInstance->PromoteTo(EPieceType::Knight), PromoteException);
	EXPECT_THROW(myInstance->PromoteTo(EPieceType::Rook), PromoteException);
}

TEST_F(IGameTest, PromoteToTest2)
{
	EXPECT_NO_THROW(myInstance->Move({6,6}, {4,6}));
	EXPECT_NO_THROW(myInstance->Move({1,7}, {3,7}));
	EXPECT_NO_THROW(myInstance->Move({4,6}, {3,7}));
	EXPECT_NO_THROW(myInstance->Move({0,7}, {2,7}));
	EXPECT_NO_THROW(myInstance->Move({6,7}, {5,7}));
	EXPECT_NO_THROW(myInstance->Move({2,7}, {2,3}));
	EXPECT_NO_THROW(myInstance->Move({3,7}, {2,7}));
	EXPECT_NO_THROW(myInstance->Move({1,0}, {2,0}));
	EXPECT_NO_THROW(myInstance->Move({2,7}, {1,7}));
	EXPECT_NO_THROW(myInstance->Move({2,0}, {3,0}));
	EXPECT_NO_THROW(myInstance->Move({1,7}, {0,7}));

	EXPECT_EQ(myStatus->IsPromoting(), true);
	EXPECT_NO_THROW(myInstance->PromoteTo(EPieceType::Queen));

	EXPECT_EQ(myStatus->GetPieceInfo({0,7})->GetColor(), EColor::White);
	EXPECT_EQ(myStatus->GetPieceInfo({0,7})->GetType(), EPieceType::Queen);
	EXPECT_EQ(myStatus->GetPieceInfo({2,3})->GetColor(), EColor::Black);
	EXPECT_EQ(myStatus->GetPieceInfo({2,3})->GetType(), EPieceType::Rook);
}

TEST_F(IGameTest, IsOverTest)
{
	EXPECT_EQ(myStatus->IsCheck(), false);

	EXPECT_NO_THROW(myInstance->Move({ 6,5 }, { 5,5 }));
	EXPECT_NO_THROW(myInstance->Move({ 1,4 }, { 2,4 }));
	
	EXPECT_EQ(myStatus->IsCheck(), false);
	EXPECT_EQ(myStatus->IsOver(), false);
	
	EXPECT_NO_THROW(myInstance->Move({ 6,6 }, { 4,6 }));
	EXPECT_NO_THROW(myInstance->Move({ 0,3 }, { 4,7 }));

	EXPECT_EQ(myStatus->IsOver(), true);
}

TEST_F(IGameTest, IsCheckTest)
{
	EXPECT_NO_THROW(myInstance->Move({ 6,3 }, { 5,3 }));
	EXPECT_NO_THROW(myInstance->Move({ 1,2 }, { 2,2 }));
	EXPECT_NO_THROW(myInstance->Move({ 6,4 }, { 4,4 }));
	EXPECT_NO_THROW(myInstance->Move({ 0,3 }, { 3,0 }));

	EXPECT_EQ(myStatus->IsCheck(), true);
	EXPECT_EQ(myStatus->IsOver(), false);
}

TEST_F(IGameTest, IsFrozenTest)
{
	EXPECT_NO_THROW(myInstance->Move({ 6,3 }, { 5,3 }));
	EXPECT_NO_THROW(myInstance->Move({ 1,2 }, { 2,2 }));
	EXPECT_NO_THROW(myInstance->Move({ 6,4 }, { 4,4 }));
	EXPECT_NO_THROW(myInstance->Move({ 0,3 }, { 3,0 }));

	EXPECT_NO_THROW(myInstance->ShowConfiguration(1));
	EXPECT_THROW(myInstance->ShowConfiguration(100), ChessException);

	EXPECT_EQ(myStatus->IsFrozen(), true);

	EXPECT_NO_THROW(myInstance->ShowConfiguration(3));
	
	EXPECT_EQ(myStatus->IsFrozen(), false);
}

TEST_F(IGameTest, GetTurnTest)
{
	EXPECT_EQ(myStatus->GetTurn(), EColor::White);

	EXPECT_NO_THROW(myInstance->Move({ 6,0 }, { 4, 0 }));

	EXPECT_EQ(myStatus->GetTurn(), EColor::Black);

	EXPECT_THROW(myInstance->Move({ 4,0 }, { 3,0 }), TurnException);

	EXPECT_EQ(myStatus->GetTurn(), EColor::Black);
}

TEST_F(IGameTest, GetMovesPawn)
{
	PositionList wpawnMoves = { {5,0}, {4,0} };
	PositionList bpawnMoves = { {2,0}, {3,0} };

	EXPECT_EQ(myStatus->GetMoves({ 6,0 }), wpawnMoves);
	EXPECT_EQ(myStatus->GetMoves({ 1,0 }), bpawnMoves);
}

TEST_F(IGameTest, GetMovesRook)
{
	EXPECT_EQ(myStatus->GetMoves({ 7,0 }), PositionList());
	EXPECT_EQ(myStatus->GetMoves({ 0,0 }), PositionList());

	EXPECT_NO_THROW(myInstance->Move({ 6,0 }, { 4,0 }));
	EXPECT_NO_THROW(myInstance->Move({ 1,0 }, { 2,0 }));

	PositionList wRookMoves = { {6,0}, {5,0} };
	PositionList bRookMoves = { {1,0} };

	EXPECT_EQ(myStatus->GetMoves({ 7,0 }), wRookMoves);
	EXPECT_EQ(myStatus->GetMoves({ 0,0 }), bRookMoves);
}

TEST_F(IGameTest, GetMovesKnight)
{
	PositionList wKnighMoves = { {5,0}, {5,2} };
	PositionList bKnighMoves = { {2,2}, {2,0} };

	EXPECT_EQ(myStatus->GetMoves({ 7,1 }), wKnighMoves);
	EXPECT_EQ(myStatus->GetMoves({ 0,1 }), bKnighMoves);

	EXPECT_NO_THROW(myInstance->Move({6,0}, {5,0}));
	EXPECT_NO_THROW(myInstance->Move({1,0}, {2,0}));
	EXPECT_NO_THROW(myInstance->Move({6,2}, {5,2}));
	EXPECT_NO_THROW(myInstance->Move({1,2}, {2,2}));

	EXPECT_EQ(myStatus->GetMoves({ 7,1 }), PositionList());
	EXPECT_EQ(myStatus->GetMoves({ 0,1 }), PositionList());
}

TEST_F(IGameTest, GetMovesBishop)
{
	EXPECT_EQ(myStatus->GetMoves({ 7,2 }), PositionList());
	EXPECT_EQ(myStatus->GetMoves({ 0,2 }), PositionList());

	EXPECT_NO_THROW(myInstance->Move({6,1}, {5,1}));
	EXPECT_NO_THROW(myInstance->Move({1,3}, {2,3}));

	PositionList wBishopMoves = { {6,1}, {5,0} };
	PositionList bBishopMoves = { {1,3}, {2,4}, {3,5}, {4,6}, {5,7} };

	EXPECT_EQ(myStatus->GetMoves({ 7,2 }), wBishopMoves);
	EXPECT_EQ(myStatus->GetMoves({ 0,2 }), bBishopMoves);
}

TEST_F(IGameTest, GetMovesQueen)
{
	EXPECT_EQ(myStatus->GetMoves({ 7,3 }), PositionList());
	EXPECT_EQ(myStatus->GetMoves({ 0,3 }), PositionList());

	EXPECT_NO_THROW(myInstance->Move({6,3}, {5,3}));
	EXPECT_NO_THROW(myInstance->Move({1,2}, {3,2}));
	EXPECT_NO_THROW(myInstance->Move({7,2}, {5,4}));

	PositionList wQueenMoves = { {6,3}, {7,2} };
	PositionList bQueenMoves = { {1,2}, {2,1}, {3,0} };

	EXPECT_EQ(myStatus->GetMoves({ 7,3 }), wQueenMoves);
	EXPECT_EQ(myStatus->GetMoves({ 0,3 }), bQueenMoves);
}

TEST_F(IGameTest, GetMovesKing1)
{
	EXPECT_EQ(myStatus->GetMoves({ 7,4 }), PositionList());
	EXPECT_EQ(myStatus->GetMoves({ 0,4 }), PositionList());

	EXPECT_NO_THROW(myInstance->Move({6,4}, {5,4}));
	EXPECT_NO_THROW(myInstance->Move({1,5}, {2,5}));
	EXPECT_NO_THROW(myInstance->Move({6,3}, {5,3}));

	PositionList wKingMoves = { {6,3}, {6,4} };
	PositionList bKingMoves = { {1,5} };

	EXPECT_EQ(myStatus->GetMoves({7,4}), wKingMoves);
	EXPECT_EQ(myStatus->GetMoves({0,4}), bKingMoves);
}

TEST_F(IGameTest, GetHistoryTest)
{
	EXPECT_EQ(myStatus->GetHistory(), MoveVector());

	EXPECT_NO_THROW(myInstance->Move({6,5}, {4,5}));
	EXPECT_NO_THROW(myInstance->Move({1,1}, {2,1}));
	EXPECT_THROW(myInstance->Move({6,0}, {2,0}), MoveException);

	MoveVector currMoves = { {{6,5}, {4,5}}, {{1,1}, {2,1}} };

	EXPECT_EQ(myStatus->GetHistory(), currMoves);
}

