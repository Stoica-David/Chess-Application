#include "ChessUIQt.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    std::shared_ptr<ChessUIQt> w = std::make_shared<ChessUIQt>();

    w->show();
    w->StartGame();

    QObject::connect(w.get(), &ChessUIQt::Exit, &a, &QApplication::quit);
    return a.exec();
}
