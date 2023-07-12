#include<iostream>
#include<memory>
#include "Board.h"
#include "Piece.h"


int main()
{

	Bishop b(EColor::white);
	Board myBoard;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			switch (myBoard.GetGameboard()[i][j]->GetType())
			{

			case EPieceType::King:
			{
				std::cout << "K ";
				break;
			}
			case EPieceType::Rook:
			{
				std::cout << "R ";
				break;
			}
			case EPieceType::Knight:
			{
				std::cout << "Kn ";
				break;
			}

			case EPieceType::Bishop:
			{
				std::cout << "B ";
				break;
			}
			case EPieceType::Pawn:
			{
				std::cout << "P ";
				break;
			}
			case EPieceType::Queen:
			{
				std::cout << "Q ";
				break;
			}
			default:
				std::cout << "- ";
				break;

			}
		}
		std::cout << std::endl;
	}
	//if (myBoard.PositionExists(1, 3) && myBoard.PositionExists(3, 5))
	//	if (b.IsMoveValid(1, 3, 3, 5))
	//		std::cout << "Miscarea este posibila\n";




	return 0;
}
