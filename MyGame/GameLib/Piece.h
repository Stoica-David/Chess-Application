#pragma once
#include<list>
#include<string>

class Piece
{
protected:
	bool color;
	std::string name;
	std::pair<int, int> curPosition;
	std::list<std::pair<int, int>> possiblePositions;

public:
	// Constructors
	Piece();
	Piece(bool, std::string, std::pair<int, int>);

	// Setters
	void setColor(bool);
	void setName(std::string);
	void setCurPosition(std::pair<int, int>);

	// Getters
	bool getColor();
	std::string getName();
	std::pair<int, int>getCurPosition();
	std::list<std::pair<int, int>> getPossiblePositions();

	// Other methods
	void showPossiblePositions();
	bool checkPosition(std::string);
	void clearPossiblePositions();
	bool move(std::string);
	
	virtual std::list<std::string> calculatePossiblePositions()=0;
	virtual bool checkMove(std::string)=0;
};