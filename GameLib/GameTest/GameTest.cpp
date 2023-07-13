#include<iostream>
#include "gtest/gtest.h"
#include "Game.h"

TEST(MoveTest, AllPositions)
{
	Game g;

	EXPECT_EQ(g.Move({ 1,0 }, { 3,0 }), true);
	EXPECT_EQ(g.Move({ 1,1 }, { 2,1 }), true);
	EXPECT_EQ(g.Move({ 1,1 }, { 2,0 }), true);
	EXPECT_EQ(g.Move({ 0,0 }, { 0,4 }), false);
}

int main(int argv, char** argc)
{
	::testing::InitGoogleTest(&argv, argc);
	return RUN_ALL_TESTS();
}