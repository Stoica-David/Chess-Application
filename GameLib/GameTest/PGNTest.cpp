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