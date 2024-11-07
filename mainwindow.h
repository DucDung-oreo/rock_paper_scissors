#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "player.h"
#include <QTimer>
#include <QTcpSocket>
#include <QtMqtt/QMqttClient>
#include <QMessageBox>
#include <QtMqtt/QMqttMessage>
#include <QtMqtt/QMqttSubscription>
#include <QJsonDocument>
#include <QJsonObject>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QMqttSubscription *sub = nullptr, QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void setClientPort(int p);
    void updateMessage(const QMqttMessage &msg);
    QString get_clientId();
    QString get_playerName();

private slots:
    void on_rockButton_clicked();
    void on_paperButton_clicked();
    void on_scissorsButton_clicked();
    void on_goButton_clicked();
    void display_round_and_result();
    void reset_for_new_round(QString round_string, QString computer_string);

    void on_goToGameButton_clicked();
    void on_backButton_clicked();

    void brokerDisconnected();
    void updateLogStateChange();
    void on_connectButton_clicked();
    void on_subscribeButton_clicked();
    void on_testSubButton_clicked();
    void on_multiCheckBox_stateChanged(int arg1);
    void disable_multiplayer(bool state);
    void disable_singleplayer(bool state);

private:
    Ui::MainWindow *ui;
    QMqttClient *m_client;
    int roundCount = 1;

    QString result_for_player1;
    QMqttSubscription *m_sub;

    Player* player1 = new Player;
    Player* player2 = new Player;
};
#endif // MAINWINDOW_H
