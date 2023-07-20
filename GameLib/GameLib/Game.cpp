#include "Game.h"

#include "PositionException.h"
#include "MoveException.h"
#include "InTheWayException.h"
#include "DoesntExistException.h"
#include "TurnException.h"
#include "PieceInfo.h"

#include <iostream>

IGamePtr IGame::Produce()
{
	return std::make_shared<Game>();
}

Game::Game() 
	: m_turn(EColor::White)
{
}

Game::Game(const Board& b, EColor color /*=EColor::White*/)
	: m_turn(color)
	, m_gameboard(b)
{
	
}

void Game::Move(Position p1, Position p2)
{
	if (!m_gameboard.PositionExists(p1) || !m_gameboard.PositionExists(p2))
	{
		throw PositionException("The given position is out of the table");
	}

	PiecesPtr currPiece = m_gameboard.GetPiece(p1);
	PiecesPtr nextPiece = m_gameboard.GetPiece(p2);

	if (!currPiece)
	{
		throw DoesntExistException("The piece doesn't exist");
	}

	if (currPiece->GetColor() != m_turn)
	{
		throw TurnException("It's the other player's turn");
	}

	m_gameboard.Move(p1, p2);

	SwitchTurn();
}

IPieceInfoPtr Game::GetPieceInfo(Position p) const
{
	if (auto piece = m_gameboard.GetPiece(p))
	{
		return PieceInfo::Produce(piece->GetType(), piece->GetColor());
	}

	return {};
}

PiecesPtr Game::GetPiece(Position p) const
{
	return m_gameboard.GetPiece(p);
}

EColor Game::GetTurn() const
{
	return m_turn;
}

bool Game::IsOver() const
{
	if (m_gameboard.IsDraw())
		return true;
	
	if (m_gameboard.IsOver(m_turn))
		return true;

	return false;

	//return IsDraw() || m_gameboard.IsOver(m_turn);
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


