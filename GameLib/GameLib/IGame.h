#pragma once

#include "IPieceInfo.h"
#include "Position.h"
#include "IGameListener.h"
#include "ChessTimer.h"

#include <string>
#include <unordered_map>

using IGamePtr = std::shared_ptr<class IGame>;
using String = std::string;
using PieceMap = std::unordered_map <EPieceType, int>;

class IGame
{
public:
	static IGamePtr Produce();

	virtual void Restart() = 0;
	virtual void Move(Position, Position) = 0;
	virtual void ProposeDraw() = 0;
	virtual void DrawResponse(bool) = 0;
	virtual void PromoteTo(EPieceType) = 0;
	virtual void SetHistory(const MoveVector&) = 0;
	
	virtual void SaveFEN(const String& file) const = 0;
	virtual void LoadFEN(const String& file) = 0;

	virtual void SavePGN(const String& file) const  = 0;
	virtual void LoadPGN(const String& file) = 0;

	virtual void AddListener(IGameListenerPtr) = 0;
	virtual void RemoveListener(IGameListener*) = 0;

	virtual bool IsDraw() const = 0;
	virtual bool IsOver() const = 0;
	virtual bool IsDrawProposed() const = 0;
	virtual bool IsCheck() const = 0;
	virtual bool IsPromoting() const = 0;
	virtual bool IsTimeExpired(ChessTimer) const = 0;

	virtual EColor GetTurn() const = 0;

	virtual PositionList GetMoves(Position p) const = 0;

	virtual MoveVector GetHistory()const = 0;

	virtual IPieceInfoPtr GetPieceInfo(Position) const = 0;
	
	virtual PieceMap PiecesLeft(EColor) const = 0;

	virtual ~IGame() = default;
};
