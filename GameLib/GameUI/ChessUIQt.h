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

    void InitializeMessage(QGridLayout* mainGridLayout);
    void InitializeButtons(QGridLayout* mainGridLayout);
    void InitializeTimers(QGridLayout* mainGridLayout);
    void InitializeHistory(QGridLayout* mainGridLayout);
    void InitializeBoard(QGridLayout* mainGridLayout);
    void InitializePlayer(QGridLayout* mainGridLayout, EColor);
    void InitializeTabBar(QGridLayout* mainGridLayout);

    bool eventFilter(QObject* obj, QEvent* event);

    //Modify if necessary with your history representation
    void UpdateHistory();

    //void UpdateCaptured(EColor color);

    //Modify if necessary with your board representation
    void UpdateBoard(const PairMatrix& newBoard);
    //Modify if necessary with your possible moves representation
    void HighlightPossibleMoves(const std::vector<std::pair<int, int>>& possibleMoves);
    //Modify or delete
    void StartGame();
    void ShowPromoteOptions();

    void SetGame(IGamePtr game);

    void OnMove() override;
    void OnGameOver(EOverState) override;
    void OnChoosePiece() override;
    void OnCheck() override;
    void OnRestart() override;
    void OnPieceCapture(EPieceType, EColor) override;

public slots:
    void GridButtonClicked(const std::pair<int, int>& position);

    void OnCopyButtonClicked();
    void OnLoadButtonClicked();
    void OnRestartButtonClicked();
    void OnDrawButtonClicked();
    void OnHistoryClicked(QListWidgetItem* item);
    void OnSaveButtonClicked();
    void centerOnScreen();

signals:
    void Exit();

private:
	PairMatrix GetBoard() const;
	void ApplyButtonStyles(QPushButton* button);
	void minimizeWindow();
	void closeWindow();
    void MakeButtonsUnselectable();
    void MakeButtonsSelectable();
    void UpdateCaptured(EColor color);
    void ClearPieces();

private:
    Ui::ChessUIQtClass ui;
    std::array<std::array<GridButton*, 8>, 8> m_grid;
    std::optional<std::pair<int, int>> m_selectedCell;
    QPushButton* closeButton;
    QPushButton* minimizeButton;
    QLabel* m_MessageLabel;
    QLabel* m_ExceptionLabel;
    QListWidget* m_MovesList;
    QListWidget* m_whitePieces, *m_blackPieces;
    QLabel* m_BlackTimer, *m_WhiteTimer;
    QPoint m_lastMousePos;
    IGamePtr m_game;
    QListWidget* playerPieces;
};
