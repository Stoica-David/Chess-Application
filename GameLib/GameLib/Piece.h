#pragma once

#include "IPiece.h"

#include<memory>
#include<vector>
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
	Piece(EPieceType, EColor = EColor::none);

	// Getters
	EPieceType GetType() const;
	EColor GetColor() const;

	//Functions
	bool IsMoveRegular(int x_curr, int y_curr, int x_next, int y_next) override;
	void DeterminePattern(int x_curr, int y_curr) override;

protected:
	EPieceType m_type;
	EColor m_color;
	std::vector<std::pair<int, int>> m_pattern;
};