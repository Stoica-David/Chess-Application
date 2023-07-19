#include "Game.h"

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

bool Game::Move(Position p1, Position p2)
{
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

		m_gameboard[p2] = currPiece;
		m_gameboard[p1] = {};

		Position kingPos = m_gameboard.FindKing(currPiece->GetColor());

		if (m_gameboard.IsCheck(kingPos, m_turn))
		{
			m_gameboard[p1] = currPiece;
			m_gameboard[p2] = nextPiece;
			return false;
		}

		SwitchTurn();
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

EColor Game::GetTurn() const
{
	return m_turn;
}

bool Game::IsDraw() const
{
	PieceVector remaining = m_gameboard.RemainingPieces();

	if (remaining.size() <= 4)
	{
		if (remaining.size() == 2)
		{
			return true;
		}

		if (Find(remaining, EPieceType::Queen) == 1)
		{
			return true;
		}

		if (Find(remaining, EPieceType::Rook) == 1)
		{
			return true;
		}

		if (Find(remaining, EPieceType::Pawn) == 1)
		{
			return true;
		}

		if (Find(remaining, EPieceType::Knight) == 1)
		{
			return true;
		}

		if ((Find(remaining, EPieceType::Bishop) == 2 && !SameBishop()) || Find(remaining, EPieceType::Bishop) == 1)
		{
			return true;
		}
	}

	return false;
}

bool Game::IsOver() const
{
	if (IsDraw())
	{
		return true;
	}
	else if (IsOverWhite())
	{
		return true;
	}
	else if (IsOverBlack())
	{
		return true;
	}

	return false;
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

int Game::Find(PieceVector v, EPieceType Piece) const
{
	int cnt = 0;
	for (const auto& x : v)
		if (x->GetType() == Piece)
			cnt++;
	return cnt;
}

bool Game::SameBishop() const
{
	EColor color1 = {},
		color2 = {};

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (m_gameboard.GetPiece({ i, j }))
			{
				if (m_gameboard.GetPiece({ i, j })->GetType() == EPieceType::Bishop)
				{
					if (color1 == EColor::Black || color1 == EColor::White)
						color2 = m_gameboard.GetPiece({ i, j })->GetColor();
					else
						color1 = m_gameboard.GetPiece({ i, j })->GetColor();
				}
			}
		}
	}
	return color1 == color2;

}

bool Game::IsOverWhite() const
{
	Position whiteKingPos = m_gameboard.FindKing(EColor::White);
	return (m_gameboard.IsCheckMate(whiteKingPos, EColor::White));
}

bool Game::IsOverBlack() const
{
	Position blackKingPos = m_gameboard.FindKing(EColor::Black);
	return (m_gameboard.IsCheckMate(blackKingPos, EColor::Black));
}
