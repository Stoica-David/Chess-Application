#include "Board.h"
#include "BoardExceptions.h"
#include "gtest/gtest.h"

TEST(VerifyTheWayTest, PawnTest)
{
	Board b;
	EXPECT_EQ(b.VerifyTheWay({ 6,0 }, { 5,0 }), true);
	EXPECT_EQ(b.VerifyTheWay({ 6,0 }, { 4,0 }), true);
	EXPECT_EQ(b.VerifyTheWay({ 6,0 }, { 5,1 }), true);
	EXPECT_EQ(b.VerifyTheWay({ 6,0 }, { 7,0 }), false);

	EXPECT_EQ(b.VerifyTheWay({ 1,0 }, { 2,0 }), true);
	EXPECT_EQ(b.VerifyTheWay({ 1,0 }, { 3,0 }), true);
	EXPECT_EQ(b.VerifyTheWay({ 1,0 }, { 2,1 }), true);
	EXPECT_EQ(b.VerifyTheWay({ 1,0 }, { 0,0 }), false);
}

TEST(VerifyTheWayTest, RookTest)
{
	Board b;
	EXPECT_EQ(b.VerifyTheWay({ 0,0 }, { 0,1 }), false);
	EXPECT_EQ(b.VerifyTheWay({ 0,0 }, { 3,0 }), false);
	EXPECT_EQ(b.VerifyTheWay({ 0,7 }, { 0,4 }), false);
	EXPECT_EQ(b.VerifyTheWay({ 0,7 }, { 2,7 }), false);
	EXPECT_EQ(b.VerifyTheWay({ 7,7 }, { 1,7 }), false);
	EXPECT_EQ(b.VerifyTheWay({ 7,7 }, { 3,7 }), false);
	EXPECT_EQ(b.VerifyTheWay({ 7,0 }, { 7,3 }), false);
	EXPECT_EQ(b.VerifyTheWay({ 7,0 }, { 7,5 }), false);
}

TEST(VerifyTheWatTest, QueenTest)
{
	Board b;
	//white
	EXPECT_EQ(b.VerifyTheWay({ 7, 3 }, { 6, 3 }), false);
	EXPECT_EQ(b.VerifyTheWay({ 7, 3 }, { 7, 0 }), false);
	EXPECT_EQ(b.VerifyTheWay({ 7, 3 }, { 7, 7 }), false);
	EXPECT_EQ(b.VerifyTheWay({ 7, 3 }, { 4, 0 }), false);
	EXPECT_EQ(b.VerifyTheWay({ 7, 3 }, { 4, 7 }), false);
	EXPECT_EQ(b.VerifyTheWay({ 7, 3 }, { 5, 4 }), false);

	//black
	EXPECT_EQ(b.VerifyTheWay({ 0, 3 }, { 0, 0 }), false);
	EXPECT_EQ(b.VerifyTheWay({ 0, 3 }, { 0, 7 }), false);
	EXPECT_EQ(b.VerifyTheWay({ 0, 3 }, { 5, 3 }), false);
	EXPECT_EQ(b.VerifyTheWay({ 0, 3 }, { 3, 0 }), false);
	EXPECT_EQ(b.VerifyTheWay({ 0, 3 }, { 4, 7 }), false);


}

TEST(VerifyTheWatTest, KnightTest)
{
	Board b;

	//white
	EXPECT_EQ(b.VerifyTheWay({ 7, 4 }, { 7, 3 }), false);
	EXPECT_EQ(b.VerifyTheWay({ 7, 4 }, { 7, 4 }), false);
	EXPECT_EQ(b.VerifyTheWay({ 7, 4 }, { 6, 4 }), false);
	EXPECT_EQ(b.VerifyTheWay({ 7, 4 }, { 6, 3 }), false);
	EXPECT_EQ(b.VerifyTheWay({ 7, 4 }, { 6, 5 }), false);

	//black
	EXPECT_EQ(b.VerifyTheWay({ 0, 4 }, { 0, 3 }), false);
	EXPECT_EQ(b.VerifyTheWay({ 0, 4 }, { 0, 5 }), false);
	EXPECT_EQ(b.VerifyTheWay({ 0, 4 }, { 1, 3 }), false);
	EXPECT_EQ(b.VerifyTheWay({ 0, 4 }, { 1, 4 }), false);
	EXPECT_EQ(b.VerifyTheWay({ 0, 4 }, { 1, 5 }), false);
}

TEST(VerifyTheWayTest, BishopTest)
{
	Board b;
	EXPECT_EQ(b.VerifyTheWay({ 0,2 }, { 1,1 }), false);
	EXPECT_EQ(b.VerifyTheWay({ 0,2 }, { 3,4 }), false);
	EXPECT_EQ(b.VerifyTheWay({ 0,5 }, { 3,2 }), false);
	EXPECT_EQ(b.VerifyTheWay({ 0,5 }, { 1,6 }), false);
	EXPECT_EQ(b.VerifyTheWay({ 7,2 }, { 6,1 }), false);
	EXPECT_EQ(b.VerifyTheWay({ 7,2 }, { 6,3 }), false);
	EXPECT_EQ(b.VerifyTheWay({ 7,5 }, { 4,2 }), false);
	EXPECT_EQ(b.VerifyTheWay({ 7,5 }, { 5,7 }), false);
}

TEST(VerifyTheWayTest, KnightTest)
{
	Board b;
	EXPECT_EQ(b.VerifyTheWay({ 0,1 }, { 2,0 }), true);
	EXPECT_EQ(b.VerifyTheWay({ 0,1 }, { 2,2 }), true);
	EXPECT_EQ(b.VerifyTheWay({ 0,6 }, { 2,5 }), true);
	EXPECT_EQ(b.VerifyTheWay({ 0,6 }, { 2,7 }), true);
	EXPECT_EQ(b.VerifyTheWay({ 7,1 }, { 5,0 }), true);
	EXPECT_EQ(b.VerifyTheWay({ 7,1 }, { 5,2 }), true);
	EXPECT_EQ(b.VerifyTheWay({ 7,6 }, { 5,5 }), true);
	EXPECT_EQ(b.VerifyTheWay({ 7,6 }, { 5,7 }), true);
	EXPECT_EQ(b.VerifyTheWay({ 0,1 }, { 1,3 }), false);
	EXPECT_EQ(b.VerifyTheWay({ 0,6 }, { 1,4 }), false);
	EXPECT_EQ(b.VerifyTheWay({ 7,1 }, { 6,3 }), false);
	EXPECT_EQ(b.VerifyTheWay({ 7,6 }, { 6,4 }), false);
}

TEST(IsCheckTest, WBishopBoard)
{
	CharMatrix m = {
	{{'-', '-', '-', '-', '-', '-', '-', 'B'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', 'K', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'}}
	};

	Board b(m);

	EXPECT_EQ(b.IsCheck({ 2,5 }, EColor::White), false);
	EXPECT_EQ(b.IsCheck({ 1,6 }, EColor::Black), true);
	EXPECT_EQ(b.IsCheck({ 1,6 }, EColor::White), false);
	EXPECT_EQ(b.IsCheck({ 0,5 }, EColor::White), false);
	EXPECT_EQ(b.IsCheck({ 0,5 }, EColor::Black), false);
}

TEST(IsCheckTest, BBishopBoard)
{

	CharMatrix m = {
	{{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', 'K', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'b', '-', '-', '-', '-', '-', '-', '-'}}
	};

	Board b(m);

	EXPECT_EQ(b.IsCheck({ 2,5 }, EColor::White), true);
}

TEST(IsCheckTest, WRookBoard)
{

	CharMatrix m = {
	{{'-', '-', '-', '-', '-', 'K', '-', 'R'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'}}
	};


	Board b(m);

	EXPECT_EQ(b.IsCheck({ 2,5 }, EColor::White), false);
}

TEST(IsCheckTest, BRookBoard)
{
	CharMatrix m = {
	{{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', 'K', '-', 'r'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'}}
	};


	Board b(m);

	EXPECT_EQ(b.IsCheck({ 2,5 }, EColor::White), true);
	EXPECT_EQ(b.IsCheck({ 5,6 }, EColor::Black), false);
	EXPECT_EQ(b.IsCheck({ 5,6 }, EColor::White), false);
	EXPECT_EQ(b.IsCheck({ 4,7 }, EColor::White), true);
	EXPECT_EQ(b.IsCheck({ 5,7 }, EColor::White), true);
	EXPECT_EQ(b.IsCheck({ 2,0 }, EColor::Black), false);
}

TEST(IsCheckTest, WQueenBoard)
{

	CharMatrix m = {
	{{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', 'k', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'Q', '-', '-', '-', '-', '-', '-', '-'}}
	};

	Board b(m);

	EXPECT_EQ(b.IsCheck({ 2,5 }, EColor::Black), true);
}

TEST(IsCheckTest, BQueenBoard)
{

	CharMatrix m = {
	{{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', 'K', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'q', '-', '-', '-', '-', '-', '-', '-'}}
	};

	Board b(m);

	EXPECT_EQ(b.IsCheck({ 2,5 }, EColor::White), true);
}

TEST(IsCheckTest, WPawnBoard)
{

	CharMatrix m = {
	{{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', 'k', '-', '-'},
	{'-', '-', '-', '-', 'P', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'}}
	};


	Board b(m);

	EXPECT_EQ(b.IsCheck({ 2,5 }, EColor::Black), true);
}

TEST(IsCheckTest, BPawnBoard)
{

	CharMatrix m = {
	{{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', 'k', '-', '-'},
	{'-', '-', '-', '-', 'p', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'}}
	};

	Board b(m);

	EXPECT_EQ(b.IsCheck({ 2,5 }, EColor::Black), false);
}

TEST(IsCheckTest, WKnightBoard)
{

	CharMatrix m = {
	{{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', 'H', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', 'k', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'}}
	};


	Board b(m);

	EXPECT_EQ(b.IsCheck({ 2,5 }, EColor::Black), true);
}

TEST(IsCheckMateTest, BishopBoard)
{
	CharMatrix m = {
	{{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', 'K', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'B', '-', '-', '-', '-', '-', '-', '-'}}
	};

	Board b(m);

	EXPECT_EQ(b.IsCheckMate(EColor::White), false);
}

TEST(IsCheckMateTest, MultipleBishopBoard)
{

	CharMatrix m = {
	{{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'b', '-', '-', '-', '-', '-', '-', '-'},
	{'b', '-', '-', '-', '-', '-', '-', '-'},
	{'b', '-', '-', '-', '-', '-', '-', '-'},
	{'b', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', 'K', '-', '-', '-', '-', '-'}}
	};


	Board b(m);

	EXPECT_EQ(b.IsCheckMate(EColor::White), true);
}

TEST(IsCheckMateTest, DRookMate)
{
	CharMatrix m = {
	{{'K', '-', '-', '-', '-', '-', 'r', '-'},
	{'-', '-', '-', '-', '-', '-', '-', 'r'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'}}
	};


	Board b(m);

	EXPECT_EQ(b.IsCheckMate(EColor::White), true);
}

TEST(IsCheckMateTest, KillCheckRook)
{

	CharMatrix m = {
	{{'K', '-', '-', '-', '-', '-', '-', 'R'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', 'B'}}
	};


	Board b(m);

	EXPECT_EQ(b.IsCheckMate(EColor::White), false);
}

TEST(IsCheckMateTest, KillCheckPawn)
{
	CharMatrix m = {
	{{'p', '-', '-', '-', '-', '-', '-', 'R'},
	{'-', 'K', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'}}
	};

	Board b(m);

	EXPECT_EQ(b.IsCheck({ 1,1 }, EColor::White), true);
	EXPECT_EQ(b.IsCheckMate(EColor::White), false);
}

TEST(IsCheckMateTest, CheckmateVariation1)
{

	CharMatrix m = {
	{{'-', '-', '-', '-', '-', 'b', '-', 'K'},
	{'-', '-', '-', '-', '-', '-', 'q', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'}}
	};


	Board b(m);

	EXPECT_EQ(b.IsCheckMate(EColor::White), true);
}

TEST(IsCheckMateTest, CheckmateVariation2)
{
	CharMatrix m = {
	{{'K', '-', 'k', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'r', '-', '-', '-', '-', '-', '-', '-'}}
	};

	Board b(m);

	EXPECT_EQ(b.IsCheckMate(EColor::White), true);
}

TEST(IsCheckMateTest, CheckmateVariation3)
{

	CharMatrix m = {
	{{'-', '-', '-', '-', '-', '-', 'r', 'K'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', 'h', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'}}
	};


	Board b(m);

	EXPECT_EQ(b.IsCheckMate(EColor::White), true);
}

TEST(IsCheckMateTest, CheckmateVariation4)
{

	CharMatrix m = {
	{{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', 'q'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', 'P', 'P', '-', '-', '-'},
	{'-', '-', '-', 'Q', 'K', 'B', '-', '-'}}
	};


	Board b(m);

	EXPECT_EQ(b.IsCheckMate(EColor::White), true);
}

TEST(IsCheckMateTest, CheckmateVariation5)
{

	CharMatrix m = {
	{{'-', '-', 'k', 'r', '-', '-', '-', '-'},
	{'-', '-', '-', 'p', '-', '-', '-', '-'},
	{'B', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', 'B'},
	{'-', '-', '-', '-', '-', '-', '-', '-'}}
	};

	Board b(m);

	EXPECT_EQ(b.IsCheckMate(EColor::Black), true);
}

TEST(IsCheckMateTest, CheckmateVariation6)
{
	CharMatrix m = {
	{{'-', '-', '-', '-', '-', '-', 'k', 'r'},
	{'-', '-', '-', '-', '-', '-', 'p', '-'},
	{'-', '-', '-', '-', '-', 'Q', '-', 'r'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', 'R', '-', '-'}}
	};


	Board b(m);

	EXPECT_EQ(b.IsCheckMate(EColor::Black), false);
}

TEST(IsCheckMateTest, CheckmateVariation7)
{
	CharMatrix m = { {
	{'-', '-', '-', '-', '-', '-', 'p', 'r'},
	{'-', '-', '-', '-', '-', '-', 'k', '-'},
	{'-', '-', '-', '-', '-', 'Q', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', 'R', '-', '-'}}
	};


	Board b(m);

	EXPECT_EQ(b.IsCheckMate(EColor::Black), false);
}



TEST(IsCheckMateTest, FindHelpTest1)
{
	CharMatrix m = { {
	{'r', 'h', 'b', 'q', 'k', 'b', 'h', 'r'},
	{'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
	{'R', 'H', 'B', 'Q', 'K', 'B', 'H', 'R'}
	} };

	Board b(m);

	EXPECT_EQ(b.IsCheckMate(EColor::White), false);
}

TEST(IsCheckMateTest, FindHelpTest2)
{

	CharMatrix m = {
	{{'K', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'B', 'R', '-', '-', '-', '-', '-', '-'},
	{'-', 'R', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'}}
	};


	Board b(m);

	EXPECT_EQ(b.IsCheckMate(EColor::White), false);
}


TEST(IsCheckMateTest, FindHelpTest3)
{

	CharMatrix m = {
	{{'-', '-', '-', '-', '-', '-', 'Q', 'K'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', 'b', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'}}
	};


	Board b(m);

	EXPECT_EQ(b.IsCheckMate(EColor::White), false);
}

TEST(IsCheckMateTest, IsSameWayTest)
{

	CharMatrix m = {
	{{'K', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', 'b', '-', '-'},
	{'-', '-', '-', '-', '-', 'R', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'}}
	};


	Board b(m);

	EXPECT_EQ(b.IsCheckMate(EColor::White), false);
}

TEST(StalemateTest, Stalemate1)
{

	CharMatrix m = {
	{{'K', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', 'r'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', 'r', '-', '-', '-', '-', '-', 'k'}}
	};

	Board b(m);

	EXPECT_EQ(b.IsStalemate(EColor::White), true);
}

TEST(PawnDiagonalTest, Diagonal1)
{
	CharMatrix m = {
	{{'K', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', 'P', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', 'k'}}
	};

	Board b(m);

	EXPECT_THROW(b.Move({ 6,1 }, { 3,1 }), MoveException);
}

TEST(Check3FoldTest, First3Fold)
{
	CharMatrix m = {
	{{'K', '-', '-', '-', '-', '-', '-', 'B'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'b', '-', '-', '-', '-', '-', '-', 'k'}}
	};

	Board b(m);

	b.Move({ 0, 7 }, { 1, 6 });
	b.Move({ 7, 0 }, { 6, 1 });
	b.Move({ 1, 6 }, { 0, 7 });
	b.Move({ 6, 1 }, { 7, 0 });
	b.Move({ 0, 7 }, { 1, 6 });
	b.Move({ 7, 0 }, { 6, 1 });
	b.Move({ 1, 6 }, { 0, 7 });
	b.Move({ 6, 1 }, { 7, 0 });
	b.Move({ 0, 7 }, { 1, 6 });
	b.Move({ 7, 0 }, { 6, 1 });
	b.Move({ 1, 6 }, { 0, 7 });
	b.Move({ 6, 1 }, { 7, 0 });

	EXPECT_EQ(b.IsDraw(), true);
}

TEST(IsPinnedTest, Pin1)
{
	CharMatrix m = { {
	{'r', 'h', '-', '-', 'k', 'b', 'h', 'r',},
	{'p', 'p', 'p', '-', 'p', 'p', 'p', 'p',},
	{'-', '-', '-', '-', '-', '-', '-', '-',},
	{'-', '-', '-', '-', '-', 'b', '-', '-',},
	{'-', '-', '-', '-', '-', '-', '-', '-',},
	{'-', '-', '-', '-', '-', '-', '-', '-',},
	{'P', 'P', '-', 'q', '-', '-', 'P', 'P',},
	{'R', 'H', 'B', '-', 'K', 'B', 'H', 'R',},
	} };

	Board b(m);

	EXPECT_EQ(b.IsPinned({ 1,0 }), false);
	EXPECT_EQ(b.IsPinned({ 6,3 }), false);
}

TEST(IsPinnedTest, Pin2)
{
	CharMatrix m = { {
	{'r', 'h', 'b', '-', 'k', 'b', 'h', 'r',},
	{'p', 'p', '-', 'p', 'p', 'p', 'p', 'p',},
	{'-', '-', 'p', '-', '-', '-', '-', '-',},
	{'q', '-', '-', '-', '-', '-', '-', '-',},
	{'-', '-', '-', 'P', '-', '-', '-', '-',},
	{'-', '-', 'H', '-', 'P', '-', '-', '-',},
	{'P', 'P', 'P', '-', '-', 'P', 'P', 'P',},
	{'R', '-', 'B', 'Q', 'K', 'B', 'H', 'R',},
	} };

	Board b(m);

	EXPECT_EQ(b.IsPinned({ 5,2 }), true);
	EXPECT_EQ(b.IsPinned({ 5,4 }), false);
}

TEST(IsPinnedTest, Pin3)
{
	CharMatrix m = { {
	{'r', 'h', 'b', '-', 'k', 'b', 'h', 'r',},
	{'p', 'p', 'p', 'p', '-', 'p', 'p', 'p',},
	{'-', '-', '-', '-', 'p', '-', '-', '-',},
	{'-', '-', '-', '-', '-', '-', '-', '-',},
	{'-', '-', '-', '-', '-', '-', 'P', 'q',},
	{'P', '-', '-', '-', '-', '-', '-', '-',},
	{'-', 'P', 'P', 'P', 'P', 'P', '-', 'P',},
	{'R', 'H', 'B', 'Q', 'K', 'B', 'H', 'R',},
	} };

	Board b(m);

	EXPECT_EQ(b.IsPinned({ 6, 5 }), true);
}

TEST(IsSameWayTest, Way1)
{
	CharMatrix m = { {
	{'r', 'h', 'b', '-', 'k', 'b', 'h', 'r',},
	{'p', 'p', 'p', 'p', '-', 'p', 'p', '-',},
	{'-', '-', '-', '-', '-', '-', '-', 'p',},
	{'-', '-', '-', '-', 'p', '-', '-', '-',},
	{'-', '-', '-', '-', 'P', '-', '-', '-',},
	{'P', '-', '-', '-', 'K', '-', '-', 'q',},
	{'-', 'P', 'P', 'P', '-', 'P', 'P', 'P',},
	{'R', 'H', 'B', 'Q', '-', 'B', 'H', 'R',},
	} };

	Board b(m);

	EXPECT_EQ(b.IsSameWay({ 5, 4 }, { 5, 3 }, EColor::White), true);
}

TEST(IsSameWayTest, Way2)
{
	CharMatrix m = { {
	{'r', 'h', 'b', '-', 'k', 'b', 'h', 'r',},
	{'-', '-', 'p', 'p', '-', 'p', 'p', '-',},
	{'p', 'p', '-', '-', '-', '-', '-', 'p',},
	{'-', '-', '-', '-', 'H', '-', '-', '-',},
	{'-', '-', '-', '-', 'P', 'K', '-', '-',},
	{'-', 'P', '-', '-', '-', 'q', '-', '-',},
	{'P', '-', 'P', 'P', '-', 'P', 'P', 'P',},
	{'R', 'H', 'B', 'Q', '-', 'B', '-', 'R',},
	} };

	Board b(m);
	EXPECT_EQ(b.IsSameWay({ 4, 5 }, { 3, 5 }, EColor::White), true);
}

TEST(IsSameWayTest, Way3)
{
	CharMatrix m = { {
	{'r', 'h', 'b', 'q', 'k', 'b', 'h', 'r',},
	{'-', '-', '-', 'p', '-', 'p', 'p', 'p',},
	{'p', 'p', 'p', '-', 'p', '-', '-', '-',},
	{'-', '-', '-', '-', '-', '-', '-', '-',},
	{'-', 'K', '-', '-', '-', '-', '-', '-',},
	{'-', '-', '-', 'P', '-', '-', '-', '-',},
	{'P', 'P', 'P', '-', 'P', 'P', 'P', 'P',},
	{'R', 'H', 'B', 'Q', '-', 'B', 'H', 'R',},
	} };

	Board b(m);
	EXPECT_EQ(b.IsSameWay({ 4, 1 }, { 5, 0 }, EColor::White), true);
}

TEST(Is3FoldTest, Fold1)
{
	CharMatrix m = { {
	{'r', 'h', 'b', 'q', 'k', 'b', 'h', 'r',},
	{'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p',},
	{'-', '-', '-', '-', '-', '-', '-', '-',},
	{'-', '-', '-', '-', '-', '-', '-', '-',},
	{'-', '-', '-', '-', '-', '-', '-', '-',},
	{'-', '-', '-', '-', '-', '-', '-', '-',},
	{'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P',},
	{'R', 'H', 'B', 'Q', 'K', 'B', 'H', 'R',},
	} };

	Board b(m);

	b.Move({ 7, 6 }, { 5, 5 });
	b.Move({ 0, 6 }, { 2, 5 });

	b.Move({ 5, 5 }, { 7, 6 });
	b.Move({ 2, 5 }, { 0, 6 });

	b.Move({ 7, 6 }, { 5, 5 });
	b.Move({ 0, 6 }, { 2, 5 });

	b.Move({ 5, 5 }, { 7, 6 });
	b.Move({ 2, 5 }, { 0, 6 });

	b.Move({ 7, 6 }, { 5, 5 });
	b.Move({ 0, 6 }, { 2, 5 });

	EXPECT_EQ(b.Is3Fold(), true);
}

TEST(Is3FoldTest, Fold2)
{
	CharMatrix m = { {
	{'r', 'h', 'b', 'q', 'k', 'b', 'h', 'r',},
	{'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p',},
	{'-', '-', '-', '-', '-', '-', '-', '-',},
	{'-', '-', '-', '-', '-', '-', '-', '-',},
	{'-', '-', '-', '-', '-', '-', '-', '-',},
	{'-', '-', '-', '-', '-', '-', '-', '-',},
	{'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P',},
	{'R', 'H', 'B', 'Q', 'K', 'B', 'H', 'R',},
	} };

	Board b(m);

	b.Move({ 6, 7 }, { 5, 7 });
	b.Move({ 1, 7 }, { 2, 7 });

	b.Move({ 7, 7 }, { 6, 7 });
	b.Move({ 0, 7 }, { 1, 7 });

	b.Move({ 6, 7 }, { 7, 7 });
	b.Move({ 1, 7 }, { 0, 7 });

	b.Move({ 7, 7 }, { 6, 7 });
	b.Move({ 0, 7 }, { 1, 7 });

	b.Move({ 6, 7 }, { 7, 7 });
	b.Move({ 1, 7 }, { 0, 7 });

	EXPECT_EQ(b.Is3Fold(), true);
}

TEST(IsPromotePossibleTest, Promote1)
{
	CharMatrix m = { {
	{'r', 'h', 'b', 'q', 'k', 'b', '-', 'r',},
	{'p', 'p', 'p', '-', 'p', 'p', 'P', 'p',},
	{'-', '-', '-', 'p', '-', 'h', '-', '-',},
	{'-', '-', '-', '-', '-', '-', '-', '-',},
	{'-', '-', '-', '-', '-', '-', '-', '-',},
	{'-', '-', '-', '-', '-', '-', '-', '-',},
	{'P', 'P', 'P', 'P', 'P', '-', 'P', 'P',},
	{'R', 'H', 'B', 'Q', 'K', 'B', 'H', 'R',},
	} };

	Board b(m);

	b.Move({ 1,6 }, { 0, 6 });

	EXPECT_EQ(b.IsPromotePossible({ 0, 6 }), true);
}

TEST(IsPromotePossibleTest, Promote2)
{
	CharMatrix m = { {
	{'r', 'h', 'b', 'q', 'k', 'b', 'h', 'r',},
	{'p', 'p', 'p', 'p', 'p', '-', 'p', 'p',},
	{'-', '-', '-', '-', '-', '-', '-', '-',},
	{'-', '-', '-', '-', '-', '-', '-', '-',},
	{'-', '-', '-', 'H', '-', '-', '-', '-',},
	{'P', 'P', '-', '-', '-', '-', '-', '-',},
	{'-', '-', 'P', 'P', 'P', 'P', 'p', 'P',},
	{'R', 'H', 'B', 'Q', 'K', 'B', '-', 'R',},
	} };

	Board b(m);

	b.Move({ 6, 6 }, { 7, 6 });

	EXPECT_EQ(b.IsPromotePossible({ 7, 6 }), true);
}

TEST(GetMovesCheckTest, MovesCheck1)
{
	CharMatrix m = { {
		{'r', 'h', 'b', '-', 'k', 'b', 'h', 'r'},
		{'-', '-', 'p', '-', '-', 'p', 'p', '-'},
		{'-', 'p', '-', 'P', 'p', 'q', '-', 'p'},
		{'p', '-', '-', '-', 'K', '-', '-', '-'},
		{'-', '-', '-', '-', '-', '-', '-', '-'},
		{'-', '-', '-', '-', '-', '-', '-', '-'},
		{'P', 'P', 'P', 'P', '-', 'P', 'P', 'P'},
		{'R', 'H', 'B', 'Q', '-', 'B', 'H', 'R'}
		} };

	Board b(m);

	PositionList moves = { {4, 4} };

	EXPECT_EQ(b.GetMovesCheck({ 3, 4 }), moves);
}

TEST(GetMovesCheckTest, MovesCheck2)
{
	CharMatrix m = { {
	{'r', 'h', 'b', '-', 'k', 'b', 'h', 'r'},
	{'p', 'p', 'p', '-', '-', 'p', 'p', 'p'},
	{'-', '-', '-', 'p', '-', '-', '-', '-'},
	{'-', '-', '-', '-', 'p', '-', 'q', '-'},
	{'-', '-', '-', '-', 'P', '-', '-', '-'},
	{'-', '-', '-', '-', 'K', '-', '-', '-'},
	{'P', 'P', 'P', 'P', '-', 'P', 'P', 'P'},
	{'R', 'H', 'B', 'Q', '-', 'B', 'H', 'R'}
	} };

	Board b(m);

	PositionList moves = { {5, 3}, {5, 5}, {6, 4} };

	EXPECT_EQ(b.GetMovesCheck({ 5, 4 }), moves);
}

TEST(CastelingTest, Casteling1)
{
	CharMatrix m = { {
	{'r', '-', 'b', 'q', 'k', 'b', 'h', 'r'},
	{'-', 'p', 'p', 'p', '-', 'p', 'p', 'p'},
	{'p', '-', 'h', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', 'p', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', 'H', 'P', '-'},
	{'P', 'P', 'P', 'P', 'P', 'P', 'B', 'P'},
	{'R', 'H', 'B', 'Q', 'K', '-', '-', 'R'}
	} };

	Board b(m);

	EXPECT_NO_THROW(b.Move({ 7, 4 }, { 7, 7 }));
}

TEST(CastelingTest, Casteling2)
{
	CharMatrix m = { {
	{'r', 'h', 'b', 'q', 'k', 'b', '-', 'r'},
	{'-', '-', '-', 'p', 'p', 'p', 'p', 'p'},
	{'p', '-', 'p', '-', '-', 'h', '-', '-'},
	{'-', 'p', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', 'H', 'P', 'B', '-', '-', '-'},
	{'P', 'P', 'P', 'Q', 'P', 'P', 'P', 'P'},
	{'R', '-', '-', '-', 'K', 'B', 'H', 'R'}
	} };

	Board b(m);

	EXPECT_NO_THROW(b.Move({ 7, 4 }, { 7, 0 }));
}

TEST(CastelingTest, Casteling3)
{
	CharMatrix m = { {
	{'r', 'h', 'b', 'q', 'k', '-', '-', 'r'},
	{'p', 'p', 'p', 'p', 'p', 'p', 'b', 'p'},
	{'-', '-', '-', '-', '-', 'h', 'p', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', 'P', '-', '-', '-', '-'},
	{'-', '-', 'H', '-', 'P', 'H', '-', '-'},
	{'P', 'P', 'P', '-', '-', 'P', 'P', 'P'},
	{'R', '-', 'B', 'Q', 'K', 'B', '-', 'R'}
	} };

	Board b(m);

	EXPECT_NO_THROW(b.Move({ 0, 4 }, { 0, 7 }));
}

TEST(CastelingTest, Casteling4)
{
	CharMatrix m = { {
	{'r', '-', '-', '-', 'k', 'b', 'h', 'r'},
	{'p', 'p', 'p', 'q', 'p', 'p', 'p', 'p'},
	{'-', '-', 'h', 'p', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', 'b', '-', '-'},
	{'-', '-', 'P', '-', 'P', '-', '-', '-'},
	{'-', '-', 'H', 'P', '-', 'H', '-', '-'},
	{'P', 'P', '-', '-', '-', 'P', 'P', 'P'},
	{'R', '-', 'B', 'Q', 'K', 'B', '-', 'R'}
	} };

	Board b(m);

	EXPECT_NO_THROW(b.Move({ 0, 4 }, { 0, 0 }));
}

TEST(FindSameColumnTest, Find1)
{
	CharMatrix m = { {
	{'r', 'h', 'b', 'q', 'k', 'b', 'h', 'r'},
	{'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', 'P', '-', '-', '-', '-', '-'},
	{'P', 'P', '-', 'P', 'P', 'P', 'P', 'P'},
	{'R', 'H', 'B', 'Q', 'K', 'B', 'H', 'R'}
	} };

	Board b(m);

	EXPECT_EQ(b.FindOnSameColumn({ 7,3 }, { 4,0 }), false);
}

TEST(EnPassantTest, Passant1)
{
	CharMatrix m = { {
	{'r', 'h', 'b', 'q', 'k', 'b', 'h', 'r'},
	{'p', 'p', 'p', 'p', '-', 'p', 'p', 'p'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', 'p', '-', '-', '-'},
	{'P', '-', 'H', '-', '-', '-', '-', '-'},
	{'-', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
	{'R', '-', 'B', 'Q', 'K', 'B', 'H', 'R'}
	} };

	Board b(m);

	EXPECT_NO_THROW(b.Move({ 6, 3 }, { 4, 3 }));
	EXPECT_NO_THROW(b.Move({ 4, 4 }, { 5, 3 }));
}

TEST(EnPassantTest, Passant2)
{
	CharMatrix m = { {
	{'r', 'h', 'b', 'q', 'k', 'b', 'h', 'r'},
	{'p', 'p', 'p', '-', 'p', 'p', 'p', 'p'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', 'P', '-', 'p', '-', '-', '-', '-'},
	{'P', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', 'P', 'P', 'P', 'P', 'P', 'P'},
	{'R', 'H', 'B', 'Q', 'K', 'B', 'H', 'R'}
	} };

	Board b(m);

	EXPECT_NO_THROW(b.Move({ 6, 4 }, { 4, 4 }));
	EXPECT_NO_THROW(b.Move({ 4, 3 }, { 5, 4 }));
}



TEST(GetHistoryTest, EmptyTest)
{
	Board b;

	MoveVector v = {};

	EXPECT_EQ(b.GetHistory(), v);
}

TEST(GetHistoryTest, NormalTest)
{
	Board b;

	b.Move({ 6,0 }, { 4,0 });
	b.Move({ 1,0 }, { 2,0 });

	MoveVector v = { {{6,0}, {4,0}}, {{1,0}, {2,0}} };

	EXPECT_EQ(b.GetHistory(), v);
}

TEST(FindCheckTest, InitialPos)
{
	Board b;

	Position p = { -1, -1 };

	EXPECT_EQ(b.FindCheck({ 0,4 }, EColor::Black), p);
	EXPECT_EQ(b.FindCheck({ 7,4 }, EColor::White), p);
}

TEST(FindCheckTest, CheckSituation)
{
	CharMatrix m = { {
	   {'r', 'h', 'b', '-', 'k', 'b', 'h', 'r'},
	   {'p', 'p', '-', 'p', 'p', 'p', 'p', 'p'},
	   {'-', '-', 'p', '-', '-', '-', '-', '-'},
	   {'q', '-', '-', '-', '-', '-', '-', '-'},
	   {'-', '-', '-', 'P', '-', '-', '-', '-'},
	   {'-', '-', '-', '-', 'P', '-', '-', '-'},
	   {'P', 'P', 'P', '-', '-', 'P', 'P', 'P'},
	   {'R', 'H', 'B', 'Q', 'K', 'B', 'H', 'R'}
	   } };

	Board b(m);

	EXPECT_EQ(b.FindCheck({ 7,4 }, EColor::White), Position(3, 0));
}

TEST(GenerateFENTest, Fen1)
{
	CharMatrix m = { {
	{'r', 'h', 'b', 'q', 'k', '-', 'h', 'r'},
	{'p', 'p', 'p', 'p', '-', '-', 'p', 'p'},
	{'-', '-', '-', '-', '-', 'p', '-', '-'},
	{'-', '-', '-', '-', 'p', '-', '-', '-'},
	{'-', 'b', '-', 'P', '-', '-', '-', '-'},
	{'-', '-', 'P', 'Q', '-', 'H', '-', '-'},
	{'P', 'P', '-', '-', 'P', 'P', 'P', 'P'},
	{'R', 'H', 'B', '-', 'K', 'B', '-', 'R'}
	} };

	Board b(m);

	String fen = "rnbqk1nr/pppp2pp/5p2/4p3/1b1P4/2PQ1N2/PP2PPPP/RNB1KB1R ";

	EXPECT_EQ(b.GetFEN(), fen);
}