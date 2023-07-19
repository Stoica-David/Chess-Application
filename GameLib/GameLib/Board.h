#pragma once

#include "Piece.h"

#include<array>

using ChessBoard = std::array<std::array<PiecesPtr, 8>, 8>;

class Board
{
public:
	// Constructors
	Board();
	Board(const PiecePairVector&);

	// Getters
	ChessBoard GetGameboard() const;

	// Setters
	void SetGameboard(Position p, PiecesPtr newPiece);

	// Functions
	bool PositionExists(Position p) const;
	bool VerifyTheWay(Position p1, Position p2) const;
	PiecesPtr GetPiece(Position p) const;
	bool IsCheck(Position p, EColor color) const;
	Position FindCheck(Position p, EColor color) const;
	bool IsSameWay(Position p1, Position p2, EColor color) const;
	bool IsCheckMate(Position p, EColor color) const;
	Position FindKing(EColor) const;
	PieceVector RemainingPieces() const;
	
private:
	PositionList GetMoves(Position p) const;
	bool FindHelp(Position p, EColor color) const;
	bool KillCheck(Position p, EColor color) const;
	PositionList DefendedPositions(Position p, EColor color) const;
	bool IsDefended(Position p, EColor color) const;
	bool SameColor(EColor color1, EColor color2) const;


private:
	ChessBoard m_board;
};