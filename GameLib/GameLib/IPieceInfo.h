#pragma once

#include "EPieceType.h"
#include "EColor.h"

#include <memory>

class IPieceInfo
{
public:
	virtual EPieceType GetType() const = 0;
	virtual EColor GetColor() const = 0;

	virtual ~IPieceInfo() = default;
};

using IPieceInfoPtr = std::shared_ptr<IPieceInfo>;