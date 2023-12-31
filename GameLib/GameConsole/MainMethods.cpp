#include "MainMethods.h"

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


bool VerifyInput(const std::string& input)
{
	return((isalpha(input[0]) && isdigit(input[1]) && isalpha(input[2]) && isdigit(input[3])) || (input == "Draw"));
}

bool VerifyPieceName(const std::string& input)
{
	return (input == "Queen" || input == "Rook" || input == "Bishop" || input == "Knight");
}

std::string DeleteSpaces(std::string input)
{
	for (int i = 0; i < input.size(); i++)
		if (input[i] == ' ')
		{
			input.erase(input.begin() + i);
		}
	return input;
}

void Play(const IGamePtr& game)
{
	std::string input;
	bool clear = false;

	PrintBoard(game);

	do
	{
		try
		{
			clear = false;
			EColor currTurn = game->GetTurn();

			if (currTurn == EColor::White)
				std::cout << color_white << "[White]";
			else
				std::cout << color_black << "[Black]";

			if (!game->IsDrawProposed() && !game->ChoosePiece())
			{
				std::cout << "Enter move: ";

				std::getline(std::cin, input);

				input = DeleteSpaces(input);

				if (VerifyInput(input))
				{
					//TODO

					if (input == "Draw")
					{
						game->ProposeDraw();
					}
					else
					{
						game->Move({ 8 - (input[1] - '0'), input[0] - 'A' }, { 8 - (input[3] - '0'), input[2] - 'A' });
					}
				}
				else if (input.size() != 0)
				{
					std::cout << color_red << "[ERROR] Invalid string given";
				}
				else
				{
					system("CLS");
					clear = true;
				}
			}
			else if (game->IsDrawProposed())
			{
				std::string response;

				std::cout << "Agree to Draw? (yes/no): ";

				std::cin >> response;

				if (response == "yes")
				{
					game->DrawResponse(1);
				}
				if (response == "no")
				{
					game->DrawResponse(0);
				}
			}
			else
			{
				std::string pieceName;

				std::cout << "Type piece you want to promote to:";

				std::cin >> pieceName; std::cin.ignore();

				if (VerifyPieceName(pieceName))
				{
					game->PromoteTo(pieceName, { 8 - (input[3] - '0'), input[2] - 'A' });
				}
			}
		}
		catch (ChessException e)
		{
			std::cout << "\n" << color_red << "[EXCEPTION]" << e.what() << "!\n\n" << color_white;
		}

		if (!clear)
		{
			system("PAUSE");
			system("CLS");
		}

		PrintBoard(game);

	} while (!game->IsOver());
}

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

void SetBackground()
{
	std::cout << "\033[100m"; // background
	std::cout << "\033[2J\033[H";
}
