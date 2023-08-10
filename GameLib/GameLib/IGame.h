#pragma once

#include "Position.h"
#include "IGameStatus.h"
#include "IGameListener.h"
#include "Timer.h"

#include <string>
#include <unordered_map>

using String = std::string;
using IGamePtr = std::shared_ptr<class IGame>;

enum class EFileFormat
{
	FEN,
	PGN
};

class IGame
{
public:
	static IGamePtr Produce(bool wantTimer = false);

	virtual ~IGame() = default;

	virtual void AddListener(IGameListenerPtr) = 0;
	virtual void RemoveListener(IGameListener*) = 0;

	virtual void Restart() = 0;

	// Game Actions
	virtual void Move(Position, Position) = 0;
	virtual void ProposeDraw() = 0;
	virtual void DrawResponse(bool) = 0;
	virtual void PromoteTo(EPieceType) = 0;
	virtual void ShowConfiguration(int confNr) = 0;

	// Game status
	virtual const IGameStatus* GetStatus() const = 0;

	// Save/Load functionality
	virtual void Save(EFileFormat format, const String& file) const = 0;
	virtual void Load(EFileFormat format, const String& file) = 0;
};
