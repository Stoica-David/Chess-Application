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
	void Set(const ChessBoard& board);
	void Reset();

	// Getters
	IPieceInfoPtr GetPieceInfo(Position p) const;

	String GetCurrPGN()const;

	BitMatrix GetPrevPositions()const;

	MoveVector GetHistory()const;

	// Elements access
	PiecesPtr& at(Position p);
	const PiecesPtr& at(Position p) const;

	// Methods that verify
	bool IsCheck(Position p, EColor color) const;
	bool IsCheckMate(EColor color) const;
	bool VerifyTheWay(Position p1, Position p2) const;
	bool IsPinned(Position p) const;
	bool IsSameWay(Position p1, Position p2, EColor color) const;
	bool IsOver(EColor color) const;
	bool IsDraw() const;
	bool IsStalemate(EColor color) const;
	bool Is3Fold() const;
	bool IsPromotePossible(Position p) const;
	bool IsEnPassant(Position p1, Position p2) const;
	bool FindOnSameColumn(Position p1, Position p2) const;
	bool PawnException(Position p1, Position p2) const;

	// Finders
	Position FindCheck(Position p, EColor color) const;
	Position FindKing(EColor) const;

	// Move related
	void Move(Position p1, Position p2);
	void PromoteTo(EPieceType pieceType, EColor color);

	PositionList GetMoves(Position p) const;
	PositionList GetMovesCheck(Position p) const;

	// FEN
	String GetFEN() const;
	void LoadFEN(const String&);

	// PGN
	void ParsePGN(StringVector Moves);

	static String GenerateInitial(EPieceType);

	// History
	ChessBoard ConvertBitset(int bitsetNr) const;

private:
	// Pawn related
	bool PawnGoesDiagonally(Position p1, Position p2) const;
	bool GoesTwoForward(int x1, int x2) const;
	bool CanMoveTwoForward(Position p1, Position p2) const;

	Position IntermediatePosition(Position p) const;

	// Draw related
	bool OnlyKing(EColor color)const;
	bool SameBishop()const;

	// Check/Checkmate helpers
	bool FindHelp(Position p, EColor color) const;
	bool KillCheck(Position p, EColor color) const;
	bool IsDefended(Position p, EColor color) const;
	bool FindOnSameLine(Position p1, Position p2) const;

	PositionList DefendedPositions(Position p, EColor color) const;

	// Finders
	int Find(PieceVector v, EPieceType Piece) const;

	PieceVector RemainingPieces() const;

	// History 
	void UpdatePrevPositions();

	Bitset GetCurrentPosition() const;

	// Castle
	bool IsCastle1(Position p1, Position p2) const;
	bool IsCastle2(Position p1, Position p2) const;
	bool CastleVerifyWay(Position p1, Position p2) const;

	void Castle1(Position p1, Position p2);
	void Castle2(Position p1, Position p2);

	// En Passant
	bool LeftPawnCheck(Position p) const;
	bool RightPawnCheck(Position p) const;
	bool IsLeftPassantPossible(Position p1, Position p2) const;
	bool IsRightPassantPossible(Position p1, Position p2) const;

	void EnPassant(Position p1, Position p2);
	void ResetEnPassant();

	// Move related
	PositionList GetMovesNormal(Position p) const;
	PositionList GetMovesPinned(Position p) const;
	PositionList GetMovesKing(Position p) const;
	PositionList GetPassantMoves(Position p)const;

	// PGN
	bool IsPrevPos(Position currPos, Position nextPos, EPieceType type, EColor color) const;

	Position FindPrevPos(Position nextPos, EPieceType type, EColor color, Position prevPos) const;

	String ConvertMove(Position p1, Position p2) const;

	// Static useful methods
	static PiecesPtr ProducePiece(char c);
	static EPieceType GetPieceType(char c);
	static EColor OppositeColor(EColor color);

private:
	ChessBoard m_board;

	BitMatrix m_prevPositions;

	MoveVector m_moves;

	String m_PGN;

	int m_nrMove;
};