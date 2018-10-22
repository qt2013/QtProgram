#pragma execution_character_set("utf-8")

#include "uidemo08.h"
#include "ui_uidemo08.h"
#include "iconhelper.h"
#include <QLabel>
#include <QColor>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QTableView>
#include <QLineEdit>
#include <QTextEdit>
#include <QMessageBox>

UIDemo08::UIDemo08(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UIDemo08)
{
    ui->setupUi(this);
    this->initForm();   //初始化窗口
    this->init_page1(); //初始化兵器知识界面
    this->init_page2(); //初始化舰船战机界面
    this->init_page3(); //初始化战史战例界面
    this->init_page4(); //初始化军事论坛界面
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

    ui->page1->setStyleSheet(QString("QWidget[flag=\"left\"] QAbstractButton{min-height:%1px;max-height:%1px;}").arg(60));
    ui->page2->setStyleSheet(QString("QWidget[flag=\"left\"] QAbstractButton{min-height:%1px;max-height:%1px;}").arg(20));
    //设置信号槽显示查询结果
    connect(this,SIGNAL(showresult_1()),this,SLOT(slotshowresult_1()));
    //设置信号槽显示查询结果
    connect(this,SIGNAL(showresult_2()),this,SLOT(slotshowresult_2()));
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
void UIDemo08::init_page1()   //设置兵器界面的内容
{
    QHBoxLayout* layout=new QHBoxLayout(ui->frame);
    layout->addWidget(search_1=new QWidget,1);
    layout->addWidget(show_1=new QWidget,3);
    show_1->setAutoFillBackground(true);
    show_1->setPalette(QPalette(QColor(Qt::white)));

    QVBoxLayout* vlayout=new QVBoxLayout(search_1);
    QHBoxLayout* hlayout=new QHBoxLayout;
    vlayout->addLayout(hlayout);
    //添加查找框
    QPushButton* button=new QPushButton(search_1);
    button->setText("查询");
    hlayout->addWidget(button);
    hlayout->addWidget(filter=new QLineEdit);
    //设置filter样式
    filter->setStyleSheet("QLineEdit{border-width:1px;border-radius:4px;font-size:12px;color:black;border:1px solid gray;}"
            "QLineEdit:hover{border-width:1px;border-radius:4px;font-size:12px;color:black;border:1px solid rgb(70,200,50);}");
    //设置过滤器，当filter中的编辑数据变化时，view显示包含edit中的数据的行
    connect(filter,SIGNAL(textChanged(const QString &)),this,SLOT(slottextChanged(const QString &)));
    //设置样式
    button->setStyleSheet("QPushButton{color:red;background:yellow}");
    //加载数据库模型
    _model=new QSqlQueryModel;
    _model->setQuery("select * from weapon;");
    QSqlQuery query=_model->query();
    _view=new QTableView;
    _view->setModel(_model);
    //设置点击表格的消息槽函数
    connect(_view,&QTableView::clicked,this,[&](const QModelIndex &index){
        slotclickview(index);
    });
    //获取要显示的数据的列坐标
    int index_name=query.record().indexOf("name");
    int index_country=query.record().indexOf("country");
    int index_kind=query.record().indexOf("kind");
    //获取不显示的数据的列坐标
    int index_img=query.record().indexOf("img");
    int index_introduce=query.record().indexOf("introduce");
    int index_html=query.record().indexOf("html");
    //更改显示的标题
    _model->setHeaderData(index_name,Qt::Horizontal,"名称");
    _model->setHeaderData(index_country,Qt::Horizontal,"生产国");
    _model->setHeaderData(index_kind,Qt::Horizontal,"类型");
    _view->hideColumn(index_img);
    _view->hideColumn(index_introduce);
    _view->hideColumn(index_html);
    _view->setBackgroundRole(QPalette::ColorRole::Light);

    vlayout->addWidget(_view);

    //设置显示界面相关显示
    QHBoxLayout* hlayout_2=new QHBoxLayout(show_1);
    hlayout_2->addWidget(html_1=new QTextEdit,2);
    hlayout_2->addWidget(html_2=new QTextEdit,1);
    html_1->setBackgroundRole(QPalette::ColorRole::Text);
    html_2->setBackgroundRole(QPalette::ColorRole::Light);
    //将显示界面设置为不可编辑
    html_1->setFocusPolicy(Qt::NoFocus);
    html_2->setFocusPolicy(Qt::NoFocus);

}
void UIDemo08::init_page2()  //进入舰船战机显示界面
{
    QHBoxLayout* layout=new QHBoxLayout(ui->frame_2);
    layout->addWidget(search_2=new QWidget,1);
    layout->addWidget(show_2=new QWidget,3);
    show_2->setAutoFillBackground(true);
    show_2->setPalette(QPalette(QColor(Qt::white)));

    QVBoxLayout* vlayout=new QVBoxLayout(search_2);
    QHBoxLayout* hlayout=new QHBoxLayout;
    vlayout->addLayout(hlayout);
    //添加查找框
    QPushButton* button=new QPushButton(search_2);
    button->setText("查询");
    hlayout->addWidget(button);
    hlayout->addWidget(filter_2=new QLineEdit);
    //设置filter_2样式
    filter_2->setStyleSheet("QLineEdit{border-width:1px;border-radius:4px;font-size:12px;color:black;border:1px solid gray;}"
            "QLineEdit:hover{border-width:1px;border-radius:4px;font-size:12px;color:black;border:1px solid rgb(70,200,50);}");
    //设置过滤器，当filter中的编辑数据变化时，view显示包含edit中的数据的行
    connect(filter_2,SIGNAL(textChanged(const QString &)),this,SLOT(slottextChanged_2(const QString &)));
    //设置样式
    button->setStyleSheet("QPushButton{color:red;background:yellow}");
    //加载数据库模型
    _model_2=new QSqlQueryModel;
    _model_2->setQuery("select * from ship;");
    QSqlQuery query=_model_2->query();
    _view_2=new QTableView;
    _view_2->setModel(_model_2);
    //设置点击表格的消息槽函数
    connect(_view_2,&QTableView::clicked,this,[&](const QModelIndex &index){
        slotclickview_2(index);
    });
    //获取要显示的数据的列坐标
    int index_name=query.record().indexOf("name");
    int index_country=query.record().indexOf("country");
    int index_kind=query.record().indexOf("kind");
    //获取不显示的数据的列坐标
    int index_img=query.record().indexOf("img");
    int index_introduce=query.record().indexOf("introduce");
    int index_html=query.record().indexOf("html");
    //更改显示的标题
    _model_2->setHeaderData(index_name,Qt::Horizontal,"名称");
    _model_2->setHeaderData(index_country,Qt::Horizontal,"生产国");
    _model_2->setHeaderData(index_kind,Qt::Horizontal,"类型");
    _view_2->hideColumn(index_img);
    _view_2->hideColumn(index_introduce);
    _view_2->hideColumn(index_html);
    _view_2->setBackgroundRole(QPalette::ColorRole::Light);

    vlayout->addWidget(_view_2);

    //设置显示界面相关显示
    QHBoxLayout* hlayout_2=new QHBoxLayout(show_2);
    hlayout_2->addWidget(html_3=new QTextEdit,2);
    hlayout_2->addWidget(html_4=new QTextEdit,1);
    html_3->setBackgroundRole(QPalette::ColorRole::Text);
    html_4->setBackgroundRole(QPalette::ColorRole::Light);
    //将显示界面设置为不可编辑
    html_3->setFocusPolicy(Qt::NoFocus);
    html_4->setFocusPolicy(Qt::NoFocus);

}
void UIDemo08::init_page3()   //进入战史战例显示界面
{
    QVBoxLayout* layout=new QVBoxLayout(ui->frame_3);
    layout->addWidget(new QLabel("test"));
}
void UIDemo08::init_page4()   //进入军事论坛显示界面
{
    QVBoxLayout* layout=new QVBoxLayout(ui->frame_4);
    layout->addWidget(new QLabel("test"));
}
void UIDemo08::slottextChanged(const QString &filter)   //filter内容改变时的槽函数
{
    if(filter.isEmpty())
    {
        _model->setQuery("select* from weapon;");
        _model->query();
        return;
    }
    QSqlRecord record=_model->record();
    QString queryfilter;
    //拼凑查询内容
    QString subfilter=QString().sprintf("name like '%%%s%%' or country like '%%%s%%' or kind like '%%%s%%'",filter.toUtf8().data(),filter.toUtf8().data(),filter.toUtf8().data());
    queryfilter="select * from weapon where "+subfilter;
    _model->setQuery(queryfilter);
    QSqlQuery temp_query=_model->query();
}
void UIDemo08::slottextChanged_2(const QString &filter)   //filter内容改变时的槽函数
{
    if(filter.isEmpty())
    {
        _model_2->setQuery("select* from ship;");
        _model_2->query();
        return;
    }
    QSqlRecord record=_model_2->record();
    QString queryfilter;
    //拼凑查询内容
    QString subfilter=QString().sprintf("name like '%%%s%%' or country like '%%%s%%' or kind like '%%%s%%'",filter.toUtf8().data(),filter.toUtf8().data(),filter.toUtf8().data());
    queryfilter="select * from ship where "+subfilter;
    _model_2->setQuery(queryfilter);
    QSqlQuery temp_query=_model_2->query();
}
void UIDemo08::slotclickview(const QModelIndex &index)  //设置兵器页面的点击view中单元格的槽函数
{
    _introduce=_model->record(index.row()).value(4).toString();
    _html=_model->record(index.row()).value(5).toString();
    //刷新显示界面
    emit(showresult_1());
}
void UIDemo08::slotclickview_2(const QModelIndex &index)  //设置舰船战机页面的点击view中单元格的槽函数
{
    _introduce_2=_model_2->record(index.row()).value(4).toString();
    _html_2=_model_2->record(index.row()).value(5).toString();
    //刷新显示界面
    emit(showresult_2());
}
void UIDemo08::slotshowresult_1()   //设置兵器界面的结果显示的槽函数
{
    html_1->setText(_introduce);
    html_2->setText(_html);
}
void UIDemo08::slotshowresult_2()   //设置舰船战机界面的结果显示的槽函数
{
    html_3->setText(_introduce_2);
    html_4->setText(_html_2);
}
