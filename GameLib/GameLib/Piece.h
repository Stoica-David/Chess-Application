#pragma once

#include "IPiece.h"
#include<memory>
#include <cmath>

using PiecesPtr = std::shared_ptr<class Piece>;
using PiecesVector = std::vector<PiecesPtr>;
using PiecePairVector = std::vector<std::pair<Position, PiecesPtr>>;
using PieceVector = std::vector<PiecesPtr>;

class Piece : public IPiece
{
public:
	// Constructors
	Piece(EPieceType, EColor);

	static PiecesPtr Produce(EPieceType type, EColor color);

	// Getters
	EPieceType GetType() const;
	EColor GetColor() const;

	bool GetHasMoved() const;
	bool GetLeftPassant() const;
	bool GetRightPassant() const;

	// Setters
	void SetHasMoved(bool);
	void SetLeftPassant(bool);
	void SetRightPassant(bool);

	// IPiece methods
	bool IsMoveRegular(Position p1, Position p2) const override;

	PositionList DeterminePattern(Position p1, Position p2) const override;

	PositionMatrix AllMoves(Position p) const override;

	// Other methods
	bool Is(EPieceType type) const;
	bool Is(EPieceType type, EColor color) const;
	bool SameColor(PiecesPtr piece) const;
	char ConvertPiece() const;

protected:
	static bool IsInTable(Position p)
	{
		int i = p.first;
		int j = p.second;

		return ((i >= 0 && i < 8) && (j >= 0 && j < 8));
	}

	bool IsColor(EColor) const;

	static int AbsValue(int, int);


protected:
	EPieceType m_type;
	EColor m_color;
	bool m_hasMoved;
	bool m_leftPassant;
	bool m_rightPassant;
};