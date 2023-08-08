#pragma once

#include "IGame.h"
#include "Board.h"
#include "PGNHandler.h"
#include "EState.h"
#include "ChessTimer.h"

using ListenersList = std::vector<IGameListenerWeakPtr>;
using CharMatrix = std::array<std::array<char, 8>, 8>;

class Game : public IGame, public IGameStatus
{
public:
	// Constructor
	Game();
	Game(const Board& b, EColor color = EColor::White);
	Game(const CharMatrix& matrix, EColor color = EColor::White, EState state = EState::Playing);
	
	// IGame methods
	void AddListener(IGameListenerPtr) override;	// Observer
	void RemoveListener(IGameListener*) override;	// Observer

	void Restart() override;

	void Move(Position p1, Position p2) override;
	void ProposeDraw() override;
	void DrawResponse(bool) override;
	void PromoteTo(EPieceType pieceType) override;
	void SetHistory(const MoveVector&) override;

	bool IsDraw() const override;
	bool IsOver() const override;
	bool IsDrawProposed() const override;
	bool IsCheck() const override;
	bool IsPromoting() const override;
	bool IsTimeExpired(ChessTimer) const override;

	const IGameStatus* GetStatus() const override;

	EColor GetTurn() const override;
	PositionList GetMoves(Position p) const override;
	MoveVector GetHistory()const override;
	IPieceInfoPtr GetPieceInfo(Position) const override;
	PieceMap GetPiecesLeft(EColor)const override;

	void Save(EFileFormat format, const String& file) const override;
	void Load(EFileFormat format, const String& file) override;

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
	void NotifyTime(ChessTimer);

	// Other methods
	void SwitchTurn();
	void UpdateState(EState);

	void SaveFEN(const String& file) const;
	void LoadFEN(const String& file);

	void SavePGN(const String& file) const;
	void LoadPGN(const String& file);

private:
	Board m_gameboard;

	EColor m_turn;

	ChessTimer m_whiteTimer;
	ChessTimer m_blackTimer;

	EState m_state;
	
	ListenersList m_listeners;
	
	PGNHandler m_PGN;
};