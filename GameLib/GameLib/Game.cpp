#include "Game.h"

#include "PositionException.h"
#include "DoesntExistException.h"
#include "TurnException.h"

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

static bool IsPositionValid(Position p)
{
	return (p.first >= 0 && p.first < 8) && (p.second >= 0 && p.second < 8);
}

void Game::Move(Position p1, Position p2)
{
	if (!IsPositionValid(p1) || !IsPositionValid(p2))
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
	return m_gameboard.GetPieceInfo(p);
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
	return m_gameboard.IsDraw() || m_gameboard.IsOver(m_turn);
}

void Game::SwitchTurn()
{
	m_turn = m_turn == EColor::Black ? EColor::White : EColor::Black;
}


