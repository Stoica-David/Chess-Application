#include<iostream>
#include "gtest/gtest.h"
#include "Game.h"

TEST(MoveTest, RookTest)
{
	Game g;

	EXPECT_EQ(g.Move({ 1,7 }, { 3,7 }), true);
	EXPECT_EQ(g.Move({ 0,7 }, { 2,7 }), true);
	EXPECT_EQ(g.Move({ 2,7 }, { 2,6 }), true);
	EXPECT_EQ(g.Move({ 2,6 }, { 6,6 }), true);
	EXPECT_EQ(g.Move({ 0,0 }, { 0,1 }), false);
	EXPECT_EQ(g.Move({ 0,0 }, { 8,1 }), false);

	EXPECT_EQ(g.m_gameboard.GetGameboard()[1][7], nullptr);
	EXPECT_EQ(g.m_gameboard.GetGameboard()[0][7], nullptr);
	EXPECT_EQ(g.m_gameboard.GetGameboard()[2][7], nullptr);
	EXPECT_EQ(g.m_gameboard.GetGameboard()[2][6], nullptr);
	EXPECT_EQ(g.m_gameboard.GetGameboard()[6][6]->GetType(), EPieceType::Rook);
	EXPECT_EQ(g.m_gameboard.GetGameboard()[0][0]->GetType(), EPieceType::Rook);
	EXPECT_EQ(g.m_gameboard.GetGameboard()[0][1]->GetType(), EPieceType::Knight);
}

TEST(MoveTest, KnightTest)
{
	Game g;

	EXPECT_EQ(g.Move({ 7, 6 }, { 4, 5 }), false);
	EXPECT_EQ(g.Move({ 0, 6 }, { 2, 7 }), true);
	EXPECT_EQ(g.Move({ 2, 7 }, { 4, 6 }), true);
	EXPECT_EQ(g.Move({ 4, 6 }, { 6, 7 }), true);
	EXPECT_EQ(g.Move({ 7,1 }, { 6,3 }), false);
	EXPECT_EQ(g.Move({ 7,1 }, { 5,0 }), true);
	EXPECT_EQ(g.Move({ 5,0 }, { 3,1 }), true);
	EXPECT_EQ(g.Move({ 3,1 }, { 1,0 }), true);
	EXPECT_EQ(g.Move({ 1,0 }, { 2,2 }), true);
	EXPECT_EQ(g.Move({ 2,2 }, { 1,4 }), true);
	EXPECT_EQ(g.Move({ 0,0 }, { 199,1 }), false);
	EXPECT_EQ(g.Move({ 0,150 }, { 199,1 }), false);
	EXPECT_EQ(g.Move({ 0,-1 }, { 0,1 }), false);

	EXPECT_EQ(g.m_gameboard.GetGameboard()[0][6], nullptr);
	EXPECT_EQ(g.m_gameboard.GetGameboard()[2][7], nullptr);
	EXPECT_EQ(g.m_gameboard.GetGameboard()[4][6], nullptr);
}

TEST(MoveTest, QueenTest)
{
	Game g;

	EXPECT_EQ(g.Move({ 7, 3 }, { 4, 3 }), false);
	EXPECT_EQ(g.Move({ 6, 3 }, { 4, 3 }), true);
	EXPECT_EQ(g.Move({ 7, 3 }, { 5, 3 }), true);
	EXPECT_EQ(g.Move({ 5, 3 }, { 1, 7 }), true);
	EXPECT_EQ(g.Move({ 1, 7 }, { 6, 2 }), false);
	EXPECT_EQ(g.Move({ 1, 7 }, { 6, 7 }), false);
	EXPECT_EQ(g.Move({ 1, 7 }, { 0, 7 }), true);
	EXPECT_EQ(g.Move({ 0, 7 }, { -1, 7 }), false);
	g.m_gameboard.printBoard();
}

TEST(MoveTest, PawnMove)
{
	Game g;

	EXPECT_EQ(g.Move({ 1,0 }, { 3,0 }), true);
	EXPECT_EQ(g.Move({ 1,1 }, { 2,1 }), true);
	EXPECT_EQ(g.Move({ 1,1 }, { 2,0 }), false);
	EXPECT_EQ(g.Move({ 1,7 }, { 2,7 }), true);
	EXPECT_EQ(g.Move({ 1,2 }, { 2,2 }), true);
	EXPECT_EQ(g.Move({ 1,4 }, { 2,3 }), false);
	EXPECT_EQ(g.Move({ 6,0 }, { 5,1 }), false);
	EXPECT_EQ(g.Move({ 6,0 }, { 5,0 }), true);
	EXPECT_EQ(g.Move({ 6,3 }, { 4,3 }), true);
	EXPECT_EQ(g.Move({ 6,3 }, { 9,3 }), false);
	EXPECT_EQ(g.Move({ 6,3 }, { 4,4 }), false);
	EXPECT_EQ(g.Move({ 3,0 }, { 2,0 }), false);
}

TEST(MoveTest, KingMove)
{
	Game g;

	EXPECT_EQ(g.Move({ 0,4 }, { 0,3 }), false);
	EXPECT_EQ(g.Move({ 0,4 }, { 0,5 }), false);
	EXPECT_EQ(g.Move({ 0,4 }, { -1,4 }), false);
	EXPECT_EQ(g.Move({ 0,4 }, { 1,3 }), false);
	EXPECT_EQ(g.Move({ 0,4 }, { 1,4 }), false);
	EXPECT_EQ(g.Move({ 0,4 }, { 1,5 }), false);
	EXPECT_EQ(g.Move({ 1,4 }, { 3,4 }), true);
	EXPECT_EQ(g.Move({ 0,4 }, { 2,4 }), false);
	EXPECT_EQ(g.Move({ 0,4 }, { 1,4 }), true);
	EXPECT_EQ(g.Move({ 1,4 }, { 2,5 }), true);
	EXPECT_EQ(g.Move({ 2,5 }, { 2,2 }), false);
	EXPECT_EQ(g.Move({ 2,5 }, { 3,6 }), true);
}

int main(int argv, char** argc)
{
	::testing::InitGoogleTest(&argv, argc);
	return RUN_ALL_TESTS();
}