#include "Piece.h"

#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "King.h"
#include "Queen.h"
#include "Pawn.h"

Piece::Piece(EPieceType type, EColor color)
{
	m_type = type;
	m_color = color;
	m_hasMoved = false;
	m_leftPassant = false;
	m_rightPassant = false;
}

PiecesPtr Piece::Produce(EPieceType type, EColor color)
{
	switch (type)
	{
	case EPieceType::Rook:
		return std::make_shared<Rook>(color); 
	case EPieceType::Knight:
		return std::make_shared<Knight>(color); 
	case EPieceType::Bishop:
		return std::make_shared<Bishop>(color); 
	case EPieceType::Queen:
		return std::make_shared<Queen>(color); 
	case EPieceType::King:
		return std::make_shared<King>(color); 
	case EPieceType::Pawn:
		return std::make_shared<Pawn>(color); 
	}
	return {};
}

EPieceType Piece::GetType() const
{
	return m_type;
}

EColor Piece::GetColor() const
{
	return m_color;
}

bool Piece::GetHasMoved() const
{
	return m_hasMoved;
}

bool Piece::GetLeftPassant() const
{
	return m_leftPassant;
}

bool Piece::GetRightPassant() const
{
	return m_rightPassant;
}

void Piece::SetHasMoved(bool hasMoved)
{
	m_hasMoved = hasMoved;
}

void Piece::SetLeftPassant(bool option)
{
	m_leftPassant = option;
}

void Piece::SetRightPassant(bool option)
{
	m_rightPassant = option;
}

bool Piece::IsMoveRegular(Position p1, Position p2) const
{
	return true;
}

PositionList Piece::DeterminePattern(Position p1, Position p2) const
{
	return {};
}

PositionMatrix Piece::AllMoves(Position p) const
{
	return {};
}

bool Piece::Is(EPieceType type) const
{
	return m_type == type;
}

bool Piece::SameColor(PiecesPtr piece) const
{
	return m_color == piece->m_color;
}

bool Piece::IsColor(EColor color) const
{
	return (m_color == color);
}

int Piece::AbsValue(int x, int y)
{
	return (std::abs(x - y));
}
