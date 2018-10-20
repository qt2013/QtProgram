#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class MainWindow : public QMainWindow   //主界面窗口
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

    QString name;   //用来记录用户姓名

    void showmain(QString name){
        this->name=name;
        this->setMaximumSize(1400,1000);
        this->setMinimumSize(1400,1000);
        this->showMaximized();
        }
signals:

public slots:
};

#endif // MAINWINDOW_H
