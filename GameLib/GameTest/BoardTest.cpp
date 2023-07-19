//#include "Board.h"
//#include "gtest/gtest.h"
//
//TEST(PositionExistsTest, AllPositions)
//{
//	Board b;
//	EXPECT_EQ(b.PositionExists({ 1, 2 }), true);
//	EXPECT_EQ(b.PositionExists({ -3, 2 }), false);
//}
//
//TEST(VerifyTheWayTest, PawnTest)
//{
//	Board b;
//	EXPECT_EQ(b.VerifyTheWay({ 6,0 }, { 5,0 }), true);
//	EXPECT_EQ(b.VerifyTheWay({ 6,0 }, { 4,0 }), true);
//	EXPECT_EQ(b.VerifyTheWay({ 6,0 }, { 5,1 }), true);
//	EXPECT_EQ(b.VerifyTheWay({ 6,0 }, { 7,0 }), false);
//
//	EXPECT_EQ(b.VerifyTheWay({ 1,0 }, { 2,0 }), true);
//	EXPECT_EQ(b.VerifyTheWay({ 1,0 }, { 3,0 }), true);
//	EXPECT_EQ(b.VerifyTheWay({ 1,0 }, { 2,1 }), true);
//	EXPECT_EQ(b.VerifyTheWay({ 1,0 }, { 0,0 }), false);
//}
//
//TEST(VerifyTheWayTest, RookTest)
//{
//	Board b;
//	EXPECT_EQ(b.VerifyTheWay({ 0,0 }, { 0,1 }), false);
//	EXPECT_EQ(b.VerifyTheWay({ 0,0 }, { 3,0 }), false);
//	EXPECT_EQ(b.VerifyTheWay({ 0,7 }, { 0,4 }), false);
//	EXPECT_EQ(b.VerifyTheWay({ 0,7 }, { 2,7 }), false);
//	EXPECT_EQ(b.VerifyTheWay({ 7,7 }, { 1,7 }), false);
//	EXPECT_EQ(b.VerifyTheWay({ 7,7 }, { 3,7 }), false);
//	EXPECT_EQ(b.VerifyTheWay({ 7,0 }, { 7,3 }), false);
//	EXPECT_EQ(b.VerifyTheWay({ 7,0 }, { 7,5 }), false);
//}
//
//TEST(VerifyTheWatTest, QueenTest)
//{
//	Board b;
//	//white
//	EXPECT_EQ(b.VerifyTheWay({ 7, 3 }, { 6, 3 }), false);
//	EXPECT_EQ(b.VerifyTheWay({ 7, 3 }, { 7, 0 }), false);
//	EXPECT_EQ(b.VerifyTheWay({ 7, 3 }, { 7, 7 }), false);
//	EXPECT_EQ(b.VerifyTheWay({ 7, 3 }, { 4, 0 }), false);
//	EXPECT_EQ(b.VerifyTheWay({ 7, 3 }, { 4, 7 }), false);
//	EXPECT_EQ(b.VerifyTheWay({ 7, 3 }, { 5, 4 }), false);
//
//	//black
//	EXPECT_EQ(b.VerifyTheWay({ 0, 3 }, { 0, 0 }), false);
//	EXPECT_EQ(b.VerifyTheWay({ 0, 3 }, { 0, 7 }), false);
//	EXPECT_EQ(b.VerifyTheWay({ 0, 3 }, { 5, 3 }), false);
//	EXPECT_EQ(b.VerifyTheWay({ 0, 3 }, { 3, 0 }), false);
//	EXPECT_EQ(b.VerifyTheWay({ 0, 3 }, { 4, 7 }), false);
//
//
//}
//
//TEST(VerifyTheWatTest, KnightTest)
//{
//	Board b;
//
//	//white
//	EXPECT_EQ(b.VerifyTheWay({ 7, 4 }, { 7, 3 }), false);
//	EXPECT_EQ(b.VerifyTheWay({ 7, 4 }, { 7, 4 }), false);
//	EXPECT_EQ(b.VerifyTheWay({ 7, 4 }, { 6, 4 }), false);
//	EXPECT_EQ(b.VerifyTheWay({ 7, 4 }, { 6, 3 }), false);
//	EXPECT_EQ(b.VerifyTheWay({ 7, 4 }, { 6, 5 }), false);
//
//	//black
//	EXPECT_EQ(b.VerifyTheWay({ 0, 4 }, { 0, 3 }), false);
//	EXPECT_EQ(b.VerifyTheWay({ 0, 4 }, { 0, 5 }), false);
//	EXPECT_EQ(b.VerifyTheWay({ 0, 4 }, { 1, 3 }), false);
//	EXPECT_EQ(b.VerifyTheWay({ 0, 4 }, { 1, 4 }), false);
//	EXPECT_EQ(b.VerifyTheWay({ 0, 4 }, { 1, 5 }), false);
//}
//
//TEST(VerifyTheWayTest, BishopTest)
//{
//	Board b;
//	EXPECT_EQ(b.VerifyTheWay({ 0,2 }, { 1,1 }), false);
//	EXPECT_EQ(b.VerifyTheWay({ 0,2 }, { 3,4 }), false);
//	EXPECT_EQ(b.VerifyTheWay({ 0,5 }, { 3,2 }), false);
//	EXPECT_EQ(b.VerifyTheWay({ 0,5 }, { 1,6 }), false);
//	EXPECT_EQ(b.VerifyTheWay({ 7,2 }, { 6,1 }), false);
//	EXPECT_EQ(b.VerifyTheWay({ 7,2 }, { 6,3 }), false);
//	EXPECT_EQ(b.VerifyTheWay({ 7,5 }, { 4,2 }), false);
//	EXPECT_EQ(b.VerifyTheWay({ 7,5 }, { 5,7 }), false);
//}
//
//TEST(VerifyTheWayTest, KnightTest)
//{
//	Board b;
//	EXPECT_EQ(b.VerifyTheWay({ 0,1 }, { 2,0 }), true);
//	EXPECT_EQ(b.VerifyTheWay({ 0,1 }, { 2,2 }), true);
//	EXPECT_EQ(b.VerifyTheWay({ 0,6 }, { 2,5 }), true);
//	EXPECT_EQ(b.VerifyTheWay({ 0,6 }, { 2,7 }), true);
//	EXPECT_EQ(b.VerifyTheWay({ 7,1 }, { 5,0 }), true);
//	EXPECT_EQ(b.VerifyTheWay({ 7,1 }, { 5,2 }), true);
//	EXPECT_EQ(b.VerifyTheWay({ 7,6 }, { 5,5 }), true);
//	EXPECT_EQ(b.VerifyTheWay({ 7,6 }, { 5,7 }), true);
//	EXPECT_EQ(b.VerifyTheWay({ 0,1 }, { 1,3 }), false);
//	EXPECT_EQ(b.VerifyTheWay({ 0,6 }, { 1,4 }), false);
//	EXPECT_EQ(b.VerifyTheWay({ 7,1 }, { 6,3 }), false);
//	EXPECT_EQ(b.VerifyTheWay({ 7,6 }, { 6,4 }), false);
//}
//
//TEST(IsCheckTest, WBishopBoard)
//{
//	PiecePairVector m1 = {
//		{ {2,5}, Piece::Produce(EPieceType::King, EColor::White)},
//		{ {0,7}, Piece::Produce(EPieceType::Bishop, EColor::White)} };
//	Board b(m1);
//
//	EXPECT_EQ(b.IsCheck({ 2,5 }, EColor::White), false);
//	EXPECT_EQ(b.IsCheck({ 1,6 }, EColor::Black), true);
//	EXPECT_EQ(b.IsCheck({ 1,6 }, EColor::White), false);
//	EXPECT_EQ(b.IsCheck({ 0,5 }, EColor::White), false);
//	EXPECT_EQ(b.IsCheck({ 0,5 }, EColor::Black), false);
//}
//
//TEST(IsCheckTest, BBishopBoard)
//{
//	PiecePairVector m1 = {
//		{ {2,5}, Piece::Produce(EPieceType::King,  EColor::White)},
//		{ {7,0}, Piece::Produce(EPieceType::Bishop, EColor::Black)} };
//	Board b(m1);
//
//	EXPECT_EQ(b.IsCheck({ 2,5 }, EColor::White), true);
//}
//
//TEST(IsCheckTest, WRookBoard)
//{
//	PiecePairVector m1 = {
//		{ {2,5}, Piece::Produce(EPieceType::King, EColor::White)},
//		{ {2,7}, Piece::Produce(EPieceType::Rook, EColor::White)} };
//	Board b(m1);
//
//	EXPECT_EQ(b.IsCheck({ 2,5 }, EColor::White), false);
//}
//
//TEST(IsCheckTest, BRookBoard)
//{
//	PiecePairVector m1 = {
//		{ {2,5}, Piece::Produce(EPieceType::King, EColor::White)},
//		{ {2,7}, Piece::Produce(EPieceType::Rook, EColor::Black)} };
//	Board b(m1);
//
//	EXPECT_EQ(b.IsCheck({ 2,5 }, EColor::White), true);
//	EXPECT_EQ(b.IsCheck({ 5,6 }, EColor::Black), false);
//	EXPECT_EQ(b.IsCheck({ 5,6 }, EColor::White), false);
//	EXPECT_EQ(b.IsCheck({ 4,7 }, EColor::White), true);
//	EXPECT_EQ(b.IsCheck({ 5,7 }, EColor::White), true);
//	EXPECT_EQ(b.IsCheck({ 2,0 }, EColor::Black), false);
//}
//
//TEST(IsCheckTest, WQueenBoard)
//{
//	PiecePairVector m1 = {
//		{ {2,5}, Piece::Produce(EPieceType::King, EColor::Black)},
//		{ {7,0}, Piece::Produce(EPieceType::Queen, EColor::White)} };
//	Board b(m1);
//
//	EXPECT_EQ(b.IsCheck({ 2,5 }, EColor::Black), true);
//}
//
//TEST(IsCheckTest, BQueenBoard)
//{
//	PiecePairVector m1 = {
//		{ {2,5}, Piece::Produce(EPieceType::King, EColor::White)},
//		{ {7,0}, Piece::Produce(EPieceType::Queen, EColor::Black)} };
//	Board b(m1);
//
//	EXPECT_EQ(b.IsCheck({ 2,5 }, EColor::White), true);
//}
//
//TEST(IsCheckTest, WPawnBoard)
//{
//	PiecePairVector m1 = {
//		{ {2,5}, Piece::Produce(EPieceType::King, EColor::Black)},
//		{ {3,4}, Piece::Produce(EPieceType::Pawn, EColor::White)} };
//	Board b(m1);
//
//	EXPECT_EQ(b.IsCheck({ 2,5 }, EColor::Black), true);
//}
//
//TEST(IsCheckTest, BPawnBoard)
//{
//	PiecePairVector m1 = {
//		{ {2,5}, Piece::Produce(EPieceType::King, EColor::Black)},
//		{ {3,4}, Piece::Produce(EPieceType::Pawn, EColor::Black)} };
//	Board b(m1);
//
//	EXPECT_EQ(b.IsCheck({ 2,5 }, EColor::Black), false);
//}
//
//TEST(IsCheckTest, WKnightBoard)
//{
//	PiecePairVector m1 = {
//		{ {2,5}, Piece::Produce(EPieceType::King, EColor::Black)},
//		{ {1,3}, Piece::Produce(EPieceType::Knight, EColor::White)} };
//	Board b(m1);
//
//	EXPECT_EQ(b.IsCheck({ 2,5 }, EColor::Black), true);
//}
//
//TEST(IsCheckMateTest, BishopBoard)
//{
//
//	PiecePairVector m1 = {
//		{ {2,5},  Piece::Produce(EPieceType::King, EColor::White)} ,
//		{ {7,0},  Piece::Produce(EPieceType::Bishop, EColor::Black)} };
//	Board b(m1);
//
//	EXPECT_EQ(b.IsCheckMate({ 2,5 }, EColor::White), false);
//}
//
//TEST(IsCheckMateTest, MultipleBishopBoard)
//{
//	PiecePairVector m1 = {
//		{ {7,2}, Piece::Produce(EPieceType::King, EColor::White)},
//		{ {6,0}, Piece::Produce(EPieceType::Bishop, EColor::Black)},
//		{ {5,0}, Piece::Produce(EPieceType::Bishop, EColor::Black)},
//		{ {4,0}, Piece::Produce(EPieceType::Bishop, EColor::Black)},
//		{ {3,0}, Piece::Produce(EPieceType::Bishop, EColor::Black)} };
//	Board b(m1);
//
//	EXPECT_EQ(b.IsCheckMate({ 7,2 }, EColor::White), true);
//}
//
//TEST(IsCheckMateTest, DRookMate)
//{
//	PiecePairVector m1 = {
//		{ {0,0}, Piece::Produce(EPieceType::King, EColor::White)},
//		{ {0,6}, Piece::Produce(EPieceType::Rook, EColor::Black)},
//		{ {1,7}, Piece::Produce(EPieceType::Rook, EColor::Black)}
//	};
//	Board b(m1);
//
//	EXPECT_EQ(b.IsCheckMate({ 0,0 }, EColor::White), true);
//}
//
//TEST(IsCheckMateTest, KillCheckRook)
//{
//	PiecePairVector m1 = {
//		{{0, 0}, Piece::Produce(EPieceType::King, EColor::White)},
//		{{7,7}, Piece::Produce(EPieceType::Bishop, EColor::Black)},
//		{{0,7}, Piece::Produce(EPieceType::Rook, EColor::Black)}
//	};
//	Board b(m1);
//
//	EXPECT_EQ(b.IsCheckMate({ 0,0 }, EColor::White), false);
//}
//
//TEST(IsCheckMateTest, KillCheckPawn)
//{
//	PiecePairVector m1 = {
//		{{1, 1}, Piece::Produce(EPieceType::King, EColor::White)},
//		{{0,7}, Piece::Produce(EPieceType::Rook, EColor::White)},
//		{{0,0}, Piece::Produce(EPieceType::Pawn, EColor::Black)}
//	};
//	Board b(m1);
//
//	EXPECT_EQ(b.IsCheck({ 1,1 }, EColor::White), true);
//	EXPECT_EQ(b.IsCheckMate({ 1,1 }, EColor::White), false);
//}
//
//TEST(IsCheckMateTest, CheckmateVariation1)
//{
//	PiecePairVector m1 = {
//		{{0, 7}, Piece::Produce(EPieceType::King, EColor::White)},
//		{{0, 5}, Piece::Produce(EPieceType::Bishop, EColor::Black)},
//		{{1, 6}, Piece::Produce(EPieceType::Queen, EColor::Black)}
//	};
//
//	Board b(m1);
//
//	EXPECT_EQ(b.IsCheckMate({ 0,7 }, EColor::White), true);
//}
//
//TEST(IsCheckMateTest, CheckmateVariation2)
//{
//	PiecePairVector m1 = {
//	{{0, 0}, Piece::Produce(EPieceType::King, EColor::White)},
//	{{0, 2}, Piece::Produce(EPieceType::King, EColor::Black)},
//	{{7, 0}, Piece::Produce(EPieceType::Rook, EColor::Black)},
//	};
//
//	Board b(m1);
//
//	EXPECT_EQ(b.IsCheckMate({ 0,0 }, EColor::White), true);
//}
//
//TEST(IsCheckMateTest, CheckmateVariation3)
//{
//	PiecePairVector m1 = {
//		{{0, 7}, Piece::Produce(EPieceType::King, EColor::White)},
//		{{0, 6}, Piece::Produce(EPieceType::Rook, EColor::Black)},
//		{{2, 5}, Piece::Produce(EPieceType::Knight, EColor::Black)},
//	};
//
//	Board b(m1);
//
//	EXPECT_EQ(b.IsCheckMate({ 0,7 }, EColor::White), true);
//}
//
//TEST(IsCheckMateTest, CheckmateVariation4)
//{
//	PiecePairVector m1 = {
//	{{7, 4}, Piece::Produce(EPieceType::King, EColor::White)},
//	{{6, 4}, Piece::Produce(EPieceType::Pawn, EColor::White)},
//	{{6, 3}, Piece::Produce(EPieceType::Pawn, EColor::White)},
//	{{7, 3}, Piece::Produce(EPieceType::Queen, EColor::White)},
//	{{7, 5}, Piece::Produce(EPieceType::Bishop, EColor::White)},
//	{{4, 7}, Piece::Produce(EPieceType::Queen, EColor::Black)},
//	};
//
//	Board b(m1);
//
//	EXPECT_EQ(b.IsCheckMate({ 7, 4 }, EColor::White), true);
//}
//
//TEST(IsCheckMateTest, CheckmateVariation5)
//{
//	PiecePairVector m1 = {
//	{{0, 2}, Piece::Produce(EPieceType::King, EColor::Black)},
//	{{0, 3}, Piece::Produce(EPieceType::Rook, EColor::Black)},
//	{{1, 3}, Piece::Produce(EPieceType::Pawn, EColor::Black)},
//	{{2, 0}, Piece::Produce(EPieceType::Bishop, EColor::White)},
//	{{6, 7}, Piece::Produce(EPieceType::Bishop, EColor::White)},
//	};
//
//	Board b(m1);
//
//	EXPECT_EQ(b.IsCheckMate({ 0, 2 }, EColor::Black), true);
//}
//
//TEST(IsCheckMateTest, CheckmateVariation6)
//{
//	PiecePairVector m1 = {
//	{{1, 6}, Piece::Produce(EPieceType::King, EColor::Black)},
//	{{1, 7}, Piece::Produce(EPieceType::Pawn, EColor::Black)},
//	{{0, 6}, Piece::Produce(EPieceType::Rook, EColor::Black)},
//	{{2, 5}, Piece::Produce(EPieceType::Queen, EColor::White)},
//	{{7, 5}, Piece::Produce(EPieceType::Rook, EColor::White)},
//	};
//
//	Board b(m1);
//
//	EXPECT_EQ(b.IsCheckMate({ 1, 6 }, EColor::Black), true);
//}
//
//
//TEST(IsCheckMateTest, FindHelpTest1)
//{
//	PiecePairVector m1 = {
//		{{0, 7}, Piece::Produce(EPieceType::King, EColor::White)},
//		{{0, 6}, Piece::Produce(EPieceType::Queen, EColor::White)},
//		{{2, 5}, Piece::Produce(EPieceType::Bishop, EColor::Black)}
//	};
//
//	Board b(m1);
//
//	EXPECT_EQ(b.IsCheckMate({ 0,7 }, EColor::White), false);
//}
//
//TEST(IsCheckMateTest, FindHelpTest2)
//{
//	PiecePairVector m1 = {
//		{{4, 0}, Piece::Produce(EPieceType::King, EColor::White)},
//		{{7, 0}, Piece::Produce(EPieceType::Rook, EColor::Black)},
//		{{7, 1}, Piece::Produce(EPieceType::Rook, EColor::Black)},
//		{{4, 1}, Piece::Produce(EPieceType::Bishop, EColor::White)},
//	};
//
//	Board b(m1);
//
//	EXPECT_EQ(b.IsCheckMate({ 4,0 }, EColor::White), false);
//}
//
//
//TEST(IsCheckMateTest, FindHelpTest3)
//{
//	PiecePairVector m1 = {
//		{{0, 7}, Piece::Produce(EPieceType::King, EColor::White)},
//		{{0, 6}, Piece::Produce(EPieceType::Queen, EColor::White)},
//		{{2, 5}, Piece::Produce(EPieceType::Bishop, EColor::Black)}
//	};
//
//	Board b(m1);
//
//	EXPECT_EQ(b.IsCheckMate({ 0,7 }, EColor::White), false);
//}
//
//TEST(IsCheckMateTest, FindHelpTest4)
//{
//	PiecePairVector m1 = {
//	{{1, 6}, Piece::Produce(EPieceType::King, EColor::Black)},
//	{{1, 7}, Piece::Produce(EPieceType::Pawn, EColor::Black)},
//	{{0, 6}, Piece::Produce(EPieceType::Rook, EColor::Black)},
//	{{2, 7}, Piece::Produce(EPieceType::Rook, EColor::Black)},
//	{{2, 5}, Piece::Produce(EPieceType::Queen, EColor::White)},
//	{{7, 5}, Piece::Produce(EPieceType::Rook, EColor::White)},
//	};
//
//	Board b(m1);
//
//	EXPECT_EQ(b.IsCheckMate({ 1, 6 }, EColor::Black), false);
//
//}
//
//
//
//TEST(IsCheckMateTest, IsSameWayTest)
//{
//	PiecePairVector m1 = {
//		{{4, 0}, Piece::Produce(EPieceType::King, EColor::White)},
//		{{7, 0}, Piece::Produce(EPieceType::Rook, EColor::Black)},
//		{{7, 1}, Piece::Produce(EPieceType::Rook, EColor::Black)},
//		{{4, 1}, Piece::Produce(EPieceType::Bishop, EColor::White)},
//	};
//
//	Board b(m1);
//
//	EXPECT_EQ(b.IsCheckMate({ 4,0 }, EColor::White), false);
//}
//
//
//
//int main(int argc, char** argv)
//{
//	::testing::InitGoogleTest(&argc, argv);
//	return RUN_ALL_TESTS();
//}