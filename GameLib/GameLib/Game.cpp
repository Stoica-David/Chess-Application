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

Game::Game(const CharMatrix& matrix, EColor color) : m_turn(color), m_state(EState::Playing)
{

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			switch (matrix[i][j])
			{
			case 'P':
			{
				m_gameboard[{i, j}] = Piece::Produce(EPieceType::Pawn, EColor::White);
				break;
			}

			case 'p':
			{
				m_gameboard[{i, j}] = Piece::Produce(EPieceType::Pawn, EColor::Black);
				break;
			}

			case 'R':
			{
				m_gameboard[{i, j}] = Piece::Produce(EPieceType::Rook, EColor::White);
				break;
			}

			case 'r':
			{
				m_gameboard[{i, j}] = Piece::Produce(EPieceType::Rook, EColor::Black);
				break;
			}

			case 'B':
			{
				m_gameboard[{i, j}] = Piece::Produce(EPieceType::Bishop, EColor::White);
				break;
			}

			case 'b':
			{
				m_gameboard[{i, j}] = Piece::Produce(EPieceType::Bishop, EColor::Black);
				break;
			}

			case 'H':
			{
				m_gameboard[{i, j}] = Piece::Produce(EPieceType::Knight, EColor::White);
				break;
			}

			case 'h':
			{
				m_gameboard[{i, j}] = Piece::Produce(EPieceType::Knight, EColor::Black);
				break;
			}

			case 'Q':
			{
				m_gameboard[{i, j}] = Piece::Produce(EPieceType::Queen, EColor::White);
				break;
			}

			case 'q':
			{
				m_gameboard[{i, j}] = Piece::Produce(EPieceType::Queen, EColor::Black);
				break;
			}

			case 'K':
			{
				m_gameboard[{i, j}] = Piece::Produce(EPieceType::King, EColor::White);
				break;
			}

			case 'k':
			{
				m_gameboard[{i, j}] = Piece::Produce(EPieceType::King, EColor::Black);
				break;
			}

			case '-':
			{
				m_gameboard[{i, j}] = {};
				break;
			}
	
			}
		}
	}
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

		if (m_gameboard[p2] && m_gameboard[p2]->Is(EPieceType::Pawn) && (p2.first == 0 || p2.first == 7))
		{
			UpdateState(EState::ChoosePiece);
			NotifyChoosePiece(p2);
		}
		else
		{
			SwitchTurn();
		}

		NotifyMove();

		if (m_gameboard.IsCheck(m_gameboard.FindKing(m_turn), m_turn))
		{
			UpdateState(EState::Check);
			NotifyCheck();
		}
		else if (m_gameboard.IsOver(EColor::White))
		{
			UpdateState(EState::BlackWon);
			NotifyGameOver();
		}
		else if (m_gameboard.IsOver(EColor::Black))
		{
			UpdateState(EState::WhiteWon);
			NotifyGameOver();
		} 
		else if (m_gameboard.IsDraw())
		{
			UpdateState(EState::Draw);
			NotifyDraw();
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
		NotifyDraw();
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

bool Game::IsDraw()
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

bool Game::ChoosePiece() const
{
	return (m_state == EState::ChoosePiece);
}

void Game::PromoteTo(const std::string& string, Position p)
{
	m_gameboard.PromoteTo(string, p, m_turn);

	if (m_gameboard.IsCheckMate(EColor::White))
	{
		UpdateState(EState::BlackWon);
	}
	else if (m_gameboard.IsCheckMate(EColor::Black))
	{
		UpdateState(EState::WhiteWon);
	}

	UpdateState(EState::Playing);
	SwitchTurn();
}

void Game::Restart()
{
	ListenersList oldList = m_listeners;

	*this = Game();

	m_listeners = oldList;
}

void Game::SwitchTurn()
{
	m_turn = m_turn == EColor::Black ? EColor::White : EColor::Black;
}

bool Game::Stalemate()
{
	return (m_gameboard.Stalemate(m_turn));
}

PositionList Game::GetMoves(Position p)
{
	return m_gameboard.GetMoves(p);
}

bool Game::IsCheck()
{
	return m_state == EState::Check;
}

void Game::NotifyDraw()
{
	for (const auto& x : m_listeners)
	{
		x->OnDraw();
	}
}

void Game::NotifyChoosePiece(Position p)
{
	for (const auto& x : m_listeners)
	{
		x->OnChoosePiece(p);
	}
}

void Game::NotifyCheck()
{
	for (const auto& x : m_listeners)
	{
		x->OnCheck();
	}
}

void Game::AddListener(IGameListener* newListener)
{
	m_listeners.push_back(newListener);
}

void Game::RemoveListener(IGameListener* listener)
{
	auto func = [listener](IGameListener* el)
	{
		return listener == el;
	};

	m_listeners.erase(std::remove_if(m_listeners.begin(), m_listeners.end(), func));
}

void Game::NotifyMove()
{
	for (const auto& x : m_listeners)
	{
		x->OnMove();
	}
}

void Game::NotifyGameOver()
{
	for (const auto& x : m_listeners)
	{
		x->OnGameOver();
	}
}

