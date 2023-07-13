#include<iostream>
#include "Game.h"

bool Game::Move(Position p1, Position p2)
{
	if (m_gameboard.GetGameboard()[p1.first][p1.second] && m_gameboard.PositionExists(p2) && m_gameboard.GetGameboard()[p1.first][p1.second]->IsMoveRegular(p1, p2) && m_gameboard.VerifyTheWay(p1, p2))
	{
		m_gameboard.GetGameboard()[p2.first][p2.second] = m_gameboard.GetGameboard()[p1.first][p1.second];
		m_gameboard.GetGameboard()[p1.first][p1.second] = {};
		return true;
	}
	return false;
}
