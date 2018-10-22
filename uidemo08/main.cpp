#include "uidemo08.h"
#include "appinit.h"
#include "logwindow.h"
#include <QApplication>
#include <QTextCodec>
#include <QFile>
#include <QSqlDatabase>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
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
        QMessageBox::critical(nullptr,"error","网络异常，请稍后再试!");   //链接失败，显示错误信息
        exit(0);
    }
#if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
#if _MSC_VER
    QTextCodec *codec = QTextCodec::codecForName("gbk");
#else
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
#endif
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
#else
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    QTextCodec::setCodecForLocale(codec);
#endif

    //加载样式表
    QFile file(":/qss/psblack.css");
    if (file.open(QFile::ReadOnly)) {
        QString qss = QLatin1String(file.readAll());
        QString paletteColor = qss.mid(20, 7);
        qApp->setPalette(QPalette(QColor(paletteColor)));
        qApp->setStyleSheet(qss);
        file.close();
    }

    a.setFont(QFont("Microsoft Yahei", 9));
    AppInit::Instance()->start();

    LogWindow w;
    w.show();

    return a.exec();
}
