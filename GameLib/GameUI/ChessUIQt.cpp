#include "ChessUIQt.h"
#include "ChessUIQt.h"
#include <QInputDialog>
#include <QMessageBox>
#include "IGame.h"
#include "BoardExceptions.h"
#include "GameExceptions.h"

#include <array>
#include <QClipboard>

void InitializeWhite(std::string& m, EPieceType type, Position p)

{
	switch (type)
	{
	case EPieceType::Rook:
	{
		m += "\'R\', ";
		break;
	}
	case EPieceType::Knight:
	{
		m += "\'H\', ";
		break;
	}
	case EPieceType::Bishop:
	{
		m += "\'B\', ";
		break;
	}
	case EPieceType::Queen:
	{	m += "\'Q\', ";
	break;
	}
	case EPieceType::King:
	{	m += "\'K\', ";
	break;
	}
	case EPieceType::Pawn:
	{	m += "\'P\', ";
	break;
	}
	}
}

void InitializeBlack(std::string& m, EPieceType type, Position p)
{
	switch (type)
	{
	case EPieceType::Rook:
	{
		m += "\'r\', ";
		break;
	}
	case EPieceType::Knight:
	{
		m += "\'r\', ";
		break;
	}
	case EPieceType::Bishop:
	{
		m += "\'b\', ";
		break;
	}
	case EPieceType::Queen:
	{	m += "\'q\', ";
	break;
	}
	case EPieceType::King:
	{	m += "\'k\', ";
	break;
	}
	case EPieceType::Pawn:
	{	m += "\'p\', ";
	break;
	}
	}
}

void InitializeExtraInfo(std::string& m, IGamePtr game)
{
	if (game->GetTurn() == EColor::Black)
	{
		if (game->IsDraw())
		{
			m += "Game g(m, EColor::Black, EState::Draw);";
			return;
		}

		if (game->IsDrawProposed())
		{
			m += "Game g(m, EColor::Black, EState::DrawIsProposed);";
			return;
		}

		if (game->IsOver())
		{
			m += "Game g(m, EColor::Black, EState::BlackWon);";
			return;
		}

		if (game->IsPromoting())
		{
			m += "Game g(m, EColor::Black, EState::ChoosePiece);";
			return;
		}

		m += "Game g(m, EColor::Black, EState::Playing);";
	}

	if (game->GetTurn() == EColor::White)
	{
		if (game->IsDraw())
		{
			m += "Game g(m, EColor::White, EState::Draw);";
			return;
		}

		if (game->IsDrawProposed())
		{
			m += "Game g(m, EColor::White, EState::DrawIsProposed);";
			return;
		}

		if (game->IsOver())
		{
			m += "Game g(m, EColor::White, EState::WhiteWon);";
			return;
		}

		if (game->IsPromoting())
		{
			m += "Game g(m, EColor::White, EState::ChoosePiece);";
			return;
		}

		m += "Game g(m, EColor::White, EState::Playing);";
	}
}

static PieceType GetType(IPieceInfoPtr currPiece)
{
	if (!currPiece)
	{
		return PieceType::none;
	}

	switch (currPiece->GetType())
	{
	case EPieceType::Rook:
		return PieceType::Rook;
	case EPieceType::Knight:
		return PieceType::Knight;
	case EPieceType::Bishop:
		return PieceType::Bishop;
	case EPieceType::Queen:
		return PieceType::Queen;
	case EPieceType::King:
		return PieceType::King;
	case EPieceType::Pawn:
		return PieceType::Pawn;
	}

	return PieceType::none;
}

static PieceColor GetColor(IPieceInfoPtr currPiece)
{
	if (!currPiece)
	{
		return PieceColor::none;
	}

	switch (currPiece->GetColor())
	{
	case EColor::White:
		return PieceColor::White;
	case EColor::Black:
		return PieceColor::Black;
	}

	return PieceColor::none;
}

PairMatrix ChessUIQt::GetBoard() const
{
	PairMatrix newMatrix;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			IPieceInfoPtr currPiece = m_game->GetPieceInfo({ i,j });

			PieceType currType;
			PieceColor currColor;

			currType = GetType(currPiece);
			currColor = GetColor(currPiece);

			newMatrix[i][j] = { currType, currColor };
		}
	}

	return newMatrix;
}

ChessUIQt::ChessUIQt(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	//Widget containing everything
	QWidget* mainWidget = new QWidget();
	QGridLayout* mainGridLayout = new QGridLayout();

	InitializeBoard(mainGridLayout);
	InitializeMessage(mainGridLayout);
	InitializeButtons(mainGridLayout);
	InitializeTimers(mainGridLayout);
	InitializeHistory(mainGridLayout);

	mainWidget->setLayout(mainGridLayout);
	this->setCentralWidget(mainWidget);
}

ChessUIQt::~ChessUIQt()
{
	//No delete?
	//https://doc.qt.io/qt-6/objecttrees.html
}

void ChessUIQt::InitializeMessage(QGridLayout* mainGridLayout)
{
	m_MessageLabel = new QLabel();

	m_MessageLabel->setText("Waiting for white player");

	m_MessageLabel->setAlignment(Qt::AlignCenter);
	m_MessageLabel->setStyleSheet("font-size: 20px; font-weight: bold;");
	mainGridLayout->addWidget(m_MessageLabel, 0, 1, 1, 1);

	m_ExceptionLabel = new QLabel();

	m_ExceptionLabel->setText("");
	m_ExceptionLabel->setAlignment(Qt::AlignCenter);
	m_ExceptionLabel->setStyleSheet("font-size: 20px; font-weight: bold;");
	mainGridLayout->addWidget(m_ExceptionLabel, 1, 1, 1, 1);
}

void ChessUIQt::InitializeButtons(QGridLayout* mainGridLayout)
{
	QPushButton* saveButton = new QPushButton("Save");
	QPushButton* loadButton = new QPushButton("Load");
	QPushButton* restartButton = new QPushButton("Restart");
	QPushButton* drawButton = new QPushButton("Draw");
	QPushButton* copyButton = new QPushButton("Copy");

	QWidget* buttonContainer = new QWidget();
	QGridLayout* btnGrid = new QGridLayout();

	btnGrid->addWidget(saveButton, 0, 0);
	btnGrid->addWidget(loadButton, 0, 1);
	btnGrid->addWidget(restartButton, 0, 2);
	btnGrid->addWidget(drawButton, 0, 3);
	btnGrid->addWidget(copyButton, 1, 0, 1, 4);

	connect(saveButton, &QPushButton::pressed, this, &ChessUIQt::OnSaveButtonClicked);
	connect(loadButton, &QPushButton::pressed, this, &ChessUIQt::OnLoadButtonClicked);
	connect(restartButton, &QPushButton::pressed, this, &ChessUIQt::OnRestartButtonClicked);
	connect(drawButton, &QPushButton::pressed, this, &ChessUIQt::OnDrawButtonClicked);
	connect(copyButton, &QPushButton::pressed, this, &ChessUIQt::OnCopyButtonClicked);

	buttonContainer->setLayout(btnGrid);
	mainGridLayout->addWidget(buttonContainer, 0, 0, 1, 1);
}

void ChessUIQt::InitializeTimers(QGridLayout* mainGridLayout)
{
	QWidget* timerContainer = new QWidget();
	QGridLayout* timerGrid = new QGridLayout();

	QLabel* blackTimerLbl = new QLabel("Black timer: ");
	m_BlackTimer = new QLabel("00:00:00");

	QPushButton* pauseTimerBtn = new QPushButton(" Pause | Resume");
	//TODO Create slot and connect button

	QLabel* whiteTimerLbl = new QLabel("    White timer: ");
	m_WhiteTimer = new QLabel("00:00:00");

	timerContainer->setFixedWidth(400);

	timerGrid->addWidget(blackTimerLbl, 0, 0);
	timerGrid->addWidget(m_BlackTimer, 0, 1);
	timerGrid->addWidget(pauseTimerBtn, 0, 2);
	timerGrid->addWidget(whiteTimerLbl, 0, 3);
	timerGrid->addWidget(m_WhiteTimer, 0, 4);

	timerContainer->setLayout(timerGrid);
	mainGridLayout->addWidget(timerContainer, 3, 0, 1, 2, Qt::AlignCenter);
}

void ChessUIQt::InitializeHistory(QGridLayout* mainGridLayout)
{
	m_MovesList = new QListWidget();
	m_MovesList->setMinimumWidth(250);
	m_MovesList->setMaximumWidth(350);
	connect(m_MovesList, &QListWidget::itemActivated, this, &ChessUIQt::OnHistoryClicked);
	mainGridLayout->addWidget(m_MovesList, 1, 0, 2, 1);
}

void ChessUIQt::InitializeBoard(QGridLayout* mainGridLayout)
{
	QGridLayout* chessGridLayout = new QGridLayout();

	QWidget* board = new QWidget();

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			m_grid[i][j] = new GridButton({ i,j }, PieceType::none, PieceColor::none);
			chessGridLayout->addWidget(m_grid[i][j], i, j, 1, 1);
			connect(m_grid[i][j], &GridButton::Clicked, this, &ChessUIQt::OnButtonClicked);
		}
	}

	board->setLayout(chessGridLayout);
	mainGridLayout->addWidget(board, 2, 1, 1, 1);
}

void ChessUIQt::OnButtonClicked(const std::pair<int, int>& position)
{
	if (m_game->IsOver() || m_game->IsDraw())
	{
		return;
	}

	m_ExceptionLabel->setText("");

	try
	{
		//At second click
		if (m_selectedCell.has_value())
		{
			int x = m_selectedCell.value().first;
			int y = m_selectedCell.value().first;

			if (m_selectedCell.value() == position)
			{
				m_grid[m_selectedCell.value().first][m_selectedCell.value().second]->setSelected(false);
				m_selectedCell.reset();
				UpdateBoard(GetBoard());
			}
			else
			{
				m_game->Move(m_selectedCell.value(), position);

				//Unselect prev. pressed button
				m_grid[m_selectedCell.value().first][m_selectedCell.value().second]->setSelected(false);
				m_selectedCell.reset();
			}
		}
		//At first click
		else if (m_game->GetPieceInfo(position) && m_game->GetPieceInfo(position)->GetColor() == m_game->GetTurn()) {
			m_selectedCell = position;
			m_grid[position.first][position.second]->setSelected(true);
			HighlightPossibleMoves(m_game->GetMoves(position));
		}
	}
	catch (ChessException E)
	{
		m_ExceptionLabel->setText(E.what());

		m_selectedCell.reset();
		UpdateBoard(GetBoard());
	}
}

void ChessUIQt::OnSaveButtonClicked()
{
	//TODO ...

}

void ChessUIQt::OnLoadButtonClicked()
{
	//TODO ...
}

void ChessUIQt::OnRestartButtonClicked()
{
	m_game->Restart();
}

void ChessUIQt::OnDrawButtonClicked()
{
	QMessageBox::StandardButton reply;
	reply = QMessageBox::question(this, "Draw proposal", "Do you accept a draw?", QMessageBox::Yes | QMessageBox::No);

	if (reply == QMessageBox::Yes)
	{
		m_game->DrawResponse(true);
		m_MessageLabel->setText("Draw! The players agreed to draw\n");
	}
	else
	{
		m_game->DrawResponse(false);
	}
}

void ChessUIQt::OnHistoryClicked(QListWidgetItem* item)
{
	int index = m_MovesList->currentRow();

	//TODO ...
}

void ChessUIQt::OnCopyButtonClicked()
{
	std::string chessBoard = "m = { {\n";

	for (int i = 0; i < 8; i++)
	{
		chessBoard += '{';
		for (int j = 0; j < 8; j++)
		{
			Position currPos = { i, j };

			if (!m_game->GetPieceInfo(currPos))
			{
				chessBoard += "\'-\', ";
				if (j == 7)
					chessBoard.erase(chessBoard.end() - 1);
				continue;
			}

			if (m_game->GetPieceInfo(currPos)->GetColor() == EColor::White)
			{
				EPieceType currType = m_game->GetPieceInfo(currPos)->GetType();

				InitializeWhite(chessBoard, currType, currPos);
			}
			else
			{
				EPieceType currType = m_game->GetPieceInfo(currPos)->GetType();

				InitializeBlack(chessBoard, currType, currPos);

			}
			if (j == 7)
				chessBoard.erase(chessBoard.end() - 1);
		}
		chessBoard += "},\n";
	}
	chessBoard += "}};\n\n";

	InitializeExtraInfo(chessBoard, m_game);

	QString qChessBoard = QString::fromStdString(chessBoard);

	QClipboard* clipboard = QApplication::clipboard();

	clipboard->setText(qChessBoard);

}

void ChessUIQt::UpdateHistory()
{
	m_MovesList->clear();

	//TODO modify me...
	int numMoves = 10;
	for (int i = 0; i < numMoves; i++) {
		m_MovesList->addItem("#1   Color: Black   Move: A1 A2");
	}
}

void ChessUIQt::UpdateBoard(const std::array<std::array<std::pair<PieceType, PieceColor>, 8>, 8>& newBoard)
{
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			m_grid[i][j]->setPiece(newBoard[i][j]);
			m_grid[i][j]->setSelected(false);
			m_grid[i][j]->setHighlighted(false);
		}
	}

}

void ChessUIQt::HighlightPossibleMoves(const std::vector<std::pair<int, int>>& possibleMoves)
{
	for (const auto& position : possibleMoves) {
		m_grid[position.first][position.second]->setHighlighted(true);
	}
}

void ChessUIQt::StartGame()
{
	UpdateBoard(GetBoard());
}

static EPieceType ConvertToEnum(const std::string& pieceType)
{
	if (pieceType == "Queen")
	{
		return EPieceType::Queen;
	}
	if (pieceType == "Rook")
	{
		return EPieceType::Rook;
	}
	if (pieceType == "Bishop")
	{
		return EPieceType::Bishop;
	}
	if (pieceType == "Knight")
	{
		return EPieceType::Knight;
	}
}

void ChessUIQt::ShowPromoteOptions(const Position& p)
{
	QInputDialog dialog;
	QList<QString> options;
	options.append("Rook");
	options.append("Bishop");
	options.append("Queen");
	options.append("Knight");

	dialog.setComboBoxItems(options);
	dialog.setModal(true);

	bool ok;
	QString item = QInputDialog::getItem(this, tr("Pawn promote"),
		tr("Promote pawn to: "), options, 0, false, &ok);

	if (ok && !item.isEmpty())
	{
		m_game->PromoteTo(ConvertToEnum(item.toStdString()));
		//TODO DELETE ME...
		QMessageBox notification;
		notification.setText("You selected " + item);
		notification.exec();
	}
}

void ChessUIQt::SetGame(IGamePtr game)
{
	m_game = game;
}

void ChessUIQt::OnMove()
{
	UpdateBoard(GetBoard());

	if (m_game->GetTurn() == EColor::Black)
	{
		m_MessageLabel->setText("Waiting for black player");
	}
	else
	{
		m_MessageLabel->setText("Waiting for white player");
	}
}

void ChessUIQt::OnGameOver(EOverState state)
{
	QMessageBox::StandardButton wonMessage;

	if (state == EOverState::WhiteWon)
	{
			wonMessage = QMessageBox::information(this, "End!", " White player won!");

			m_MessageLabel->setText("White player won!");
	}
	else if (state == EOverState::BlackWon)
	{
		wonMessage = QMessageBox::information(this, "End!", " Black player won!");

		m_MessageLabel->setText("Black player won!");
	}
	else if (state == EOverState::Draw)
	{
		m_game->DrawResponse(true);

		QMessageBox::StandardButton drawMessage;

		drawMessage = QMessageBox::information(this, "Draw!", " The game concluded as a draw!");

		m_MessageLabel->setText("Draw!");
	}

	m_ExceptionLabel->setText("");
}

void ChessUIQt::OnChoosePiece(Position position)
{
	if (m_game->IsPromoting())
	{
		ShowPromoteOptions(position);
	}
}

void ChessUIQt::OnCheck()
{
	if (m_game->IsCheck())
	{
		QMessageBox::StandardButton checkMessage;

		checkMessage = QMessageBox::information(this, "Check!", " The king is in check!");

		m_MessageLabel->setText("Check!");
	}
}

void ChessUIQt::OnRestart()
{
	m_MessageLabel->setText("Waiting for white player");
	m_ExceptionLabel->setText("");
	StartGame();
}
