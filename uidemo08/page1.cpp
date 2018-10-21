#include "page1.h"
#include <QHBoxLayout>
Page1::Page1(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout* hlayout=new QHBoxLayout(this);
    search=new QWidget;
    show=new QWidget;
    hlayout->addWidget(search,1);
    hlayout->addWidget(show,3);
    show->setAutoFillBackground(true);
    show->setPalette(QPalette(QColor(Qt::white)));
}
