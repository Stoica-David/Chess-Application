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

Game::Game(const CharMatrix& matrix, EColor color, EState state) : m_turn(color), m_state(state)
{
	m_gameboard = Board::Board(matrix);
}

static bool IsPositionValid(Position p)
{
	return (p.first >= 0 && p.first < 8) && (p.second >= 0 && p.second < 8);
}

void Game::Move(Position p1, Position p2)
{
	if (m_state == EState::Playing || m_state == EState::Check)
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

		if(m_gameboard.IsPromotePossible(p2))
		{
			UpdateState(EState::ChoosePiece);
			NotifyChoosePiece(p2);
		}
		else
		{
			SwitchTurn();
		}

		NotifyMove();

		if (m_gameboard.IsOver(EColor::White))
		{
			UpdateState(EState::BlackWon);
			NotifyGameOver(EOverState::BlackWon);
		}
		else if (m_gameboard.IsOver(EColor::Black))
		{
			UpdateState(EState::WhiteWon);
			NotifyGameOver(EOverState::WhiteWon);
		}
		else if (m_gameboard.IsCheck(m_gameboard.FindKing(m_turn), m_turn))
		{
			UpdateState(EState::Check);
			NotifyCheck();
		}
		else if (IsDraw())
		{
			UpdateState(EState::Draw);
			NotifyGameOver(EOverState::Draw);
		}
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

bool Game::IsPromoting() const
{
	return (m_state == EState::ChoosePiece);
}

void Game::PromoteTo(EPieceType pieceType)
{
	m_gameboard.PromoteTo(pieceType, m_turn);

	if (m_gameboard.IsCheckMate(EColor::White))
	{
		UpdateState(EState::BlackWon);
		NotifyGameOver(EOverState::BlackWon);
	}
	else if (m_gameboard.IsCheckMate(EColor::Black))
	{
		UpdateState(EState::WhiteWon);
		NotifyGameOver(EOverState::WhiteWon);
	}

	UpdateState(EState::Playing);
	SwitchTurn();
}

void Game::Restart()
{
	m_turn = EColor::White;
	m_state = EState::Playing;
	m_gameboard.Reset();
	NotifyRestart();
}

void Game::SwitchTurn()
{
	m_turn = m_turn == EColor::Black ? EColor::White : EColor::Black;
}

bool Game::Stalemate() const
{
	return (m_gameboard.IsStalemate(m_turn));
}

PositionList Game::GetMoves(Position p)
{
	return m_gameboard.GetMoves(p);
}

bool Game::IsCheck() const
{
	return m_state == EState::Check;
}

void Game::NotifyChoosePiece(Position p)
{
	for (const auto& x : m_listeners)
	{
		if (auto sp = x.lock())
		{
			sp->OnChoosePiece(p);
		}
	}
}

void Game::NotifyCheck()
{
	for (const auto& x : m_listeners)
	{
		if (auto sp = x.lock())
		{
			sp->OnCheck();
		}
	}
}

void Game::NotifyRestart()
{
	for (const auto& x : m_listeners)
	{
		if (auto sp = x.lock())
		{
			sp->OnRestart();
		}
	}
}

void Game::AddListener(IGameListenerPtr newListener)
{
	m_listeners.push_back(newListener);
}

void Game::RemoveListener(IGameListener* listener)
{
	auto func = [listener](IGameListenerWeakPtr el)
	{ 
		auto sp = el.lock();

		return !sp || listener == sp.get();
	};

	m_listeners.erase(std::remove_if(m_listeners.begin(), m_listeners.end(), func));
}

void Game::NotifyMove()
{
	for (const auto& x : m_listeners)
	{
		if (auto sp = x.lock())
		{
			sp->OnMove();
		}
	}
}

void Game::NotifyGameOver(EOverState state)
{
	for (const auto& x : m_listeners)
	{
		if (auto sp = x.lock())
		{
			sp->OnGameOver(state);
		}
	}
}

