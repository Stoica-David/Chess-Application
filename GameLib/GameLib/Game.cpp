#include <iostream>
#include "Game.h"

ChessBoard Game::GetBoard()
{
	return m_gameboard.GetGameboard();
}

bool Game::Move(Position p1, Position p2)
{
	PiecesPtr currPiece, nextPiece;

	if (m_gameboard.PositionExists(p1) && m_gameboard.PositionExists(p2))
	{
		currPiece = GetBoard()[p1.first][p1.second];
		nextPiece = GetBoard()[p2.first][p2.second];
	}
	else
	{
		return false;
	}

	if (currPiece && currPiece->IsMoveRegular(p1, p2) && m_gameboard.VerifyTheWay(p1, p2))
	{
		if (currPiece->GetType() == EPieceType::Pawn && std::abs(p2.first - p1.first) == 1 && std::abs(p2.second - p1.second) == 1 && (!nextPiece || nextPiece->GetColor() == currPiece->GetColor()))
		{
			return false;
		}

		if (nextPiece && currPiece->GetColor() == nextPiece->GetColor())
		{
			return false;
		}

		m_gameboard.SetGameboard(p2, currPiece);
		m_gameboard.FreePosition(p1);
		return true;
	}

	return false;
}
