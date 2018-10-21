#ifndef PAGE1_H
#define PAGE1_H

#include <QWidget>

class Page1 : public QWidget    //设置兵器显示界面
{
    Q_OBJECT
public:
    explicit Page1(QWidget *parent = nullptr);
    QWidget* search;    //定义查找界面
    QWidget* show;      //定义显示界面
signals:

public slots:
};

#endif // PAGE1_H
