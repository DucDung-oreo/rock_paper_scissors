#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    // w.setWindowTitle("Player 1");
    QString title = w.get_clientId() + " - " + w.get_playerName();
    
    w.show();
    w.setWindowTitle(title);

    return a.exec();
}
