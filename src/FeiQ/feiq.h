#ifndef FEIQ_H
#define FEIQ_H

#include <QtGui/QDialog>
#include "ui_feiq.h"

#include "./loader/loader.h"
 
class FeiQ : public QDialog
{
    Q_OBJECT

public:
    FeiQ(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~FeiQ();

private slots:
    void AcceptUser(UserInfo);

private:
    Ui::FeiQClass ui;
};

#endif // FEIQ_H
