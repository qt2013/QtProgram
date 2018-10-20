#pragma execution_character_set("utf-8")

#include "uidemo08.h"
#include "ui_uidemo08.h"
#include "iconhelper.h"
#include <QLabel>
UIDemo08::UIDemo08(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UIDemo08)
{
    ui->setupUi(this);
    this->initForm();   //初始化窗口
    this->initLeftMain();   //初始化兵器知识页面左侧按钮
    this->initLeftConfig(); //初始化舰船战机页面左侧按钮
    this->setGeometry(200,20,1400,1000);    //设置初始化窗口大小
}

UIDemo08::~UIDemo08()
{
    delete ui;
}

void UIDemo08::initForm()
{   
    //设置扩展属性
    this->setProperty("form", true);
    this->setProperty("canMove", true);
    //设置窗口属性
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);

    //对上方菜单栏中的应用图标，应用标题，及最小化按钮，最大化按钮，关闭按钮设置图标及字体属性
    IconHelper::Instance()->setIcon(ui->labIco, QChar(0xf073), 30);
    IconHelper::Instance()->setIcon(ui->btnMenu_Min, QChar(0xf068));
    IconHelper::Instance()->setIcon(ui->btnMenu_Max, QChar(0xf067));
    IconHelper::Instance()->setIcon(ui->btnMenu_Close, QChar(0xf00d));

    //ui->widgetMenu->setVisible(false);
    ui->widgetTitle->setProperty("form", "title");
    ui->widgetTop->setProperty("nav", "top");
    //设置应用标题名称及显示字体属性
    ui->labTitle->setText("军事百科");
    ui->labTitle->setFont(QFont("Microsoft Yahei", 20));
    this->setWindowTitle(ui->labTitle->text());

    QString welcome_str="welcome "+name;
    ui->label->setText(welcome_str);
    ui->label->setFont(QFont("Microsoft Yahei", 10));

    ui->stackedWidget->setStyleSheet("QLabel{font:60pt;}");

    QSize icoSize(32, 32);
    int icoWidth = 85;

    //设置顶部导航按钮
    QList<QToolButton *> tbtns = ui->widgetTop->findChildren<QToolButton *>();
    foreach (QToolButton *btn, tbtns) {
        btn->setIconSize(icoSize);
        btn->setMinimumWidth(icoWidth);
        btn->setCheckable(true);
        connect(btn, SIGNAL(clicked()), this, SLOT(buttonClick()));
    }

    ui->btnMain->click();

    ui->widgetLeftMain->setProperty("flag", "left");
    ui->widgetLeftConfig->setProperty("flag", "left");
    ui->page1->setStyleSheet(QString("QWidget[flag=\"left\"] QAbstractButton{min-height:%1px;max-height:%1px;}").arg(60));
    ui->page2->setStyleSheet(QString("QWidget[flag=\"left\"] QAbstractButton{min-height:%1px;max-height:%1px;}").arg(20));
}

void UIDemo08::buttonClick()    //设置菜单按钮的槽函数
{
    QToolButton *b = (QToolButton *)sender();
    QString name = b->text();   //获取按钮的文本

    //设置个按钮被点击时的checkable属性
    QList<QToolButton *> tbtns = ui->widgetTop->findChildren<QToolButton *>();
    foreach (QToolButton *btn, tbtns) {
        if (btn == b) {
            btn->setChecked(true);
        } else {
            btn->setChecked(false);
        }
    }
    //根据按下的按钮来切换到相应的堆栈窗口
    if (name == "兵器知识") {
        ui->stackedWidget->setCurrentIndex(0);
    } else if (name == "舰船战机") {
        ui->stackedWidget->setCurrentIndex(1);
    } else if (name == "战史战例") {
        ui->stackedWidget->setCurrentIndex(2);
    } else if (name == "军事论坛") {
        ui->stackedWidget->setCurrentIndex(3);
    } else if (name == "用户退出") {
        exit(0);
    }
}

void UIDemo08::initLeftMain()
{
    //将按钮的索引和按钮本身装进列表，方便后继调用
    pixCharMain << 0xf030 << 0xf03e << 0xf247;
    btnsMain << ui->tbtnMain1 << ui->tbtnMain2 << ui->tbtnMain3;
    //初始化个按钮的属性和样式
    int count = btnsMain.count();
    for (int i = 0; i < count; i++) {
        btnsMain.at(i)->setCheckable(true);
        btnsMain.at(i)->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        connect(btnsMain.at(i), SIGNAL(clicked(bool)), this, SLOT(leftMainClick()));
    }

    IconHelper::Instance()->setStyle(ui->widgetLeftMain, btnsMain, pixCharMain, 15, 35, 25, "left", 4);
    //将页面显示在第一页
    ui->tbtnMain1->click();
}

void UIDemo08::initLeftConfig()
{
     //将按钮的索引和按钮本身装进列表，方便后继调用
    pixCharConfig << 0xf031 << 0xf036 << 0xf249 << 0xf055 << 0xf05a << 0xf249;
    btnsConfig << ui->tbtnConfig1 << ui->tbtnConfig2 << ui->tbtnConfig3 << ui->tbtnConfig4 << ui->tbtnConfig5 << ui->tbtnConfig6;
    //初始化个按钮的属性和样式
    int count = btnsConfig.count();
    for (int i = 0; i < count; i++) {
        btnsConfig.at(i)->setCheckable(true);
        btnsConfig.at(i)->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        connect(btnsConfig.at(i), SIGNAL(clicked(bool)), this, SLOT(leftConfigClick()));
    }

    IconHelper::Instance()->setStyle(ui->widgetLeftConfig, btnsConfig, pixCharConfig, 10, 20, 15, "left", 5);
     //将页面显示在第一页
    ui->tbtnConfig1->click();
}

void UIDemo08::leftMainClick()  //兵器知识页面左侧按钮的槽函数
{
    QToolButton *b = (QToolButton *)sender();
    QString name = b->text();

    int count = btnsMain.count();
    for (int i = 0; i < count; i++) {
        if (btnsMain.at(i) == b) {
            btnsMain.at(i)->setChecked(true);
            btnsMain.at(i)->setIcon(QIcon(IconHelper::Instance()->getPixmap(btnsMain.at(i), false)));
        } else {
            btnsMain.at(i)->setChecked(false);
            btnsMain.at(i)->setIcon(QIcon(IconHelper::Instance()->getPixmap(btnsMain.at(i), true)));
        }
    }
    //根据按钮的名称来绘制相应的widget
    if(name=="轻兵器类")
    {
        qDebug()<<name;
        ui->stackedWidget_2->setCurrentWidget(ui->page);
        QVBoxLayout* layout=new QVBoxLayout(ui->page);
        layout->addWidget(new QLabel(name));
    }
    else if(name=="重兵器类")
    {
        qDebug()<<name;
        ui->stackedWidget_2->setCurrentWidget(ui->page_2);
        QVBoxLayout* layout=new QVBoxLayout(ui->page_2);
        layout->addWidget(new QLabel(name));
    }
    else
    {
        qDebug()<<name;
        ui->stackedWidget_2->setCurrentWidget(ui->page_3);
        QVBoxLayout* layout=new QVBoxLayout(ui->page_3);
        layout->addWidget(new QLabel(name));
    }
}

void UIDemo08::leftConfigClick()
{
    QToolButton *b = (QToolButton *)sender();
    QString name = b->text();

    int count = btnsConfig.count();
    for (int i = 0; i < count; i++) {
        if (btnsConfig.at(i) == b) {
            btnsConfig.at(i)->setChecked(true);
            btnsConfig.at(i)->setIcon(QIcon(IconHelper::Instance()->getPixmap(btnsConfig.at(i), false)));
        } else {
            btnsConfig.at(i)->setChecked(false);
            btnsConfig.at(i)->setIcon(QIcon(IconHelper::Instance()->getPixmap(btnsConfig.at(i), true)));
        }
    }

//    ui->lab2->setText(name);
}

void UIDemo08::on_btnMenu_Min_clicked()     //设置最小化的槽函数
{
    showMinimized();
}

void UIDemo08::on_btnMenu_Max_clicked() //设置最大化的槽函数
{
    static bool max = false;
    static QRect location = this->geometry();

    if (max) {
        this->setGeometry(location);
    } else {
        location = this->geometry();
        this->setGeometry(qApp->desktop()->availableGeometry());
    }

    this->setProperty("canMove", max);
    max = !max;
}

void UIDemo08::on_btnMenu_Close_clicked()   //设置关闭的槽函数
{
    close();
}

