#include<iostream>
#include<memory>
#include "Board.h"


int main()
{
	Board myBoard;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			std::cout << myBoard.GetGameboard()[i][j] << " ";
		}
		std::cout << std::endl;
	}

	return 0;
}