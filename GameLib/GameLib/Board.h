#pragma once

#include "Piece.h"
#include "IPieceInfo.h"

#include<array>
#include<string>
#include<bitset>

using ChessBoard = std::array<std::array<PiecesPtr, 8>, 8>;
using CharMatrix = std::array<std::array<char, 8>, 8>;
using BitMatrix = std::vector<std::bitset<256>>;
using Bitset = std::bitset<256>;
using PiecesVector = std::vector<PiecesPtr>;

class Board
{
public:
	// Constructors
	Board();
	Board(const CharMatrix&);

	// Setters
	PiecesPtr& operator[](Position p);

	// Getters
	IPieceInfoPtr GetPieceInfo(Position p) const;
	PiecesPtr GetPiece(Position p) const;

	// Functions
	bool IsOver(EColor color) const;
	bool VerifyTheWay(Position p1, Position p2) const;
	bool IsCheck(Position p, EColor color) const;
	bool IsSameWay(Position p1, Position p2, EColor color) const;
	bool IsCheckMate(EColor color) const;
	bool IsDraw() const;
	bool IsStalemate(EColor color) const;
	bool Is3Fold(const Bitset& bitset) const;
	bool IsPromotePossible(Position p) const;

	Position FindCheck(Position p, EColor color) const;
	Position FindKing(EColor) const;

	PieceVector RemainingPieces() const;

	void PromoteTo(EPieceType pieceType, EColor color);
	void UpdatePiece(EPieceType type, Position p, EColor color);
	void Move(Position p1, Position p2);
	void Reset();

	PositionList GetMoves(Position p) const;
	PositionList GetMovesNormal(Position p) const;
	PositionList GetMovesCheck(Position p) const;

	PiecesVector GetWhiteDead() const;
	PiecesVector GetBlackDead() const;

private:
	static bool PawnGoesDiagonally(Position p1, Position p2);

	bool OnlyKing(EColor color)const;
	bool FindHelp(Position p, EColor color) const;
	bool KillCheck(Position p, EColor color) const;
	bool IsDefended(Position p, EColor color) const;
	bool SameBishop()const;
	bool PawnException(Position p1, Position p2)const;
	bool IsCastle(Position p1, Position p2) const;

	PositionList DefendedPositions(Position p, EColor color) const;

	int Find(PieceVector v, EPieceType Piece) const;

	static EColor OppositeColor(EColor color)
	{
		if (color == EColor::White)
			return EColor::Black;
		return EColor::White;
	}

	Bitset GetCurrentPosition() const;

	void Castle(Position p1, Position p2);
	void UpdatePrevPositions();
	void InitializeWhite(char c, Position p);
	void InitializeBlack(char c, Position p);

	Position IntermediatePosition(Position p) const;
private:
	ChessBoard m_board;
	BitMatrix m_prevPositions;
	PiecesVector m_whiteDead;
	PiecesVector m_blackDead;
};