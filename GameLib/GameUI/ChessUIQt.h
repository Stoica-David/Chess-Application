#pragma once

#include "IGame.h"

#include "ui_ChessUIQt.h"
#include "GridButton.h"
#include "Position.h"

#include <QtWidgets/QMainWindow>
#include <QtWidgets/qgridlayout.h>
#include <QPushButton>
#include <QLabel>
#include <QListWidget>
#include <QApplication>
#include <QScrollArea>
#include <QtGlobal>
#include <utility>
#include <memory>

using PieceTypeColor = std::pair<PieceType, PieceColor>;
using PairMatrix = std::array<std::array<PieceTypeColor, 8>, 8>;

class ChessUIQt : public QMainWindow, public IGameListener, public std::enable_shared_from_this<ChessUIQt>
{
    Q_OBJECT

public:
    ChessUIQt(QWidget *parent = nullptr);
    ~ChessUIQt() override;

    void SetGame(IGamePtr game);
    void StartGame();

    void Show();
    IGamePtr GetGame() const;

    void PopUp();

private:
    // IGameListener methods
    void OnMove() override;
    void OnGameOver(EOverState) override;
    void OnChoosePiece() override;
    void OnCheck() override;
    void OnRestart() override;
    void OnPieceCapture(EPieceType, EColor) override;

    // Initializers
    void InitializeMessage(QGridLayout* mainGridLayout);
    void InitializeButtons(QGridLayout* mainGridLayout);
    void InitializeTimers(QGridLayout* mainGridLayout);
    void InitializeHistory(QGridLayout* mainGridLayout);
    void InitializeBoard(QGridLayout* mainGridLayout);
    void InitializePlayer(QGridLayout* mainGridLayout, EColor);
    void InitializeTabBar(QGridLayout* mainGridLayout);
	void InitializePlayerPieces(QListWidget*&, EColor) const;
    void InitializeTabButtons();

	void SetTimers(bool isTimer);
    void AddMissingPieces(int, EPieceType, EColor);
    int ActualNumberPieces(int&, PiecesLeftVector, EPieceType) const;

    //Update methods
    void UpdateHistory();
    void UpdateCaptured(EColor color);
    void UpdateBoard(const PairMatrix& newBoard);
    void UpdateTimer();

    //Button related methods
    bool eventFilter(QObject* obj, QEvent* event);
	
    void ApplyButtonStyles(QPushButton* button);
    void HighlightPossibleMoves(const PositionList& possibleMoves);
    void UnhighlightPossibleMoves(const PositionList& possibleMoves);
    void MakeButtonsSelectable();
    void MakeButtonsUnselectable();

    //Other methods
	PairMatrix GetBoard() const;

    void CenterOnScreen();
    void ShowPromoteOptions();
    void ClearPieces();

    void RunMethod(std::function<void(void)> func);

private slots:
    void GridButtonClicked(Position position);

    void OnCopyButtonClicked();
    void OnSaveButtonClicked();
    void OnLoadButtonClicked();
    void OnRestartButtonClicked();
    void OnDrawButtonClicked();
    void OnHistoryClicked(QListWidgetItem* item);
    void OnPauseButtonClicked();
    void OnTimerChange();

private:
    Ui::ChessUIQtClass ui;
    
    std::array<std::array<GridButton*, 8>, 8> m_grid;
    
    std::optional<Position> m_selectedCell;
    
    QPushButton* m_closeButton;
    QPushButton* m_minimizeButton;
    QPushButton* pauseTimerBtn;
    
    QLabel* m_messageLabel;
    QLabel* m_exceptionLabel;

    QListWidget* m_movesList;
    QListWidget* m_whiteCapturedPiecesList;
    QListWidget* m_blackCapturedPiecesList;
    
    QLabel* m_blackTimer;
    QLabel* m_whiteTimer;

    IGamePtr m_game;
};
