#ifndef GAMECLIENT_H
#define GAMECLIENT_H
#pragma once

#include <QDialog>
#include <QComboBox>
#include <QLabel>
//#include <QAbstractSocket>
//#include <QTcpSocket>


class GameClient : public QDialog
{
    Q_OBJECT

public:
    GameClient();

private slots:
    void requestNewFortune();
    void readFortune();
//    void displayError(QAbstractSocket::SocketError socketError);
    void enableGetFortuneButton();

    private:
    QComboBox *hostCombo = nullptr;
    QLineEdit *portLineEdit = nullptr;
    QLabel *statusLabel = nullptr;
    QPushButton *getFortuneButton = nullptr;

//    QTcpSocket *tcpSocket = nullptr;
    QDataStream in;
    QString currentFortune;
};

#endif // GAMECLIENT_H
