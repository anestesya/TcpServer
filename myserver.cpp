#include "myserver.h"

#include <QTcpSocket>

MyServer::MyServer()
{
    running = false;
    qTcpServer = new QTcpServer;
    //clientList = new QLinkedList;
    QObject::connect(this, SIGNAL(newConnection()),this, SLOT(newClientConnected()));
}

void MyServer::runServer()
{
    if (running){
        this->stopServer();
        running = false;
    }
    else{
        this->startServer();
        running = true;
    }
    emit situationChanged(running);
}

void MyServer::startServer(){
    this->printMessage("Server is listenning on 1234 port...");
    this->listen(QHostAddress::Any, 1234);

}

void MyServer::stopServer(){    
    this->printMessage("Server Stopped!");
    ClientThread *ptrClient;
    foreach(ptrClient, clientList){
        ptrClient->disconnectClient();
    }
    this->close();
}

void MyServer::newClientConnected(){
    this->printMessage("New client connected...");

    QTcpSocket *clientConnection = this->nextPendingConnection();
    connect(clientConnection, SIGNAL(disconnected()),clientConnection, SLOT(deleteLater()));

    QString clientName = QString("Client%1").arg(clientList.size() + 1);
    ClientThread *clientThread = new ClientThread(this,clientConnection,clientName);

    connect(clientThread, SIGNAL(msgRecived(ClientThread*,QString)),this, SLOT(recivedFromClient(ClientThread*,QString)));
    connect(clientThread, SIGNAL(disconnecting(ClientThread*)),this, SLOT(clientDisconnecting(ClientThread*)));

    clientList.append(clientThread);
    clientThread->start();
    this->recivedFromClient(clientThread, "Im online now!!!");
}

void MyServer::printMessage(QString message){
    emit sendMainWindowMessage(message);
}

void MyServer::recivedFromClient(ClientThread *client, QString message){

    QString sendingMessage = client->clientName + " says: " + message;

    ClientThread *prtClient;
    foreach (prtClient, clientList){
        if (client != prtClient){
            prtClient->sendMessage(sendingMessage);
        }
    }
}

void MyServer::clientDisconnecting(ClientThread *client){
    if (clientList.removeOne(client)){
        this->printMessage(client->clientName + " is disconnected.");
        this->recivedFromClient(client,"im leaving...");
    }
    else {
        this->printMessage("Nao deu pra disconectar nada");
    }
}

