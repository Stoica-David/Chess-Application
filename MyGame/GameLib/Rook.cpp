#include "Rook.h"

Rook::Rook() :Piece()
{
}

Rook::Rook(bool color, std::string curPosition) : Piece(color, curPosition)
{
}

std::list<std::string> Rook::calculatePossiblePositions()
{
	this->clearPossiblePositions();

	std::list<std::string> newPossiblePositions;	std::string currentPossiblePosition;

	currentPossiblePosition.push_back(this->getCurPosition()[0]);

	for (int i = 1; i <= 8; i++)
	{
		currentPossiblePosition.push_back(i + 48);
		newPossiblePositions.push_back(currentPossiblePosition);
		currentPossiblePosition.pop_back();
	}

	currentPossiblePosition.pop_back();

	currentPossiblePosition.push_back(this->getCurPosition()[1]);

	const std::string letters = "ABCDEFGH";

	for (auto curLetter : letters)
	{
		currentPossiblePosition.push_back(curLetter);
		std::swap(currentPossiblePosition[0], currentPossiblePosition[1]);
		newPossiblePositions.push_back(currentPossiblePosition);
		std::swap(currentPossiblePosition[0], currentPossiblePosition[1]);
		currentPossiblePosition.pop_back();
	}

	this->setPossiblePositions(newPossiblePositions);
}

bool Rook::move(std::string newPosition)
{
	if (checkPosition(newPosition) && checkMove(newPosition))
	{
		this->setCurPosition(newPosition);
		return true;
	}
	return false;
}

bool Rook::checkMove(std::string newPosition)
{
	return ((newPosition[0] == this->getCurPosition()[0]) || (newPosition[1] == this->getCurPosition()[1]));
}
