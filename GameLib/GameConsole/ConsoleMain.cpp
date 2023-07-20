#include <iostream>
#include <windows.h>
#include "IGame.h"
#include "PositionException.h"
#include "MoveException.h"
#include "InTheWayException.h"
#define color_gray "\x1b[90m"
#define color_white "\x1b[37m"
#define color_black "\x1b[30m"
#define color_blue "\033[34m"
#define color_cyan "\033[36m"
#define color_yellow "\033[33m"
#define color_red "\033[31m"

void PrintMinus()
{
	for (int i = 0; i < 18; i++)
		std::cout << color_blue << "--";

	std::cout << std::endl << color_white;
}

void PrintVerticalLine()
{
	std::cout << color_blue << "|" << color_white;
}

void PrintHorizohtalLine()
{
	std::cout << color_blue << "--" << color_white;
}

void PrintSpace()
{
	std::cout << " ";
}

void Enter()
{
	std::cout << "\n";
}

void PrintBoard(const IGamePtr& game)
{
	char c;
	PrintMinus();
	PrintVerticalLine();
	PrintSpace();
	std::cout << color_blue << "X" << color_white;
	PrintSpace();
	PrintVerticalLine();
	PrintSpace();
	for (int i = 0; i < 8; i++)
	{
		c = 'A' + i;

		std::cout << color_yellow << c << color_yellow;

		PrintSpace();
		PrintVerticalLine();
		PrintSpace();
	}

	Enter();

	PrintMinus();

	for (int i = 0; i < 8; i++)
	{
		PrintVerticalLine();
		PrintSpace();
		std::cout << color_yellow << 8 - i << color_yellow;
		PrintSpace();
		PrintVerticalLine();

		for (int j = 0; j < 8; j++)
		{
			IPieceInfoPtr currPiece = game->GetPieceInfo({ i , j });

			if (!currPiece)
			{
				std::cout << color_cyan << " ~ " << color_cyan;
				PrintVerticalLine();
				continue;
			}
			switch (currPiece->GetType())
			{
			case EPieceType::Rook:
			{
				if (currPiece->GetColor() == EColor::Black)
					std::cout << color_black << " R ";
				else
					std::cout << color_white << " R ";

				PrintVerticalLine();
				break;
			}
			case EPieceType::Knight:
			{
				if (currPiece->GetColor() == EColor::Black)
					std::cout << color_black << " H ";
				else
					std::cout << color_white << " H ";

				PrintVerticalLine();
				break;
			}
			case EPieceType::Queen:
			{
				if (currPiece->GetColor() == EColor::Black)
					std::cout << color_black << " Q ";
				else
					std::cout << color_white << " Q ";

				PrintVerticalLine();
				break;
			}
			case EPieceType::Bishop:
			{
				if (currPiece->GetColor() == EColor::Black)
					std::cout << color_black << " B ";
				else
					std::cout << color_white << " B ";

				PrintVerticalLine();
				break;
			}
			case EPieceType::King:
			{
				if (currPiece->GetColor() == EColor::Black)
					std::cout << color_black << " K ";
				else
					std::cout << color_white << " K ";

				PrintVerticalLine();
				break;
			}
			case EPieceType::Pawn:
			{
				if (currPiece->GetColor() == EColor::Black)
					std::cout << color_black << " P ";
				else
					std::cout << color_white << " P ";

				PrintVerticalLine();
				break;
			}
			}
		}
		std::cout << "\n";
		PrintMinus();
	}

	std::cout << "\n\n";
}

void Play(const IGamePtr& game)
{
	char x1, y1, x2, y2;
	PrintBoard(game);

	do
	{
		try
		{
			EColor currTurn = game->GetTurn();

			if (currTurn == EColor::White)
				std::cout << color_white << "[White]";
			else
				std::cout << color_black <<"[Black]";

			std::cout << "Enter move: ";
			std::cin >> y1 >> x1 >> y2 >> x2;

			system("PAUSE");
			system("CLS");

			game->Move({ 8 - (x1 - '0'), y1 - 'A'}, {8 - (x2 - '0'), y2 - 'A'});
		}
		catch (char* const m)
		{
			std::cout << m;
		}
		catch (IException e)
		{
			std::cout << color_red << "[EXCEPTION]" << e.what() << "!\n" << color_white;
		}

		PrintBoard(game);

	} while (!game->IsOver());
}

int main()
{
	std::cout << "\033[100m"; // background
	std::cout << "\033[2J\033[H";

	IGamePtr game = IGame::Produce();

	Play(game);

	return 0;
}