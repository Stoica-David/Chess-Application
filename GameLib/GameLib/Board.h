#pragma once

#include "Piece.h"
#include "IPieceInfo.h"

#include<array>
#include<string>

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

	// Getters
	IPieceInfoPtr GetPieceInfo(Position p) const;
	PiecesPtr GetPiece(Position p) const;

	// Functions
	bool VerifyTheWay(Position p1, Position p2) const;
	bool IsCheck(Position p, EColor color) const;
	bool IsSameWay(Position p1, Position p2, EColor color) const;
	bool IsCheckMate(Position p, EColor color) const;
	bool IsDraw() const;
	bool Stalemate(EColor color) const;

	Position FindCheck(Position p, EColor color) const;
	Position FindKing(EColor) const;
	PieceVector RemainingPieces() const;

	void PromoteTo(const std::string& string, Position p1, Position p2, EColor color);
	void UpdatePiece(EPieceType type, Position p, EColor color);
	
	void Move(Position p1, Position p2);
	
private:
	static bool PawnGoesDiagonally(Position p1, Position p2);
	bool OnlyKing(EColor color)const;
	bool FindHelp(Position p, EColor color) const;
	bool KillCheck(Position p, EColor color) const;
	bool IsDefended(Position p, EColor color) const;
	bool SameBishop()const;
	
	PositionList DefendedPositions(Position p, EColor color) const;
	PositionList GetMoves(Position p) const;
	
	int Find(PieceVector v, EPieceType Piece) const;


private:
	ChessBoard m_board;
};