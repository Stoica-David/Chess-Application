#include "ChessUIQt.h"

#include "IGame.h"
#include "BoardExceptions.h"
#include "GameExceptions.h"

#include <QInputDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <QScrollArea>
#include <QFileInfo>
#include <QMouseEvent>
#include <QClipboard>
#include <QIcon>
#include <QEvent>
#include <unordered_set>
#include <fstream>
#include <sstream>

#include <array>

// Static methods

static char GetCharForType(EPieceType type)
{
	switch (type)
	{
	case EPieceType::Rook:
		return 'R';
	case EPieceType::Knight:
		return 'H';
	case EPieceType::Bishop:
		return 'B';
	case EPieceType::Queen:
		return 'Q';
	case EPieceType::King:
		return 'K';
	case EPieceType::Pawn:
		return 'P';
	}
	return ' ';
}

static char GetPieceChar(EPieceType type, EColor color)
{
	char toReturn = color == EColor::White ? GetCharForType(type) : tolower(GetCharForType(type));

	return toReturn;
}

static std::string StateToString(IGamePtr game)
{
	auto status = game->GetStatus();

	if (status->IsDraw())
		return "EState::Draw";
	if (status->IsDrawProposed())
		return "EState::DrawIsProposed";
	if (status->IsOver())
		return "EState::BlackWon";
	if (status->IsPromoting())
		return "EState::ChoosePiece";
	return "EState::Playing";
}

static std::string ColorToString(IGamePtr game)
{
	auto status = game->GetStatus();

	return status->GetTurn() == EColor::Black ? "EColor::Black" : "EColor::White";
}

void AppendExtraInfo(std::string& m, IGamePtr game)
{
	m += "Game g(m, ";
	m += ColorToString(game);
	m += ", ";
	m += StateToString(game);
	m += ");";
}

static int GetDefaultNumberOfPieces(EPieceType type)
{
	switch (type)
	{
	case EPieceType::Rook:
		return 2;
	case EPieceType::Knight:
		return 2;
	case EPieceType::Bishop:
		return 2;
	case EPieceType::Queen:
		return 1;
	case EPieceType::King:
		return 1;
	case EPieceType::Pawn:
		return 8;
	}
	return 0;
}

static char ConvertIntToChar(int x)
{
	return 'a' + x;
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
}

static PieceColor GetColor(IPieceInfoPtr currPiece)
{
	if (!currPiece)
	{
		return PieceColor::none;
	}

	return currPiece->GetColor() == EColor::White ? PieceColor::White : PieceColor::Black;
}

static std::string GenerateStringBoard(IGamePtr m_game)
{
	std::string chessBoard = "CharMatrix m = { {\n";

	auto status = m_game->GetStatus();

	for (int i = 0; i < 8; i++)
	{
		chessBoard += "\t{";
		for (int j = 0; j < 8; j++)
		{
			Position currPos = { i, j };

			if (!status->GetPieceInfo(currPos))
			{
				chessBoard += "\'-\'";
				if (j != 7)
					chessBoard.append(", ");
				continue;
			}

			EPieceType currType = status->GetPieceInfo(currPos)->GetType();
			EColor currColor = status->GetPieceInfo(currPos)->GetColor();

			char c = GetPieceChar(currType, currColor);
			chessBoard.insert(chessBoard.length(), 1, '\'');
			chessBoard.insert(chessBoard.length(), 1, c);
			chessBoard.append("\'");
			if (j != 7)
				chessBoard.append(", ");
		}

		i != 7 ? chessBoard += "},\n" : chessBoard += "}\n\t";
	}
	chessBoard += "}};\n\n";

	AppendExtraInfo(chessBoard, m_game);

	return chessBoard;
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

// Class methods

ChessUIQt::ChessUIQt(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	setWindowFlags(Qt::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground);

	// Apply stylesheet to change the background color of the main window
	setStyleSheet("background-color: #F8FFE5;");

	QWidget* mainWidget = new QWidget(this);
	QGridLayout* mainGridLayout = new QGridLayout();

	InitializePlayer(mainGridLayout, EColor::White);
	InitializePlayer(mainGridLayout, EColor::Black);
	InitializeBoard(mainGridLayout);
	InitializeMessage(mainGridLayout);
	InitializeButtons(mainGridLayout);
	InitializeTimers(mainGridLayout);
	InitializeHistory(mainGridLayout);
	InitializeTabBar(mainGridLayout);

	mainWidget->setLayout(mainGridLayout);

	setCentralWidget(mainWidget);
	setMouseTracking(false);
	setStatusBar(nullptr);

	QList<QToolBar*> toolbars = findChildren<QToolBar*>();
	for (auto& it : toolbars)
	{
		it->hide();
	}

	CenterOnScreen();
}

ChessUIQt::~ChessUIQt()
{
	//No delete?
	//https://doc.qt.io/qt-6/objecttrees.html
}

void ChessUIQt::SetGame(IGamePtr game)
{
	m_game = game;
}

void ChessUIQt::StartGame()
{
	UpdateBoard(GetBoard());
	MakeButtonsSelectable();
	m_movesList->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);
}

void ChessUIQt::Show()
{
	show();
	CenterOnScreen();
}

IGamePtr ChessUIQt::GetGame() const
{
	return m_game;
}

void ChessUIQt::PopUp()
{
	QList<QString> timerOptions;
	timerOptions.append("Yes");
	timerOptions.append("No");

	QInputDialog dialog;
	dialog.setComboBoxItems(timerOptions);
	dialog.setModal(true);

	bool ok;
	QString item = QInputDialog::getItem(this, tr("Pawn promote"),
		tr("Do you want a timer? "), timerOptions, 0, false, &ok);


	if (ok && !item.isEmpty())
	{
		if (item == "Yes")
		{
			m_game = IGame::Produce(true);

		}

			m_game->AddListener(shared_from_this());

			StartGame();
			
	}
}

void ChessUIQt::OnMove()
{
	UpdateBoard(GetBoard());

	auto status = m_game->GetStatus();

	status->GetTurn() == EColor::Black ? m_messageLabel->setText("Waiting for black player") : m_messageLabel->setText("Waiting for white player");
}

void ChessUIQt::OnGameOver(EOverState state)
{
	RunMethod([&, state]() {
		if (state == EOverState::WhiteWon)
		{
			QMessageBox::information(this, "End!", " White player won!");

			m_messageLabel->setText("White player won!");
		}
		else if (state == EOverState::BlackWon)
		{
			QMessageBox::information(this, "End!", " Black player won!");

			m_messageLabel->setText("Black player won!");
		}
		else if (state == EOverState::Draw)
		{
			m_game->DrawResponse(true);

			QMessageBox::information(this, "Draw!", " The game concluded as a draw!");

			m_messageLabel->setText("Draw!");
		}

		m_exceptionLabel->setText("");
		});
}

void ChessUIQt::OnChoosePiece()
{
	auto status = m_game->GetStatus();

	if (status->IsPromoting())
	{
		ShowPromoteOptions();
	}
}

void ChessUIQt::OnCheck()
{
	auto status = m_game->GetStatus();

	if (status->IsCheck())
	{
		QMessageBox::information(this, "Check!", " The king is in check!");

		m_messageLabel->setText("Check!");
	}
}

void ChessUIQt::OnRestart()
{
	m_messageLabel->setText("Waiting for white player");
	m_exceptionLabel->setText("");

	m_movesList->clear();
	ClearPieces();
	m_movesList->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);

	m_whiteTimer->setText("10:00");
	m_blackTimer->setText("10:00");

	StartGame();
}

void ChessUIQt::OnPieceCapture(EPieceType pieceType, EColor pieceColor)
{
	qDebug() << (int)pieceColor;

	QListWidget* playerPieces;
	playerPieces = pieceColor == EColor::Black ? m_whiteCapturedPiecesList : m_blackCapturedPiecesList;

	static const QString pieces[] = { "r", "h", "b", "q", "k", "p", "empty" };

	QString imagePath = pieceColor == EColor::Black ? "res/b" : "res/w";
	imagePath.push_back(pieces[(int)pieceType] + ".png");

	QListWidgetItem* capturedPiece = new QListWidgetItem();
	capturedPiece->setIcon(QIcon(QPixmap(imagePath)));

	playerPieces->addItem(capturedPiece);
}

void ChessUIQt::InitializeMessage(QGridLayout* mainGridLayout)
{
	m_messageLabel = new QLabel();
	m_messageLabel->setText("Waiting for white player");
	m_messageLabel->setAlignment(Qt::AlignCenter);
	m_messageLabel->setStyleSheet("font-size: 20px; font-weight: bold; color:#7A6C5D");

	m_exceptionLabel = new QLabel();
	m_exceptionLabel->setText("");
	m_exceptionLabel->setAlignment(Qt::AlignCenter);
	m_exceptionLabel->setStyleSheet("font-size: 20px; font-weight: bold;");

	QVBoxLayout* messageLayout = new QVBoxLayout();
	messageLayout->addWidget(m_messageLabel);
	messageLayout->addWidget(m_exceptionLabel);
	messageLayout->setContentsMargins(0, 0, 0, 0);

	mainGridLayout->addLayout(messageLayout, 0, 1, 2, 1);
}

void ChessUIQt::InitializeButtons(QGridLayout* mainGridLayout)
{
	QPushButton* copyButton = new QPushButton("Copy");
	QPushButton* loadButton = new QPushButton("Load");
	QPushButton* restartButton = new QPushButton("Restart");
	QPushButton* drawButton = new QPushButton("Draw");
	QPushButton* saveButton = new QPushButton("Save");

	QWidget* buttonContainer = new QWidget();
	QGridLayout* btnGrid = new QGridLayout();

	btnGrid->addWidget(saveButton, 0, 0);
	btnGrid->addWidget(loadButton, 0, 1);
	btnGrid->addWidget(restartButton, 0, 2);
	btnGrid->addWidget(drawButton, 0, 3);
	btnGrid->addWidget(copyButton, 1, 0, 1, 4);

	connect(copyButton, &QPushButton::pressed, this, &ChessUIQt::OnCopyButtonClicked);
	connect(loadButton, &QPushButton::pressed, this, &ChessUIQt::OnLoadButtonClicked);
	connect(restartButton, &QPushButton::pressed, this, &ChessUIQt::OnRestartButtonClicked);
	connect(drawButton, &QPushButton::pressed, this, &ChessUIQt::OnDrawButtonClicked);
	connect(saveButton, &QPushButton::pressed, this, &ChessUIQt::OnSaveButtonClicked);

	buttonContainer->setLayout(btnGrid);
	mainGridLayout->addWidget(buttonContainer, 0, 0, 1, 1);

	ApplyButtonStyles(saveButton);
	ApplyButtonStyles(loadButton);
	ApplyButtonStyles(restartButton);
	ApplyButtonStyles(drawButton);
	ApplyButtonStyles(copyButton);

	saveButton->installEventFilter(this);
	copyButton->installEventFilter(this);
	loadButton->installEventFilter(this);
	restartButton->installEventFilter(this);
	drawButton->installEventFilter(this);
}

void ChessUIQt::InitializeTimers(QGridLayout* mainGridLayout)
{
	QWidget* timerContainer = new QWidget();
	QGridLayout* timerGrid = new QGridLayout();

	QLabel* blackTimerLbl = new QLabel("Black timer: ");
	m_blackTimer = new QLabel("10:00");

	pauseTimerBtn = new QPushButton("  Pause  ");

	connect(pauseTimerBtn, &QPushButton::pressed, this, &ChessUIQt::OnPauseButtonClicked);
	//TODO Create slot and connect button

	QLabel* whiteTimerLbl = new QLabel("    White timer: ");
	m_whiteTimer = new QLabel("10:00");

	timerContainer->setFixedWidth(400);

	timerGrid->addWidget(blackTimerLbl, 0, 0);
	timerGrid->addWidget(m_blackTimer, 0, 1);
	timerGrid->addWidget(pauseTimerBtn, 0, 2);
	timerGrid->addWidget(whiteTimerLbl, 0, 3);
	timerGrid->addWidget(m_whiteTimer, 0, 4);

	timerContainer->setLayout(timerGrid);
	mainGridLayout->addWidget(timerContainer, 6, 0, 1, 2, Qt::AlignCenter);

	ApplyButtonStyles(pauseTimerBtn);

	pauseTimerBtn->installEventFilter(this);
}

void ChessUIQt::InitializeHistory(QGridLayout* mainGridLayout)
{
	QScrollArea* scrollArea = new QScrollArea();
	scrollArea->setWidgetResizable(true);

	m_movesList = new QListWidget();

	m_movesList->setStyleSheet("QListWidget::item:hover { background-color: #7A6C5D; } "
		"QListWidget::item:selected { background-color: #7A6C5D; border: 3px solid #2A3D45;}");

	connect(m_movesList, &QListWidget::itemActivated, this, &ChessUIQt::OnHistoryClicked);

	scrollArea->setWidget(m_movesList);
	scrollArea->setStyleSheet("background-color: #D2C4B5; height: 30px;");

	mainGridLayout->addWidget(scrollArea, 3, 0, 3, 1);
}


void ChessUIQt::InitializeBoard(QGridLayout* mainGridLayout)
{
	QGridLayout* chessGridLayout = new QGridLayout();

	QWidget* board = new QWidget();

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			m_grid[i][j] = new GridButton({ i,j }, PieceType::none, PieceColor::none);
			chessGridLayout->addWidget(m_grid[i][j], i, j, 1, 1);
			connect(m_grid[i][j], &GridButton::Clicked, this, &ChessUIQt::GridButtonClicked);
		}
	}

	board->setLayout(chessGridLayout);

	mainGridLayout->addWidget(board, 4, 1, 1, 1);
}

void ChessUIQt::InitializePlayer(QGridLayout* mainGridLayout, EColor color)
{
	QString path, name;
	path = color == EColor::Black ? "res/black.png" : "res/white.png";
	name = color == EColor::Black ? "Black" : "White";

	QWidget* player = new QWidget();
	QGridLayout* playerGrid = new QGridLayout();

	QLabel* profilePicture = new QLabel();
	QPixmap pic(path);
	profilePicture->setPixmap(pic.scaled(60, 60));

	QLabel* profileName = new QLabel();
	profileName->setText(name);
	profileName->setStyleSheet("color: black; font-size: 18px; font-weight: bold;");

	color == EColor::Black ? m_blackCapturedPiecesList = new QListWidget() : m_whiteCapturedPiecesList = new QListWidget();

	QListWidget* playerPieces;
	playerPieces = color == EColor::Black ? m_blackCapturedPiecesList : m_whiteCapturedPiecesList;
	playerPieces->setFlow(QListWidget::LeftToRight);
	playerPieces->setStyleSheet("QListWidget::item, QListWidget{background-color:transparent; border: none}");
	playerPieces->setMaximumHeight(30);
	playerPieces->setFixedWidth(400);

	playerGrid->addWidget(profilePicture, 0, 0, 2, 1);
	playerGrid->addWidget(profileName, 0, 1, Qt::AlignTop);
	playerGrid->addWidget(playerPieces, 1, 1, Qt::AlignCenter);

	player->setLayout(playerGrid);

	color == EColor::Black ? mainGridLayout->addWidget(player, 3, 1, Qt::AlignLeft) : mainGridLayout->addWidget(player, 5, 1, Qt::AlignLeft);
}

void ChessUIQt::InitializeTabBar(QGridLayout* mainGridLayout)
{
	QLabel* messageLabel = new QLabel();
	messageLabel->setText("SucChess");
	messageLabel->setAlignment(Qt::AlignCenter);
	messageLabel->setStyleSheet("font-size: 20px; font-weight: bold; color:#7A6C5D");

	QIcon closeIcon("res/close.png");
	QIcon minimizeIcon("res/minimize.png");

	m_closeButton = new QPushButton(closeIcon, "", this);
	m_closeButton->setStyleSheet("background-color: #D2C4B5; color: #7A6C5D; border: none;");
	m_closeButton->setFixedHeight(30);
	m_closeButton->setFixedWidth(30);
	m_closeButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

	m_minimizeButton = new QPushButton(minimizeIcon, "", this);
	m_minimizeButton->setStyleSheet("background-color: #D2C4B5; color: #7A6C5D; border: none;");
	m_minimizeButton->setFixedHeight(30);
	m_minimizeButton->setFixedWidth(30);
	m_minimizeButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

	QHBoxLayout* titleBarLayout = new QHBoxLayout();

	titleBarLayout->setContentsMargins(0, 0, 0, 0);

	titleBarLayout->addWidget(messageLabel, 0, Qt::AlignLeft);
	messageLabel->setContentsMargins(20, 0, 0, 0);

	titleBarLayout->addStretch();
	titleBarLayout->addWidget(m_minimizeButton, 0, Qt::AlignRight);
	titleBarLayout->addWidget(m_closeButton, 0, Qt::AlignRight);

	QWidget* titleBarWidget = new QWidget();
	titleBarWidget->setLayout(titleBarLayout);
	titleBarWidget->setStyleSheet("background-color: #BCAC9B;");

	setMenuWidget(titleBarWidget);

	connect(m_closeButton, &QPushButton::pressed, this, &QMainWindow::close);
	connect(m_minimizeButton, &QPushButton::pressed, this, &QMainWindow::showMinimized);

	m_closeButton->installEventFilter(this);
	m_minimizeButton->installEventFilter(this);
}

void ChessUIQt::UpdateHistory()
{
	m_movesList->clear();

	auto status = m_game->GetStatus();

	MoveVector newHistory = status->GetHistory();

	for (int i = 0; i < newHistory.size(); i++) {
		QString itemText = QString("%1. %2%3 \t %4%5")
			.arg(i + 1)
			.arg(ConvertIntToChar(newHistory[i].first.y))
			.arg(8 - newHistory[i].first.x)
			.arg(ConvertIntToChar(newHistory[i].second.y))
			.arg(8 - newHistory[i].second.x);

		m_movesList->addItem(new QListWidgetItem(itemText));
	}
}

void ChessUIQt::UpdateCaptured(EColor color)
{
	auto status = m_game->GetStatus();

	auto leftPieces = status->GetPiecesLeft(color);

	std::unordered_set<EPieceType> allPieces = {
		EPieceType::Rook,
		EPieceType::Knight,
		EPieceType::Bishop,
		EPieceType::Queen,
		EPieceType::King,
		EPieceType::Pawn
	};

	for (auto currPiece : allPieces)
	{
		if (currPiece == EPieceType::King)
			continue;

		int missingPieces = GetDefaultNumberOfPieces(currPiece);

		if (leftPieces.find(currPiece) != leftPieces.end())
		{
			int actualApperences = (*leftPieces.find(currPiece)).second;

			missingPieces -= actualApperences;
		}

		for (int i = 0; i < missingPieces; i++)
		{
			OnPieceCapture(currPiece, color);
		}

	}
}

void ChessUIQt::UpdateBoard(const PairMatrix& newBoard)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			m_grid[i][j]->SetPiece(newBoard[i][j]);
			m_grid[i][j]->SetSelected(false);
			m_grid[i][j]->SetHighlighted(false);
		}
	}
}

void ChessUIQt::UpdateTimer()
{
	OnTimerChange();
}

bool ChessUIQt::eventFilter(QObject* obj, QEvent* event)
{
	if (event->type() == QEvent::Enter)
	{
		if (auto button = qobject_cast<QPushButton*>(obj))
		{
			if (button == m_closeButton || button == m_minimizeButton)
			{
				button->setStyleSheet("background-color: #E8E5DA; color: #E8E5DA; border: none;");
			}
			else
			{
				button->setStyleSheet("background-color: #BCAC9B; color: white; border-radius: 5px; padding: 5px;");
			}
		}
	}
	else if (event->type() == QEvent::Leave)
	{
		if (QPushButton* button = qobject_cast<QPushButton*>(obj))
		{
			if (button == m_closeButton || button == m_minimizeButton)
			{
				button->setStyleSheet("background-color: #D2C4B5; color: #7A6C5D; border: none;");
			}
			else
			{
				ApplyButtonStyles(button);
			}
		}
	}

	return false;
}

void ChessUIQt::ApplyButtonStyles(QPushButton* button)
{
	button->setStyleSheet("background-color: #7A6C5D; color: white; border-radius: 5px; padding: 5px;");

	button->setFont(QFont("Arial", 12));
}

void ChessUIQt::HighlightPossibleMoves(const PositionList& possibleMoves)
{
	for (const auto& position : possibleMoves)
	{
		m_grid[position.x][position.y]->SetHighlighted(true);
	}
}

void ChessUIQt::MakeButtonsSelectable()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			m_grid[i][j]->setEnabled(true);
		}
	}
}

void ChessUIQt::MakeButtonsUnselectable()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			m_grid[i][j]->setEnabled(false);
		}
	}
}

PairMatrix ChessUIQt::GetBoard() const
{
	PairMatrix newMatrix;

	auto status = m_game->GetStatus();

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			IPieceInfoPtr currPiece = status->GetPieceInfo({ i,j });

			newMatrix[i][j] = { GetType(currPiece), GetColor(currPiece) };
		}
	}

	return newMatrix;
}

void ChessUIQt::CenterOnScreen()
{
	QScreen* screen = QGuiApplication::primaryScreen();
	QRect screenGeometry = screen->availableGeometry();

	int x = (screenGeometry.width() - width()) / 2;
	int y = (screenGeometry.height() - height()) / 2;

	move(x, y);
}

void ChessUIQt::ShowPromoteOptions()
{
	QList<QString> options;
	options.append("Rook");
	options.append("Bishop");
	options.append("Queen");
	options.append("Knight");

	QInputDialog dialog;
	dialog.setComboBoxItems(options);
	dialog.setModal(true);

	bool ok;
	QString item = QInputDialog::getItem(this, tr("Pawn promote"),
		tr("Promote pawn to: "), options, 0, false, &ok);

	if (ok && !item.isEmpty())
	{
		m_game->PromoteTo(ConvertToEnum(item.toStdString()));

		QMessageBox notification;
		notification.setText("You selected " + item);
		notification.exec();
	}
}

void ChessUIQt::ClearPieces()
{
	m_whiteCapturedPiecesList->clear();
	m_blackCapturedPiecesList->clear();
}

void ChessUIQt::RunMethod(std::function<void(void)> func)
{
	QMetaObject::invokeMethod(this, func, Qt::QueuedConnection);
}

void ChessUIQt::GridButtonClicked(Position position)
{
	auto status = m_game->GetStatus();

	if (status->IsOver() || status->IsDraw() || status->IsFrozen())
	{
		return;
	}

	m_exceptionLabel->setText("");

	try
	{
		//At second click
		if (m_selectedCell.has_value())
		{
			auto& button = m_grid[m_selectedCell.value().x][m_selectedCell.value().y];

			m_selectedCell.value() == position ? UpdateBoard(GetBoard()) : m_game->Move(m_selectedCell.value(), position), UpdateHistory();

			button->SetSelected(false);
			m_selectedCell.reset();
		}
		//At first click
		else if (status->GetPieceInfo(position) && status->GetPieceInfo(position)->GetColor() == status->GetTurn() && !status->GetMoves(position).empty())
		{
			m_selectedCell = position;
			m_grid[position.x][position.y]->SetSelected(true);
			HighlightPossibleMoves(status->GetMoves(position));
		}
	}
	catch (ChessException E)
	{
		m_exceptionLabel->setText(E.what());

		m_selectedCell.reset();
		UpdateBoard(GetBoard());
	}
}

void ChessUIQt::OnCopyButtonClicked()
{
	QString qChessBoard = QString::fromStdString(GenerateStringBoard(m_game));

	QClipboard* clipboard = QApplication::clipboard();
	clipboard->setText(qChessBoard);
}

void ChessUIQt::OnSaveButtonClicked()
{
	QString fileName = QFileDialog::getSaveFileName(this, "Save Text File", "", "FEN Files (*.fen);;PGN Files(*.pgn);;All files(*.*)");

	if (fileName.isEmpty())
		return;

	QFile file(fileName);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		qDebug() << "Error: Could not open the file for writing.";
		return;
	}

	QString extension = QFileInfo(file).suffix();

	try
	{
		if (extension == "pgn")
		{
			m_game->Save(EFileFormat::PGN, fileName.toStdString());
		}
		else if (extension == "fen")
		{
			m_game->Save(EFileFormat::FEN, fileName.toStdString());
		}
		else
		{
			throw ChessException("Unrecognized format");
		}
	}
	catch (ChessException& e)
	{
		QMessageBox exception;
		exception.setText(e.what());
		exception.exec();
		return;
	}
}

void ChessUIQt::OnLoadButtonClicked()
{
	QString fileName = QFileDialog::getOpenFileName(this, "Open Text File", "", "FEN Files (*.fen);;PGN Files (*.pgn);;All Files(*.*)");

	if (fileName.isEmpty())
		return;

	QFile file(fileName);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		qDebug() << "Error: Could not open the file for reading.";
		return;
	}

	QTextStream in(&file);
	QString data = in.readAll();
	file.close();

	QString extension = QFileInfo(file).suffix();

	try
	{
		if (extension == "pgn")
		{
			m_game->Load(EFileFormat::PGN, fileName.toStdString());
		}
		else if (extension == "fen")
		{
			m_movesList->setEditTriggers(QAbstractItemView::NoEditTriggers);
			m_game->Load(EFileFormat::FEN, fileName.toStdString());
		}
		else
		{
			throw ChessException("Unrecognized format");
		}
	}
	catch (ChessException exc)
	{
		QMessageBox exception;
		exception.setText(exc.what());
		exception.exec();
		return;
	}

	UpdateBoard(GetBoard());
	UpdateHistory();

	auto status = m_game->GetStatus();

	status->GetTurn() == EColor::White ? m_messageLabel->setText("Waiting for white player") : m_messageLabel->setText("Waiting for black player");

	if (status->IsDraw())
	{
		OnGameOver(EOverState::Draw);
	}
	else if (status->IsOver())
	{
		EOverState whoWon = status->GetTurn() == EColor::White ? EOverState::WhiteWon : EOverState::BlackWon;

		OnGameOver(whoWon);
	}
	else
	{
		m_movesList->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);
	}

	ClearPieces();
	UpdateCaptured(EColor::White);
	UpdateCaptured(EColor::Black);
}

void ChessUIQt::OnRestartButtonClicked()
{
	m_game->Restart();
	OnTimerChange();
}

void ChessUIQt::OnDrawButtonClicked()
{
	QMessageBox::StandardButton reply = QMessageBox::question(this, "Draw proposal", "Do you accept a draw?", QMessageBox::Yes | QMessageBox::No);

	reply == QMessageBox::Yes ? m_game->DrawResponse(true), m_messageLabel->setText("The players agreed to draw!") : m_game->DrawResponse(false);
}

void ChessUIQt::OnHistoryClicked(QListWidgetItem* item)
{
	QAbstractItemView::EditTriggers currentEditTriggers = m_movesList->editTriggers();

	if (currentEditTriggers == QAbstractItemView::NoEditTriggers)
	{
		return;
	}

	int index = m_movesList->currentRow();

	m_game->ShowConfiguration(index);

	UpdateBoard(GetBoard());

	auto status = m_game->GetStatus();

	index != status->GetHistory().size() - 1 ? MakeButtonsUnselectable() : MakeButtonsSelectable();
}

void ChessUIQt::OnPauseButtonClicked()
{
	auto status = m_game->GetStatus();

	if (status->IsFrozen())
	{
		UpdateTimer();
		m_game->ResumeGame();
		
	}
	else if(status->IsPlaying())
	{
		UpdateTimer();
		m_game->PauseGame();
	}
}

void ChessUIQt::OnTimerChange()
{
	auto status = m_game->GetStatus();

	if (status->IsFrozen())
	{
		pauseTimerBtn->setText(" Resume ");
	}
	else if (status->IsPlaying())
	{
		pauseTimerBtn->setText(" Pause ");
	}

	const Timer& wTimer = status->GetTimer(EColor::White);
	const Timer& bTimer = status->GetTimer(EColor::Black);

	int seconds, minutes;

	if (status->GetTurn() == EColor::White)
	{
		seconds = wTimer.GetSeconds();
		minutes = wTimer.GetMinutes();
	}
	else
	{
		seconds = bTimer.GetSeconds();
		minutes = bTimer.GetMinutes();
	}

	String minutesStr;
	String secondStr;

	if (minutes == 10)
	{
		minutesStr = "10";
	}
	else
	{
		minutesStr.push_back('0');
		minutesStr.push_back('0' + minutes);
	}

	char zecimal;
	char unit = '0' + (int)(seconds % 10);

	if (seconds > 9)
	{
		zecimal = '0' + (int)((seconds / 10) % 10);
		secondStr.push_back(zecimal);
	}
	else
	{
		secondStr.push_back('0');
	}

	secondStr.push_back(unit);

	String time = minutesStr + ":" + secondStr;

	RunMethod([&, status, time]() {
		if (status->GetTurn() == EColor::White)
		{
			m_whiteTimer->setText(QString::fromStdString(time));
		}
		else
		{
			m_blackTimer->setText(QString::fromStdString(time));
		}
		});
}
