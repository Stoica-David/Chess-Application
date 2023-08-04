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
using String = std::string;
using StringVector = std::vector<std::string>;

class Board
{
public:
	// Constructors
	Board();
	Board(const CharMatrix&);
	Board(const Board&);

	// Setters
	PiecesPtr& operator[](Position p);
	void SetHistory(const MoveVector& v);
	void SetBoard(const StringVector& string);

	// Getters
	IPieceInfoPtr GetPieceInfo(Position p) const;
	PiecesPtr GetPiece(Position p) const;
	MoveVector GetHistory()const;
	String GetCurrPGN()const;

	// Functions
	bool IsOver(EColor color) const;
	bool VerifyTheWay(Position p1, Position p2) const;
	bool IsCheck(Position p, EColor color) const;
	bool IsSameWay(Position p1, Position p2, EColor color) const;
	bool IsCheckMate(EColor color) const;
	bool IsDraw() const;
	bool IsStalemate(EColor color) const;
	bool Is3Fold() const;
	bool IsPromotePossible(Position p) const;
	bool IsPinned(Position p) const;

	Position FindCheck(Position p, EColor color) const;
	Position FindKing(EColor) const;

	PieceVector RemainingPieces() const;

	void PromoteTo(EPieceType pieceType, EColor color);
	void Move(Position p1, Position p2);
	void Reset();

	PositionList GetMoves(Position p) const;
	PositionList GetMovesNormal(Position p) const;
	PositionList GetMovesCheck(Position p) const;
	PositionList GetMovesPinned(Position p) const;

	String GenerateFEN() const;

	bool FindSameLine(Position p1, Position p2) const;
	bool FindSameColumn(Position p1, Position p2) const;

	void ParsePGN(StringVector Moves);

	String ConvertMove(Position p1, Position p2) const;

private:
	bool PawnGoesDiagonally(Position p1, Position p2) const;

	bool LeftPawnCheck(Position p) const;
	bool RightPawnCheck(Position p) const;
	bool OnlyKing(EColor color)const;
	bool FindHelp(Position p, EColor color) const;
	bool KillCheck(Position p, EColor color) const;
	bool IsDefended(Position p, EColor color) const;
	bool SameBishop()const;
	bool PawnException(Position p1, Position p2)const;
	bool IsCastle(Position p1, Position p2) const;
	bool IsEnPassant(Position p1, Position p2) const;

	PositionList DefendedPositions(Position p, EColor color) const;
	PositionList GetPassantMoves(Position p)const;

	int Find(PieceVector v, EPieceType Piece) const;

	static EColor OppositeColor(EColor color);

	Bitset GetCurrentPosition() const;

	void Castle(Position p1, Position p2);
	void UpdatePrevPositions();
	void EnPassant(Position p1, Position p2);
	void ResetEnPassant();
	bool IsLeftPassantPossible(Position p1, Position p2) const;
	bool IsRightPassantPossible(Position p1, Position p2) const;

	Position IntermediatePosition(Position p) const;

	static PiecesPtr ProducePiece(char c);
	static EPieceType GetPieceType(char c);

	Position FindPrevPos(Position nextPos, EPieceType type, EColor color, Position prevPos) const;

	void ValidateFEN(const String& s);

private:
	ChessBoard m_board;
	BitMatrix m_prevPositions;
	MoveVector m_moves;
	String m_PGN;
};