#include "ChessUIQt.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    std::shared_ptr<ChessUIQt> w = std::make_shared<ChessUIQt>();

	auto game = IGame::Produce();

    game->AddListener(w);

    w->SetGame(game);
    w->show();
    w->StartGame();

    QObject::connect(w.get(), &ChessUIQt::Exit, &a, &QApplication::quit);

    auto result = a.exec();

    game->RemoveListener(w.get());

    return result;
}
