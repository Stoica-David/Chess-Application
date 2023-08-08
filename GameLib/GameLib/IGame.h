#pragma once

#include "IPieceInfo.h"
#include "Position.h"
#include "IGameListener.h"
#include "ChessTimer.h"

#include <string>
#include <unordered_map>

using String = std::string;
using IGamePtr = std::shared_ptr<class IGame>;
using PieceMap = std::unordered_map <EPieceType, int>;

enum class EFileFormat
{
	Fen,
	Pgn
};

class IGame
{
public:
	static IGamePtr Produce();

	virtual ~IGame() = default;

	virtual void AddListener(IGameListenerPtr) = 0;
	virtual void RemoveListener(IGameListener*) = 0;

	virtual void Restart() = 0;

	// Game Actions
	virtual void Move(Position, Position) = 0;
	virtual void ProposeDraw() = 0;
	virtual void DrawResponse(bool) = 0;
	virtual void PromoteTo(EPieceType) = 0;
	virtual void SetHistory(const MoveVector&) = 0;

	// Game status
	virtual bool IsDraw() const = 0;
	virtual bool IsOver() const = 0;
	virtual bool IsDrawProposed() const = 0;
	virtual bool IsCheck() const = 0;
	virtual bool IsPromoting() const = 0;
	virtual bool IsTimeExpired(ChessTimer) const = 0;

	virtual EColor GetTurn() const = 0;
	virtual PositionList GetMoves(Position p) const = 0;
	virtual MoveVector GetHistory() const = 0;
	virtual IPieceInfoPtr GetPieceInfo(Position) const = 0;
	virtual PieceMap GetPiecesLeft(EColor) const = 0;

	// Save/Load functionality
	virtual void Save(EFileFormat format, String& file) const = 0;
	virtual void Load(EFileFormat format, String& file) = 0;
};
