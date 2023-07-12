#include<iostream>
#include "gtest/gtest.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "King.h"
#include "Queen.h"
#include "Pawn.h"

class PieceParametricTest : public testing::TestWithParam<std::tuple<Piece, EPieceType, EColor>>
{
};

TEST_P(PieceParametricTest, CreationTest)
{
	Piece p;
	EPieceType pType;
	EColor pColor;

	std::tie(p, pType, pColor) = GetParam();

	EXPECT_EQ(p.GetType(), pType);
	EXPECT_EQ(p.GetColor(), pColor);
}

INSTANTIATE_TEST_SUITE_P(Default, PieceParametricTest, testing::Values(
	std::make_tuple(Rook(EColor::white), EPieceType::Rook, EColor::white),
	std::make_tuple(Bishop(EColor::white), EPieceType::Bishop, EColor::white),
	std::make_tuple(Knight(EColor::white), EPieceType::Knight, EColor::white),
	std::make_tuple(King(EColor::white), EPieceType::King, EColor::white),
	std::make_tuple(Queen(EColor::white), EPieceType::Queen, EColor::white),
	std::make_tuple(Pawn(EColor::white), EPieceType::Pawn, EColor::white),
	std::make_tuple(Rook(EColor::black), EPieceType::Rook, EColor::black),
	std::make_tuple(Bishop(EColor::black), EPieceType::Bishop, EColor::black),
	std::make_tuple(Knight(EColor::black), EPieceType::Knight, EColor::black),
	std::make_tuple(King(EColor::black), EPieceType::King, EColor::black),
	std::make_tuple(Queen(EColor::black), EPieceType::Queen, EColor::black),
	std::make_tuple(Pawn(EColor::black), EPieceType::Pawn, EColor::black)
));

TEST(IsMoveRegularTest, BishopMove)
{
	Bishop b(EColor::white);
	EXPECT_EQ(b.IsMoveRegular(4, 1, 2, 3), true);
	EXPECT_EQ(b.IsMoveRegular(4, 1, 4, 5), false);
	EXPECT_EQ(b.IsMoveRegular(4, 1, 4, 1), false);
}

TEST(IsMoveRegularTest, KingMove)
{
	King k(EColor::black);
	EXPECT_EQ(k.IsMoveRegular(4, 1, 5, 1), true);
	EXPECT_EQ(k.IsMoveRegular(4, 1, 5, 3), false);
	EXPECT_EQ(k.IsMoveRegular(4, 1, 4, 1), false);

}

TEST(IsMoveRegularTest, PawnMove)
{
	Pawn p1(EColor::black), p2(EColor::white);

	EXPECT_EQ(p1.IsMoveRegular(1, 1, 0, 1), false);
	EXPECT_EQ(p1.IsMoveRegular(1, 1, 3, 1), true);
	EXPECT_EQ(p1.IsMoveRegular(1, 1, 2, 1), true);
	EXPECT_EQ(p1.IsMoveRegular(6, 1, 6, 1), false);

	EXPECT_EQ(p2.IsMoveRegular(6, 1, 5, 1), true);
	EXPECT_EQ(p2.IsMoveRegular(6, 1, 4, 1), true);
	EXPECT_EQ(p2.IsMoveRegular(6, 1, 7, 1), false);
	EXPECT_EQ(p2.IsMoveRegular(6, 1, 6, 1), false);

	EXPECT_EQ(p1.IsMoveRegular(2, 7, 3, 7), true);
	EXPECT_EQ(p1.IsMoveRegular(2, 7, 4, 7), false);
	EXPECT_EQ(p1.IsMoveRegular(2, 7, 6, 7), false);

	EXPECT_EQ(p2.IsMoveRegular(5, 7, 4, 7), true);
	EXPECT_EQ(p2.IsMoveRegular(5, 7, 3, 7), false);
	EXPECT_EQ(p2.IsMoveRegular(5, 7, 1, 7), false);

	EXPECT_EQ(p1.IsMoveRegular(1, 3, 2, 2), true);
	EXPECT_EQ(p1.IsMoveRegular(1, 3, 2, 4), true);
	EXPECT_EQ(p1.IsMoveRegular(1, 3, 1, 4), false);

	EXPECT_EQ(p2.IsMoveRegular(4, 5, 3, 4), true);
	EXPECT_EQ(p2.IsMoveRegular(4, 5, 3, 6), true);
	EXPECT_EQ(p2.IsMoveRegular(4, 5, 2, 7), false);
}

TEST(IsMoveRegularTest, RookMove)
{
	Rook r(EColor::black);
	EXPECT_EQ(r.IsMoveRegular(0, 7, 0, 4), true);
	EXPECT_EQ(r.IsMoveRegular(0, 7, 3, 7), true);
	EXPECT_EQ(r.IsMoveRegular(0, 7, 0, 7), false);
	EXPECT_EQ(r.IsMoveRegular(0, 7, 3, 5), false);
}

TEST(IsMoveRegularTest, KnightMove)
{
	Knight Kn(EColor::black);
	EXPECT_EQ(Kn.IsMoveRegular(3, 4, 1, 3), true);
	EXPECT_EQ(Kn.IsMoveRegular(3, 4, 1, 5), true);
	EXPECT_EQ(Kn.IsMoveRegular(3, 4, 2, 2), true);
	EXPECT_EQ(Kn.IsMoveRegular(3, 4, 2, 6), true);
	EXPECT_EQ(Kn.IsMoveRegular(3, 4, 4, 2), true);
	EXPECT_EQ(Kn.IsMoveRegular(3, 4, 4, 6), true);
	EXPECT_EQ(Kn.IsMoveRegular(3, 4, 5, 3), true);
	EXPECT_EQ(Kn.IsMoveRegular(3, 4, 5, 5), true);

	EXPECT_EQ(Kn.IsMoveRegular(3, 4, 3, 4), false);
	EXPECT_EQ(Kn.IsMoveRegular(3, 4, 1, 2), false);
	EXPECT_EQ(Kn.IsMoveRegular(3, 4, 7, 7), false);
}

TEST(IsMoveRegularTest, QueenMove)
{
	Queen Q(EColor::white);
	EXPECT_EQ(Q.IsMoveRegular(2, 5, 0, 5), true);
	EXPECT_EQ(Q.IsMoveRegular(2, 5, 0, 7), true);
	EXPECT_EQ(Q.IsMoveRegular(2, 5, 4, 7), true);
	EXPECT_EQ(Q.IsMoveRegular(2, 5, 0, 7), true);

	EXPECT_EQ(Q.IsMoveRegular(2, 5, 2, 5), false);
	EXPECT_EQ(Q.IsMoveRegular(2, 5, 3, 3), false);
	EXPECT_EQ(Q.IsMoveRegular(2, 5, 7, 7), false);
}


int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}