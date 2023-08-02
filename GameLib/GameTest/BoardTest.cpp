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

	EXPECT_EQ(b.IsSameWay({5, 4}, { 5, 3 }, EColor::White), true);
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

	b.Move({6, 7}, {5, 7});
	b.Move({1, 7}, {2, 7});

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

	EXPECT_EQ(b.ParsePGN("1.c4 e6 2.f4 b6 "), v);
}

TEST(ParsePGNTest, PGN2)
{
	Board b;
	MoveVector v = { {{6,2}, {4,2}}, {{1,4}, {2,4}}, {{6,5}, {4,5}}, {{1,1}, {2,1}} };

	EXPECT_EQ(b.ParsePGN("1. bxa8=B Rh7 2. a5 h5 3. a6 h4 4. axb7 h3 5. bxa8=B Rh7 6. c4 Rh6 7. c5 Rh5 8. c6 f6 9. cxd7+ Kf7 10. dxc8=B Rh4 11. g3 Rh5 12. g4 f5 13. gxh5 f4 14. h6 f3 15. h7 Kg6 16. hxg8=B Kg5 17. Bgd5 Kh6 18. Bdc6 Qe8 19. e3 Qf7 20. Bfa6 Qg6 21. Bc6b7 Qh5 22. Bc6 Qh4 23. Ba6b7 Qg4 24. Ba6 Qg5 25. Bc8b7 Qg6 26. Bc8 Qf6 27. Ba8b7 Qf5 28. Ba8 Qh7 29. Bxf3 Qh8 30. Bfe2 Kg5 31. Bc6 g6 32. Bc6b7 e6 33. Bc6 e5 34. B8b7 e4 35. Bc8 Kh4 36. Bab7 g5 37. Bba6"), v);
}