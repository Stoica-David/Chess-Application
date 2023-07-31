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
	Game(const CharMatrix& matrix, EColor color = EColor::White, EState state = EState::Playing);
	
	// IGame methods
	void Move(Position p1, Position p2) override;
	void ProposeDraw() override;
	void DrawResponse(bool) override;

	IPieceInfoPtr GetPieceInfo(Position) const override;
	EColor GetTurn() const override;

	bool IsDraw() const override;
	bool IsOver() const override;
	bool IsDrawProposed() const override;
	bool IsCheck() const override;
	bool IsPromoting() const override;

	void PromoteTo(EPieceType pieceType) override;

	void Restart() override;
	
	void AddListener(IGameListenerPtr) override;
	void RemoveListener(IGameListener*) override;

	PositionList GetMoves(Position p) override;

	const IPieceInfoVector& GetWhiteDeadPieces() const override;
	const IPieceInfoVector& GetBlackDeadPieces() const override;

	String GenerateFEN() const override;

	//Other methods
	void NotifyMove();
	void NotifyGameOver(EOverState);
	void NotifyChoosePiece();
	void NotifyCheck();
	void NotifyRestart();

	PiecesPtr GetPiece(Position) const;
	bool Stalemate() const;


private:
	void SwitchTurn();
	void UpdateState(EState);

private:
	Board m_gameboard;
	EColor m_turn;
	EState m_state;
	ListenersList m_listeners;

};