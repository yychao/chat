#pragma once
 #include <QTcpServer>

class QTcpSocket;
class Server : public QTcpServer
{
    Q_OBJECT

public:
    Server(QObject* parent = 0);

private slots:
    void _disconnect();
    void _sendMessage();
    void _readMessage();

private:
    QTcpSocket *clientConnection;
};