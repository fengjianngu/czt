#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <QtCore/qmath.h>
#include <time.h>
#include <QPainter>
#include <QProxyStyle>

//重写tabWidget
class CustomTabStyle : public QProxyStyle
{
public:
    QSize sizeFromContents(ContentsType type, const QStyleOption *option,
                           const QSize &size, const QWidget *widget) const
    {
        QSize s = QProxyStyle::sizeFromContents(type, option, size, widget);
        if (type == QStyle::CT_TabBarTab) {
            s.transpose();
            s.rwidth() = 91; // 设置每个tabBar中item的大小
            s.rheight() = 108;
        }
        return s;
    }

    void drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
    {
        if (element == CE_TabBarTabLabel) {
            if (const QStyleOptionTab *tab = qstyleoption_cast<const QStyleOptionTab *>(option)) {
                QRect allRect = tab->rect;

                if (tab->state & QStyle::State_Selected) {
                    painter->save();
                    painter->setPen(0x58ffbe);
                    painter->setBrush(QBrush(0x58ffbe));
                    painter->drawRect(allRect.adjusted(0, 0, 0, 0));
                    painter->restore();
                }else{

                    painter->save();
                    painter->setPen(0x009f4b);
                    painter->setBrush(QBrush(0x009f4b));
                    painter->drawRect(allRect.adjusted(0, 0, 0, 0));
                    painter->restore();
                }
                QTextOption option;
                option.setAlignment(Qt::AlignCenter);
                painter->setFont(QFont("Ubuntu", 14));
                if (tab->state & QStyle::State_Selected) {
                    painter->setPen(0xf8fcff);
                }
                else {
                    painter->setPen(0x030303);
                }

                painter->drawText(allRect, tab->text, option);
                return;
            }
        }

        if (element == CE_TabBarTab) {
            QProxyStyle::drawControl(element, option, painter, widget);
        }
    }
};

class CustomTabStyle2 : public QProxyStyle
{
public:
    QSize sizeFromContents(ContentsType type, const QStyleOption *option,
                           const QSize &size, const QWidget *widget) const
    {
        QSize s = QProxyStyle::sizeFromContents(type, option, size, widget);
        if (type == QStyle::CT_TabBarTab) {
            s.transpose();
            s.rwidth() = 224; // 设置每个tabBar中item的大小
            s.rheight() = 40;
        }
        return s;
    }

    void drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
    {
        if (element == CE_TabBarTabLabel) {
            if (const QStyleOptionTab *tab = qstyleoption_cast<const QStyleOptionTab *>(option)) {
                QRect allRect = tab->rect;

                QTextOption option;
                option.setAlignment(Qt::AlignCenter);
                if (tab->state & QStyle::State_Selected) {
                    painter->setPen(0x009f4b);
                }
                else {
                    painter->setPen(0x030303);
                }

                painter->drawText(allRect, tab->text, option);
                return;
            }
        }

        if (element == CE_TabBarTab) {
            QProxyStyle::drawControl(element, option, painter, widget);
        }
    }
};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget_2->tabBar()->setStyle(new CustomTabStyle2);
    ui->tabWidget->setTabPosition(QTabWidget::West);
    ui->tabWidget->tabBar()->setStyle(new CustomTabStyle);

    ui->tabWidget->setStyleSheet("QTabWidget::pane{ \
                                 border-left: 1px solid #eeeeee;\
}");

//新建websockets
webscoket1 = new QWebSocket();
webscoket2 = new QWebSocket();
connect(webscoket1,SIGNAL(connected()),this, SLOT(websocket_on_connect()));
connect(webscoket1,SIGNAL(textMessageReceived(QString)),this, SLOT(socket_read1(QString)));
connect(webscoket1,SIGNAL(disconnected()),this, SLOT(websocket_dis_connect()));
connect(webscoket2,SIGNAL(textMessageReceived(QString)),this, SLOT(socket_read2(QString)));

//刷新主界面改为画能谱曲线
bruse_ui = new QTimer(this);
bruse_ui->setInterval(3000);    // 3s
connect( bruse_ui, SIGNAL(timeout()), this, SLOT(Bruse_Ui()));

//设置等待界面
set_wait_ui = new Set_Wait(this);
set_wait_ui->move(200,165);
set_wait_ui->hide();

//低电量界面
low_power_ui = new Low_Power(this);
low_power_ui->move(200,165);
low_power_ui->hide();

//关机界面
ui_off = new Power_Off(this);
ui_off->move(200,165);
ui_off->hide();

//新建键盘
xkeypad = new QxKeyBoard(false, NULL, 0);
xkeypad->createKeyboard();
xkeypad->setGeometry(QRect( 0, 0, this->width(), this->height()));
xkeypad->setWindowOpacity( 0.9);
xkeypad->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
xkeypad->hide();

//显示开始界面定时器
timer_xstart = new QTimer(this);
timer_xstart->setInterval(3000);    // 3s
connect( timer_xstart, SIGNAL(timeout()), this, SLOT(timeout_xstart()));
timer_xstart->start();

//开始界面
xstart = new sys_start(this);
xstart->setWindowFlags(Qt::FramelessWindowHint);
xstart->move(0, 0);
xstart->show();

//刷新时间
timer_brush_data = new QTimer(this);
timer_brush_data->setInterval(1000);    // 1s
connect( timer_brush_data, SIGNAL(timeout()), this, SLOT(Brush_Time()));
timer_brush_data->start();

//刷新电池信息
brush_battery= new QTimer(this);
brush_battery->setInterval(3000);    // 3s
connect( brush_battery, SIGNAL(timeout()), this, SLOT(Brush_Battery()));
brush_battery->start();

//刷新充电图标显示
charger_battery= new QTimer(this);
charger_battery->setInterval(2000);    // 2s
connect( charger_battery, SIGNAL(timeout()), this, SLOT(Charger_Battery()));

//刷新核素识别时间计数
timer_cs =  new QTimer(this);
timer_cs->setInterval(1000);
connect(timer_cs, SIGNAL(timeout()), this, SLOT(hssb_cal()));

//核素识别时间达到规定时间发出test_cal()信号，执行核素计算
connect(this, SIGNAL(test_cal()), this, SLOT(Test_cal()));

//定时连接webserver
web_connect_timer= new QTimer(this);
web_connect_timer->setInterval(1000);    // 1s
connect(  web_connect_timer, SIGNAL(timeout()), this, SLOT(websocket_connect()));
web_connect_timer->start();

//连接探头 改为自动发送配置
connect_tt = new QTimer(this);
connect_tt->setInterval(5000);    // 5s
connect( connect_tt, SIGNAL(timeout()), this, SLOT(on_Button_Set1_clicked()));
connect_tt->start();

//循环给探头发送要数据,改用为按键蜂鸣器
sendcommd = new QTimer(this);
sendcommd->setInterval(60);    // 0.06s
connect( sendcommd, SIGNAL(timeout()), this, SLOT(Brush_data_commd()));

//新建登录界面
xlogin = new CsysLogin(this);
xlogin->setWindowFlags(Qt::FramelessWindowHint);
xlogin->move(155, 45);
xlogin->hide();

//设置并隐藏报警图标
pix.load("/home/lts/qtwork/CztHost/img/alertl.png");
ui->Sys_Warn->setPixmap(pix);
ui->Sys_Warn->clear();

//显示静音图标
pix_sound.load("/home/lts/qtwork/CztHost/img/speaker_off.png");
ui->Sound->setPixmap(pix_sound);

//显示电池图标
pix_battery.load("/home/lts/qtwork/CztHost/img/battery1.png");
ui->Battery->setPixmap(pix_battery);

//显示探头按钮图片
ui->Button_Tt->setStyleSheet(tr("background-image: url(/home/lts/qtwork/CztHost/img/btn_normal.png);"));

//显示低阈值报警按钮图片
ui->Button_Db->setStyleSheet(tr("background-image: url(/home/lts/qtwork/CztHost/img/btn_normal.png);"));

//显示高阈值报警按钮图片
ui->Button_Gb->setStyleSheet(tr("background-image: url(/home/lts/qtwork/CztHost/img/btn_normal.png);"));

//点击登录返回，触发登录失败槽函数
connect(xlogin,SIGNAL(XloginMsg()),this,SLOT(login_fail()));

//连接lineEdit信号显示键盘
connect(xlogin, SIGNAL(mySignal(void*)), this, SLOT(KeyBoardShow(void*)));
connect(ui->Set_time, SIGNAL(mySignal(void*)), this, SLOT(KeyBoardShow(void*)));
connect(ui->lineEdit_Jll_Star_Time, SIGNAL(mySignal(void*)), this, SLOT(KeyBoardShow(void*)));
connect(ui->lineEdit_Jll_End_Time, SIGNAL(mySignal(void*)), this, SLOT(KeyBoardShow(void*)));
connect(ui->lineEdit_Rz__Star_Time, SIGNAL(mySignal(void*)), this, SLOT(KeyBoardShow(void*)));
connect(ui->lineEdit_Rz_End_Time, SIGNAL(mySignal(void*)), this, SLOT(KeyBoardShow(void*)));
connect(ui->lineEdit_Fd_1, SIGNAL(mySignal(void*)), this, SLOT(KeyBoardShow(void*)));
connect(ui->lineEdit_Fd_2, SIGNAL(mySignal(void*)), this, SLOT(KeyBoardShow(void*)));
connect(ui->lineEdit_Yz_1, SIGNAL(mySignal(void*)), this, SLOT(KeyBoardShow(void*)));
connect(ui->lineEdit_Yz_2, SIGNAL(mySignal(void*)), this, SLOT(KeyBoardShow(void*)));
connect(ui->lineEdit_Ss_Time_1, SIGNAL(mySignal(void*)), this, SLOT(KeyBoardShow(void*)));
connect(ui->lineEdit_Ss_Time_2 ,SIGNAL(mySignal(void*)), this, SLOT(KeyBoardShow(void*)));
connect(ui->lineEdit_Pd_Time_1, SIGNAL(mySignal(void*)), this, SLOT(KeyBoardShow(void*)));
connect(ui->lineEdit_Pd_Time_2, SIGNAL(mySignal(void*)), this, SLOT(KeyBoardShow(void*)));
connect(ui->lineEdit_Gy, SIGNAL(mySignal(void*)), this, SLOT(KeyBoardShow(void*)));
connect(ui->lineEdit_Low_Warn, SIGNAL(mySignal(void*)), this, SLOT(KeyBoardShow(void*)));
connect(ui->lineEdit_Hight_Warn_, SIGNAL(mySignal(void*)), this, SLOT(KeyBoardShow(void*)));
connect(ui->lineEdit_jll_phsj, SIGNAL(mySignal(void*)), this, SLOT(KeyBoardShow(void*)));
connect(ui->lineEdit_npjl,SIGNAL(mySignal(void*)),this,SLOT(FileDialog_Npjl()));
connect(ui->lineEdit_Jllkd,SIGNAL(mySignal(void*)),this,SLOT(FileDialog_Jlkd()));
connect(ui->lineEdit_Nlkd_1,SIGNAL(mySignal(void*)),this,SLOT(FileDialog_Nlkd_1()));
connect(ui->lineEdit_Nlkd_2,SIGNAL(mySignal(void*)),this,SLOT(FileDialog_Nlke_2()));
connect(ui->lineEdit_Hsk,SIGNAL(mySignal(void*)),this,SLOT(FileDialog_Hsk()));
connect(ui->lineEdit_Low_Warn,SIGNAL(textChanged(QString)),this,SLOT(LineEdit_Db_Change()));
connect(ui->lineEdit_Hight_Warn_,SIGNAL(textChanged(QString)),this,SLOT(LineEdit_Gb_Change()));

//文件浏览
fileDialog = new QFileDialog(this);
fileDialog->setFileMode(QFileDialog::AnyFile);
fileDialog->setViewMode(QFileDialog::Detail);
fileDialog->setGeometry(0,0,800,480);

// 判断是否有数据库驱动——QSQLITE
if (!QSqlDatabase::drivers().contains("QSQLITE"))
QMessageBox::critical(this, "Unable to load database", "This demo needs the SQLITE driver");
datebase = QSqlDatabase::addDatabase( "QSQLITE", "main");   // 添加数据库驱动
createDateBaseFile();               // 打开/建立一个当天的数据库
//创建曲线
curGraph = ui->charts_widget1->addGraph();
curGraph1 = ui->charts_widget2->addGraph();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sleep(unsigned int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void MainWindow::power_off()
{
    ui_off->show();
    sleep(10);
    system("init 0");
}


//刷新能谱曲线
void MainWindow::Bruse_Ui()

{
    int cnt = 0;
    float tmp = 0;
    int n = 0;
    for(int i = 0; i < 512; i ++)
    {
        count_chart1[i] = 0.0;
    }
    for(int i = 0; i < 4096; i++)
    {
        tmp += count_npljhb[i];
        cnt += 1;
        if(cnt == 16)
        {
            count_chart1[n] = tmp;
            n ++;
            cnt = 0;
            tmp = 0;
        }

    }

    if(ch1_zds == 1024)
    {
        int s = 0;
        for(int i = 1; i <256; i ++)
        {
            energy_chart1[i] = s ;
            s+=4;


        }
        energy_chart1[255] = 1023 ;
    }

    //    if(ch1_zds == 2048)
    //    {
    //        int s1 = 0;
    //        for(int i = 0; i <256; i ++)
    //        {
    //            energy_chart1[i] = s1 ;
    //            s1+=8;

    //        }
    //        energy_chart1[255] = 2047 ;
    //    }

    double energy_max = energy_chart1[255];
    double count_max = count_chart1[0];

    for(int i = 1; i <256; i ++)
    {

        count_max = (count_max > count_chart1[i]) ? count_max : count_chart1[i];
    }

    ui->charts_widget1->xAxis->setRange(0, 5);
    ui->charts_widget1->yAxis->setRange(0, 5);
    curGraph->clearData();
    ui->charts_widget1->replot();

    QVector<double> x(256), y(256);
    for (int i=0; i<256; i++)
    {
        x[i] = energy_chart1[i];
        y[i] = count_chart1[i];
    }

    curGraph->setData(x, y);
    ui->charts_widget1->xAxis->setRange(0, energy_max);// 设置坐标轴的范围，以看到所有数据
    ui->charts_widget1->yAxis->setRange(0, count_max);

    ui->charts_widget1->replot();

    // qDebug()<<"                                              ui->charts_widget1->replot();"<<endl;
    x.clear();
    y.clear();

}

//刷新时间
void MainWindow::Brush_Time()
{
    Current_data_time = QDateTime::currentDateTime();
    QString date_time =Current_data_time.toString("yyyy年MM月dd日 hh:mm:ss");
    ui->label_Sys_Time->setText(date_time);
    //检测关机状态标志
        system(" cp /proc/power-off /poweroff  ");

        QFile file1("/poweroff" );
        file1.open(QIODevice::ReadOnly | QIODevice::Text);

        file1.readLine(data_power,100);

        int ret = QString(QLatin1String(data_power)).toInt();

        file1.close();

        if(ret == 1)
        {
            power_off();
        }

}

//充电显示
void MainWindow::Charger_Battery(void)
{

    pix_battery.load("/home/lts/qtwork/CztHost/img/battery0.png");
    ui->Battery->setPixmap(pix_battery);

}

//刷新电池信息
void MainWindow::Brush_Battery(void)
{
    system(" cp /proc/charger-info /charger ");
    char data1[100]={};
    char data2[100]={};
    QFile file1("/charger" );
    if(!file1.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::information( this, "提示", "没有电池信息", QObject::tr("确定"));
        return;
    }
    file1.readLine(data1,100);
    file1.readLine(data2,100);
    bat_mA = QString(QLatin1String(data1)).toInt();
    bat_mV =QString(QLatin1String(data2)).toInt();
    file1.close();
    if(bat_mA == 0)
    {
        charger_battery->stop();
        if((bat_mV == 8400) || (bat_mV > 8400)){
            pix_battery.load("/home/lts/qtwork/CztHost/img/battery5.png");
            ui->Battery->setPixmap(pix_battery);
        }
        else if ((8000< bat_mV) && (bat_mV< 8400)) {
            pix_battery.load("/home/lts/qtwork/CztHost/img/battery5.png");
            ui->Battery->setPixmap(pix_battery);
        }
        else if ((7600< bat_mV)&&( bat_mV < 8000)) {
            pix_battery.load("/home/lts/qtwork/CztHost/img/battery4.png");
            ui->Battery->setPixmap(pix_battery);
        }
        else if ((7300< bat_mV)&& (bat_mV < 7600)) {
            pix_battery.load("/home/lts/qtwork/CztHost/img/battery3.png");
            ui->Battery->setPixmap(pix_battery);
        }
        else if ((7000< bat_mV)&& (bat_mV < 7300)) {
            pix_battery.load("/home/lts/qtwork/CztHost/img/battery2.png");
            ui->Battery->setPixmap(pix_battery);
        }
        else if ((6500< bat_mV)&&(bat_mV < 7000)) {
            pix_battery.load("/home/lts/qtwork/CztHost/img/battery1.png");
            ui->Battery->setPixmap(pix_battery);
        }else if (bat_mV < 6500) {
            low_power_ui->show();
            system("echo 0 > /sys/class/leds/user-led0/brightness");
            sleep(1000);
            system("init 0");
        }
    }
    if  (bat_mA > 0) {
        charger_battery->start();
        if (( bat_mA < 600)&& (bat_mV == 8400)) {
            pix_battery.load("/home/lts/qtwork/CztHost/img/battery4.png");
            ui->Battery->setPixmap(pix_battery);
        }
        else if ((8200< bat_mV)&& (bat_mV <= 8400)) {
            pix_battery.load("/home/lts/qtwork/CztHost/img/battery3.png");
            ui->Battery->setPixmap(pix_battery);
        }
        else if ((7000< bat_mV)&& (bat_mV < 8200)) {
            pix_battery.load("/home/lts/qtwork/CztHost/img/battery2.png");
            ui->Battery->setPixmap(pix_battery);
        }else if ( bat_mV<7000) {
            pix_battery.load("/home/lts/qtwork/CztHost/img/battery1.png");
            ui->Battery->setPixmap(pix_battery);
        }
    }
}

//按键蜂鸣器响
void MainWindow::Brush_data_commd()
{
    system("echo 1 > /sys/class/leds/user-led0/brightness");
    sendcommd->stop();
}

//连接web
void MainWindow::websocket_connect()
{
    char ch = 0;
    QString path = QString("ws://%1:%2").arg(IP).arg(webport);
    QUrl url = QUrl(path);
    webscoket1->open(url,ch);

    char ch1 = 1;
    QString path1 = QString("ws://%1:%2").arg(IP).arg(webport);
    QUrl url1 = QUrl(path1);
    webscoket2->open(url1,ch1);
}

//web连接成功
void MainWindow::websocket_on_connect()
{
    web_connect_timer->stop();
    flags_sendcomd = 1;
    ui->Button_Tt->setStyleSheet(tr("background-image: url(/home/lts/qtwork/CztHost/img/btn_normal.png);"));
    ui->Sys_Warn->clear();
    ui->Sound->setPixmap(pix_sound);

    SQL_Add_data_Rz(2);
    system("echo 1 > /sys/class/leds/user-led0/brightness");
    system("echo 1 > /sys/class/leds/user-led1/brightness");
    system("echo 1 > /sys/class/leds/user-led2/brightness");
}

//web断开
void MainWindow::websocket_dis_connect()
{
    web_connect_timer->start();
    ui->Sys_Warn->setPixmap(pix);
    ui->Button_Tt->setStyleSheet(tr("background-image: url(/home/lts/qtwork/CztHost/img/btn_alert.png);"));
    pix_sound_on.load("/home/lts/qtwork/CztHost/img/speaker_on.png");
    ui->Sound->setPixmap(pix_sound_on);

    SQL_Add_data_Rz(1);
    // system("echo 0 > /sys/class/leds/user-led0/brightness");
    system("echo 0 > /sys/class/leds/user-led1/brightness");
    system("echo 0 > /sys/class/leds/user-led2/brightness");
}

//接收web1的数据
void MainWindow::socket_read1(QString mm1)
{
    double dead_time;
    double real_time;
    QString Ch_Name1;
    QJsonDocument doucment = QJsonDocument::fromJson(mm1.toLocal8Bit().data());  // 转化为 JSON 文档
    if (!doucment.isNull() ) {  // 解析未发生错误
        if (doucment.isObject()) {  // JSON 文档为对象
            QJsonObject object = doucment.object();  // 转化为对象
            if (object.contains("channel_id")) {
                QJsonValue value = object.value("channel_id");
                if (value.isString()) {
                    Ch_Name1 = value.toString();
                    //qDebug() << "Ch_Name : " << Ch_Name1;
                }
            }

            if (object.contains("live_time")) {
                QJsonValue value = object.value("live_time");
                if (value.isDouble()) {
                    dd1 = value.toDouble();
                }
            }
            if (object.contains("dead_time")) {
                QJsonValue value = object.value("dead_time");
                if (value.isDouble()) {
                    dead_time = value.toDouble();
                }
            }

            if (object.contains("real_time")) {
                QJsonValue value = object.value("real_time");
                if (value.isDouble()) {
                    dd3= real_time = value.toDouble();
                }
            }

            //            qDebug()<<"live_time:   "<<dd1;
            //            qDebug()<<"dead_time:   "<<dead_time;
            //            qDebug()<<"real_time:   "<<real_time;
            //            qDebug()<<"////////////////////////////////"<<endl;

            if (object.contains("channels") )
            {
                QJsonValue value = object.value("channels");

                if (value.isArray()) {  // channels 的 value 是数组
                    QJsonArray array = value.toArray();
                    int nSize = array.size();
                    for (int i = 0; i < nSize; ++i) {
                        QJsonValue value = array.at(i);
                        if (value.isObject()) {
                            QJsonObject ch_object = value.toObject();
                            if (ch_object.contains("value")) {
                                QJsonValue value = ch_object.value("value");

                                if (value.isDouble()) {

                                    double   ch1_value = value.toDouble();
                                    count1[i] = ch1_value/dd1;
                                }
                            }
                        }
                    }
                }
            }
        }
        if(flags_hssb == 1)
        {
            if(flags_cs== 1)
            {
                ch1_live += dd1;
                ch1_real += dd3;
            }
        }
    }
    //处理数据显示剂量率
    socket_data();
}

void MainWindow::socket_read2(QString mm2)
{
    QString Ch_Name2;
    QJsonDocument doucment2 = QJsonDocument::fromJson(mm2.toLocal8Bit().data());  // 转化为 JSON 文档
    if (!doucment2.isNull()) {  // 解析未发生错误
        if (doucment2.isObject()) {  // JSON 文档为对象
            QJsonObject object2 = doucment2.object();  // 转化为对象
            if (object2.contains("channel_id")) {
                QJsonValue value2 = object2.value("channel_id");
                if (value2.isString()) {
                    Ch_Name2 = value2.toString();
                }
            }

            if (object2.contains("live_time")) {
                QJsonValue value2 = object2.value("live_time");
                if (value2.isDouble()) {
                    dd2 = value2.toDouble();
                }
            }
            if (object2.contains("real_time")) {
                QJsonValue value2 = object2.value("real_time");
                if (value2.isDouble()) {
                    dd4 = value2.toDouble();
                }
            }

            if (object2.contains("channels") )
            {
                QJsonValue value2 = object2.value("channels");
                if (value2.isArray()) {  // channels 的 value 是数组
                    QJsonArray array2 = value2.toArray();
                    int nSize2 = array2.size();
                    for (int i = 0; i < nSize2; ++i) {
                        QJsonValue value2 = array2.at(i);
                        if (value2.isObject()) {
                            QJsonObject ch_object2 = value2.toObject();
                            if (ch_object2.contains("value")) {
                                QJsonValue value2 = ch_object2.value("value");
                                if (value2.isDouble()) {
                                    double ch2_value = value2.toDouble();
                                    count2[i] = ch2_value/dd2;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    if(flags_hssb == 1)
    {
        if(flags_cs== 1)
        {
            ch2_live += dd2;
            ch2_real += dd4;
        }
    }
}

//数据处理
void MainWindow::socket_data(void)
{
    int cnt1=1;
    int cnt2=1;
    int cnt3 = 1;
    int cnt4 = 1;
    float n = 0.0625;
    float m = 0.25;
    for(int i=0; i<ch1_zds;i++)
    {
        ch1_sz[i]=cnt1;
        cnt1++;
    }
    for(int i=0; i< ch1_zds; i++)
    {
        energy1[i]= (ch1_coe_E1*ch1_sz[i]*ch1_sz[i] + ch1_coe_E2*ch1_sz[i] +ch1_coe_E3);
    }
    for(int i=0; i<ch2_zds;i++)
    {
        ch2_sz[i]=cnt2;
        cnt2++;
    }
    for(int i=0; i< ch2_zds; i++)
    {
        energy2[i]= (ch2_coe_E1*ch2_sz[i]*ch2_sz[i] + ch2_coe_E2*ch2_sz[i] +ch2_coe_E3);
    }
    for(int i=0; i<4096;i++)
    {
        ch1_sz[i]=cnt3;
        cnt3++;
    }
    for(int i=0; i<4096;i++)
    {
        ch2_sz[i]=cnt4;
        cnt4++;
    }
    switch (ch1_zds) {
    case 1024:
        for(int i= 0; i < 1024; i++)
        {
            count1_1024[i] = count1[i];
            energy1_1024[i] = energy1[i];
        }
        for(int i =0; i <4096; i ++)
        {
            energy1_cz[i] = (ch1_coe_E1*n*ch1_sz[i]*ch1_sz[i] + ch1_coe_E2*m*ch1_sz[i] +ch1_coe_E3);
        }
        interp1024_4096(energy1_1024,count1_1024,energy1_cz,count1_cz);
        break;
        //    case 2048:

        //        for(int i= 0; i < 2048; i++)
        //        {
        //            count1_2048[i] = count1[i];
        //            energy1_2048[i] = energy1[i];

        //        }

        //        for(int i =0; i <4096; i ++)
        //        {
        //            energy1_cz[i] = (ch1_coe_E1*m*ch1_sz[i]*ch1_sz[i] + ch1_coe_E2*x*ch1_sz[i] +ch1_coe_E3);
        //        }

        //        interp2048_4096(energy1_2048,count1_2048,energy1_cz,count1_cz);

        //        break;
        //    case 4096:
        //        for(int i= 0; i < 4096; i++)
        //        {
        //            count1_cz[i] = count1[i];
        //            energy1_cz[i] = energy1[i];
        //        }

        //  interp(energy1_4096,count1_4096,energy1_cz,count1_cz);

        //     break;
        //    case 8192:
        //        for(int i= 0; i < 8192; i++)
        //        {
        //            count1_8192[i] = count1[i];
        //            energy1_8192[i] = energy1[i];
        //        }

        //        interp8192_4096(energy1_8192,count1_8192,energy1_cz,count1_cz);

        //        break;
    default:
        break;
    }
    switch (ch2_zds) {
    case 1024:
        for(int i= 0; i < 1024; i++)
        {
            count2_1024[i] = count2[i];
            energy2_1024[i] = energy2[i];
        }
        for(int i =0; i <4096; i ++)
        {
            energy2_cz[i] = (ch2_coe_E1*n*ch2_sz[i]*ch2_sz[i] + ch2_coe_E2*m*ch2_sz[i] +ch2_coe_E3);
        }
        interp1024_4096(energy2_1024,count2_1024,energy2_cz,count2_cz);
        break;
        //    case 2048:
        //        for(int i= 0; i < 2048; i++)
        //        {
        //            count2_2048[i] = count2[i];
        //            energy2_2048[i] = energy2[i];
        //        }

        //        for(int i =0; i <4096; i ++)
        //        {
        //            energy2_cz[i] = (ch2_coe_E1*m*ch2_sz[i]*ch2_sz[i] + ch2_coe_E2*x*ch2_sz[i] +ch2_coe_E3);
        //        }
        //        interp2048_4096(energy2_2048,count2_2048,energy2_cz,count2_cz);
        //        break;
        //    case 4096:
        //        for(int i= 0; i < 4096; i++)
        //        {
        //            count2_cz[i] = count2[i];
        //            energy2_cz[i] = energy2[i];
        //        }
        //  interp(energy2_4096,count2_4096,energy2_cz,count2_cz);
        //      break;
        //    case 8192:
        //        for(int i= 0; i < 8192; i++)
        //        {
        //            count2_8192[i] = count2[i];
        //            energy2_8192[i] = energy2[i];
        //        }
        //        interp8192_4096(energy2_8192,count2_8192,energy2_cz,count2_cz);
        //        break;
    default:
        break;
    }
    interp(energy2_cz,count2_cz,energy1_cz,count2_interp);
    for(int i = 0 ; i < 4096; i ++)
    {
        if(count2_interp[i] < 0)
            count2_interp[i] = 0;
    }
    for(int i=0; i<4096; i++)
    {
        spe_user[i] =( count1_cz[i] + count2_interp[i] );
        eng_user[i] =energy1_cz[i];
    }
    doseFromGeStd(eng_user,spe_user,eng_std,ge_std,&jlls,ge_user);
    //   qDebug()<<"jll_data:   "<<(jlls*1000);
    if(time_ph == 1)
    {
        jll = jlls*1000;
    }
    else if(time_ph == 2)
    {
        jll = ((jll_data[0] + jlls )/2) * 1000;
        jll_data[0] = jlls;
    }
    else if(time_ph > 2)
    {
        jll_tmp = 0;
        int j = 1;
        for(int i=0; i <(time_ph-1); i ++)
        {
            jll_tmp += jll_data[i];
        }
        jll = ((jll_tmp + jlls)/time_ph)*1000;
        for(int i =0; i < (time_ph-2); i ++)
        {
            jll_data[i] = jll_data[j];
            j++;
        }
        jll_data[time_ph-2] = jlls;
    }
    //判断阈值
    QString str_db = ui->low_warn->text();
    QString str_gb = ui->hight_warn->text();
    double db_yz = str_db.toDouble();
    double gb_yz = str_gb.toDouble();
    if((jll/1000)>(db_yz))
    {
        SQL_Add_data_Rz(5);
        ui->Sys_Warn->setPixmap(pix);
        ui->Button_Db->setStyleSheet(tr("background-image: url(/home/lts/qtwork/CztHost/img/btn_alert.png);"));
        pix_sound_on.load("/home/lts/qtwork/CztHost/img/speaker_on.png");
        ui->Sound->setPixmap(pix_sound_on);
        system("echo 0 > /sys/class/leds/user-led0/brightness");
        system("echo 0 > /sys/class/leds/user-led1/brightness");
        system("echo 0 > /sys/class/leds/user-led2/brightness");
    }
    if(jll>(gb_yz*1000))
    {
        SQL_Add_data_Rz(7);
        ui->Sys_Warn->setPixmap(pix);
        ui->Button_Gb->setStyleSheet(tr("background-image: url(/home/lts/qtwork/CztHost/img/btn_alert.png);"));
        pix_sound_on.load("/home/lts/qtwork/CztHost/img/speaker_on.png");
        ui->Sound->setPixmap(pix_sound_on);
        system("echo 0 > /sys/class/leds/user-led0/brightness");
        system("echo 0 > /sys/class/leds/user-led1/brightness");
        system("echo 0 > /sys/class/leds/user-led2/brightness");
    }
    //插入数据库
    SQL_Add_data(jll);
    //能谱测试数据累加
    if(flags_hssb == 1)
    {
        if(flags_cs== 1)
        {
            for(int i = 0; i < 1024; i ++)
            {
                count1_nplj[i] +=count1[i];
                count2_nplj[i] +=count2[i];
            }
            interp1024_4096(energy1_1024,count1_nplj,energy1_cz,count1_npljcz_4);
            interp1024_4096(energy2_1024,count2_nplj,energy2_cz,count2_npljcz_4);
            for(int i = 0; i <4096; i ++)
            {
                count1_npljcz[i] = (count1_npljcz_4[i]);
                count2_npljcz[i] = (count2_npljcz_4[i]);
            }
            interp(energy2_cz,count2_npljcz,energy1_cz,count2_npljinterp);
            for(int i = 0 ; i < 4096; i ++)
            {
                if(count2_npljinterp[i] < 0)
                    count2_npljinterp[i] = 0;
            }
            for(int i=0; i<4096; i++)
            {
                count_npljhb[i] =( count1_npljcz[i] + count2_npljinterp[i] );
            }
        }
    }
    //显示剂量率
    if(flags_JLL == 1)
    {
        QString datas = QString::number(jll,'f',2);
        QString show_jll;
        char tmp[100] = {};
        char data_jll[6]={};
        QByteArray dome = datas.toLocal8Bit();
        strcpy(tmp, dome.data());
        if(jll == 0)
            ui->lineEdit_jll->setText("000.00");
        if(tmp[1] == '.')
        {
            for(int i= 0; i<4; i++)
            {
                data_jll[i]=tmp[i];
            }
            show_jll=QString("%1").arg(data_jll);
            ui->lineEdit_jll->setText(show_jll);
            ui->label_6->setText("nSv/h");
        }
        else if (tmp[2] == '.') {
            for(int i= 0; i<5; i++)
            {
                data_jll[i]=tmp[i];
            }
            show_jll=QString("%1").arg(data_jll);
            ui->lineEdit_jll->setText(show_jll);
            ui->label_6->setText("nSv/h");
        }
        else if (tmp[3] == '.') {
            for(int i= 0; i<6; i++)
            {
                data_jll[i]=tmp[i];
            }
            show_jll=QString("%1").arg(data_jll);
            ui->lineEdit_jll->setText(show_jll);
            ui->label_6->setText("nSv/h");
        }
        else if (tmp[4] == '.') {
            data_jll[0] = tmp[0];
            data_jll[1] = tmp[4];
            data_jll[2] = tmp[1];
            data_jll[3] = tmp[2];
            show_jll=QString("%1").arg(data_jll);
            ui->lineEdit_jll->setText(show_jll);
            ui->label_6->setText("uSv/h");
        }
        else if (tmp[5] == '.') {
            data_jll[0] = tmp[0];
            data_jll[1] = tmp[1];
            data_jll[2] = tmp[5];
            data_jll[3] = tmp[2];
            data_jll[4] = tmp[3];
            show_jll=QString("%1").arg(data_jll);
            ui->lineEdit_jll->setText(show_jll);
            ui->label_6->setText("uSv/h");
        }
        else if (tmp[6] == '.') {
            data_jll[0] = tmp[0];
            data_jll[1] = tmp[1];
            data_jll[2] = tmp[2];
            data_jll[3] = tmp[6];
            data_jll[4] = tmp[3];
            data_jll[5] = tmp[4];
            show_jll=QString("%1").arg(data_jll);
            ui->lineEdit_jll->setText(show_jll);
            ui->label_6->setText("uSv/h");
        }
        else if (tmp[7] == '.') {
            data_jll[0] = tmp[0];
            data_jll[1] = tmp[7];
            data_jll[2] = tmp[1];
            data_jll[3] = tmp[2];
            show_jll=QString("%1").arg(data_jll);
            ui->lineEdit_jll->setText(show_jll);
            ui->label_6->setText("mSv/h");
        }
        else if (tmp[8] == '.') {
            data_jll[0] = tmp[0];
            data_jll[1] = tmp[1];
            data_jll[2] = tmp[8];
            data_jll[3] = tmp[3];
            data_jll[4] = tmp[4];
            show_jll=QString("%1").arg(data_jll);
            ui->lineEdit_jll->setText(show_jll);
            ui->label_6->setText("mSv/h");
        }
        else if (tmp[9] == '.') {
            data_jll[0] = tmp[0];
            data_jll[1] = tmp[1];
            data_jll[2] = tmp[2];
            data_jll[3] = tmp[9];
            data_jll[4] = tmp[3];
            data_jll[5] = tmp[4];
            show_jll=QString("%1").arg(data_jll);
            ui->lineEdit_jll->setText(show_jll);
            ui->label_6->setText("mSv/h");
        }
    }
}

//登录失败
void MainWindow::login_fail()
{
    ui->Button_Root->show();
    ui->comboBox_Mcjx_1->setEnabled(false);
    ui->comboBox_Mcjx_2->setEnabled(false);
    ui->comboBox_Zds_1->setEnabled(false);
    ui->comboBox_Zds_2->setEnabled(false);
    ui->lineEdit_Fd_1->setEnabled(false);
    ui->lineEdit_Fd_2->setEnabled(false);
    ui->lineEdit_Gy->setEnabled(false);
    ui->lineEdit_Jllkd->setEnabled(false);
    ui->lineEdit_Nlkd_1->setEnabled(false);
    ui->lineEdit_Nlkd_2->setEnabled(false);
    ui->lineEdit_Pd_Time_1->setEnabled(false);
    ui->lineEdit_Pd_Time_2->setEnabled(false);
    ui->lineEdit_Ss_Time_1->setEnabled(false);
    ui->lineEdit_Ss_Time_2->setEnabled(false);
    ui->lineEdit_Yz_1->setEnabled(false);
    ui->lineEdit_Yz_2->setEnabled(false);
    ui->lineEdit_Hsk->setEnabled(false);
}

//能谱记录选择
void  MainWindow::FileDialog_Npjl()
{
    fileDialog->setWindowTitle(tr("能谱记录"));
    fileDialog->setDirectory("/npjl");
    fileDialog->show();
    if(fileDialog->exec() == QDialog::Accepted) {
        path = fileDialog->selectedFiles()[0];
    }
    ui->lineEdit_npjl->setText(path);
}

//剂量率刻度选择
void MainWindow::FileDialog_Jlkd()
{
    fileDialog->setWindowTitle(tr("jll刻度"));
    fileDialog->setDirectory("/jllkd");
    fileDialog->show();
    if(fileDialog->exec() == QDialog::Accepted) {
        path1 = fileDialog->selectedFiles()[0];
    }
    ui->lineEdit_Jllkd->setText(path1);
}

//能量刻度1选择
void MainWindow::FileDialog_Nlkd_1()
{
    fileDialog->setWindowTitle(tr("能量刻度1"));
    fileDialog->setDirectory("/nlkd");
    fileDialog->show();
    if(fileDialog->exec() == QDialog::Accepted) {
        path2 = fileDialog->selectedFiles()[0];
    }
    ui->lineEdit_Nlkd_1->setText(path2);
}

//能量刻度2选择
void MainWindow::FileDialog_Nlke_2()
{
    fileDialog->setWindowTitle(tr("能量刻度2"));
    fileDialog->setDirectory("/nlkd");
    fileDialog->show();
    if(fileDialog->exec() == QDialog::Accepted) {
        path3 = fileDialog->selectedFiles()[0];
    }
    ui->lineEdit_Nlkd_2->setText(path3);
}

//核素库选择
void MainWindow::FileDialog_Hsk()
{
    fileDialog->setWindowTitle(tr("核素库"));
    fileDialog->setDirectory("/librarySimple");
    fileDialog->show();
    if(fileDialog->exec() == QDialog::Accepted) {
        path4 = fileDialog->selectedFiles()[0];
    }
    ui->lineEdit_Hsk->setText(path4);
}

//开机图片停止
void MainWindow::timeout_xstart(void)
{   
    timer_xstart->stop();
    xstart->close();
    //更新配置参数
    QString str_st;
    QString str_st1;
    char datas[50]={};
    int tmp ;
    QFile file_st(path_setconf);
    file_st.open(QIODevice::ReadOnly);
    file_st.readLine(datas,50);
    tmp = QString(QLatin1String(datas)).toInt();

    if(tmp == 1 ){
        ui->comboBox_Mcjx_1->setCurrentIndex(0);
    }
    else if(tmp == 0) {
        ui->comboBox_Mcjx_1->setCurrentIndex(1);
    }

    file_st.readLine(datas,50);
    tmp = QString(QLatin1String(datas)).toInt();

    if(tmp == 1 ){
        ui->comboBox_Mcjx_2->setCurrentIndex(0);
    }
    else if(tmp == 0) {
        ui->comboBox_Mcjx_2->setCurrentIndex(1);
    }


    file_st.readLine(datas,50);
    tmp = QString(QLatin1String(datas)).toInt();
    if(tmp == 1024){
        ui->comboBox_Zds_1->setCurrentIndex(0);
    }
    else if(tmp == 2048) {
        ui->comboBox_Zds_1->setCurrentIndex(1);
    }

    file_st.readLine(datas,50);
    tmp = QString(QLatin1String(datas)).toInt();
    if(tmp == 1024){
        ui->comboBox_Zds_2->setCurrentIndex(0);
    }
    else if(tmp == 2048) {
        ui->comboBox_Zds_2->setCurrentIndex(1);
    }

    file_st.readLine(datas,50);
    str_st = QString(QLatin1String(datas));
    str_st1 = str_st.section('\n',0,0);
    ui->lineEdit_Fd_1->setText(str_st1);

    file_st.readLine(datas,50);
    str_st = QString(QLatin1String(datas));
    str_st1 = str_st.section('\n',0,0);
    ui->lineEdit_Fd_2->setText(str_st1);

    file_st.readLine(datas,50);
    str_st = QString(QLatin1String(datas));
    str_st1 = str_st.section('\n',0,0);
    ui->lineEdit_Yz_1->setText(str_st1);

    file_st.readLine(datas,50);
    str_st = QString(QLatin1String(datas));
    str_st1 = str_st.section('\n',0,0);
    ui->lineEdit_Yz_2->setText(str_st1);

    file_st.readLine(datas,50);
    str_st = QString(QLatin1String(datas));
    str_st1 = str_st.section('\n',0,0);
    ui->lineEdit_Ss_Time_1->setText(str_st1);

    file_st.readLine(datas,50);
    str_st = QString(QLatin1String(datas));
    str_st1 = str_st.section('\n',0,0);
    ui->lineEdit_Ss_Time_2->setText(str_st1);

    file_st.readLine(datas,50);
    str_st = QString(QLatin1String(datas));
    str_st1 = str_st.section('\n',0,0);
    ui->lineEdit_Pd_Time_1->setText(str_st1);

    file_st.readLine(datas,50);
    str_st = QString(QLatin1String(datas));
    str_st1 = str_st.section('\n',0,0);
    ui->lineEdit_Pd_Time_2->setText(str_st1);

    file_st.readLine(datas,50);
    str_st = QString(QLatin1String(datas));
    str_st1 = str_st.section('\n',0,0);
    ui->lineEdit_Nlkd_1->setText(str_st1);

    file_st.readLine(datas,50);
    str_st = QString(QLatin1String(datas));
    str_st1 = str_st.section('\n',0,0);
    ui->lineEdit_Nlkd_2->setText(str_st1);

    file_st.readLine(datas,50);
    str_st = QString(QLatin1String(datas));
    str_st1 = str_st.section('\n',0,0);
    ui->lineEdit_Gy->setText(str_st1);

    file_st.readLine(datas,50);
    str_st = QString(QLatin1String(datas));
    str_st1 = str_st.section('\n',0,0);
    ui->lineEdit_Jllkd->setText(str_st1);

    file_st.readLine(datas,50);
    str_st = QString(QLatin1String(datas));
    str_st1 = str_st.section('\n',0,0);
    ui->lineEdit_Hsk->setText(str_st1);
    file_st.close();
}

// 键盘显示
void MainWindow::KeyBoardShow(void *pthis)
{
    if( pthis == ui->Set_time)
        xkeypad->show( (myLineEdit *)pthis, "设置开始测量时间");
    else if( pthis == ui->lineEdit_Jll_Star_Time)
        xkeypad->show( (myLineEdit *)pthis, "剂量率记录开始日期");
    else if( pthis == ui->lineEdit_Jll_End_Time)
        xkeypad->show( (myLineEdit *)pthis, "剂量率记录结束日期");
    else if( pthis == ui->lineEdit_npjl)
        xkeypad->show( (myLineEdit *)pthis, "能谱记录");
    else if( pthis == ui->lineEdit_Rz__Star_Time)
        xkeypad->show( (myLineEdit *)pthis, "设备日志开始时间");
    else if( pthis == ui->lineEdit_Rz_End_Time)
        xkeypad->show( (myLineEdit *)pthis, "设备日志结束时间");
    else if( pthis == ui->lineEdit_Fd_1)
        xkeypad->show( (myLineEdit *)pthis, "放大1");
    else if( pthis == ui->lineEdit_Fd_2)
        xkeypad->show( (myLineEdit *)pthis, "放大2");
    else if( pthis == ui->lineEdit_Yz_1)
        xkeypad->show( (myLineEdit *)pthis, "阈值1");
    else if( pthis == ui->lineEdit_Yz_2)
        xkeypad->show( (myLineEdit *)pthis, "阈值2");
    else if( pthis == ui->lineEdit_Ss_Time_1)
        xkeypad->show( (myLineEdit *)pthis, "上升时间1");
    else if( pthis == ui->lineEdit_Ss_Time_2)
        xkeypad->show( (myLineEdit *)pthis, "上升时间2");
    else if( pthis == ui->lineEdit_Pd_Time_1)
        xkeypad->show( (myLineEdit *)pthis, "平顶时间1");
    else if( pthis == ui->lineEdit_Pd_Time_2)
        xkeypad->show( (myLineEdit *)pthis, "平顶时间2");
    else if( pthis == ui->lineEdit_Gy)
        xkeypad->show( (myLineEdit *)pthis, "高压");
    else if( pthis == ui->lineEdit_Low_Warn)
        xkeypad->show( (myLineEdit *)pthis, "低报警阈值");
    else if( pthis == ui->lineEdit_Hight_Warn_)
        xkeypad->show( (myLineEdit *)pthis, "高报警阈值");
    else if( pthis == ui->lineEdit_jll_phsj)
        xkeypad->show( (myLineEdit *)pthis, "剂量率平滑时间");
    else
        xkeypad->show( (myLineEdit *)pthis, "登录");
}

//获取权限按钮
void MainWindow::on_Button_Root_clicked()
{
    system("echo 0 > /sys/class/leds/user-led0/brightness");
    sendcommd->start();
    xlogin->show();
    xlogin->setFocus();
    ui->Button_Root->hide();
    ui->comboBox_Mcjx_1->setEnabled(true);
    ui->comboBox_Mcjx_2->setEnabled(true);
    ui->comboBox_Zds_1->setEnabled(true);
    ui->comboBox_Zds_2->setEnabled(true);
    ui->lineEdit_Fd_1->setEnabled(true);
    ui->lineEdit_Fd_2->setEnabled(true);
    ui->lineEdit_Gy->setEnabled(true);
    ui->lineEdit_Jllkd->setEnabled(true);
    ui->lineEdit_Nlkd_1->setEnabled(true);
    ui->lineEdit_Nlkd_2->setEnabled(true);
    ui->lineEdit_Pd_Time_1->setEnabled(true);
    ui->lineEdit_Pd_Time_2->setEnabled(true);
    ui->lineEdit_Ss_Time_1->setEnabled(true);
    ui->lineEdit_Ss_Time_2->setEnabled(true);
    ui->lineEdit_Yz_1->setEnabled(true);
    ui->lineEdit_Yz_2->setEnabled(true);
    ui->lineEdit_Hsk->setEnabled(true);
}

void MainWindow::on_tabWidget_tabBarClicked(int index)
{
    system("echo 0 > /sys/class/leds/user-led0/brightness");
    sendcommd->start();
    if(index == 0)
    {
        ui->lineEdit_jll->setText("000.00");
        flags_JLL = 1;
    }
    else if(index == 1)
    {
        flags_JLL = 0;
    }
    else if(index == 2)
    {
        flags_JLL = 0;
    }
    else if(index == 3)
    {
        flags_JLL = 0;
    }
    ui->Button_Root->show();
    ui->comboBox_Mcjx_1->setEnabled(false);
    ui->comboBox_Mcjx_2->setEnabled(false);
    ui->comboBox_Zds_1->setEnabled(false);
    ui->comboBox_Zds_2->setEnabled(false);
    ui->lineEdit_Fd_1->setEnabled(false);
    ui->lineEdit_Fd_2->setEnabled(false);
    ui->lineEdit_Gy->setEnabled(false);
    ui->lineEdit_Jllkd->setEnabled(false);
    ui->lineEdit_Nlkd_1->setEnabled(false);
    ui->lineEdit_Nlkd_2->setEnabled(false);
    ui->lineEdit_Pd_Time_1->setEnabled(false);
    ui->lineEdit_Pd_Time_2->setEnabled(false);
    ui->lineEdit_Ss_Time_1->setEnabled(false);
    ui->lineEdit_Ss_Time_2->setEnabled(false);
    ui->lineEdit_Yz_1->setEnabled(false);
    ui->lineEdit_Yz_2->setEnabled(false);
    ui->lineEdit_Hsk->setEnabled(false);
    //判断低阈值和高阈值是否被设置
    if((flags_db == 1)&& (flags_set2 == 0) )
    {
        ui->lineEdit_Low_Warn->setText(db);
        flags_db = 0;
    }
    else if((flags_gb == 1)&&(flags_set2 == 0))
    {
        ui->lineEdit_Hight_Warn_->setText(gb);
        flags_gb = 0;
    }
    flags_set2 = 0;
}

void MainWindow::on_tabWidget_2_tabBarClicked()
{
    system("echo 0 > /sys/class/leds/user-led0/brightness");
    sendcommd->start();
}

//探头按钮
void MainWindow::on_Button_Tt_clicked()
{
    system("echo 0 > /sys/class/leds/user-led0/brightness");
    sendcommd->start();
    ui->Sys_Warn->clear();
    ui->Sound->setPixmap(pix_sound);
    ui->Button_Tt->setStyleSheet(tr("background-image: url(/home/lts/qtwork/CztHost/img/btn_normal.png);"));
    SQL_Add_data_Rz(10);
    system("echo 1 > /sys/class/leds/user-led0/brightness");
    system("echo 1 > /sys/class/leds/user-led1/brightness");
    system("echo 1 > /sys/class/leds/user-led2/brightness");
}

//低阈值报警按钮
void MainWindow::on_Button_Db_clicked()
{
    system("echo 0 > /sys/class/leds/user-led0/brightness");
    sendcommd->start();
    ui->Sys_Warn->clear();
    ui->Sound->setPixmap(pix_sound);
    ui->Button_Db->setStyleSheet(tr("background-image: url(/home/lts/qtwork/CztHost/img/btn_normal.png);"));
    SQL_Add_data_Rz(4);
    system("echo 1 > /sys/class/leds/user-led0/brightness");
    system("echo 1 > /sys/class/leds/user-led1/brightness");
    system("echo 1 > /sys/class/leds/user-led2/brightness");
}

//高阈值报警按钮
void MainWindow::on_Button_Gb_clicked()
{
    system("echo 0 > /sys/class/leds/user-led0/brightness");
    sendcommd->start();
    ui->Sys_Warn->clear();
    ui->Sound->setPixmap(pix_sound);
    ui->Button_Gb->setStyleSheet(tr("background-image: url(/home/lts/qtwork/CztHost/img/btn_normal.png);"));
    SQL_Add_data_Rz(6);
    system("echo 1 > /sys/class/leds/user-led0/brightness");
    system("echo 1 > /sys/class/leds/user-led1/brightness");
    system("echo 1 > /sys/class/leds/user-led2/brightness");
}

//开始测试按钮
void MainWindow::on_Button_Cs_clicked()
{
    if(flags_cs1 == 1)
    {
        system("echo 0 > /sys/class/leds/user-led0/brightness");
        sendcommd->start();
        ch1_live = 0.0;
        ch1_real = 0.0;
        ch2_live = 0.0;
        ch2_real = 0.0;
        ui->Button_Cs->setText("停止");
        ui->textEdit_hssb->clear();
        for(int i = 0; i <4096; i++)
        {
            count1_nplj[i] =0;
            count2_nplj[i] =0;
            count1_npljcz[i] =0;
            count2_npljcz[i] =0;
            count2_npljinterp[i] =0;
            count_npljhb[i] =0;
        }
        flags_cs1 = 0;
        flags_hssb = 1;
        flags_cs =1;
        test_time =ui->Set_time->text().toDouble();
        bruse_ui->start();
        timer_cs->start();
        //进度条
        ui->progressBar->setRange(0,(int)test_time);
        ui->progressBar->setValue(0);
    }
    else if(flags_cs1 == 0){
        system("echo 0 > /sys/class/leds/user-led0/brightness");
        sendcommd->start();
        flags_cs1 = 1;
        flags_hssb = 0;
        flags_cs = 0;
        cnt_bar =2;
        timer_cs->stop();
        bruse_ui->stop();
        ui->Button_Cs->setText("设置开始");
        ui->progressBar->setValue(0);
    }
}

//刷新核素时间计数
void MainWindow::hssb_cal()
{
    ui->progressBar->setValue((int)(ch1_live));
    if ((ch1_live > test_time))
    {
        emit test_cal();
        ui->progressBar->setValue((int)test_time);
    }
}

//测试结束核素识别计算
void MainWindow::Test_cal()
{
    system("echo 0 > /sys/class/leds/user-led0/brightness");
    sendcommd->start();
    ui->Button_Cs->setText("设置开始");
    flags_hssb = 0;
    flags_cs = 0;
    cnt_bar =2;
    flags_cs1 = 1;
    timer_cs->stop();
    bruse_ui->stop();
    QString str_npjl;
    QString str_count1;
    QString str_count2;
    QString str_count2_interp;
    QString str_couint_hb;
    QString str_hssb;
    QString energy_1;
    QString energy_2;
    QString ch_1;
    QString ch_2;
    char * ch;
    QByteArray ba;
//保存能谱记录
    Current_data_time = QDateTime::currentDateTime();
    QString date_time =Current_data_time.toString("yyyy-MM-dd-hh-mm-ss");
    QString filename = file_np_path+date_time;
    filename.append(".txt");
    QString file_hssb =(filename + "-hsjl.txt" );
    //  QString file_count =(filename + "-json" );
    // QFile filejson(file_count);
    //  filejson.open(QIODevice::WriteOnly);
    QFile filenp(filename);
    filenp.open(QIODevice::WriteOnly);
    QFile filehssb(file_hssb);
    filehssb.open(QIODevice::WriteOnly);
    for(int i = 0; i < 4096; i ++)
    {
        str_count1 = QString("%1").arg(count1_npljcz[i]);
        str_count2 = QString("%1").arg(count2_npljcz[i]);
        str_count2_interp = QString("%1").arg(count2_npljinterp[i]);
        energy_1 = QString("%1").arg(energy1_cz[i]);
        energy_2 = QString("%1").arg(energy2_cz[i]);
        str_couint_hb = QString("%1").arg(count_npljhb[i]);
        // str_npjl = ( "count1: "+  str_count1 +"         count2: " +str_count2 + "         energy_1: "+energy_1+ "          energy_2: "+energy_2 +   ("        count2_interp:"+str_count2_interp)+ "         count: " +str_couint_hb );
        str_npjl = (  energy_1 + " " +str_couint_hb );
        str_npjl.append('\n');
        ba = str_npjl.toLatin1();
        ch=ba.data();
        filenp.write(ch);
    }
    ch_1 = QString("%1").arg(ch1_live);
    ch_2 = QString("%1").arg(ch1_real);
    QString  str_ch = ( ch_2 +" " + ch_1 );
    str_ch.append('\n');
    ba = str_ch.toLatin1();
    ch=ba.data();
    filenp.write(ch);
    ch_1 = QString("%1").arg(ch2_live);
    ch_2 = QString("%1").arg(ch2_real);
    QString  str_ch1 = ( ch_2 +" " +ch_1  );
    str_ch1.append('\n');
    ba = str_ch1.toLatin1();
    ch=ba.data();
    filenp.write(ch);
    filenp.close();
    //核素识别计算
    peakfindczt(count_npljhb,peakm);
    for (int i= 0; i <100; i ++)
    {
        for(int j= 0; j < hsk_data_s; j++)
        {
            if((peakm[i]< (Energy_MeV[j] + (Energy_MeV[j] * 0.02))) && (peakm[i] > (Energy_MeV[j] - (Energy_MeV[j] * 0.02))))
            {
                ui->textEdit_hssb->append("     "+Nuclide[j] + "         " + Energy_MeV_str[j] + "         " + Probability[j]);
                str_hssb = (Nuclide[j]+" " + Energy_MeV_str[j]+ " "+ Probability[j]+" " + '\n' );
                ba = str_hssb.toLatin1();
                ch=ba.data();
                filehssb.write(ch);
            }
        }
    }
    filehssb.close();
    /*
    for(int i = 0; i <1024; i ++)
    {
        ch_1 = QString("%1").arg(count1_nplj[i]);
        ch_2 = QString("%1").arg(count2_nplj[i]);
      QString  str_ch = ( "count1_json:  "+  ch_1 +"         count2_json:  " +ch_2  );
        str_ch.append('\n');
        ba = str_ch.toLatin1();
        ch=ba.data();
        filejson.write(ch);
    }
    filejson.close();
*/
}

//设置通道参数按钮
void MainWindow::on_Button_Set1_clicked()
{
    if(flags_sendcomd == 1)
    {
        system("echo 0 > /sys/class/leds/user-led0/brightness");
        sendcommd->start();
        set_wait_ui->show();
        connect_tt->stop();
        SQL_Add_data_Rz(8);
        QString str_std1;
        QString str_std2;
        QString str_std3;
        QString str_std4;
        QString str_std5;
        QString mcjx1;
        QString mcjx2;
        char data1[100]={};
        char data2[100]={};
        char data3[100]={};
        str_std4=ui->comboBox_Mcjx_1->currentText();
        str_std5=ui->comboBox_Mcjx_2->currentText();
        ch1_zds=ui->comboBox_Zds_1->currentText().toInt();
        ch2_zds=ui->comboBox_Zds_2->currentText().toInt();
        ch1_fd=ui->lineEdit_Fd_1->text().toDouble();
        ch2_fd=ui->lineEdit_Fd_2->text().toDouble();
        ch1_yz=ui->lineEdit_Yz_1->text().toDouble();
        ch2_yz=ui->lineEdit_Yz_2->text().toDouble();
        ch1_sh_time=ui->lineEdit_Ss_Time_1->text().toDouble();
        ch2_sh_time=ui->lineEdit_Ss_Time_2->text().toDouble();
        ch1_sp_time=ui->lineEdit_Pd_Time_1->text().toDouble();
        ch2_sp_time=ui->lineEdit_Pd_Time_2->text().toDouble();
        nlkd1=ui->lineEdit_Nlkd_1->text();
        nlkd2=ui->lineEdit_Nlkd_2->text();
        gy=ui->lineEdit_Gy->text().toDouble();
        jllke=ui->lineEdit_Jllkd->text();
        hsk=ui->lineEdit_Hsk->text();
        if(str_std4 == "正")
        {
            ch1_mcjx = 1;
            mcjx1 = "1";
        }else if(str_std4 == "负") {
            ch1_mcjx = 0;
            mcjx1 = "0";
        }
        if(str_std5 == "正")
        {
            ch2_mcjx = 1;
            mcjx2 = "1";
        }else if(str_std5 == "负") {
            ch2_mcjx = 0;
            mcjx2 = "0";
        }
//保存配置
        char * ch;
        QByteArray ba;
        QString str_set;

        QFile file_set(path_setconf);
        file_set.open(QIODevice::Truncate|QIODevice::WriteOnly);
        str_set = mcjx1;
        str_set.append('\n');
        ba = str_set.toLatin1();
        ch=ba.data();
        file_set.write(ch);

        str_set = mcjx2;
        str_set.append('\n');
        ba = str_set.toLatin1();
        ch=ba.data();
        file_set.write(ch);

        str_set = ui->comboBox_Zds_1->currentText();
        str_set.append('\n');
        ba = str_set.toLatin1();
        ch=ba.data();
        file_set.write(ch);

        str_set = ui->comboBox_Zds_2->currentText();
        str_set.append('\n');
        ba = str_set.toLatin1();
        ch=ba.data();
        file_set.write(ch);

        str_set = ui->lineEdit_Fd_1->text();
        str_set.append('\n');
        ba = str_set.toLatin1();
        ch=ba.data();
        file_set.write(ch);

        str_set = ui->lineEdit_Fd_2->text();
        str_set.append('\n');
        ba = str_set.toLatin1();
        ch=ba.data();
        file_set.write(ch);

        str_set = ui->lineEdit_Yz_1->text();
        str_set.append('\n');
        ba = str_set.toLatin1();
        ch=ba.data();
        file_set.write(ch);

        str_set = ui->lineEdit_Yz_2->text();
        str_set.append('\n');
        ba = str_set.toLatin1();
        ch=ba.data();
        file_set.write(ch);

        str_set = ui->lineEdit_Ss_Time_1->text();
        str_set.append('\n');
        ba = str_set.toLatin1();
        ch=ba.data();
        file_set.write(ch);

        str_set = ui->lineEdit_Ss_Time_2->text();
        str_set.append('\n');
        ba = str_set.toLatin1();
        ch=ba.data();
        file_set.write(ch);

        str_set = ui->lineEdit_Pd_Time_1->text();
        str_set.append('\n');
        ba = str_set.toLatin1();
        ch=ba.data();
        file_set.write(ch);

        str_set = ui->lineEdit_Pd_Time_2->text();
        str_set.append('\n');
        ba = str_set.toLatin1();
        ch=ba.data();
        file_set.write(ch);

        str_set =ui->lineEdit_Nlkd_1->text();
        str_set.append('\n');
        ba = str_set.toLatin1();
        ch=ba.data();
        file_set.write(ch);

        str_set = ui->lineEdit_Nlkd_2->text();
        str_set.append('\n');
        ba = str_set.toLatin1();
        ch=ba.data();
        file_set.write(ch);

        str_set = ui->lineEdit_Gy->text();
        str_set.append('\n');
        ba = str_set.toLatin1();
        ch=ba.data();
        file_set.write(ch);

        str_set = ui->lineEdit_Jllkd->text();
        str_set.append('\n');
        ba = str_set.toLatin1();
        ch=ba.data();
        file_set.write(ch);

        str_set = ui->lineEdit_Hsk->text();
        str_set.append('\n');
        ba = str_set.toLatin1();
        ch=ba.data();
        file_set.write(ch);
        file_set.close();
        QFile file1(nlkd1);
        if(!file1.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QMessageBox::information( this, "提示", "未找到通道1能量刻度，请选择正确的能量刻度。", QObject::tr("确定"));
            return;
        }
        file1.readLine(data1,100);
        file1.readLine(data2,100);
        file1.readLine(data3,100);
        ch1_coe_E1=QString(QLatin1String(data1)).toFloat();
        ch1_coe_E2=QString(QLatin1String(data2)).toFloat();
        ch1_coe_E3=QString(QLatin1String(data3)).toFloat();
        file1.close();
        QFile file2(nlkd2);
        if(!file2.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QMessageBox::information( this, "提示", "未找到通道2能量刻度，请选择正确的能量刻度。", QObject::tr("确定"));
            return;
        }
        file2.readLine(data1,100);
        file2.readLine(data2,100);
        file2.readLine(data3,100);
        ch2_coe_E1=QString(QLatin1String(data1)).toFloat();
        ch2_coe_E2=QString(QLatin1String(data2)).toFloat();
        ch2_coe_E3=QString(QLatin1String(data3)).toFloat();
        file2.close();
        QFile file3(jllke);
        if(!file3.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QMessageBox::information( this, "提示", "未找到剂量率刻度，请选择正确的剂量率刻度。", QObject::tr("确定"));
            return;
        }
        for(int i=0;i<3000;i++)
        {
            file3.readLine(data1,100);
            str_std1 = QString("%1").arg(data1);
            str_std2 = str_std1.section(' ',0,0);
            str_std3 = str_std1.section(' ',1,1);
            eng_std[i] = str_std2.toFloat();
            ge_std[i]= str_std3.toFloat();
        }
        file3.close();
        QFile file4(hsk);
        if(!file4.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QMessageBox::information( this, "提示", "未找到剂量率刻度，请选择正确的剂量率刻度。", QObject::tr("确定"));
            return;
        }
        file4.readLine(data1,100); //先读一行，过滤掉库文件的第一行。
        int i = 0;
        hsk_data_s =0;
        QTextStream in(&file4);
        in.setCodec("GBK");
        while (!in.atEnd())
        {
            file4.readLine(data1,100);
            str_hsk_line = QString("%1").arg(data1);
            str_hsk1 = str_hsk_line.section(' ',0,0);
            str_hsk2 = str_hsk_line.section(' ',1,1);
            str_hsk3 = str_hsk_line.section(' ',2,2);
            Probability[i] = str_hsk1;
            Energy_MeV_str[i] = str_hsk2;
            Energy_MeV[i] = str_hsk2.toFloat();
            Nuclide[i] = str_hsk3;
            //qDebug()<< Nuclide[i]+"     "+Energy_MeV_str[i]+"      "+Probability[i]<<endl;
            i++;
        }
        hsk_data_s = i;
        file4.close();
//通道1
        Mca_Param1.channel_no = 0;
        Mca_Param1.input_pulse_polarity = ch1_mcjx;
        Mca_Param1.nal = nal1;
        Mca_Param1.channel_num = ch1_zds;
        Mca_Param1.gain = ch1_fd;
        Mca_Param1.threshold_value = ch1_yz;
        Mca_Param1.filtering_molding_rising_time_value = ch1_sh_time;
        Mca_Param1.filtering_molding_flat_topping_time = ch1_sp_time;
        Mca_Param1.screening_time_rising_time_value = ch1_sp_time;
        Mca_Param1.baseline_restorer = baseline_restorer1;
        Mca_Param1.decay_time_constant =decay_time_constant1;
        Mca_Param1.voltage_value = gy;
        Mca_Param1.rising_speed = rising_speed1;
//通道2
        Mca_Param2.channel_no = 1;
        Mca_Param2.input_pulse_polarity = ch2_mcjx;
        Mca_Param2.nal = nal2;
        Mca_Param2.channel_num = ch2_zds;
        Mca_Param2.gain = ch2_fd;
        Mca_Param2.threshold_value = ch2_yz;
        Mca_Param2.filtering_molding_rising_time_value = ch2_sh_time;
        Mca_Param2.filtering_molding_flat_topping_time = ch2_sp_time;
        Mca_Param2.screening_time_rising_time_value = ch2_sp_time;
        Mca_Param2.baseline_restorer = baseline_restorer2;
        Mca_Param2.decay_time_constant =decay_time_constant2;
        Mca_Param2.voltage_value = gy;
        Mca_Param2.rising_speed = rising_speed2;
//准备命令
        unsigned int len = 84;
        char buffer1[300] = {};
        char buffer2[300] = {};
        u_char version = NET_MSG_HEADER_VER;
        u_char type = NET_MSG_CONFIG_PACKET;
        u_char module = NET_MSG_CLIENT_MODULE;
        u_char flag =  NET_MSG_FLAG;
        memcpy(buffer1 , (char *)&version, 1);
        memcpy(buffer1 +1 , (char *)&type, 1);
        memcpy(buffer1 +2 , (char *)&module, 1);
        memcpy(buffer1 +3, (char *)&flag, 1);
        memcpy(buffer1 +4 , (char *)&len +3, 1);
        memcpy(buffer1 +5 , (char *)&len +2, 1);
        memcpy(buffer1 +6 , (char *)&len +1, 1);
        memcpy(buffer1 +7, (char *)&len, 1);
        memcpy(buffer1 +8,(char *)&Mca_Param1,sizeof(mca_param));

        memcpy(buffer2 , (char *)&version, 1);
        memcpy(buffer2 +1 , (char *)&type, 1);
        memcpy(buffer2 +2 , (char *)&module, 1);
        memcpy(buffer2 +3, (char *)&flag, 1);
        memcpy(buffer2 +4 , (char *)&len +3, 1);
        memcpy(buffer2 +5 , (char *)&len +2, 1);
        memcpy(buffer2 +6 , (char *)&len +1, 1);
        memcpy(buffer2 +7, (char *)&len, 1);
        memcpy(buffer2 +8,(char *)&Mca_Param2,sizeof(mca_param));
        QString strmm3 = "stop channel0";
        webscoket1->sendTextMessage(strmm3);
        sleep(1000);
        QString strmm4 = "stop channel1";
        webscoket2->sendTextMessage(strmm4);
        sleep(1000);
        socket = new QTcpSocket();
        socket->connectToHost(QHostAddress( IP ),PORT);
        sleep(2000);
        socket->write(buffer1,88);
        socket->flush();
        sleep(2000);
        socket->close();
        socket->deleteLater();
        sleep(4000);
        socket = new QTcpSocket();
        socket->connectToHost(QHostAddress( IP ),PORT);
        sleep(2000);
        socket->write(buffer2, 88);
        socket->flush();
        sleep(2000);
        socket->close();
        socket->deleteLater();
        QString strmm1 = "start channel0";
        webscoket1->sendTextMessage(strmm1);
        QString strmm2 = "start channel1";
        webscoket2->sendTextMessage(strmm2);
        set_wait_ui->hide();
    }
}

//设置报警按钮
void MainWindow::on_Button_Set2_clicked()
{
    system("echo 0 > /sys/class/leds/user-led0/brightness");
    sendcommd->start();
    flags_set2 = 1;
    db = ui->lineEdit_Low_Warn->text();
    gb = ui->lineEdit_Hight_Warn_->text();
    ui->low_warn->setText(db);
    ui->hight_warn->setText(gb);
    time_ph = ui->lineEdit_jll_phsj->text().toInt();
    SQL_Add_data_Rz(9);
}

//LineEdit_Gb值发生改变
void MainWindow::LineEdit_Gb_Change()
{
    flags_gb = 1;
}

//LineEdit_Gb值发生改变
void MainWindow::LineEdit_Db_Change()
{
    flags_db = 1;
}

//创建数据库
void MainWindow::createDateBaseFile()
{
    datebase.setDatabaseName( "./Main.db");
    datebase.open();                // 打开数据库
    QSqlQuery query(datebase);      // 建立一个数据库表
    datebase.transaction();
    if( !datebase.record("main").isEmpty()) return;
    query.exec("create table jll ( date0 varchar(20), Hour int, Minute int, Second int, "                // 运行数据保存数据库表
               "JLL float )");
    query.exec("create table rz ( date0 varchar(20), Hour int, Minute int, Second int, "                // 运行数据保存数据库表
               "flag int )");
    datebase.commit();
}

// 增加一条剂量率数据记录
void MainWindow::SQL_Add_data( float JLL )
{
    QSqlQuery query(datebase);      // 建立一个数据库操作
    QString str1 = this->Current_data_time.toString("yyyy-MM-dd");
    datebase.transaction();         // 启动事务操作
    query.exec( QString("insert into jll values( '%1', %2, %3, %4, %5)") .arg(str1)
                .arg(Current_data_time.time().hour()).arg(Current_data_time.time().minute()).arg(Current_data_time.time().second())
                .arg(JLL));   // 插入一行数据
    datebase.commit();          // 提交
}

// 增加一条设备日志数据记录
void MainWindow::SQL_Add_data_Rz(int flag)
{
    QSqlQuery query(datebase);      // 建立一个数据库操作
    QString str2 = this->Current_data_time.toString("yyyy-MM-dd");
    datebase.transaction();         // 启动事务操作
    query.exec( QString("insert into rz values( '%1', %2, %3, %4, %5)") .arg(str2)
                .arg(Current_data_time.time().hour()).arg(Current_data_time.time().minute()).arg(Current_data_time.time().second())
                .arg(flag));   // 插入一行数据
    datebase.commit();          // 提交
}

//能谱查询
void MainWindow::on_Button_npjl_clicked()
{
    system("echo 0 > /sys/class/leds/user-led0/brightness");
    sendcommd->start();
    QString npji_path = ui->lineEdit_npjl->text();
    QString  path23= npji_path;
    QFile file_np(path23);
    QString hssb_path = npji_path.append("-hsjl.txt");
    QFile file_hs(hssb_path);
    QString str_npjl;
    QString str_npjl1;
    QString str_npjl2;
    QString str_hsjl;
    QString str_hsjl1;
    QString str_hsjl2;
    QString str_hsjl3;
    char data_npjl[100]={};
    char data_hsjl[100]={};
    if(!file_np.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::information( this, "提示", "能谱记录打开失败", QObject::tr("确定"));
        return;
    }
    for(int i =0; i<4096; i ++)
    {
        file_np.readLine(data_npjl,100);
        str_npjl = QString("%1").arg(data_npjl);
        str_npjl1 = str_npjl.section(' ',0,0);
        str_npjl2 = str_npjl.section(' ',1,1);
        count_jl[i] = str_npjl2.toDouble();
        energy_jl[i] = str_npjl1.toDouble();
    }
    file_np.close();
    if(!file_hs.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::information( this, "提示", "核素记录打开失败", QObject::tr("确定"));
        return;
    }
    QString show_hsji = "核素名  能量（Kev) 分支比";
    QString show_hsji1;
    show_hsji.append('\n');
    ui->textEdit_hsjl->setText( show_hsji);
    QTextStream in(&file_hs);
    in.setCodec("GBK");
    while (!in.atEnd())
    {
        file_hs.readLine(data_hsjl,100);
        str_hsjl = QString("%1").arg(data_hsjl);
        str_hsjl1 = str_hsjl.section(' ',0,0);
        str_hsjl2 = str_hsjl.section(' ',1,1);
        str_hsjl3 = str_hsjl.section(' ',2,2);
        show_hsji1 = ( str_hsjl1 +"  " + str_hsjl2+ "  " + str_hsjl3);
        show_hsji1.append('\n');
        ui->textEdit_hsjl->append( show_hsji1);
    }
    file_hs.close();
//显示能谱记录曲线
    int cnt = 0;
    float tmp = 0;
    int n = 0;
    for(int i = 0; i < 4096; i++)
    {
        tmp += count_jl[i];
        cnt += 1;
        if(cnt == 16)
        {
            count_chart2[n] = tmp;
            n ++;
            cnt = 0;
            tmp = 0;
        }
    }
    //        if(ch1_zds == 1024)
    //        {
    int s = 0;
    for(int i = 1; i <256; i ++)
    {
        energy_chart2[i] = s ;
        s+=4;
    }
    energy_chart2[255] = 1023 ;
    //        }
    /*
        if(ch1_zds == 2048)
        {
            int s1 = 0;
            for(int i = 0; i <256; i ++)
            {
                energy_chart2[i] = s1 ;
                s1+=8;
            }
            energy_chart2[255] = 2047 ;
        }
*/
    double energy_max = energy_chart2[255];
    double count_max = count_chart2[0];
    for(int i = 1; i <256; i ++)
    {
        count_max = (count_max > count_chart2[i]) ? count_max : count_chart2[i];
    }
    ui->charts_widget2->xAxis->setRange(0, 5);
    ui->charts_widget2->yAxis->setRange(0, 5);
    curGraph1->clearData();
    ui->charts_widget2->replot();
    QVector<double> x(256), y(256);
    for (int i=0; i<256; i++)
    {
        x[i] = energy_chart2[i];
        y[i] = count_chart2[i];
    }
    curGraph1->setData(x, y);
    ui->charts_widget2->xAxis->setRange(0, energy_max);// 设置坐标轴的范围，以看到所有数据
    ui->charts_widget2->yAxis->setRange(0, count_max);
    ui->charts_widget2->replot();
    x.clear();
    y.clear();
}

//剂量率记录查询
void MainWindow::on_Button_Jll_clicked()
{
    system("echo 0 > /sys/class/leds/user-led0/brightness");
    sendcommd->start();
    QSqlTableModel *model;
    QSqlRecord tmpRecord;
    QString str, str_t0;
// 参数保存数据库表
    model = new QSqlTableModel( this, datebase);    // 很关键
    model->setTable("jll");
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    QDateTime dt0 = QDateTime::fromString(ui->lineEdit_Jll_Star_Time->text(), "yyyy.MM.dd.hh.mm.ss");
    if( dt0.isValid() == false)
    {
        QMessageBox::information( this, "提示", "起始日期设置无效，正确输入格式：yyyy.MM.dd.hh.mm.ss 。", QObject::tr("确定"));
        return;
    }
    QDateTime dt2 = QDateTime::fromString(ui->lineEdit_Jll_End_Time->text(), "yyyy.MM.dd.hh.mm.ss");
    if( dt2.isValid() == false)
    {
        QMessageBox::information( this, "提示", "截至日期设置无效，正确输入格式：yyyy.MM.dd.hh.mm.ss 。", QObject::tr("确定"));
        return;
    }
    if( dt0 > dt2)
    {
        dt0 = QDateTime::fromString(ui->lineEdit_Jll_End_Time->text(), "yyyy.MM.dd.hh.mm.ss");
        dt2 = QDateTime::fromString(ui->lineEdit_Jll_Star_Time->text(), "yyyy.MM.dd.hh.mm.ss");
        ui->lineEdit_Jll_Star_Time->setText( dt0.toString("yyyy.MM.dd.hh.mm.ss"));
        ui->lineEdit_Jll_End_Time->setText( dt2.toString("yyyy.MM.dd.hh.mm.ss"));
    }
    model->setFilter( QString("date0 >='%1' and date0 <='%2' and Hour >= %3 and Hour <= %4 "
                              "and Minute >= %5 and Minute <= %6 and Second >= %7 and Second <= %8")
                      .arg(dt0.toString("yyyy-MM-dd")).arg(dt2.toString("yyyy-MM-dd"))
                      .arg(dt0.time().hour() ).arg(dt2.time().hour() )
                      .arg(dt0.time().minute() ).arg(dt2.time().minute() )
                      .arg(dt0.time().second() ).arg(dt2.time().second() ) );
    model->select();
    while(model->canFetchMore()) model->fetchMore();
    int countToSave = model->rowCount();
    if(countToSave == 0)
    {
        QMessageBox::information( this, "提示", "该时间节点没有数据", QObject::tr("确定"));
        return;
    }
    while(model->canFetchMore()) model->fetchMore();
    int RowCount = model->rowCount();
    for( int i= 0; i< RowCount; i++)
    {
        tmpRecord =	model->record( i);
        str_t0 = tmpRecord.value(0).toString() + " " + tmpRecord.value(1).toString() + ":" + tmpRecord.value(2).toString() + ":" + tmpRecord.value(3).toString();
        str = tmpRecord.value(4).toString();                                   // 剂量率
        ui->textEdit_Jll->append("  时间：  " + str_t0 + "       剂量率：  "+str);
    }
}

//日志查询
void MainWindow::on_Button_Rz_clicked()
{
    system("echo 0 > /sys/class/leds/user-led0/brightness");
    sendcommd->start();
    QSqlTableModel *model1;
    QSqlRecord tmpRecord1;
    QString str3, str_t10;
    int Flag;
// 参数保存数据库表
    model1 = new QSqlTableModel( this, datebase);    // 很关键
    model1->setTable("rz");
    model1->setEditStrategy(QSqlTableModel::OnFieldChange);
    QDateTime dt10 = QDateTime::fromString(ui->lineEdit_Rz__Star_Time->text(), "yyyy.MM.dd.hh.mm.ss");
    if( dt10.isValid() == false)
    {
        QMessageBox::information( this, "提示", "起始日期设置无效，正确输入格式：yyyy.MM.dd.hh.mm.ss 。", QObject::tr("确定"));
        return;
    }
    QDateTime dt12 = QDateTime::fromString(ui->lineEdit_Rz_End_Time->text(), "yyyy.MM.dd.hh.mm.ss");
    if( dt12.isValid() == false)
    {
        QMessageBox::information( this, "提示", "截至日期设置无效，正确输入格式：yyyy.MM.dd.hh.mm.ss 。", QObject::tr("确定"));
        return;
    }
    if( dt10 > dt12)
    {
        dt10 = QDateTime::fromString(ui->lineEdit_Rz_End_Time->text(), "yyyy.MM.dd.hh.mm.ss");
        dt12 = QDateTime::fromString(ui->lineEdit_Rz__Star_Time->text(), "yyyy.MM.dd.hh.mm.ss");
        ui->lineEdit_Rz__Star_Time->setText( dt10.toString("yyyy.MM.dd.hh.mm.ss"));
        ui->lineEdit_Rz_End_Time->setText( dt12.toString("yyyy.MM.dd.hh.mm.ss"));
    }
    model1->setFilter( QString("date0 >='%1' and date0 <='%2' and Hour >= %3 and Hour <= %4 "
                               "and Minute >= %5 and Minute <= %6 and Second >= %7 and Second <= %8")
                       .arg(dt10.toString("yyyy-MM-dd")).arg(dt12.toString("yyyy-MM-dd"))
                       .arg(dt10.time().hour() ).arg(dt12.time().hour() )
                       .arg(dt10.time().minute() ).arg(dt12.time().minute() )
                       .arg(dt10.time().second() ).arg(dt12.time().second() ) );
    model1->select();
    while(model1->canFetchMore()) model1->fetchMore();
    int countToSave1 = model1->rowCount();
    if(countToSave1 == 0)
    {
        QMessageBox::information( this, "提示", "该时间节点没有数据", QObject::tr("确定"));
        return;
    }
    while(model1->canFetchMore()) model1->fetchMore();
    int RowCount1 = model1->rowCount();
    for( int i= 0; i< RowCount1; i++)
    {
        tmpRecord1 =	model1->record( i);
        str_t10 = tmpRecord1.value(0).toString() + " " + tmpRecord1.value(1).toString() + ":" + tmpRecord1.value(2).toString() + ":" + tmpRecord1.value(3).toString();
        Flag = (tmpRecord1.value(4).toString()).toInt();
        switch (Flag) {
        case 1:
            str3 = "探头未连接";
            break;
        case 2:
            str3 = "探头已连接";
            break;
        case 3:
            str3 = "探头断开连接";
            break;
        case 4:
            str3 = "解除低阈值报警";
            break;
        case 5:
            str3 = "低阈值报警";
            break;
        case 6:
            str3 = "解除高阈值报警";
            break;
        case 7:
            str3 = "高阈值报警";
            break;
        case 8:
            str3 = "设置通道参数";
            break;
        case 9:
            str3 = "设置报警参数";
            break;
        case 10:
            str3 = "解除探头报警";
            break;
        default:
            break;
        }
        ui->textEdit_Rz->append("  时间：  " + str_t10 + "       设备日志：  "+str3);
    }
}



















































