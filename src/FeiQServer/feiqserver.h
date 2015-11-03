#ifndef FEIQSERVER_H
#define FEIQSERVER_H

#include <QtGui/QDialog>
#include "ui_feiqserver.h"
#include "server.h"

class FeiQServer : public QDialog
{
    Q_OBJECT

public:
    FeiQServer(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~FeiQServer();

private:
    Ui::FeiQServerClass ui;

    Server server;
};

#endif // FEIQSERVER_H
