#pragma once

#include "IGame.h"
#include "Board.h"
#include "Piece.h"

#include<vector>
#include<memory>

class Game : public IGame
{
public:
	// Constructor
	Game();
	Game(const Board& b, EColor color = EColor::White);

	//Other methods
	PiecesPtr GetPiece(Position) const;

	//API methods
	bool Move(Position p1, Position p2) override;
	IPieceInfoPtr GetPieceInfo(Position) const override;
	EColor GetTurn() const override;
	bool IsDraw() const override;
	bool IsOver() const override;

private:
	bool PawnGoesDiagonally(Position p1, Position p2) const;
	bool SameColor(Position p1, Position p2) const;
	void SwitchTurn();
	int Find(PieceVector v, EPieceType Piece) const;
	bool SameBishop()const;
	bool IsOverWhite()const;
	bool IsOverBlack()const;

private:
	Board m_gameboard;
	EColor m_turn;
};