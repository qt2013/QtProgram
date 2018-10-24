#ifndef UIDEMO08_H
#define UIDEMO08_H
#include <QWidget>
#include <QDebug>
#include <QSqlQueryModel>
#include <QTableView>
#include <QTextEdit>
#include "qnavigationwidget.h"
#include <QtCharts>
using namespace QtCharts;
class QToolButton;

namespace Ui {
class UIDemo08;
}

class UIDemo08 : public QWidget
{
    Q_OBJECT

public:
    explicit UIDemo08(QWidget *parent = 0);
    ~UIDemo08();
    QString name;   //用来记录用户名
    void showmain(QString name)
    {
        this->name=name;
        show();
    }
private:
    Ui::UIDemo08 *ui;    

    QList<int> pixCharMain;
    QList<QToolButton *> btnsMain;  //用来储存兵器知识页面中左侧的三个按钮

    QList<int> pixCharConfig;
    QList<QToolButton *> btnsConfig;    //用来存储舰船战机页面中左侧的六个按钮

    QWidget* search_1;  //兵器知识显示界面中的查询窗口
    QWidget* show_1;    //兵器知识显示界面中的显示结果窗口
    QWidget* search_2;  //舰船战机显示界面中的查询窗口
    QWidget* show_2;    //舰船战机显示界面中的显示结果窗口

    void init_page1();    //进入兵器知识显示界面
    void init_page2();    //进入舰船战机显示界面
    void init_page3();    //进入战史战例显示界面
    void init_page4();    //进入军事论坛显示界面

    QLineEdit* filter;  //兵器页面查询框
    QLineEdit* filter_2;  //舰船战机页面查询框
    QTextEdit* html_1;      //介绍兵器页面的html文本显示框
    QTextEdit* html_2;      //兵器界面格子页面的html文本显示框
    QTextEdit* html_3;      //介绍舰船战机页面的html文本显示框
    QTextEdit* html_4;      //舰船战机界面格子页面的html文本显示框
    QSqlQueryModel* _model;
    QTableView* _view;
    QSqlQueryModel* _model_2;
    QTableView* _view_2;
    QString _introduce;    //暂存兵器界面的查询结果中的兵器介绍文本
    QString _html;    //暂存兵器界面的查询结果中的html文本
    QString _introduce_2;    //暂存舰船战机界面的查询结果中的兵器介绍文本
    QString _html_2;    //暂存舰船战机界面的查询结果中的html文本
    QNavigationWidget* navigationWidget;
    QTextEdit* text;    //军事军例页面介绍文本
    QWidget* chart_widget;  //军事军例图表显示界面
    void show_info_0();     //显示二战相关信息
    void show_info_1();     //显示一战相关信息
signals:
    void showresult_1();  //设置显示兵器界面查询结果的信号函数
    void showresult_2();  //设置显示舰船战机界面查询结果的信号函数
private slots:
    void initForm();
    void buttonClick();
    void slottextChanged(const QString &);
    void slottextChanged_2(const QString &);
    void slotclickview(const QModelIndex &index);
    void slotclickview_2(const QModelIndex &indexindex);
    void slotshowresult_1();
    void slotshowresult_2();
private slots:
    void on_btnMenu_Min_clicked();
    void on_btnMenu_Max_clicked();
    void on_btnMenu_Close_clicked();
};

#endif // UIDEMO08_H
