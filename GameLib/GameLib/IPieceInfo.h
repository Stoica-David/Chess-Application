#pragma once

#include "EPieceType.h"
#include "EColor.h"

#include <memory>
#include <vector>

using IPieceInfoPtr = std::shared_ptr<class IPieceInfo>;
using IPieceInfoVector = std::vector<IPieceInfoPtr>;

class IPieceInfo
{
public:

	virtual EPieceType GetType() const = 0;

	virtual EColor GetColor() const = 0;

	virtual ~IPieceInfo() = default;
};
