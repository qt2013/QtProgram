#ifndef LOGWINDOW_H
#define LOGWINDOW_H

#include <QWidget>
#include "uidemo08.h"
namespace Ui {
class LogWindow;    //登录界面
}

class LogWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LogWindow(QWidget *parent = nullptr);
    ~LogWindow();
    UIDemo08* mainwindow;
private slots:
    void on_pushButton_clicked();   //点击登录框的槽函数

    void on_pushButton_2_clicked();     //点击注册框的槽函数

private:
    Ui::LogWindow *ui;
};

#endif // LOGWINDOW_H
