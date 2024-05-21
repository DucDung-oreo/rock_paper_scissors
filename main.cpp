#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Player 1");
    w.show();

    MainWindow test_window;
    test_window.setWindowTitle("Player 2");
    test_window.show();
    return a.exec();
}
