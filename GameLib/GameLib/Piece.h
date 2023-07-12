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
	Rook,
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
protected:
	EPieceType m_type;
	EColor m_color;
};