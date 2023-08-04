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

TEST(ParsePGNTest, PGN1)
{
	Board b;
	MoveVector v = { {{6,2}, {4,2}}, {{1,4}, {2,4}}, {{6,5}, {4,5}}, {{1,1}, {2,1}} };

	EXPECT_NO_THROW(b.ParsePGN("1.c4 e6 2.f4 b6 "), v);
}

TEST(ParsePGNTest, PGN2)
{
	Board b;
	MoveVector v = { {{6,2}, {4,2}},  {{1,3}, {3,3}}, {{4,2}, {3,3}}, {{1,2}, {2,2}}, {{3,3}, {2,2}}, {{1,1}, {2,1}}, {{2,2}, {1,2}}, {{2,1}, {3,1}}, {{7,3}, {4,0}}, {{0,1}, {2,2}} };

	EXPECT_NO_THROW(b.ParsePGN("1.c4 d5 2.cxd5 c6 3.dxc6 b6 4.c7 b5 5.Qa4 Nc6 "), v);
}

TEST(ParsePGNTest, PGN3)
{
	Board b;
	MoveVector v = { {{6,2}, {4,2}},  {{1,3}, {3,3}}, {{4,2}, {3,3}}, {{1,2}, {2,2}}, {{3,3}, {2,2}}, {{1,1}, {2,1}}, {{2,2}, {1,2}}, {{2,1}, {3,1}}, {{7,3}, {4,0}}, {{0,1}, {2,2}} };

	EXPECT_NO_THROW(b.ParsePGN("1.d4 Nf6 2.h4 e6 3.h5 Ba3 4.h6 O-O "), v);
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

	EXPECT_EQ(b.FindSameColumn({ 7,3 }, { 4,0 }), false);
}

TEST(GeneratePGNTest, PGN1)
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

	MoveVector v = { { {6,2}, {4,2} }, { {1,3}, {3,3} }, { {4,2}, {3,3} }, { {1,2}, {2,2} }, { {3,3}, {2,2} }, { {1,1}, {2,1} }, { {2,2}, {1,2} }, { {2,1}, {3,1} }, { {7,3}, {4,0} }, { {0,1}, {2,2} } };

	Board b(m);

	for (const auto& move : v)
	{
		b.Move(move.first, move.second);
	}

	EXPECT_EQ(b.GeneratePGN(), "1.c4 d5 2.cxd5 c6 3.dxc6 b6 4.c7 b5 5.Qa4 Nc6 *");
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

TEST(SetBoardTest, FENTestGood)
{
	String FEN = "rnbqkbnr/pp1p2pp/2p5/4Np2/3P4/8/PPP2PPP/RNBQKB1R b";

	Board b;

	EXPECT_NO_THROW(b.SetBoard(FEN));
}

TEST(SetBoardTest, FENTestBad)
{
	String FEN = "rnbqkb1r/pp1ppppp/2p2n2/8/3P4/5N2/PPP1sPPPP/RNBQKB1R w";

	Board b;

	EXPECT_THROW(b.SetBoard(FEN), FENException);
}

TEST(SetBoardTest, PGNTestGood)
{
	String PGN = "1.d4 Nf6 2.h4 e6 3.h5 Ba3 4.h6 O-O 5.hxg7 e5 6.gxf8=N Ne8 7.Nxh7 f5 8.Be3 f4 9.Nc3 f3 10.Qd2 fxg2 11.O-O-O gxh1=Q 12.Ne4 Bb4 13.Nf3 a6 14.Neg5 a5 15.Ne4 a4 16.Nfg5 a3 17.Nf3 axb2+ 18.Kb1 Bc5 19.Nhg5 Bd6 20.c4 b5 21.Kc2 b1=B+ 22.Kc1 Bxe4 23.a3 Bb4 24.a4 d5 25.a5 Be6 26.Nh7 Qf6 27.a6 Qg6 28.a7 Qh4 29.axb8=Q Qhg4 30.Qa7 B4f5 31.Qa6 Be4 32.Qa5 B6f5 33.Qa4 Be6 34.Qa3 Q6f5 35.Qaa2 Qfg6 36.Qxb4 Q6h5 37.Qd6 Nf6 38.Qxe6+ Kh8 39.Qxf6+ Kg8 40.cxd5 b4 41.d6+ Kxh7 42.Rd3 b3 43.Rc3 b2+ 44.Kd2 b1=N+ 45.Ke1 c5 46.Qa6 Na3 47.Qxa8 Nc2+ 48.Rxc2 c4 49.Rxc4 Bb1 50.Rc7+ Qd7 51.Rxd7+ Qf7 52.Rxf7#";

	Board b;

	EXPECT_NO_THROW(b.SetBoard(PGN));
}

TEST(SetBoardTest, PGNTestBad)
{
	String PGN = "1.c4dadas d5 2.f3 f5 ";

	Board b;

	EXPECT_THROW(b.SetBoard(PGN), PGNException);
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