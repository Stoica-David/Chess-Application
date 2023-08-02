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

		EPieceType type;
		EColor color;
		bool pieceCaptured = false;

		if (nextPiece)
		{
			pieceCaptured = true;
			type = nextPiece->GetType();
			color = nextPiece->GetColor();
		}

		m_gameboard.Move(p1, p2);

		currPiece = m_gameboard.GetPiece(p1);

		if (!currPiece && pieceCaptured)
		{
			NotifyCaptured(type, color);
		}

		if (m_gameboard.IsPromotePossible(p2))
		{
			UpdateState(EState::ChoosePiece);
			NotifyChoosePiece();
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
		else if (Stalemate() || m_gameboard.IsDraw() || m_gameboard.Is3Fold())
		{
			UpdateState(EState::Draw);
			NotifyGameOver(EOverState::Draw);
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
	m_state = draw ? EState::Draw : EState::Playing;
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
	return m_state == EState::Draw;
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

std::unordered_map<EPieceType, int> Game::PiecesLeft(EColor color)const
{
	std::unordered_map <EPieceType, int> leftPieces;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			PiecesPtr piece = m_gameboard.GetPiece({ i, j });

			if (piece && piece->GetColor() == color)
			{
				leftPieces[piece->GetType()]++;
			}
		}
	}

	return leftPieces;
}

void Game::SwitchTurn()
{
	m_turn = m_turn == EColor::Black ? EColor::White : EColor::Black;
}

bool Game::Stalemate() const
{
	return (m_gameboard.IsStalemate(m_turn));
}

String Game::GenerateFEN() const
{
	String FEN = m_gameboard.GenerateFEN();

	if (m_turn == EColor::White)
	{
		FEN.push_back('w');
	}
	else
	{
		FEN.push_back('b');
	}

	return FEN;
}

String Game::GeneratePGN() const
{
	String PGN = m_gameboard.GeneratePGN();

	if (m_state == EState::BlackWon)
	{
		PGN.push_back(' ');
		PGN.push_back('0');
		PGN.push_back('-');
		PGN.push_back('1');
	}
	else if (m_state == EState::WhiteWon)
	{
		PGN.push_back(' ');
		PGN.push_back('1');
		PGN.push_back('-');
		PGN.push_back('0');
	}
	else if (m_state == EState::Draw)
	{
		PGN.push_back(' ');
		PGN.push_back('1');
		PGN.push_back('/');
		PGN.push_back('2');
		PGN.push_back('-');
		PGN.push_back('1');
		PGN.push_back('/');
		PGN.push_back('2');
	}

	return PGN;
}

MoveVector Game::GetHistory() const
{
	return m_gameboard.GetHistory();
}

PositionList Game::GetMoves(Position p)
{
	return m_gameboard.GetMoves(p);
}

bool Game::IsCheck() const
{
	return m_state == EState::Check;
}

void Game::NotifyChoosePiece()
{
	for (const auto& x : m_listeners)
	{
		if (auto sp = x.lock())
		{
			sp->OnChoosePiece();
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

void Game::NotifyCaptured(EPieceType type, EColor color)
{
	for (const auto& x : m_listeners)
	{
		if (auto sp = x.lock())
		{
			sp->OnPieceCapture(type, color);
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

void Game::SetGame(const String& string)
{
	m_gameboard.SetBoard(string);

	if (string[string.size() - 1] == 'w')
	{
		m_turn = EColor::White;
	}
	else
	{
		m_turn = EColor::Black;
	}
}

void Game::SetHistory(const MoveVector& v)
{
	m_gameboard.SetHistory(v);
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

