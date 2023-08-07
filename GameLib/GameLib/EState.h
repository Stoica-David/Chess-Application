#pragma once

enum class EState
{
	Standby,
	Playing,
	Draw,
	Check,
	WhiteWon,
	BlackWon,
	DrawIsProposed,
	ChoosePiece
};