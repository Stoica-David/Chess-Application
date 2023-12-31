#include "Game.h"

#include "GameExceptions.h"
#include "FENException.h"
#include "FileUtils.h"

#include <functional>

static char LastChar(const String& string)
{
	for (int i = string.size() - 1; i >= 0; i--)
	{
		if (string[i] != ' ')
			return string[i];
	}

	return ' ';
}

IGamePtr IGame::Produce(bool wantTimer)
{
	if (wantTimer)
	{
		return std::make_shared<Game>(wantTimer);
	}
	else
	{
		return std::make_shared<Game>();
	}
}

// Class methods

Game::Game(bool wantTimer)
	: m_turn(EColor::White)
	, m_state(EState::Playing)
	, m_initialState(EState::Playing)
	, m_timer(10)
	, m_nrMoves(0)
	, m_wantTimer(wantTimer)
{
	if (wantTimer)
	{
		m_timer.StartTimer();
	}
}

Game::Game(const Board& b, EColor color /*=EColor::White*/, bool wantTimer)
	: m_turn(color)
	, m_gameboard(b)
	, m_state(EState::Playing)
	, m_initialState(EState::Playing)
	, m_timer(10)
	, m_nrMoves(0)
	, m_wantTimer(wantTimer)
{
	if (wantTimer)
	{
		m_timer.StartTimer();
	}
}

Game::Game(const CharMatrix& matrix, EColor color, EState state, bool wantTimer)
	: m_turn(color)
	, m_state(state)
	, m_initialState(state)
	, m_gameboard(matrix)
	, m_timer(10)
	, m_nrMoves(0)
	, m_wantTimer(wantTimer)
{
	if (wantTimer)
	{
		m_timer.StartTimer();
	}
}

Game::Game(std::function<void()> function, bool wantTimer /*= false*/)	// for testing
	: m_turn(EColor::White)
	, m_state(EState::Playing)
	, m_initialState(EState::Playing)
	, m_timer(1, wantTimer)
	, m_wantTimer(wantTimer)
{
	auto nothing = []() {};

	m_timer.SetNotifyChange(nothing);

	if (wantTimer)
	{
		m_timer.StartTimer();
	}
}

void Game::Restart()
{
	m_turn = EColor::White;
	m_state = EState::Playing;

	m_gameboard.Reset();

	m_PGN.Clear();

	if (m_wantTimer)
	{
		m_timer.ResetTimer();
		m_timer.StartTimer();
	}

	NotifyRestart();
}

void Game::Move(Position p1, Position p2)
{
	if (m_state == EState::Playing || m_state == EState::Check)
	{
		if (!p1.IsValid() || !p2.IsValid())
		{
			throw PositionException("The given position is out of the table");
		}

		PiecesPtr currPiece = m_gameboard.at(p1);
		PiecesPtr nextPiece = m_gameboard.at(p2);

		if (!currPiece)
		{
			throw DoesntExistException("The piece doesn't exist");
		}

		if (currPiece->GetColor() != m_turn)
		{
			throw TurnException("It's the other player's turn");
		}

		NotifyIfCaptured(p1, p2);

		m_gameboard.Move(p1, p2);

		m_PGN.AddMove(m_gameboard.GetCurrPGN());

		m_gameboard.IsPromotePossible(p2) ? UpdateState(EState::ChoosePiece), NotifyChoosePiece() : SwitchTurn();

		NotifyMove();
		m_nrMoves++;

		if (m_gameboard.IsOver(EColor::White))
		{
			UpdateState(EState::BlackWon);
			NotifyGameOver(EOverState::BlackWon);
			m_timer.StopTimer();
		}
		else if (Stalemate() || m_gameboard.IsDraw() || m_gameboard.Is3Fold() || IsDraw())
		{
			UpdateState(EState::Draw);
			NotifyGameOver(EOverState::Draw);
			m_timer.StopTimer();
		}
		else if (m_gameboard.IsOver(EColor::Black))
		{
			UpdateState(EState::WhiteWon);
			NotifyGameOver(EOverState::WhiteWon);
			m_timer.StopTimer();
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

	m_timer.SetColor(m_turn);
}

void Game::DrawResponse(bool draw)
{
	m_state = draw ? m_timer.StopTimer(), EState::Draw : EState::Playing, SwitchTurn(), m_timer.SetColor(m_turn);
}

void Game::PromoteTo(EPieceType pieceType)
{
	m_gameboard.PromoteTo(pieceType, m_turn);

	m_PGN.Append(m_gameboard.GenerateInitial(pieceType));

	UpdateState(EState::Playing);

	SwitchTurn();
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
	m_wantTimer = false;
	m_timer.StopTimer();

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

void Game::Pause()
{
	UpdateState(EState::Frozen);
	m_timer.StopTimer();
}

void Game::Resume()
{
	UpdateState(EState::Playing);
	m_timer.StartTimer();
}

void Game::ShowConfiguration(int confNr)
{
	ChessBoard currBoard = m_gameboard.ConvertBitset(confNr);

	if (confNr != m_gameboard.GetPrevPositions().size() - 1)
	{
		m_initialState = m_state;
		UpdateState(EState::Frozen);
	}
	else
	{
		UpdateState(m_initialState);
		m_initialState = EState::Playing;
	}

	m_gameboard.Set(currBoard);
}

int Game::GetTotalTime() const
{
	return m_timer.GetInitialTime();
}

int Game::GetRemainingTime(EColor color) const
{
	return m_timer.GetRemainingTime(color);
}

int Game::GetCurrentMoveTime() const
{
	return m_timer.GetCurrentMoveTime();
}

int Game::GetThinkingTime(int nrMove) const
{
	return m_timer.GetThinkingTimes(nrMove);
}

int Game::GetTimerResolution() const
{
	return m_timer.GetTimerResolution();
}

int Game::GetNrMoves() const
{
	return m_nrMoves;
}

void Game::SetTimerResolution(int ms)
{
	m_timer.SetTimerResolution(ms);
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

	m_turn = m_PGN.GetNrMove() % 2 == 1 ? EColor::Black : EColor::White;
}

void Game::AddListener(IGameListenerPtr newListener)
{
	m_listeners.push_back(newListener);

	m_timer.SetNotifyChange(std::bind(&Game::NotifyTimerChange, this));
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

bool Game::IsFrozen() const
{
	return m_state == EState::Frozen;
}

bool Game::IsPlaying() const
{
	return m_state == EState::Playing;
}

const IGameStatus* Game::GetStatus() const
{
	return this;
}

const ITimerInfo* Game::GetTimer() const
{
	return m_wantTimer ? this : nullptr;
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

PiecesLeftVector Game::GetPiecesLeft(EColor color)const
{
	PiecesLeftVector leftPieces;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			PiecesPtr piece = m_gameboard.at({ i, j });

			if (piece && piece->GetColor() == color)
			{
				bool found = false;

				for (auto& currPiece : leftPieces)
				{
					EPieceType leftPieceType = currPiece.first;

					if (leftPieceType == piece->GetType())
					{
						found = true;
						currPiece.second++;
					}
				}

				if (!found)
				{
					leftPieces.push_back({ piece->GetType(), 1 });
				}
			}
		}
	}

	return leftPieces;
}

PiecesPtr Game::GetPiece(Position p) const
{
	return m_gameboard.at(p);
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

void Game::NotifyTimerChange()
{
	if (m_timer.IsTimeExpired())
	{
		if (m_turn == EColor::White)
		{
			UpdateState(EState::BlackWon);
			NotifyGameOver(EOverState::BlackWon);
		}
		else
		{
			UpdateState(EState::WhiteWon);
			NotifyGameOver(EOverState::WhiteWon);
		}
	}

	for (const auto& x : m_listeners)
	{
		if (auto sp = x.lock())
		{
			sp->OnTimerChange();
		}
	}
}

void Game::NotifyIfCaptured(Position p1, Position p2)
{
	PiecesPtr currPiece = m_gameboard.at(p1);
	PiecesPtr nextPiece = m_gameboard.at(p2);

	if (nextPiece && nextPiece->GetColor() != currPiece->GetColor())
	{
		if (currPiece->IsMoveRegular(p1,p2) || !m_gameboard.PawnException(p1, p2))
		{
			NotifyCaptured(nextPiece->GetType(), nextPiece->GetColor());
		}
	}

	if (m_gameboard.IsEnPassant(p1, p2))
	{
		if (currPiece->GetColor() == EColor::White)
		{
			NotifyCaptured(EPieceType::Pawn, EColor::Black);
		}
		else
		{
			NotifyCaptured(EPieceType::Pawn, EColor::White);
		}
	}
}

void Game::SwitchTurn()
{
	if (m_turn == EColor::White)
	{
		if (m_wantTimer)
		{
			m_timer.SetColor(EColor::Black);
		}
		m_turn = EColor::Black;
	}
	else
	{
		if (m_wantTimer)
		{
			m_timer.SetColor(EColor::White);
		}
		m_turn = EColor::White;
	}
}

void Game::UpdateState(EState state)
{
	m_state = state;
}
