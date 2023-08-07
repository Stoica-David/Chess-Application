#include "PGNHandler.h"
#include "BoardExceptions.h"
#include "gtest/gtest.h"
#include <fstream>

TEST(AddMoveTest, AddMove1)
{
	PGNHandler p;
	StringVector v = { "f4", "e5", "Nc3", "Nc6", "e3", "Bb4" };

	p.AddMove("f4");
	p.AddMove("e5");
	p.AddMove("Nc3");
	p.AddMove("Nc6");
	p.AddMove("e3");
	p.AddMove("Bb4");

	EXPECT_EQ(p.GetMoves(), v);
}

TEST(SavePGNTEST, Save1)
{
	String pgnstr;
	PGNHandler p;

	p.AddMove("f4");
	p.AddMove("e5");
	p.AddMove("Nc3");
	p.AddMove("Nc6");
	p.AddMove("e3");
	p.AddMove("Bb4");

	p.SavePGNToFile("PGN/m_pgn.pgn");

	std::ifstream f("PGN/m_pgn.pgn");
	while (!f.eof())
	{
		std::string s;
		f >> s;
		if (s == " ")
		{
			pgnstr += ' ';
			continue;
		}
		if (s == "\n")
		{
			pgnstr += '\n';
			continue;
		}
		pgnstr += s;
	}

	EXPECT_EQ(pgnstr, "[Event\"?\"][Site\"?\"][Date\"????.??.??\"][Round\"?\"][White\"?\"][Black\"?\"][Result\"*\"]1.f4e52.Nc3Nc63.e3Bb4*");
}

TEST(ParseToPGNTest, Parse2)
{
	PGNHandler p;

	p.AddMove("e4");
	p.AddMove("f5");
	p.AddMove("Nc3");
	p.AddMove("nc6");
	p.AddMove("f3");
	p.AddMove("d5");
	p.AddMove("exd5");
	p.AddMove("nd4");
	p.AddMove("g4");
	p.AddMove("nf6");
	p.AddMove("Bb5+");
	p.AddMove("bd7");
	p.AddMove("gxf5");
	p.AddMove("c6");
	p.AddMove("dxc6");
	p.AddMove("bxc6");
	p.AddMove("Bxc6+");
	p.AddMove("xc6");
	p.AddMove("Qe2");
	p.AddMove("ne4");
	p.AddMove("fxe4");
	p.AddMove("g5");
	p.AddMove("Nd5");
	p.AddMove("nd4");

	p.SavePGNToFile("PGN/m_pgn1.pgn");

	std::ifstream f("PGN/m_pgn1.pgn");
	String pgnstr;

	if (f.is_open())
	{
		std::string s;
		while (std::getline(f, s))
		{
			if(s != "")
			pgnstr += s + " ";
		}

		f.close();
	}

	EXPECT_EQ(pgnstr, "[Event \"?\"] [Site \"?\"] [Date \"????.??.??\"] [Round \"?\"] [White \"?\"] [Black \"?\"] [Result \"*\"] 1.e4 f5 2.Nc3 nc6 3.f3 d5 4.exd5 nd4 5.g4 nf6 6.Bb5+ bd7 7.gxf5 c6 8.dxc6 bxc6 9.Bxc6+ xc6 10.Qe2 ne4 11.fxe4 g5 12.Nd5 nd4 * ");
}

TEST(SavePGNFileTest, PGNFile1)
{

	PGNHandler p;

	p.AddMove("e4");
	p.AddMove("f5");
	p.AddMove("Nc3");
	p.AddMove("nc6");
	p.AddMove("f3");
	p.AddMove("d5");
	p.AddMove("exd5");
	p.AddMove("nd4");
	p.AddMove("g4");
	p.AddMove("nf6");
	p.AddMove("Bb5+");
	p.AddMove("bd7");
	p.AddMove("gxf5");
	p.AddMove("c6");
	p.AddMove("dxc6");
	p.AddMove("bxc6");
	p.AddMove("Bxc6+");
	p.AddMove("xc6");
	p.AddMove("Qe2");
	p.AddMove("ne4");
	p.AddMove("fxe4");
	p.AddMove("g5");
	p.AddMove("Nd5");
	p.AddMove("nd4");

	p.LoadPGNFromFile("PGN/m_pgn1.pgn");

	EXPECT_EQ(p.GetPGN(), "[Event \"?\"]\n[Site \"?\"]\n[Date \"????.??.??\"]\n[Round \"?\"]\n[White \"?\"]\n[Black \"?\"]\n[Result \"*\"]\n\n1.e4 f5 2.Nc3 nc6 3.f3 d5 4.exd5 nd4 5.g4 nf6 6.Bb5+ bd7 7.gxf5 c6 8.dxc6 bxc6 9.Bxc6+ xc6 10.Qe2 ne4 11.fxe4 g5 12.Nd5 nd4 *");
}