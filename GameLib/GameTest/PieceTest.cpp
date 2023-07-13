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
	std::make_tuple(Rook(EColor::White), EPieceType::Rook, EColor::White),
	std::make_tuple(Bishop(EColor::White), EPieceType::Bishop, EColor::White),
	std::make_tuple(Knight(EColor::White), EPieceType::Knight, EColor::White),
	std::make_tuple(King(EColor::White), EPieceType::King, EColor::White),
	std::make_tuple(Queen(EColor::White), EPieceType::Queen, EColor::White),
	std::make_tuple(Pawn(EColor::White), EPieceType::Pawn, EColor::White),
	std::make_tuple(Rook(EColor::Black), EPieceType::Rook, EColor::Black),
	std::make_tuple(Bishop(EColor::Black), EPieceType::Bishop, EColor::Black),
	std::make_tuple(Knight(EColor::Black), EPieceType::Knight, EColor::Black),
	std::make_tuple(King(EColor::Black), EPieceType::King, EColor::Black),
	std::make_tuple(Queen(EColor::Black), EPieceType::Queen, EColor::Black),
	std::make_tuple(Pawn(EColor::Black), EPieceType::Pawn, EColor::Black)
));

TEST(IsMoveRegularTest, BishopMove)
{
	Bishop b(EColor::White);
	EXPECT_EQ(b.IsMoveRegular({ 4, 1 }, { 2, 3 }), true);
	EXPECT_EQ(b.IsMoveRegular({ 4, 1 }, { 4, 5 }), false);
	EXPECT_EQ(b.IsMoveRegular({ 4, 1 }, { 4, 1 }), false);
}

TEST(IsMoveRegularTest, KingMove)
{
	King k(EColor::Black);
	EXPECT_EQ(k.IsMoveRegular({ 4, 1 }, { 5, 1 }), true);
	EXPECT_EQ(k.IsMoveRegular({ 4, 1 }, { 5, 3 }), false);
	EXPECT_EQ(k.IsMoveRegular({ 4, 1 }, { 4, 1 }), false);

}

TEST(IsMoveRegularTest, PawnMove)
{
	Pawn p1(EColor::Black), p2(EColor::White);

	EXPECT_EQ(p1.IsMoveRegular({ 1, 1 }, { 0, 1 }), false);
	EXPECT_EQ(p1.IsMoveRegular({ 1, 1 }, { 3, 1 }), true);
	EXPECT_EQ(p1.IsMoveRegular({ 1, 1 }, { 2, 1 }), true);
	EXPECT_EQ(p1.IsMoveRegular({ 6, 1 }, { 6, 1 }), false);

	EXPECT_EQ(p2.IsMoveRegular({ 6, 1 }, { 5, 1 }), true);
	EXPECT_EQ(p2.IsMoveRegular({ 6, 1 }, { 4, 1 }), true);
	EXPECT_EQ(p2.IsMoveRegular({ 6, 1 }, { 7, 1 }), false);
	EXPECT_EQ(p2.IsMoveRegular({ 6, 1 }, { 6, 1 }), false);

	EXPECT_EQ(p1.IsMoveRegular({ 2, 7 }, { 3, 7 }), true);
	EXPECT_EQ(p1.IsMoveRegular({ 2, 7 }, { 4, 7 }), false);
	EXPECT_EQ(p1.IsMoveRegular({ 2, 7 }, { 6, 7 }), false);

	EXPECT_EQ(p2.IsMoveRegular({ 5, 7 }, { 4, 7 }), true);
	EXPECT_EQ(p2.IsMoveRegular({ 5, 7 }, { 3, 7 }), false);
	EXPECT_EQ(p2.IsMoveRegular({ 5, 7 }, { 1, 7 }), false);

	EXPECT_EQ(p1.IsMoveRegular({ 1, 3 }, { 2, 2 }), true);
	EXPECT_EQ(p1.IsMoveRegular({ 1, 3 }, { 2, 4 }), true);
	EXPECT_EQ(p1.IsMoveRegular({ 1, 3 }, { 1, 4 }), false);

	EXPECT_EQ(p2.IsMoveRegular({ 4, 5 }, { 3, 4 }), true);
	EXPECT_EQ(p2.IsMoveRegular({ 4, 5 }, { 3, 6 }), true);
	EXPECT_EQ(p2.IsMoveRegular({ 4, 5 }, { 2, 7 }), false);
}

TEST(IsMoveRegularTest, RookMove)
{
	Rook r(EColor::Black);
	EXPECT_EQ(r.IsMoveRegular({ 0, 7 }, { 0, 4 }), true);
	EXPECT_EQ(r.IsMoveRegular({ 0, 7 }, { 3, 7 }), true);
	EXPECT_EQ(r.IsMoveRegular({ 0, 7 }, { 0, 7 }), false);
	EXPECT_EQ(r.IsMoveRegular({ 0, 7 }, {3, 5}), false);
}

TEST(IsMoveRegularTest, KnightMove)
{
	Knight Kn(EColor::Black);
	EXPECT_EQ(Kn.IsMoveRegular({ 3, 4 }, { 1, 3 }), true);
	EXPECT_EQ(Kn.IsMoveRegular({ 3, 4 }, { 1, 5 }), true);
	EXPECT_EQ(Kn.IsMoveRegular({ 3, 4 }, { 2, 2 }), true);
	EXPECT_EQ(Kn.IsMoveRegular({ 3, 4 }, { 2, 6 }), true);
	EXPECT_EQ(Kn.IsMoveRegular({ 3, 4 }, { 4, 2 }), true);
	EXPECT_EQ(Kn.IsMoveRegular({ 3, 4 }, { 4, 6 }), true);
	EXPECT_EQ(Kn.IsMoveRegular({ 3, 4 }, { 5, 3 }), true);
	EXPECT_EQ(Kn.IsMoveRegular({ 3, 4 }, { 5, 5 }), true);

	EXPECT_EQ(Kn.IsMoveRegular({ 3, 4 }, { 3, 4 }), false);
	EXPECT_EQ(Kn.IsMoveRegular({ 3, 4 }, { 1, 2 }), false);
	EXPECT_EQ(Kn.IsMoveRegular({ 3, 4 }, { 7, 7 }), false);
}

TEST(IsMoveRegularTest, QueenMove)
{
	Queen Q(EColor::White);
	EXPECT_EQ(Q.IsMoveRegular({ 2, 5 }, { 0, 5 }), true);
	EXPECT_EQ(Q.IsMoveRegular({ 2, 5 }, { 0, 7 }), true);
	EXPECT_EQ(Q.IsMoveRegular({ 2, 5 }, { 4, 7 }), true);
	EXPECT_EQ(Q.IsMoveRegular({ 2, 5 }, { 0, 7 }), true);

	EXPECT_EQ(Q.IsMoveRegular({ 2, 5 }, { 2, 5 }), false);
	EXPECT_EQ(Q.IsMoveRegular({ 2, 5 }, { 3, 3 }), false);
	EXPECT_EQ(Q.IsMoveRegular({ 2, 5 }, { 7, 7 }), false);
}

TEST(DeterminePatternTest, RookPattern)
{
	Rook R(EColor::Black);
	PositionList P1 = { { 0,1 }, { 0,2 }, { 0,3 }, { 0,4 } };
	PositionList P2 = { { 1,3 }, { 1,4 }, { 1,5 }, {1,6} };
	PositionList P3 = { { 2,5 }, { 3,5 }, { 4,5 }, {5,5} };
	PositionList P4 = { { 1,0 }, { 2,0 }};

	EXPECT_EQ(R.DeterminePattern({ 0, 0 }, { 0, 4 }), P1);
	EXPECT_EQ(R.DeterminePattern({ 1, 2 }, { 1, 6 }), P2);
	EXPECT_EQ(R.DeterminePattern({ 1, 5 }, { 5, 5 }), P3);
	EXPECT_EQ(R.DeterminePattern({ 0, 0 }, { 2, 0 }), P4);
}

TEST(DeterminePatternTest, BishopPattern)
{
	Bishop B(EColor::Black);
	PositionList P1 = { { 3,5 }, { 2,6} };
	PositionList P2 = { { 3,3 }, { 2,2 }, { 1,1 }, {0,0} };
	PositionList P3 = { { 5,3 }, { 6,2 }, { 7,1} };
	PositionList P4 = { { 5,5 }, { 6,6 } };

	EXPECT_EQ(B.DeterminePattern({ 4, 4 }, { 2, 6 }), P1);
	EXPECT_EQ(B.DeterminePattern({ 4, 4 }, { 0, 0 }), P2);
	EXPECT_EQ(B.DeterminePattern({ 4, 4 }, { 7, 1 }), P3);
	EXPECT_EQ(B.DeterminePattern({ 4, 4 }, { 6, 6 }), P4);
}

TEST(DeterminePatternTest, QueenTest)
{
	Queen Q(EColor::White);

	PositionList P1 = { { 0,1 }, { 0,2 }, { 0,3 }, { 0,4 } };
	PositionList P2 = { { 1,3 }, { 1,4 }, { 1,5 }, {1,6} };
	PositionList P3 = { { 2,5 }, { 3,5 }, { 4,5 }, {5,5} };
	PositionList P4 = { { 1,0 }, { 2,0 } };
	PositionList P5 = { { 3,5 }, { 2,6} };
	PositionList P6 = { { 3,3 }, { 2,2 }, { 1,1 }, {0,0} };
	PositionList P7 = { { 5,3 }, { 6,2 }, { 7,1} };
	PositionList P8 = { { 5,5 }, { 6,6 } };

	EXPECT_EQ(Q.DeterminePattern({ 0, 0 }, { 0, 4 }), P1);
	EXPECT_EQ(Q.DeterminePattern({ 1, 2 }, { 1, 6 }), P2);
	EXPECT_EQ(Q.DeterminePattern({ 1, 5 }, { 5, 5 }), P3);
	EXPECT_EQ(Q.DeterminePattern({ 0, 0 }, { 2, 0 }), P4);
	EXPECT_EQ(Q.DeterminePattern({ 4, 4 }, { 2, 6 }), P5);
	EXPECT_EQ(Q.DeterminePattern({ 4, 4 }, { 0, 0 }), P6);
	EXPECT_EQ(Q.DeterminePattern({ 4, 4 }, { 7, 1 }), P7);
	EXPECT_EQ(Q.DeterminePattern({ 4, 4 }, { 6, 6 }), P8);
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}