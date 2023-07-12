#pragma once

#include "IPiece.h"

#include<memory>
#include <string>
#include <cmath>

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

class Piece:public IPiece
{
public:
	// Constructors
	Piece();
	Piece(EPieceType, EColor=EColor::none);

	// Getters
	EPieceType GetType() const;
	EColor GetColor() const;


	bool IsMoveRegular(int x_curr, int y_curr, int x_next, int y_next) override;

	//Functions

	

protected:
	EPieceType m_type;
	EColor m_color;
};