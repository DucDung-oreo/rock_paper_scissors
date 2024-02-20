#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "player.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_rockButton_clicked();
    void on_paperButton_clicked();
    void on_scissorsButton_clicked();
    void on_goButton_clicked();

private:
    Ui::MainWindow *ui;
    int roundCount = 1;
    void display_round();
    void display_result(Player* player_ptr);

    Player* player1 = new Player;
    Player* player2 = new Player;
};
#endif // MAINWINDOW_H
