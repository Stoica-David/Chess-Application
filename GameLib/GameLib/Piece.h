#pragma once

#include "IPiece.h"

#include<memory>
#include<vector>
#include <cmath>
#include <utility>

using PiecesPtr = std::shared_ptr<class Piece>;

class Piece:public IPiece
{

public:
	// Constructors
	Piece(EPieceType, EColor);

	// Getters
	EPieceType GetType() const;
	EColor GetColor() const;

	//Functions
	bool IsMoveRegular(Position p1, Position p2) const override;
	PositionList DeterminePattern(Position p1, Position p2) const override;
	PositionMatrix AllMoves(Position p) const override;

protected:
	static bool IsInTable(int i, int j)
	{
		return ((i >= 0 && i < 8) && (j >= 0 && j < 8));
	}

	bool IsWhite() const;
	bool IsBlack() const;

	int AbsValue(int, int) const;

protected:
	EPieceType m_type;
	EColor m_color;
};