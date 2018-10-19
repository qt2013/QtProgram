#include <QApplication>
#include <QDebug>
#include "logwindow.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QMessageBox>
int main(int argc,char** argv)
{
    QApplication app(argc,argv);
    //链接远程数据库
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("202.182.112.123");
    db.setUserName("root");
    db.setPassword("123456");
    db.setDatabaseName("info");   //要链接的数据库名称
    bool open=db.open();
    if(open)
    {
        qDebug()<<"open db successfully";
    }
    else
    {
        QMessageBox::critical(nullptr,"error",db.lastError().text());   //链接失败，显示错误信息
        exit(0);
    }
    LogWindow w;
    w.show();
    return app.exec();
}
