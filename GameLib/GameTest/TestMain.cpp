#include<iostream>
#include "gtest/gtest.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"

class PieceParametricTest : public testing::TestWithParam<std::pair<EPieceType, EPieceType>>
{
protected:
	Piece m_piece;
};

TEST_P(PieceParametricTest, CreationTest)
{
	EPieceType E1, E2;

	std::tie(E1, E2) = GetParam();

	EXPECT_EQ(E1, E2);
}

Rook r;
Bishop b;
Knight k;

INSTANTIATE_TEST_SUITE_P(Default, PieceParametricTest, testing::Values(
std::make_pair(r.GetType(), EPieceType::Rook),
std::make_pair(b.GetType(), EPieceType::Bishop),
std::make_pair(k.GetType(), EPieceType::Knight)
));

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}