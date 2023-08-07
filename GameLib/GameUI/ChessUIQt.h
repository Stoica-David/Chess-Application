#pragma once

#include "IGame.h"

#include "ui_ChessUIQt.h"
#include "GridButton.h"

#include <QtWidgets/QMainWindow>
#include <QtWidgets/qgridlayout.h>
#include <QPushButton>
#include <QLabel>
#include <QListWidget>

using PieceTypeColor = std::pair<PieceType, PieceColor>;
using PairMatrix = std::array<std::array<PieceTypeColor, 8>, 8>;

class ChessUIQt : public QMainWindow, public IGameListener
{
    Q_OBJECT

public:
    ChessUIQt(QWidget *parent = nullptr);
    ~ChessUIQt() override;

    void SetGame(IGamePtr game);
    void StartGame();

    void Show();

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

    //Update methods
    void UpdateHistory();
    void UpdateCaptured(EColor color);
    void UpdateBoard(const PairMatrix& newBoard);

    //Button related methods
    bool eventFilter(QObject* obj, QEvent* event);
	
    void ApplyButtonStyles(QPushButton* button);
    void HighlightPossibleMoves(const PositionList& possibleMoves);
    void MakeButtonsSelectable();
    void MakeButtonsUnselectable();

    //Other methods
	PairMatrix GetBoard() const;

    void CenterOnScreen();
    void ShowPromoteOptions();
    void ClearPieces();

private slots:
    void GridButtonClicked(Position position);

    void OnCopyButtonClicked();
    void OnSaveButtonClicked();
    void OnLoadButtonClicked();
    void OnRestartButtonClicked();
    void OnDrawButtonClicked();
    void OnHistoryClicked(QListWidgetItem* item);

private:
    Ui::ChessUIQtClass ui;
    
    std::array<std::array<GridButton*, 8>, 8> m_grid;
    
    std::optional<std::pair<int, int>> m_selectedCell;
    
    QPushButton* m_closeButton;
    QPushButton* m_minimizeButton;
    
    QLabel* m_messageLabel;
    QLabel* m_exceptionLabel;

    QListWidget* m_movesList;
    QListWidget* m_whiteCapturedPiecesList;
    QListWidget* m_blackCapturedPiecesList;
    
    QLabel* m_blackTimer;
    QLabel* m_whiteTimer;
    
    IGamePtr m_game;
};
