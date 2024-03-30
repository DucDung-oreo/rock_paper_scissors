#ifndef GAMESERVER_H
#define GAMESERVER_H

#include <QDialog>
#include <QString>
#include <QList>

QT_BEGIN_NAMESPACE
class QLabel;
class QTcpServer;
QT_END_NAMESPACE

class GameServer : public QDialog
{
    Q_OBJECT

public:
    explicit GameServer(QWidget *parent = nullptr);

private slots:
    void sendFortune();

private:
    void initGameServer();

    QLabel *statusLabel = nullptr;
    QTcpServer *tcpGameServer = nullptr;
    QList<QString> fortunes;
};

#endif // GAMESERVER_H
