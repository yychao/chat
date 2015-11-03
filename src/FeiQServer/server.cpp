#include "server.h"
#include "connection.h"

Server::Server(QObject* parent)
: QTcpServer(parent)
{
    listen(QHostAddress::Any, 4305);
}


void Server::incomingConnection(int handle)
{
	Connection* connection = new Connection(this);
	connection->setSocketDescriptor(handle);
	emit newConnection(connection);
}

// void Server::_disconnect()
// {
// //     qDebug() << "Connection::_disconnect";
// //     this->deleteLater();
// }
// 
// void Server::_sendMessage()
// {
//     qDebug() << "Connection::_sendMessage";
//     QByteArray block;
//     QDataStream out(&block, QIODevice::WriteOnly);
//     out.setVersion(QDataStream::Qt_4_0);
// 
//     out << (quint16)0;
//     out << "Who is that?";
//     out.device()->seek(0);
//     out << (quint16)(block.size() - sizeof(quint16));
// 
// //    this->write(block);
// 
//     clientConnection = this->nextPendingConnection();
//     connect(clientConnection, SIGNAL(disconnected()), clientConnection, SLOT(deleteLater()));
//     connect(clientConnection, SIGNAL(readyRead()), this, SLOT(_readMessage()));
// 
//     clientConnection->write(block);
// }
// 
// void Server::_readMessage()
// {
//     qDebug() << "Connection::_readMessage";
//     QDataStream in(clientConnection);
// 
//     quint16 size;
//     if (clientConnection->bytesAvailable() < (int)sizeof(quint16)) {
//         return ;
//     }
//     in >> size;
// 
//     if (clientConnection->bytesAvailable() < size) {
//         return ;
//     }
// 
//     QString participator;
//     in >> participator;
// 
//     qDebug() << participator;
// }
