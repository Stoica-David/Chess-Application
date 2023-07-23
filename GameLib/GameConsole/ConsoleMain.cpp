#include "MainMethods.h"


int main()
{
	SetBackground();

	IGamePtr game = IGame::Produce();

	Play(game);

	return 0;
}