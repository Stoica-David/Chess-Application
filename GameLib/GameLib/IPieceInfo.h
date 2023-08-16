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
	/**
 * Return type of a piece
 *
 * @return EPieceType type of piece
 */
	virtual EPieceType GetType() const = 0;

	/**
 * Return color of a piece
 *
 * @return EColor color of piece
 */
	virtual EColor GetColor() const = 0;

	/**
 * Necessary virtual destructor
 */
	virtual ~IPieceInfo() = default;
};
