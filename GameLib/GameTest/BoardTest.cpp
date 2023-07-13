#include "Board.h"
#include "gtest/gtest.h"

TEST(PositionExistsTest, AllPositions)
{
	Board b;
	EXPECT_EQ(b.PositionExists({ 1, 2 }), true);
	EXPECT_EQ(b.PositionExists({ -3, 2 }), false);
}

TEST(VerifyTheWayTest, PawnTest)
{
	Board b;
	EXPECT_EQ(b.VerifyTheWay({6,0}, {5,0}), true);
	EXPECT_EQ(b.VerifyTheWay({6,0}, {4,0}), true);
	EXPECT_EQ(b.VerifyTheWay({6,0}, {5,1}), true);
	EXPECT_EQ(b.VerifyTheWay({6,0}, {7,0}), false);

	EXPECT_EQ(b.VerifyTheWay({ 1,0 }, { 2,0 }), true);
	EXPECT_EQ(b.VerifyTheWay({ 1,0 }, { 3,0 }), true);
	EXPECT_EQ(b.VerifyTheWay({ 1,0 }, { 2,1 }), true);
	EXPECT_EQ(b.VerifyTheWay({ 1,0 }, { 0,0 }), false);
}

TEST(VerifyTheWayTest, RookTest)
{
	Board b;

	EXPECT_EQ(b.VerifyTheWay({ 0,0 }, { 0,1 }), false);
	EXPECT_EQ(b.VerifyTheWay({ 0,0 }, { 3,0 }), false);
	EXPECT_EQ(b.VerifyTheWay({ 0,7 }, { 0,4 }), false);
	EXPECT_EQ(b.VerifyTheWay({ 0,7 }, { 2,7 }), false);
	EXPECT_EQ(b.VerifyTheWay({ 7,7 }, { 1,7 }), false);
	EXPECT_EQ(b.VerifyTheWay({ 7,7 }, { 3,7 }), false);
	EXPECT_EQ(b.VerifyTheWay({ 7,0 }, { 7,3 }), false);
	EXPECT_EQ(b.VerifyTheWay({ 7,0 }, { 7,5 }), false);
}

int main(int argc, char** argv)
{
	Board b;

	b.printBoard();

	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}