#include "Board.h"
#include "gtest/gtest.h"

TEST(PositionExistsTest, AllPositions)
{
	Board b;
	EXPECT_EQ(b.positionExists(1, 2), true);
	EXPECT_EQ(b.positionExists(-3, 2), false);
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}