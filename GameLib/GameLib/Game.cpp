#include<iostream>
#include "Game.h"

bool Game::Move(Position p1, Position p2)
{
	//PiecesPtr currPiece = Game::m_gameboard.GetGameboard()[p1.first][p2.first];

	if (m_gameboard.GetGameboard()[p1.first][p1.second] && m_gameboard.PositionExists(p2) && m_gameboard.GetGameboard()[p1.first][p1.second]->IsMoveRegular(p1, p2) && m_gameboard.VerifyTheWay(p1, p2))
	{
		m_gameboard.SetGameboard(p2, m_gameboard.GetGameboard()[p1.first][p1.second]);
		m_gameboard.FreePosition(p1);
		return true;
	}
	return false;
}
