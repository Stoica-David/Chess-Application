#include<iostream>
#include "gtest/gtest.h"
#include "Game.h"

TEST(MoveTest, AllPositions)
{
	Game g;

	EXPECT_EQ(g.Move({ 1,0 }, { 3,0 }), true);
	EXPECT_EQ(g.Move({ 1,1 }, { 2,1 }), true);
	EXPECT_EQ(g.Move({ 1,1 }, { 2,0 }), false);
	EXPECT_EQ(g.Move({ 0,0 }, { 0,4 }), false);
	EXPECT_EQ(g.Move({ 1,7 }, { 2,7 }), true);
	EXPECT_EQ(g.Move({ 1,2 }, { 2,2 }), true);
	EXPECT_EQ(g.Move({ 0,1 }, { 2,2 }), false);
	EXPECT_EQ(g.Move({ 0,2 }, { 2,0 }), true);

	EXPECT_NE(g.m_gameboard.GetGameboard()[3][0], nullptr);
	EXPECT_EQ(g.m_gameboard.GetGameboard()[1][0], nullptr);
	EXPECT_EQ(g.m_gameboard.GetGameboard()[4][7], nullptr);
	EXPECT_EQ(g.m_gameboard.GetGameboard()[3][0]->GetType(), EPieceType::Pawn);
	EXPECT_EQ(g.m_gameboard.GetGameboard()[0][1]->GetType(), EPieceType::Knight);

	g.m_gameboard.printBoard();
}

int main(int argv, char** argc)
{
	::testing::InitGoogleTest(&argv, argc);
	return RUN_ALL_TESTS();
}