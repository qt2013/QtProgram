#include "logwindow.h"
#include "ui_logwindow.h"
#include <QPixmap>
#include <QtDebug>
#include <QMessageBox>
#include <QtSql/QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlRecord>
LogWindow::LogWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogWindow)
{
    ui->setupUi(this);
    ui->label_3->setPixmap(QPixmap(":/jpg/bbb.jpg"));   //添加资源文件
}

LogWindow::~LogWindow()
{
    delete ui;
}

void LogWindow::on_pushButton_clicked()     //响应登录按钮的槽函数
{
    //获取输入的账号和密码
    QString username=ui->lineEdit->text();
    QString password=ui->lineEdit_2->text();
    //判断输入的账号和密码是否为空
    if(username==nullptr)
    {
        QMessageBox::critical(nullptr,"error","输入的账号不能为空");
        return;
    }
    if(password==nullptr)
    {
        QMessageBox::critical(nullptr,"error","输入的密码不能为空");
        return;
    }
    //判断输入的账号是否存在及输入的密码是否正确
    QSqlQueryModel model;
    model.setQuery("select name,password from user;");
    QSqlQuery query=model.query();
    int index_name=query.record().indexOf("name");      //获取姓名在数据库中的第几列
    int index_password=query.record().indexOf("password");  //获取密码在数据库中的第几列
    bool name_exit=false;   //用来记录数据库中是否存在输入的账号
    bool password_true=false;   //用来记录输入的密码是否正确
    while(query.next())
    {
        QString name=query.value(index_name).toString();
        QString password=query.value(index_password).toString();
        if(name==ui->lineEdit->text())
        {
            name_exit=true;
            if(password==ui->lineEdit_2->text())
            {
                password_true=true;
            }
        }
    }
    if(!name_exit)
    {
        QMessageBox::warning(nullptr,"warning","账号不存在,请先注册");
        return;
    }
    if(!password_true)
    {
        QMessageBox::critical(nullptr,"error","密码错误");
        return;
    }
    //账号存在且密码正确，则进入主界面
//    qDebug()<<"登录成功";
    emit(this->close());    //关闭登录窗口
    _main=new MainWindow;
    _main->showmain(ui->lineEdit->text());   //将用户姓名传递到主界面
}

void LogWindow::on_pushButton_2_clicked()
{

}
