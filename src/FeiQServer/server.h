#pragma once
 #include <QTcpServer>

class Connection;
class Server : public QTcpServer
{
    Q_OBJECT

public:
    Server(QObject* parent = 0);

protected:
	//override
	virtual void incomingConnection(int handle);

signals:
	void newConnection(Connection*);
};