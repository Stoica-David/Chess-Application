#pragma once

#include<memory>
#include <string>

using PiecesPtr = std::shared_ptr<class Piece>;

enum class EColor
{
	black,
	white,
	none
};

class Piece
{
public:
	// Constructors
	Piece();
	Piece(std::string, EColor=EColor::none);

	// Getters
	std::string GetName();
protected:
	std::string name;
	EColor color;
};