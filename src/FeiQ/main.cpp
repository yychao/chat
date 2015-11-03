#include "feiq.h"
#include "./loader/loader.h"
#include <QtGui/QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Loader loader;
    FeiQ w;

    QObject::connect(&loader, SIGNAL(userLoad(UserInfo)), &w, SLOT(AcceptUser(UserInfo)));


    loader.show();
    return a.exec();
}
