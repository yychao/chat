#include "feiqserver.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FeiQServer w;
    w.show();
    return a.exec();
}
