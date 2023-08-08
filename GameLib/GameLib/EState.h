#pragma once

enum class EState
{
	Playing,
	Draw,
	Check,
	WhiteWon,
	BlackWon,
	DrawIsProposed,
	ChoosePiece
};