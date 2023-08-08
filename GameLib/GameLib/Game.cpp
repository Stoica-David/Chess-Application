#include "Game.h"

#include "GameExceptions.h"
#include "FENException.h"

#include "FileUtils.h"

static bool IsPositionValid(Position p)
{
	return (p.first >= 0 && p.first < 8) && (p.second >= 0 && p.second < 8);
}

static char LastChar(const String& string)
{
	for (int i = string.size() - 1; i >= 0; i--)
	{
		if (string[i] != ' ')
			return string[i];
	}

	return ' ';
}

IGamePtr IGame::Produce()
{
	return std::make_shared<Game>();
}

// Class methods

Game::Game()
	: m_turn(EColor::White)
	, m_state(EState::Playing)
	, m_whiteTimer(10)
	, m_blackTimer(10)
{
}

Game::Game(const Board& b, EColor color /*=EColor::White*/)
	: m_turn(color)
	, m_gameboard(b)
	, m_state(EState::Playing)
	, m_whiteTimer(10)
	, m_blackTimer(10)
{
}

Game::Game(const CharMatrix& matrix, EColor color, EState state) 
	: m_turn(color)
	, m_state(state)
	, m_whiteTimer(10)
	, m_blackTimer(10)
{
	m_gameboard = Board::Board(matrix);
}

void Game::Restart()
{
	m_turn = EColor::White;
	m_state = EState::Playing;

	m_gameboard.Reset();
	
	m_PGN.Clear();
	
	NotifyRestart();
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

		m_PGN.AddMove(m_gameboard.GetCurrPGN());

		currPiece = m_gameboard.GetPiece(p1);

		if (!currPiece && pieceCaptured)
		{
			NotifyCaptured(type, color);
		}

		m_gameboard.IsPromotePossible(p2) ? UpdateState(EState::ChoosePiece), NotifyChoosePiece() : SwitchTurn();

		NotifyMove();

		if (m_gameboard.IsOver(EColor::White))
		{
			UpdateState(EState::BlackWon);
			NotifyGameOver(EOverState::BlackWon);
		}
		else if (Stalemate() || m_gameboard.IsDraw() || m_gameboard.Is3Fold() || IsDraw())
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

void Game::PromoteTo(EPieceType pieceType)
{
	m_gameboard.PromoteTo(pieceType, m_turn);

	UpdateState(EState::Playing);
	SwitchTurn();
}

void Game::SetHistory(const MoveVector& v)
{
	m_gameboard.SetHistory(v);
}

void Game::Save(EFileFormat format, const String& file) const
{
	switch (format)
	{
	case EFileFormat::FEN:
		SaveFEN(file);
		break;
	case EFileFormat::PGN:
		SavePGN(file);
		break;
	}
}

void Game::Load(EFileFormat format, const String& file)
{
	switch (format)
	{
	case EFileFormat::FEN:
		LoadFEN(file);
		break;
	case EFileFormat::PGN:
		LoadPGN(file);
		break;
	}
}

void Game::ShowConfiguration(int confNr)
{
	ChessBoard currBoard = m_gameboard.ConvertBitset(confNr);

	m_gameboard.Set(currBoard);
}

void Game::SaveFEN(const String& file) const
{
	String FEN = m_gameboard.GetFEN();
	m_turn == EColor::White ? FEN.push_back('w') : FEN.push_back('b');

	if (!FileUtils::WriteStringToFile(file, FEN))
		throw FENException("FEN not properly saved");
}

void Game::LoadFEN(const String& file)
{
	String FEN;
	FileUtils::ReadStringFromFile(file, FEN);
	m_gameboard.LoadFEN(FEN);

	if (m_gameboard.IsCheckMate(EColor::White))
	{
		UpdateState(EState::BlackWon);
	}
	else if (m_gameboard.IsCheckMate(EColor::Black))
	{
		UpdateState(EState::WhiteWon);
	}
	else if (m_gameboard.IsDraw())
	{
		UpdateState(EState::Draw);
	}
	else
	{
		UpdateState(EState::Playing);
	}
}

void Game::SavePGN(const String& file) const
{
	PGNHandler pgn = m_PGN;

	if (IsDraw())
	{
		pgn.SetHeader(ETag::Result, "1/2-1/2");
	}
	else if (IsOver())
	{
		m_turn == EColor::White ? pgn.SetHeader(ETag::Result, "0-1") : pgn.SetHeader(ETag::Result, "1-0");
	}

	pgn.SavePGNToFile(file);
}

void Game::LoadPGN(const String& filePath)
{
	m_PGN.LoadPGNFromFile(filePath);

	m_PGN.ParseFromPGN();

	m_gameboard.ParsePGN(m_PGN.GetMoves());

	if (m_PGN.IsDraw())
	{
		UpdateState(EState::Draw);
	}
	else if (m_PGN.IsOverWhite())
	{
		UpdateState(EState::WhiteWon);
	}
	else if (m_PGN.IsOverBlack())
	{
		UpdateState(EState::BlackWon);
	}
	else
	{
		UpdateState(EState::Playing);
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

bool Game::IsTimeExpired(ChessTimer timer) const
{
	return timer.isTimeExpired();
}

const IGameStatus* Game::GetStatus() const
{
	return this;
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
	return m_state == EState::DrawIsProposed;
}

bool Game::IsCheck() const
{
	return m_state == EState::Check;
}

bool Game::IsPromoting() const
{
	return m_state == EState::ChoosePiece;
}

EColor Game::GetTurn() const
{
	return m_turn;
}

PositionList Game::GetMoves(Position p) const
{
	return m_gameboard.GetMoves(p);
}

MoveVector Game::GetHistory() const
{
	return m_gameboard.GetHistory();
}

IPieceInfoPtr Game::GetPieceInfo(Position p) const
{
	return m_gameboard.GetPieceInfo(p);
}

PieceMap Game::GetPiecesLeft(EColor color)const
{
	PieceMap leftPieces;

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

PiecesPtr Game::GetPiece(Position p) const
{
	return m_gameboard.GetPiece(p);
}

bool Game::Stalemate() const
{
	return m_gameboard.IsStalemate(m_turn);
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

void Game::NotifyTime(ChessTimer timer)
{
	{
		for (const auto& x : m_listeners)
		{
			if (auto sp = x.lock())
			{
				sp->OnNotifyTime(timer);
			}
		}
	}
}

void Game::SwitchTurn()
{
	if (m_turn == EColor::White)
	{
		m_whiteTimer.endTurn();
		m_turn = EColor::Black;
		m_blackTimer.startTurn();
	}
	else
	{
		m_blackTimer.endTurn();
		m_turn = EColor::White;
		m_whiteTimer.startTurn();
	}
}

void Game::UpdateState(EState state)
{
	m_state = state;
}
