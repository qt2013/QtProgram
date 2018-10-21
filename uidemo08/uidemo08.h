#ifndef UIDEMO08_H
#define UIDEMO08_H
#include <QWidget>
#include <QDebug>
#include <QSqlQueryModel>
#include <QTableView>
#include <QTextEdit>
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

    void do_page1();    //进入兵器知识显示界面
    void do_page2();    //进入舰船战机显示界面
    void do_page3();    //进入战史战例显示界面
    void do_page4();    //进入军事论坛显示界面

    QLineEdit* filter;  //兵器页面查询框
    QTextEdit* html_1;      //介绍兵器页面的html文本显示框
    QTextEdit* html_2;      //兵器界面格子页面的html文本显示框
    QSqlQueryModel* _model;
    QTableView* _view;
    QString _introduce;    //暂存兵器界面的查询结果中的兵器介绍文本
    QString _html;    //暂存兵器界面的查询结果中的html文本
signals:
    void showresult_1();  //设置显示兵器界面查询结果的信号函数
private slots:
    void initForm();
    void buttonClick();
    void slotshowresult(bool);
    void slottextChanged(const QString &);
    void slotclickview(const QModelIndex &index);
    void slotshowresult_1();
private slots:
    void on_btnMenu_Min_clicked();
    void on_btnMenu_Max_clicked();
    void on_btnMenu_Close_clicked();
};

#endif // UIDEMO08_H
