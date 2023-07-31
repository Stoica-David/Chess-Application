#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ChessUIQt.h"
#include "GridButton.h"
#include <QtWidgets/qgridlayout.h>
#include <QPushButton>
#include <QLabel>
#include <QListWidget>

#include "IGame.h"

using PairMatrix = std::array<std::array<std::pair<PieceType, PieceColor>, 8>, 8>;

class ChessUIQt : public QMainWindow, public IGameListener
{
    Q_OBJECT

private:
    PairMatrix GetBoard() const;

public:
    ChessUIQt(QWidget *parent = nullptr);
    ~ChessUIQt() override;

    void InitializeMessage(QGridLayout* mainGridLayout);
    void InitializeButtons(QGridLayout* mainGridLayout);
    void InitializeTimers(QGridLayout* mainGridLayout);
    void InitializeHistory(QGridLayout* mainGridLayout);
    void InitializeBoard(QGridLayout* mainGridLayout);
    void InitializeDeadWhitePieces(QGridLayout* mainGridLayout);
    void InitializeDeadBlackPieces(QGridLayout* mainGridLayou); 

    //Modify if necessary with your history representation
    void UpdateHistory();
    //Modify if necessary with your board representation
    void UpdateBoard(const std::array<std::array<std::pair<PieceType, PieceColor>, 8>, 8>& newBoard);
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

public slots:
    void OnButtonClicked(const std::pair<int, int>& position);

    void OnSaveButtonClicked();
    void OnLoadButtonClicked();
    void OnRestartButtonClicked();
    void OnDrawButtonClicked();
    void OnHistoryClicked(QListWidgetItem* item);
    void OnCopyButtonClicked();
    

signals:
    void Exit();

private:
    Ui::ChessUIQtClass ui;
    std::array<std::array<GridButton*, 8>, 8> m_grid;
    //std::array<std::array<GridButton*, 2>, 8> m_whiteGrid;
    //std::array<std::array<GridButton*, 2>, 8> m_blackGrid;
    std::optional<std::pair<int, int>> m_selectedCell;
    QLabel* m_MessageLabel;
    QLabel* m_ExceptionLabel;
    QListWidget* m_MovesList;
    QLabel* m_BlackTimer, *m_WhiteTimer;
    IGamePtr m_game;
};