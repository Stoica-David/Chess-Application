#pragma once

#include "Piece.h"
#include "IPieceInfo.h"

#include<array>

using ChessBoard = std::array<std::array<PiecesPtr, 8>, 8>;

class Board
{
public:
	// Constructors
	Board();
	Board(const PiecePairVector&);

	// Setters
	PiecesPtr& operator[](Position p);

	bool IsOver(EColor color) const;

	IPieceInfoPtr GetPieceInfo(Position p) const;

	// Functions
	bool VerifyTheWay(Position p1, Position p2) const;
	PiecesPtr GetPiece(Position p) const;
	bool IsCheck(Position p, EColor color) const;
	Position FindCheck(Position p, EColor color) const;
	bool IsSameWay(Position p1, Position p2, EColor color) const;
	bool IsCheckMate(Position p, EColor color) const;
	Position FindKing(EColor) const;
	PieceVector RemainingPieces() const;
	void Move(Position p1, Position p2);
	bool IsDraw() const;
	
private:
	static bool PawnGoesDiagonally(Position p1, Position p2);
	PositionList GetMoves(Position p) const;
	bool FindHelp(Position p, EColor color) const;
	bool KillCheck(Position p, EColor color) const;
	PositionList DefendedPositions(Position p, EColor color) const;
	bool IsDefended(Position p, EColor color) const;
	bool SameColor(EColor color1, EColor color2) const; // TO REMOVE
	int Find(PieceVector v, EPieceType Piece) const;
	bool SameBishop()const;


private:
	ChessBoard m_board;
};