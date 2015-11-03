#ifndef _LOADER_H
#define _LOADER_H

#include <QtGui/QDialog>
#include "ui_loader.h"

typedef struct _UserInfo {
    QString userName;
}UserInfo;

class QTcpSocket;
class Loader : public QDialog, public Ui::LoaderDialog
{
    Q_OBJECT

public:
    Loader(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~Loader();

    bool IsActivedUser(const QString& userName, const QString& password);

private slots:
    void accept();
    void _disconnect();
    void _sendMessage();
    void _readMessage();

signals:
    void userLoad(UserInfo userInfo);

private:
    QTcpSocket *pTcpSocket;
    UserInfo userInfo;
};

#endif // _LOADER_H
