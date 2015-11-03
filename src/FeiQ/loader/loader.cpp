#include "loader.h"
#include <QtGui>
#include <QtNetwork>

Loader::Loader(QWidget *parent, Qt::WFlags flags)
: QDialog(parent, flags)
, pTcpSocket(NULL)
{
    setupUi(this);

	lineEdit_serverIp->setText("192.168.1.107");
	lineEdit_serverPort->setText("4305");
	lineEdit_user->setFocus(Qt::OtherFocusReason);
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
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    pTcpSocket->write(block);
}