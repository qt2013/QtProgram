#include "mainwindow.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    //添加菜单
    QMenuBar* menubar=this->menuBar();
    QMenu* file_menu=menubar->addMenu("&文件");
}
