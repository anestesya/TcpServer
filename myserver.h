#ifndef MYSERVER_H
#define MYSERVER_H

#include <QTcpServer>
#include <QLinkedList>
#include "clientthread.h"

class MyServer : public QTcpServer
{
    Q_OBJECT
public:
    MyServer();
    void runServer();
    void startServer();
    void stopServer();    

private:
    bool running;
    QTcpServer *qTcpServer;
    void printMessage(QString message);
    QLinkedList<ClientThread *> clientList;

public slots:
    void recivedFromClient(ClientThread *client, QString message);
    void newClientConnected();
    void clientDisconnecting(ClientThread *client);

signals:
    void situationChanged(bool running);
    void sendMainWindowMessage(QString message);    
};

#endif // MYSERVER_H
