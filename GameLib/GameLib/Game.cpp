#include "Game.h"
#include "GameExceptions.h"

IGamePtr IGame::Produce()
{
	return std::make_shared<Game>();
}

Game::Game()
	: m_turn(EColor::White)
	, m_state(EState::Playing)
{
}

Game::Game(const Board& b, EColor color /*=EColor::White*/)
	: m_turn(color)
	, m_gameboard(b)
	, m_state(EState::Playing)
{
}

static bool IsPositionValid(Position p)
{
	return (p.first >= 0 && p.first < 8) && (p.second >= 0 && p.second < 8);
}

void Game::Move(Position p1, Position p2)
{
	if (m_state == EState::Playing)
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

		if (m_gameboard.IsOver(EColor::White))
		{
			UpdateState(EState::BlackWon);
		}

		if (m_gameboard.IsOver(EColor::Black))
		{
			UpdateState(EState::WhiteWon);
		}

		if (m_gameboard.IsDraw())
		{
			UpdateState(EState::Draw);
		}

		SwitchTurn();
	}
}

void Game::ProposeDraw()
{
	UpdateState(EState::DrawIsProposed);
	SwitchTurn();
}

void Game::DrawResponse(bool draw)
{
	if (draw)
	{
		m_state = EState::Draw;
	}
	else
	{
		m_state = EState::Playing;
		SwitchTurn();
	}
}

IPieceInfoPtr Game::GetPieceInfo(Position p) const
{
	return m_gameboard.GetPieceInfo(p);
}

PiecesPtr Game::GetPiece(Position p) const
{
	return m_gameboard.GetPiece(p);
}

void Game::UpdateState(EState state)
{
	m_state = state;
}

EColor Game::GetTurn() const
{
	return m_turn;
}

bool Game::IsDraw() const
{
	return (m_gameboard.IsDraw() || m_state == EState::Draw || Stalemate());
}

bool Game::IsOver() const
{
	return (m_state == EState::Draw || m_state == EState::BlackWon || m_state == EState::WhiteWon);
}

bool Game::IsDrawProposed() const
{
	return (m_state == EState::DrawIsProposed);
}

void Game::PromoteTo(const std::string& string, Position p)
{
	if (string == "Queen")
		UpdatePiece(EPieceType::Queen, p);
	if (string == "Rook")
		UpdatePiece(EPieceType::Rook, p);
	if (string == "Bishop")
		UpdatePiece(EPieceType::Bishop, p);
	if (string == "Knight")
		UpdatePiece(EPieceType::Knight, p);
}

void Game::SwitchTurn()
{
	m_turn = m_turn == EColor::Black ? EColor::White : EColor::Black;
}

void Game::UpdatePiece(EPieceType type, Position p)
{
	m_gameboard[p] = {};
	m_gameboard[p] = Piece::Produce(type, m_turn);
}

bool Game::Stalemate() const
{
	return (m_gameboard.Stalemate(EColor::White) || m_gameboard.Stalemate(EColor::Black));
}

