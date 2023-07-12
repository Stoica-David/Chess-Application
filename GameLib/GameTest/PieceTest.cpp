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
protected:
	Piece m_piece;
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

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}