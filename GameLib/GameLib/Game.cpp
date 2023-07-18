#include "Game.h"

#include "PieceInfo.h"

IGamePtr IGame::Produce()
{
	return std::make_shared<Game>();
}

Game::Game()
{
}

ChessBoard Game::GetBoard() const
{
	return m_gameboard.GetGameboard();
}

bool Game::Move(Position p1, Position p2)
{
	PiecesPtr currPiece, nextPiece;

	int x1 = p1.first, y1 = p1.second, x2 = p2.first, y2 = p2.second;

	if (m_gameboard.PositionExists(p1) && m_gameboard.PositionExists(p2))
	{
		currPiece = m_gameboard.GetPiece({ x1, y1 });
		nextPiece = m_gameboard.GetPiece({ x2, y2 });
	}
	else
	{
		return false;
	}

	if (currPiece && currPiece->IsMoveRegular(p1, p2) && m_gameboard.VerifyTheWay(p1, p2))
	{
		if (currPiece->GetType() == EPieceType::Pawn && std::abs(x2 - x1) == 1 && std::abs(y2 - y1) == 1 && (!nextPiece || nextPiece->GetColor() == currPiece->GetColor()))
		{
			return false;
		}

		if (nextPiece && currPiece->GetColor() == nextPiece->GetColor())
		{
			return false;
		}

		m_gameboard.SetGameboard(p2, currPiece);
		m_gameboard.FreePosition(p1);

		Position kingPos;

		if (currPiece->GetColor() == EColor::White)
			kingPos = m_gameboard.FindKing(EColor::White);
		else
			kingPos = m_gameboard.FindKing(EColor::Black);

		if (m_gameboard.IsCheck(kingPos))
		{
			m_gameboard.SetGameboard(p1, currPiece);
			m_gameboard.FreePosition(p2);
			return false;
		}
		return true;
	}



	return false;
}

IPieceInfoPtr Game::GetPieceInfo(Position p) const
{
	return std::make_shared<PieceInfo>(m_gameboard.GetPiece(p)->GetType(), m_gameboard.GetPiece(p)->GetColor());
}
