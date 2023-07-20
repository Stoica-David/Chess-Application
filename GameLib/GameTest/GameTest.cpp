#include "gtest/gtest.h"
#include "Game.h"
#include "BoardExceptions.h"
#include "GameExceptions.h"

TEST(MoveTest, RookTest)
{
	Game g;

	EXPECT_NO_THROW(g.Move({ 6,0 }, { 4,0 }));
	EXPECT_NO_THROW(g.Move({ 1,7 }, { 3,7 }));
	EXPECT_NO_THROW(g.Move({ 7,0 }, { 5,0 }));
	EXPECT_NO_THROW(g.Move({ 0,7 }, { 2,7 }));
	EXPECT_NO_THROW(g.Move({ 5,0 }, { 5,1 }));
	EXPECT_NO_THROW(g.Move({ 2,7 }, { 2,6 }));
	EXPECT_NO_THROW(g.Move({ 5,1 }, { 1,1 }));
	EXPECT_NO_THROW(g.Move({ 2,6 }, { 6,6 }));
	EXPECT_THROW(g.Move({ 7,7 }, { 7,6 }), InTheWayException);
	EXPECT_THROW(g.Move({ 0,0 }, { 0,1 }), TurnException);
	EXPECT_THROW(g.Move({ 7,7 }, { 8,1 }), PositionException);
	EXPECT_THROW(g.Move({ 0,0 }, { 8,1 }), PositionException);


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

	EXPECT_THROW(g.Move({ 7, 6 }, { 4, 5 }), MoveException);
	EXPECT_NO_THROW(g.Move({ 7, 6 }, { 5, 5 }));
	EXPECT_NO_THROW(g.Move({ 0, 1 }, { 2, 2 }));
	EXPECT_NO_THROW(g.Move({ 7, 1 }, { 5, 0 }));
	EXPECT_NO_THROW(g.Move({ 0, 6 }, { 2, 7 }));
	EXPECT_NO_THROW(g.Move({ 5, 0 }, { 3, 1 }));
	EXPECT_NO_THROW(g.Move({ 2, 7 }, { 4, 6 }));
	EXPECT_NO_THROW(g.Move({ 3, 1 }, { 1, 0 }));
	EXPECT_NO_THROW(g.Move({ 4, 6 }, { 6, 7 }));
	EXPECT_THROW(g.Move({ 7,1 }, { 6,3 }), DoesntExistException);
	EXPECT_THROW(g.Move({ 0,0 }, { 199,1 }), PositionException);
	EXPECT_THROW(g.Move({ 0,150 }, { 199,1 }), PositionException);
	EXPECT_THROW(g.Move({ 0,-1 }, { 0,1 }), PositionException);

	EXPECT_EQ(g.GetPiece({ 0,6 }), nullptr);
	EXPECT_EQ(g.GetPiece({ 2,7 }), nullptr);
	EXPECT_EQ(g.GetPiece({ 4,6 }), nullptr);
}

TEST(MoveTest, QueenTest)
{
	Game g;

	EXPECT_THROW(g.Move({ 7, 3 }, { 4, 3 }), InTheWayException);
	EXPECT_NO_THROW(g.Move({ 6, 3 }, { 4, 3 }));
	EXPECT_NO_THROW(g.Move({ 1, 3 }, { 3, 3 }));
	EXPECT_NO_THROW(g.Move({ 7, 3 }, { 5, 3 }));
	EXPECT_NO_THROW(g.Move({ 0, 3 }, { 2, 3 }));
	EXPECT_NO_THROW(g.Move({ 5, 3 }, { 1, 7 }));
	EXPECT_NO_THROW(g.Move({ 2, 3 }, { 6, 7 }));
	EXPECT_THROW(g.Move({ 1, 7 }, { 6, 2 }), InTheWayException);
	EXPECT_NO_THROW(g.Move({ 1, 7 }, { 0, 7 }));
	EXPECT_NO_THROW(g.Move({ 6, 7 }, { 7, 7 }));
	EXPECT_THROW(g.Move({ 0, 7 }, { -1, 7 }), PositionException);
}

TEST(MoveTest, PawnMove)
{
	Game g;
	EXPECT_NO_THROW(g.Move({ 6,0 }, { 4,0 }));
	EXPECT_NO_THROW(g.Move({ 1,0 }, { 3,0 }));
	EXPECT_NO_THROW(g.Move({ 6,1 }, { 5,1 }));
	EXPECT_NO_THROW(g.Move({ 1,1 }, { 2,1 }));
	EXPECT_THROW(g.Move({ 1,1 }, { 2,0 }), DoesntExistException);
	EXPECT_NO_THROW(g.Move({ 6,7 }, { 5,7 }));
	EXPECT_NO_THROW(g.Move({ 1,7 }, { 2,7 }));
	EXPECT_NO_THROW(g.Move({ 6,2 }, { 5,2 }));
	EXPECT_NO_THROW(g.Move({ 1,2 }, { 2,2 }));
	EXPECT_THROW(g.Move({ 1,4 }, { 2,3 }), TurnException);
	EXPECT_THROW(g.Move({ 6,0 }, { 5,1 }), DoesntExistException);
	EXPECT_NO_THROW(g.Move({ 6,3 }, { 4,3 }));
	EXPECT_NO_THROW(g.Move({ 1,3 }, { 3,3 }));
	EXPECT_THROW(g.Move({ 6,3 }, { 9,3 }), PositionException);
	EXPECT_THROW(g.Move({ 6,3 }, { 4,4 }), DoesntExistException);
	EXPECT_THROW(g.Move({ 3,0 }, { 2,0 }), TurnException);
}

TEST(MoveTest, KingMove)
{
	Game g;

	EXPECT_THROW(g.Move({ 0,4 }, { 0,3 }), TurnException);
	EXPECT_THROW(g.Move({ 0,4 }, { 0,5 }), TurnException);
	EXPECT_THROW(g.Move({ 0,4 }, { -1,4 }), PositionException);
	EXPECT_THROW(g.Move({ 0,4 }, { 1,3 }), TurnException);
	EXPECT_THROW(g.Move({ 0,4 }, { 1,4 }), TurnException);
	EXPECT_THROW(g.Move({ 0,4 }, { 1,5 }), TurnException);
	EXPECT_NO_THROW(g.Move({ 6,4 }, { 4,4 }));
	EXPECT_NO_THROW(g.Move({ 1,4 }, { 3,4 }));
	EXPECT_THROW(g.Move({ 0,4 }, { 2,4 }), TurnException);
	EXPECT_NO_THROW(g.Move({ 7,4 }, { 6,4 }));
	EXPECT_NO_THROW(g.Move({ 0,4 }, { 1,4 }));
	EXPECT_NO_THROW(g.Move({ 6,4 }, { 5,3 }));
	EXPECT_NO_THROW(g.Move({ 1,4 }, { 2,5 }));
	EXPECT_THROW(g.Move({ 2,5 }, { 2,2 }), TurnException);
	EXPECT_NO_THROW(g.Move({ 5,3 }, { 4,2 }));
	EXPECT_NO_THROW(g.Move({ 2,5 }, { 3,6 }));
}

TEST(MoveTest, BishopMove)
{
	Game g;

	EXPECT_NO_THROW(g.Move({ 6,1 }, { 4,1 }));
	EXPECT_NO_THROW(g.Move({ 1,1 }, { 3,1 }));
	EXPECT_NO_THROW(g.Move({ 7,2 }, { 6,1 }));
	EXPECT_NO_THROW(g.Move({ 0,2 }, { 1,1 }));
	EXPECT_NO_THROW(g.Move({ 6,1 }, { 1,6 }));
	EXPECT_NO_THROW(g.Move({ 1,1 }, { 6,6 }));
	EXPECT_NO_THROW(g.Move({ 6,5 }, { 5,5 }));
	EXPECT_NO_THROW(g.Move({ 1,5 }, { 2,5 }));
	EXPECT_THROW(g.Move({ 6,6 }, { 4,4 }), TurnException);
	EXPECT_THROW(g.Move({ 1,6 }, { 3,4 }), InTheWayException);
	EXPECT_NO_THROW(g.Move({ 1,6 }, { 0,7 }));
	EXPECT_NO_THROW(g.Move({ 6,6 }, { 7,7 }));
	EXPECT_THROW(g.Move({ 6,6 }, { 12,7 }), PositionException);
	EXPECT_THROW(g.Move({ 6,6 }, { 5,6 }), DoesntExistException);
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
	g.Move({ 6, 0 }, { 5, 0 });
	EXPECT_EQ(g.GetTurn(), EColor::Black);
}