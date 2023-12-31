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
	bool Is(EColor color) const;
	bool Is(EPieceType type, EColor color) const;
	bool SameColor(PiecesPtr piece) const;

	char ConvertPiece() const;

protected:
	static int AbsValue(int, int);

	static bool IsInTable(Position p);

	bool IsColor(EColor) const;

protected:
	EColor m_color;

	EPieceType m_type;
	
	bool m_hasMoved;
	bool m_leftPassant;
	bool m_rightPassant;
};