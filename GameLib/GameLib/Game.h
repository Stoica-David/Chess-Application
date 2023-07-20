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

	// IGame methods
	void Move(Position p1, Position p2) override;
	
	IPieceInfoPtr GetPieceInfo(Position) const override;
	EColor GetTurn() const override;

	bool IsOver() const override;

	//Other methods
	PiecesPtr GetPiece(Position) const;

private:
	bool PawnGoesDiagonally(Position p1, Position p2) const;
	bool SameColor(Position p1, Position p2) const;
	void SwitchTurn();

private:
	Board m_gameboard;
	EColor m_turn;
};