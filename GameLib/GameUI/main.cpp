#include "ChessUIQt.h"
#include <QtWidgets/QApplication>
#include <QInputDialog>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon("res/greg.png"));
    std::shared_ptr<ChessUIQt> w = std::make_shared<ChessUIQt>();

    w->Show();
    w->PopUp();

    auto result = a.exec();

    w->GetGame()->RemoveListener(w.get());

    return result;
}
