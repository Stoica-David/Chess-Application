#include "ChessUIQt.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon("res/greg.png"));
    std::shared_ptr<ChessUIQt> w = std::make_shared<ChessUIQt>();

	auto game = IGame::Produce();

    game->AddListener(w);

    w->SetGame(game);
    w->StartGame();

    w->Show();

    auto result = a.exec();

    game->RemoveListener(w.get());

    return result;
}
