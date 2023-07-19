#include "Game.h"

#include "PieceInfo.h"
#include <iostream>

IGamePtr IGame::Produce()
{
	return std::make_shared<Game>();
}

Game::Game():m_turn(EColor::Black)
{
}

bool Game::Move(Position p1, Position p2)
{
	SwitchTurn();
	PiecesPtr currPiece, nextPiece;

	int x1 = p1.first;
	int y1 = p1.second;
	int x2 = p2.first;
	int y2 = p2.second;

	if (!m_gameboard.PositionExists(p1) || !m_gameboard.PositionExists(p2))
		return false;

	currPiece = m_gameboard.GetPiece(p1);
	nextPiece = m_gameboard.GetPiece(p2);

	if (!currPiece || currPiece->GetColor() != m_turn)
	{
		std::cout << "da";
		return false;
	}

	if (currPiece->IsMoveRegular(p1, p2) && m_gameboard.VerifyTheWay(p1, p2))
	{
		if (currPiece->GetType() == EPieceType::Pawn 
			&& PawnGoesDiagonally(p1, p2)
			&& (!nextPiece || SameColor(p1, p2)))
		{
			return false;
		}

		if (nextPiece && SameColor(p1, p2))
		{
			return false;
		}

		m_gameboard.SetGameboard(p2, currPiece);
		m_gameboard.SetGameboard(p1, {});

		Position kingPos = m_gameboard.FindKing(currPiece->GetColor());

		if (m_gameboard.IsCheck(kingPos, m_turn))
		{
			m_gameboard.SetGameboard(p1, currPiece);
			m_gameboard.SetGameboard(p2, nextPiece);
			return false;
		}
		return true;
	}

	return false;
}

IPieceInfoPtr Game::GetPieceInfo(Position p) const
{
	auto piece = m_gameboard.GetPiece(p);

	return PieceInfo::Produce(piece->GetType(), piece->GetColor());
}

PiecesPtr Game::GetPiece(Position p) const
{
	return m_gameboard.GetPiece(p);
}

bool Game::PawnGoesDiagonally(Position p1, Position p2) const
{
	int x1 = p1.first, y1 = p1.second, x2 = p2.first, y2 = p2.second;
	
	return (std::abs(x2 - x1) == 1 && std::abs(y2 - y1) == 1);
}

bool Game::SameColor(Position p1, Position p2) const
{
	return (m_gameboard.GetPiece(p1)->GetColor() == m_gameboard.GetPiece(p2)->GetColor());
}

void Game::SwitchTurn()
{
	if (m_turn == EColor::Black)
		m_turn = EColor::White;
	else
		m_turn = EColor::Black;
}