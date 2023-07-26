#pragma once

#include "IGame.h"
#include "Board.h"
#include "Piece.h"
#include "EState.h"

#include<vector>
#include<memory>

using ListenersList = std::vector<IGameListenerWeakPtr>;

class Game : public IGame
{
public:
	// Constructor
	Game();
	Game(const Board& b, EColor color = EColor::White);
	Game(const CharMatrix& matrix, EColor color = EColor::White);
	

	// IGame methods
	void Move(Position p1, Position p2) override;
	void ProposeDraw() override;
	void DrawResponse(bool) override;

	IPieceInfoPtr GetPieceInfo(Position) const override;
	EColor GetTurn() const override;

	bool IsDraw() const override;
	bool IsOver() const override;
	bool IsDrawProposed() const override;

	bool IsPromoting() const override;
	void PromoteTo(EPieceType pieceType, Position p) override;

	void Restart() override;
	
	void AddListener(IGameListenerPtr) override;
	void RemoveListener(IGameListener*) override;

	//Other methods
	void NotifyMove();
	void NotifyGameOver();
	void NotifyDraw();
	void NotifyChoosePiece(Position);
	void NotifyCheck();

	PiecesPtr GetPiece(Position) const;
	bool Stalemate() const;

	PositionList GetMoves(Position p) override;

	bool IsCheck() const override;

private:
	void SwitchTurn();
	void UpdateState(EState);

private:
	Board m_gameboard;
	EColor m_turn;
	EState m_state;
	ListenersList m_listeners;
};