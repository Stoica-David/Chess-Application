#include "ChessUIQt.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    IGamePtr game = IGame::Produce();

    auto ui = std::make_shared<ChessUIQt>();

    game->AddListener(ui);

    ui->setGame(game);
    ui->show();
    ui->StartGame();

    QObject::connect(ui.get(), &ChessUIQt::Exit, &a, &QApplication::quit);
    return a.exec();
}
