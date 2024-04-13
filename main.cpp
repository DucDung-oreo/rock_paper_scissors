#include "mainwindow.h"
#include "gameclient.h"
#include "gameserver.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // running the gameClient, keep this to use the application
    QApplication::setApplicationDisplayName(GameClient::tr("Fortune GameClient 1"));
    GameClient gameClient1;
    gameClient1.show();

//    QApplication::setApplicationDisplayName(GameClient::tr("Fortune GameClient 2"));
//    GameClient gameClient2;
//    gameClient2.show();

    // running the gameServer, keep this to use the server for local testing
    // comment this out to check with a remote server
    QApplication::setApplicationDisplayName(GameServer::tr("Fortune GameServer"));
    GameServer gameServer;
    gameServer.show();

    // our main game here, you can comment this out to not run the game application
    MainWindow w;
    w.show();
    return a.exec();
}
