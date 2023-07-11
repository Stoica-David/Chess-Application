#pragma once

#include<list>
#include<string>

class Piece
{
private:
	bool color;
	std::string curPosition;
	std::list<std::string> possiblePositions;

public:
	// Constructors
	Piece();
	Piece(bool, std::string);

	// Setters
	void setColor(bool);
	void setCurPosition(std::string);
	void setPossiblePositions(std::list<std::string>);

	// Getters
	bool getColor();
	std::string getCurPosition();
	std::list<std::string> getPossiblePositions();

	// Other methods
	void showPossiblePositions();
	bool checkPosition(std::string);
	void clearPossiblePositions();
	
	virtual std::list<std::string> calculatePossiblePositions()=0;
	virtual bool move(std::string)=0;
	virtual bool checkMove(std::string)=0;
};