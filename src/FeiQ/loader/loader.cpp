#include "loader.h"
#include <QtGui>
#include <QtNetwork>

Loader::Loader(QWidget *parent, Qt::WFlags flags)
: QDialog(parent, flags)
, pTcpSocket(NULL)
{
    setupUi(this);
}

Loader::~Loader()
{

}


void Loader::accept()
{
    userInfo.userName = lineEdit_user->text();
    if (IsActivedUser(userInfo.userName, lineEdit_password->text())) {
        //emit userLoad(userInfo);
        //QDialog::accept();
    }
    else {
        QMessageBox::warning(this, QLatin1String("Warring"), QLatin1String("UserName or  Password Error."));
    }
}


bool Loader::IsActivedUser(const QString& userName, const QString& password)
{
    pTcpSocket = new QTcpSocket(this);
    QObject::connect(pTcpSocket, SIGNAL(readyRead()), this, SLOT(_readMessage()));
    QObject::connect(pTcpSocket, SIGNAL(disconnected()), this, SLOT(_disconnect()));

    // find out which IP to connect to
    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // use the first non-localhost IPv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
            ipAddressesList.at(i).toIPv4Address()) {
                ipAddress = ipAddressesList.at(i).toString();
                break;
        }
    }
    // if we did not find one, use IPv4 localhost
    if (ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();

    pTcpSocket->connectToHost(ipAddress, 4305);
    
    return true;
}


void Loader::_disconnect()
{
    qDebug() << "Connection::_disconnect";
    pTcpSocket->deleteLater();
    pTcpSocket = NULL;
}

void Loader::_readMessage()
{
    qDebug() << "Connection::_readMessage";
    QDataStream in(pTcpSocket);

    quint16 size;
    if (pTcpSocket->bytesAvailable() < (int)sizeof(quint16)) {
        return ;
    }
    in >> size;

    if (pTcpSocket->bytesAvailable() < size) {
        return ;
    }

    QByteArray block;
    in >> block;

    QString participator(block);
    qDebug() << participator;

    _sendMessage();
}

void Loader::_sendMessage()
{
    qDebug() << "Connection::_sendMessage";
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);

    out << (quint16)0;
    out << userInfo.userName;
    out << userInfo.userIp;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    pTcpSocket->write(block);
}