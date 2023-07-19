#include "gtest/gtest.h"
#include "Game.h"

TEST(MoveTest, RookTest)
{
	Game g;

	EXPECT_EQ(g.Move({ 6,0 }, { 4,0 }), true);
	EXPECT_EQ(g.Move({ 1,7 }, { 3,7 }), true);
	EXPECT_EQ(g.Move({ 7,0 }, { 5,0 }), true);
	EXPECT_EQ(g.Move({ 0,7 }, { 2,7 }), true);
	EXPECT_EQ(g.Move({ 5,0 }, { 5,1 }), true);
	EXPECT_EQ(g.Move({ 2,7 }, { 2,6 }), true);
	EXPECT_EQ(g.Move({ 5,1 }, { 1,1 }), true);
	EXPECT_EQ(g.Move({ 2,6 }, { 6,6 }), true);
	EXPECT_EQ(g.Move({ 7,7 }, { 7,6 }), false);
	EXPECT_EQ(g.Move({ 0,0 }, { 0,1 }), false);
	EXPECT_EQ(g.Move({ 7,7 }, { 8,1 }), false);
	EXPECT_EQ(g.Move({ 0,0 }, { 8,1 }), false);

	EXPECT_EQ(g.GetPiece({ 1,7 }), nullptr);
	EXPECT_EQ(g.GetPiece({ 0,7 }), nullptr);
	EXPECT_EQ(g.GetPiece({ 2,7 }), nullptr);
	EXPECT_EQ(g.GetPiece({ 2,6 }), nullptr);
	EXPECT_EQ(g.GetPiece({ 6,6 })->GetType(), EPieceType::Rook);
	EXPECT_EQ(g.GetPiece({ 0,0 })->GetType(), EPieceType::Rook);
	EXPECT_EQ(g.GetPiece({ 0,1 })->GetType(), EPieceType::Knight);
}

TEST(MoveTest, KnightTest)
{
	Game g;

	EXPECT_EQ(g.Move({ 7, 6 }, { 4, 5 }), false);
	EXPECT_EQ(g.Move({ 7, 6 }, { 5, 5 }), true);
	EXPECT_EQ(g.Move({ 0, 1 }, { 2, 2 }), true);
	EXPECT_EQ(g.Move({ 7, 1 }, { 5, 0 }), true);
	EXPECT_EQ(g.Move({ 0, 6 }, { 2, 7 }), true);
	EXPECT_EQ(g.Move({ 5, 0 }, { 3, 1 }), true);
	EXPECT_EQ(g.Move({ 2, 7 }, { 4, 6 }), true);
	EXPECT_EQ(g.Move({ 3, 1 }, { 1, 0 }), true);
	EXPECT_EQ(g.Move({ 4, 6 }, { 6, 7 }), true);
	EXPECT_EQ(g.Move({ 7,1 }, { 6,3 }), false);
	EXPECT_EQ(g.Move({ 0,0 }, { 199,1 }), false);
	EXPECT_EQ(g.Move({ 0,150 }, { 199,1 }), false);
	EXPECT_EQ(g.Move({ 0,-1 }, { 0,1 }), false);

	EXPECT_EQ(g.GetPiece({ 0,6 }), nullptr);
	EXPECT_EQ(g.GetPiece({ 2,7 }), nullptr);
	EXPECT_EQ(g.GetPiece({ 4,6 }), nullptr);
}

TEST(MoveTest, QueenTest)
{
	Game g;

	EXPECT_EQ(g.Move({ 7, 3 }, { 4, 3 }), false);
	EXPECT_EQ(g.Move({ 6, 3 }, { 4, 3 }), true);
	EXPECT_EQ(g.Move({ 1, 3 }, { 3, 3 }), true);
	EXPECT_EQ(g.Move({ 7, 3 }, { 5, 3 }), true);
	EXPECT_EQ(g.Move({ 0, 3 }, { 2, 3 }), true);
	EXPECT_EQ(g.Move({ 5, 3 }, { 1, 7 }), true);
	EXPECT_EQ(g.Move({ 2, 3 }, { 6, 7 }), true);
	EXPECT_EQ(g.Move({ 1, 7 }, { 6, 2 }), false);
	EXPECT_EQ(g.Move({ 1, 7 }, { 0, 7 }), true);
	EXPECT_EQ(g.Move({ 6, 7 }, { 7, 7 }), true);
	EXPECT_EQ(g.Move({ 0, 7 }, { -1, 7 }), false);
}

TEST(MoveTest, PawnMove)
{
	Game g;
	EXPECT_EQ(g.Move({ 6,0 }, { 4,0 }), true);
	EXPECT_EQ(g.Move({ 1,0 }, { 3,0 }), true);
	EXPECT_EQ(g.Move({ 6,1 }, { 5,1 }), true);
	EXPECT_EQ(g.Move({ 1,1 }, { 2,1 }), true);
	EXPECT_EQ(g.Move({ 1,1 }, { 2,0 }), false);
	EXPECT_EQ(g.Move({ 6,7 }, { 5,7 }), true);
	EXPECT_EQ(g.Move({ 1,7 }, { 2,7 }), true);
	EXPECT_EQ(g.Move({ 6,2 }, { 5,2 }), true);
	EXPECT_EQ(g.Move({ 1,2 }, { 2,2 }), true);
	EXPECT_EQ(g.Move({ 1,4 }, { 2,3 }), false);
	EXPECT_EQ(g.Move({ 6,0 }, { 5,1 }), false);
	EXPECT_EQ(g.Move({ 6,3 }, { 4,3 }), true);
	EXPECT_EQ(g.Move({ 1,3 }, { 3,3 }), true);
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
	EXPECT_EQ(g.Move({ 6,4 }, { 4,4 }), true);
	EXPECT_EQ(g.Move({ 1,4 }, { 3,4 }), true);
	EXPECT_EQ(g.Move({ 0,4 }, { 2,4 }), false);
	EXPECT_EQ(g.Move({ 7,4 }, { 6,4 }), true);
	EXPECT_EQ(g.Move({ 0,4 }, { 1,4 }), true);
	EXPECT_EQ(g.Move({ 6,4 }, { 5,3 }), true);
	EXPECT_EQ(g.Move({ 1,4 }, { 2,5 }), true);
	EXPECT_EQ(g.Move({ 2,5 }, { 2,2 }), false);
	EXPECT_EQ(g.Move({ 5,3 }, { 4,2 }), true);
	EXPECT_EQ(g.Move({ 2,5 }, { 3,6 }), true);
}

TEST(MoveTest, BishopMove)
{
	Game g;

	EXPECT_EQ(g.Move({ 6,1 }, { 4,1 }), true);
	EXPECT_EQ(g.Move({ 1,1 }, { 3,1 }), true);
	EXPECT_EQ(g.Move({ 7,2 }, { 6,1 }), true);
	EXPECT_EQ(g.Move({ 0,2 }, { 1,1 }), true);
	EXPECT_EQ(g.Move({ 6,1 }, { 1,6 }), true);
	EXPECT_EQ(g.Move({ 1,1 }, { 6,6 }), true);
	EXPECT_EQ(g.Move({ 6,5 }, { 5,5 }), true);
	EXPECT_EQ(g.Move({ 1,5 }, { 2,5 }), true);
	EXPECT_EQ(g.Move({ 6,6 }, { 4,4 }), false);
	EXPECT_EQ(g.Move({ 1,6 }, { 3,4 }), false);
	EXPECT_EQ(g.Move({ 1,6 }, { 0,7 }), true);
	EXPECT_EQ(g.Move({ 6,6 }, { 7,7 }), true);
	EXPECT_EQ(g.Move({ 6,6 }, { 12,7 }), false);
	EXPECT_EQ(g.Move({ 6,6 }, { 5,6 }), false);
}

TEST(IsOverTest, RookCheckmate)
{
	PiecePairVector v = {
		{{0, 0}, Piece::Produce(EPieceType::King, EColor::White)},
		{{7, 0}, Piece::Produce(EPieceType::Rook, EColor::Black)},
		{{7, 1}, Piece::Produce(EPieceType::Rook, EColor::Black)},
	};
	Board b(v);

	Game g(b);

	EXPECT_EQ(g.IsOver(), true);
}


TEST(IsOverTest, KingVKing)
{
	PiecePairVector v = {
		{{4, 0}, Piece::Produce(EPieceType::King, EColor::White)},
		{{1, 0}, Piece::Produce(EPieceType::King, EColor::Black)},
	};
	Board b(v);

	Game g(b);

	EXPECT_EQ(g.IsOver(), true);
}

TEST(IsOverTest, KingVKingKnight)
{
	PiecePairVector v = {
		{{4, 0}, Piece::Produce(EPieceType::King, EColor::White)},
		{{1, 0}, Piece::Produce(EPieceType::King, EColor::Black)},
		{{2, 7}, Piece::Produce(EPieceType::Knight, EColor::Black)},
	};
	Board b(v);

	Game g(b);

	EXPECT_EQ(g.IsOver(), true);
}

TEST(IsOverTest, KingVKingBishop)
{
	PiecePairVector v = {
		{{4, 0}, Piece::Produce(EPieceType::King, EColor::White)},
		{{1, 0}, Piece::Produce(EPieceType::King, EColor::Black)},
		{{2, 7}, Piece::Produce(EPieceType::Bishop, EColor::Black)},
	};
	Board b(v);

	Game g(b);

	EXPECT_EQ(g.IsOver(), true);
}

TEST(IsOverTest, KingBishopVKingBishop)
{
	PiecePairVector v = {
		{{4, 0}, Piece::Produce(EPieceType::King, EColor::White)},
		{{1, 0}, Piece::Produce(EPieceType::King, EColor::Black)},
		{{2, 7}, Piece::Produce(EPieceType::Bishop, EColor::Black)},
		{{5, 2}, Piece::Produce(EPieceType::Bishop, EColor::White)},
	};
	Board b(v);

	Game g(b);

	EXPECT_EQ(g.IsOver(), true);
}

TEST(IsOverTest, DRookCheckMate)
{
	PiecePairVector v = {
		{{4, 0}, Piece::Produce(EPieceType::King, EColor::White)},
		{{7, 0}, Piece::Produce(EPieceType::Rook, EColor::Black)},
		{{7, 1}, Piece::Produce(EPieceType::Rook, EColor::Black)},
		{{5, 0}, Piece::Produce(EPieceType::Rook, EColor::White)},
		{{7, 7}, Piece::Produce(EPieceType::King, EColor::Black)}
	};
	Board b(v);

	Game g(b);

	EXPECT_EQ(g.IsOver(), false);
}

TEST(IsOverTest, FoolMate)
{
	Game g;

	g.Move({ 6, 5 }, { 5, 5 });
	g.Move({ 1, 4 }, { 3, 4 });
	g.Move({ 6, 6 }, { 4, 6 });
	g.Move({ 0, 3 }, { 4, 7 });

	EXPECT_EQ(g.IsOver(), true);
}

TEST(GetTurnTest, Normal)
{
	Game g;

	EXPECT_EQ(g.GetTurn(), EColor::White);
	g.Move({6, 0}, {5, 0});
	EXPECT_EQ(g.GetTurn(), EColor::Black);
}

int main(int argv, char** argc)
{
	::testing::InitGoogleTest(&argv, argc);
	return RUN_ALL_TESTS();
}