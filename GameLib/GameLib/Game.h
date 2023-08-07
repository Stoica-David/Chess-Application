#pragma once

#include "IGame.h"
#include "Board.h"
#include "Piece.h"
#include "PGNHandler.h"
#include "EState.h"

#include<vector>
#include<memory>
#include<unordered_map>

using ListenersList = std::vector<IGameListenerWeakPtr>;
using PieceMap = std::unordered_map <EPieceType, int>;

class Game : public IGame
{
public:
	// Constructor
	Game();
	Game(const Board& b, EColor color = EColor::White);
	Game(const CharMatrix& matrix, EColor color = EColor::White, EState state = EState::Playing);
	
	// IGame methods
	void Restart() override;
	void Move(Position p1, Position p2) override;
	void ProposeDraw() override;
	void DrawResponse(bool) override;
	void PromoteTo(EPieceType pieceType) override;
	void SetHistory(const MoveVector&) override;
	
	String SaveFEN() const override;
	void LoadFEN(const String&) override;
	
	void SavePGN(const String&)override;
	void LoadPGN(const String&) override;

	void AddListener(IGameListenerPtr) override;
	void RemoveListener(IGameListener*) override;

	bool IsDraw() const override;
	bool IsOver() const override;
	bool IsDrawProposed() const override;
	bool IsCheck() const override;
	bool IsPromoting() const override;

	EColor GetTurn() const override;
	
	PositionList GetMoves(Position p) override;
	
	MoveVector GetHistory()const override;

	IPieceInfoPtr GetPieceInfo(Position) const override;
	
	PieceMap PiecesLeft(EColor)const override;

	//Other methods
	PiecesPtr GetPiece(Position) const;

	bool Stalemate() const;

private:
	// Observer methods
	void NotifyMove();
	void NotifyGameOver(EOverState);
	void NotifyChoosePiece();
	void NotifyCheck();
	void NotifyRestart();
	void NotifyCaptured(EPieceType type, EColor color);

	// Other methods
	void SwitchTurn();
	void UpdateState(EState);

private:
	Board m_gameboard;
	EColor m_turn;
	EState m_state;
	ListenersList m_listeners;
	PGNHandler m_PGN;
};