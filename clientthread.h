#ifndef CLIENTTHREAD_H
#define CLIENTTHREAD_H

#include <QThread>
#include <QTcpSocket>

class ClientThread : public QThread
{
    Q_OBJECT
public:
    ClientThread(QObject *parent, QTcpSocket *tcpSocket, QString name);
    ~ClientThread();
    void run();
    QString clientName;
    void sendMessage(QString message);
    void disconnectClient();

private:
    QTcpSocket *socketClient;
    bool connected;

public slots:
    void sendDisconnecting();
    void readFromSock();

signals:
    void error(QTcpSocket::SocketError socketError);
    void msgRecived(ClientThread *client, QString message);
    void disconnecting(ClientThread *client);

};

#endif // CLIENTTHREAD_H
