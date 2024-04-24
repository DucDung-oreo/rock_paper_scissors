#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "player.h"
#include <QTimer>
#include <QTcpSocket>
#include <QtMqtt/QMqttClient>

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
    void display_round_and_result();
    void reset_for_new_round(QString round_string, QString computer_string);

    void on_goToGameButton_clicked();

private:
    Ui::MainWindow *ui;
    int roundCount = 1;
    QString result_for_player1;

    Player* player1 = new Player;
    Player* player2 = new Player;
};
#endif // MAINWINDOW_H
