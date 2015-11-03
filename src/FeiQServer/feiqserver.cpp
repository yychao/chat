#include "feiqserver.h"
#include "connection.h"
#include <QtNetwork>

FeiQServer::FeiQServer(QWidget *parent, Qt::WFlags flags)
    : QDialog(parent, flags)
{
    setupUi(this);

	QObject::connect(&server, SIGNAL(newConnection(Connection*)), this, SLOT(newConnection(Connection*)));

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

	lineEdit_serverIp->setText(ipAddress);
	lineEdit_serverIp->setReadOnly(true);
	lineEdit_serverPort->setText(QString::number(server.serverPort()));
	lineEdit_serverPort->setReadOnly(true);
}

FeiQServer::~FeiQServer()
{

}

void FeiQServer::newConnection(Connection* con)
{
	QObject::connect(con, SIGNAL(readyRead()), con, SLOT(_readMessage()));
	QObject::connect(con, SIGNAL(disconnected()), con, SLOT(_disconnect()));

	con->_sendMessage();
}
