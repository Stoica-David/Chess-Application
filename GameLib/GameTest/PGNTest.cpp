#include "PGNHandler.h"
#include "BoardExceptions.h"
#include "gtest/gtest.h"

//TEST(GeneratePGNTest, PGN1)
//{
//	CharMatrix m = { {
//	{'r', 'h', 'b', 'q', 'k', 'b', 'h', 'r'},
//	{'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
//	{'-', '-', '-', '-', '-', '-', '-', '-'},
//	{'-', '-', '-', '-', '-', '-', '-', '-'},
//	{'-', '-', '-', '-', '-', '-', '-', '-'},
//	{'-', '-', '-', '-', '-', '-', '-', '-'},
//	{'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
//	{'R', 'H', 'B', 'Q', 'K', 'B', 'H', 'R'}
//	} };
//
//	MoveVector v = { { {6,2}, {4,2} }, { {1,3}, {3,3} }, { {4,2}, {3,3} }, { {1,2}, {2,2} }, { {3,3}, {2,2} }, { {1,1}, {2,1} }, { {2,2}, {1,2} }, { {2,1}, {3,1} }, { {7,3}, {4,0} }, { {0,1}, {2,2} } };
//
//	Board b(m);
//
//	for (const auto& move : v)
//	{
//		b.Move(move.first, move.second);
//	}
//
//	EXPECT_EQ(b.GeneratePGN(), "1.c4 d5 2.cxd5 c6 3.dxc6 b6 4.c7 b5 5.Qa4 Nc6 *");
//}

//TEST(ParsePGNTest, PGN1)
//{
//	Board b;
//	MoveVector v = { {{6,2}, {4,2}}, {{1,4}, {2,4}}, {{6,5}, {4,5}}, {{1,1}, {2,1}} };
//
//	EXPECT_NO_THROW(b.ParsePGN("1.c4 e6 2.f4 b6 "), v);
//}
//
//TEST(ParsePGNTest, PGN2)
//{
//	Board b;
//	MoveVector v = { {{6,2}, {4,2}},  {{1,3}, {3,3}}, {{4,2}, {3,3}}, {{1,2}, {2,2}}, {{3,3}, {2,2}}, {{1,1}, {2,1}}, {{2,2}, {1,2}}, {{2,1}, {3,1}}, {{7,3}, {4,0}}, {{0,1}, {2,2}} };
//
//	EXPECT_NO_THROW(b.ParsePGN("1.c4 d5 2.cxd5 c6 3.dxc6 b6 4.c7 b5 5.Qa4 Nc6 "), v);
//}
//
//TEST(ParsePGNTest, PGN3)
//{
//	Board b;
//	MoveVector v = { {{6,2}, {4,2}},  {{1,3}, {3,3}}, {{4,2}, {3,3}}, {{1,2}, {2,2}}, {{3,3}, {2,2}}, {{1,1}, {2,1}}, {{2,2}, {1,2}}, {{2,1}, {3,1}}, {{7,3}, {4,0}}, {{0,1}, {2,2}} };
//
//	EXPECT_NO_THROW(b.ParsePGN("1.d4 Nf6 2.h4 e6 3.h5 Ba3 4.h6 O-O "), v);
//}

//TEST(SetBoardTest, FENTestGood)
//{
//	String FEN = "rnbqkbnr/pp1p2pp/2p5/4Np2/3P4/8/PPP2PPP/RNBQKB1R b";
//
//	Board b;
//
//	EXPECT_NO_THROW(b.SetBoard(FEN));
//}
//
//TEST(SetBoardTest, FENTestBad)
//{
//	String FEN = "rnbqkb1r/pp1ppppp/2p2n2/8/3P4/5N2/PPP1sPPPP/RNBQKB1R w";
//
//	Board b;
//
//	EXPECT_THROW(b.SetBoard(FEN), FENException);
//}
//
//TEST(SetBoardTest, PGNTestGood)
//{
//	String PGN = "1.d4 Nf6 2.h4 e6 3.h5 Ba3 4.h6 O-O 5.hxg7 e5 6.gxf8=N Ne8 7.Nxh7 f5 8.Be3 f4 9.Nc3 f3 10.Qd2 fxg2 11.O-O-O gxh1=Q 12.Ne4 Bb4 13.Nf3 a6 14.Neg5 a5 15.Ne4 a4 16.Nfg5 a3 17.Nf3 axb2+ 18.Kb1 Bc5 19.Nhg5 Bd6 20.c4 b5 21.Kc2 b1=B+ 22.Kc1 Bxe4 23.a3 Bb4 24.a4 d5 25.a5 Be6 26.Nh7 Qf6 27.a6 Qg6 28.a7 Qh4 29.axb8=Q Qhg4 30.Qa7 B4f5 31.Qa6 Be4 32.Qa5 B6f5 33.Qa4 Be6 34.Qa3 Q6f5 35.Qaa2 Qfg6 36.Qxb4 Q6h5 37.Qd6 Nf6 38.Qxe6+ Kh8 39.Qxf6+ Kg8 40.cxd5 b4 41.d6+ Kxh7 42.Rd3 b3 43.Rc3 b2+ 44.Kd2 b1=N+ 45.Ke1 c5 46.Qa6 Na3 47.Qxa8 Nc2+ 48.Rxc2 c4 49.Rxc4 Bb1 50.Rc7+ Qd7 51.Rxd7+ Qf7 52.Rxf7#";
//
//	Board b;
//
//	EXPECT_NO_THROW(b.SetBoard(PGN));
//}
//
//TEST(SetBoardTest, PGNTestBad)
//{
//	String PGN = "1.c4dadas d5 2.f3 f5 ";
//
//	Board b;
//
//	EXPECT_THROW(b.SetBoard(PGN), PGNException);
//}