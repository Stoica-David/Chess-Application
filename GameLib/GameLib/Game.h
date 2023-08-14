#pragma once

#include "IGame.h"
#include "Board.h"
#include "PGNHandler.h"
#include "EState.h"
#include "Timer.h"

using ListenersList = std::vector<IGameListenerWeakPtr>;
using CharMatrix = std::array<std::array<char, 8>, 8>;

class Game : public IGame, public IGameStatus
{
public:
	// Constructor
	Game(bool wantTimer = false);
	Game(const Board& b, EColor color = EColor::White, bool wantTimer = false);
	Game(const CharMatrix& matrix, EColor color = EColor::White, EState state = EState::Playing, bool wantTimer = false);

	~Game() {}
	
	// IGame methods
	void AddListener(IGameListenerPtr) override;	// Observer
	void RemoveListener(IGameListener*) override;	// Observer

	void Restart() override;

	void Move(Position p1, Position p2) override;
	void ProposeDraw() override;
	void DrawResponse(bool) override;
	void PromoteTo(EPieceType pieceType) override;

	bool IsDraw() const override;
	bool IsOver() const override;
	bool IsDrawProposed() const override;
	bool IsCheck() const override;
	bool IsPromoting() const override;
	bool IsFrozen() const override;
	bool IsPlaying() const override;

	const IGameStatus* GetStatus() const override;

	EColor GetTurn() const override;
	PositionList GetMoves(Position p) const override;
	MoveVector GetHistory()const override;
	IPieceInfoPtr GetPieceInfo(Position) const override;

	PiecesLeftVector GetPiecesLeft(EColor)const override;

	void Save(EFileFormat format, const String& file) const override;
	void Load(EFileFormat format, const String& file) override;

	void PauseGame() override;
	void ResumeGame() override;

	void ShowConfiguration(int confNr);

	int GetMs(EColor color) const override;

	//Other methods
	PiecesPtr GetPiece(Position) const;

	bool Stalemate() const;

	void UpdateState(EState);

private:
	// Observer methods
	void NotifyMove();
	void NotifyGameOver(EOverState);
	void NotifyChoosePiece();
	void NotifyCheck();
	void NotifyRestart();
	void NotifyCaptured(EPieceType type, EColor color);
	void NotifyTimerChange();

	//Move method
	void NotifyIfCaptured(Position, Position);

	// Other methods
	void SwitchTurn();

	void SaveFEN(const String& file) const;
	void LoadFEN(const String& file);

	void SavePGN(const String& file) const;
	void LoadPGN(const String& file);

private:
	Board m_gameboard;

	EColor m_turn;

	Timer m_timer;

	EState m_state;
	EState m_initialState;
	
	ListenersList m_listeners;
	
	PGNHandler m_PGN;

	bool m_wantTimer;
};