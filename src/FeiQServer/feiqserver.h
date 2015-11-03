#ifndef FEIQSERVER_H
#define FEIQSERVER_H

#include <QtGui/QDialog>
#include "ui_feiqserver.h"
#include "server.h"

class Connection;
class FeiQServer : public QDialog, protected Ui::FeiQServerClass
{
    Q_OBJECT

public:
    FeiQServer(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~FeiQServer();

private slots:
	void newConnection(Connection*);

private:
    Server server;
};

#endif // FEIQSERVER_H
