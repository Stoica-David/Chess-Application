#include<iostream>
#include <windows.h>
#include "IGame.h"
#include "PositionException.h"
#include "MoveException.h"
#include "InTheWayException.h"
#define color_gray "\x1b[90m"
#define color_white "\x1b[37m"
#define color_black "\x1b[30m"
#define color_bold_black "\033[1;30m"
#define color_dark_gray "\033[100m"

void PrintMinus()
{
	for (int i = 0; i < 18; i++)
		std::cout << color_black << "--";

	std::cout << std::endl;
}

void PrintVerticalLine()
{
	std::cout << color_black << "|";
}

void PrintHorizohtalLine()
{
	std::cout << color_black << "--";
}

void PrintSpace()
{
	std::cout << " ";
}

void Enter()
{
	std::cout << "\n";
}

void ResetColor()
{
	std::cout << color_white << "";
}

void PrintBoard(const IGamePtr& game)
{
	HANDLE console_color;
	console_color = GetStdHandle(STD_OUTPUT_HANDLE);

	char c;
	PrintMinus();
	PrintVerticalLine();
	PrintSpace();
	PrintSpace();
	PrintSpace();
	PrintVerticalLine();
	PrintSpace();
	for (int i = 0; i < 8; i++)
	{
		c = 'A' + i;

		std::cout << c;

		PrintSpace();
		PrintVerticalLine();
		PrintSpace();
	}

	Enter();

	PrintMinus();

	for (int i = 1; i < 9; i++)
	{
		PrintVerticalLine();
		PrintSpace();
		std::cout << i;
		PrintSpace();
		PrintVerticalLine();

		for (int j = 0; j < 8; j++)
		{
			IPieceInfoPtr currPiece = game->GetPieceInfo({ i - 1 , j });

			if (!currPiece)
			{
				std::cout << color_black << " ~ ";
				ResetColor();
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

				ResetColor();
				PrintVerticalLine();
				break;
			}
			case EPieceType::Knight:
			{
				if (currPiece->GetColor() == EColor::Black)
					std::cout << color_black << " H ";
				else
					std::cout << color_white << " H ";

				ResetColor();
				PrintVerticalLine();
				break;
			}
			case EPieceType::Queen:
			{
				if (currPiece->GetColor() == EColor::Black)
					std::cout << color_black << " Q ";
				else
					std::cout << color_white << " Q ";

				ResetColor();
				PrintVerticalLine();
				break;
			}
			case EPieceType::Bishop:
			{
				if (currPiece->GetColor() == EColor::Black)
					std::cout << color_black << " B ";
				else
					std::cout << color_white << " B ";

				ResetColor();
				PrintVerticalLine();
				break;
			}
			case EPieceType::King:
			{
				if (currPiece->GetColor() == EColor::Black)
					std::cout << color_black << " K ";
				else
					std::cout << color_white << " K ";

				ResetColor();
				PrintVerticalLine();
				break;
			}
			case EPieceType::Pawn:
			{
				if (currPiece->GetColor() == EColor::Black)
					std::cout << color_black << " P ";
				else
					std::cout << color_white << " P ";

				ResetColor();
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
	
	EColor currTurn = game->GetTurn();
	
	//if (currTurn == EColor::White)
	//	std::cout << "[White]";
	//else
	//	std::cout << "[Black]";

	//std::cout << "Enter move: ";
	//std::cin >> y1 >> x1 >> y2 >> x2;

	//system("PAUSE");
	//system("CLS");

	do
	{
		try
		{
			currTurn = game->GetTurn();

			if (currTurn == EColor::White)
				std::cout << "[White]";
			else
				std::cout << "[Black]";

			std::cout << "Enter move: ";
			std::cin >> y1 >> x1 >> y2 >> x2;

			game->Move({ x1 - '0' - 1, y1 - 'A'}, {x2 - '0' - 1, y2 - 'A'});
			
			//system("PAUSE");
			//system("CLS");
			PrintBoard(game);
		}
		catch (const char* m)
		{
			std::cout << m;
		}
		catch (IException e)
		{
			std::cout << e.what();
		}
		
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