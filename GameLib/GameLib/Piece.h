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

enum class EPieceType
{
	Rook = 0,
	Knight,
	Bishop,
	Queen,
	King,
	Pawn,
	None
};

class Piece
{
public:
	// Constructors
	Piece();
	Piece(EPieceType, EColor=EColor::none);

	// Getters
	EPieceType GetType() const;

	//Functions
	virtual bool IsMoveValid(int x_curr, int y_curr, int x_next, int y_next) = 0;
protected:
	EPieceType m_type;
	EColor m_color;
};