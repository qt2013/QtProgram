#ifndef UIDEMO08_H
#define UIDEMO08_H
#include <QWidget>
#include <QDebug>
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

private slots:
    void initForm();
    void buttonClick();
    void initLeftMain();
    void initLeftConfig();
    void leftMainClick();
    void leftConfigClick();

private slots:
    void on_btnMenu_Min_clicked();
    void on_btnMenu_Max_clicked();
    void on_btnMenu_Close_clicked();
};

#endif // UIDEMO08_H
