#include "feiq.h"

FeiQ::FeiQ(QWidget *parent, Qt::WFlags flags)
    : QDialog(parent, flags)
{
    ui.setupUi(this);
}

FeiQ::~FeiQ()
{

}


void FeiQ::AcceptUser(UserInfo)
{
    this->show();
}
