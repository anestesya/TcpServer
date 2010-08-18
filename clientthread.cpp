#include "clientthread.h"

ClientThread::ClientThread(QObject *parent, QTcpSocket *tcpSocket, QString name)
{
    socketClient = tcpSocket;
    clientName = name;
    connected = true;
    connect(socketClient, SIGNAL(disconnected()), this, SLOT(sendDisconnecting()) );     
    connect(socketClient, SIGNAL(readyRead()), this, SLOT(readFromSock()) );
}

ClientThread::~ClientThread()
{
    delete socketClient;
}

void ClientThread::run()
{   
    while (connected){
        //faz algo
    }
}

void ClientThread::disconnectClient()
{
    socketClient->disconnectFromHost();
}

void ClientThread::readFromSock(){
    QByteArray *block = new QByteArray;
    block->append(socketClient->readAll());    
    emit msgRecived(this, QString(*block));
    delete block;

}

void ClientThread::sendMessage(QString message)
{
    QByteArray *block = new QByteArray;
    block->append(message);
    socketClient->write(*block);
    delete block;
}

void ClientThread::sendDisconnecting(){
    connected = false;
    emit disconnecting(this);
}
