#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QKeyEvent>
#include <QDateTime>
#include <QDate>
#include <QTime>
#include <QTimer>
#include <QMessageBox>
#include <QtSql>
#include <QTcpSocket>
#include <QHostAddress>
#include <QWebSocket>
#include <QVector>
#include <QFileDialog>
#include <QFile>
#include <QByteArray>
#include <stdio.h>
#include <arpa/inet.h>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QJsonValuePtr>
#include <QJsonValueRef>
#include <QJsonValueRefPtr>
#include "sys_start.h"
#include "set_wait.h"
#include "low_power.h"
#include "qcustomplot.h"
#include "qxkeypad/QxKeyBoard.h"
#include "mylineedit.h"
#include <unistd.h>
#include "csys_login.h"
#include "power_off.h"
#include "dose/doseFromGeStd.h"
#include "dose/doseFromGeStd_initialize.h"
#include "dose/doseFromGeStd_terminate.h"
#include "dose/doseFromGeStd_types.h"
#include "dose/rtGetInf.h"
#include "dose/rtGetNaN.h"
#include "dose/rtwtypes.h"
#include "dose/rt_nonfinite.h"
#include "dose/fliplr.h"
#include "dose/interp.h"
#include "dose/interp1.h"
#include "dose/interp_initialize.h"
#include "dose/interp_terminate.h"
#include "dose/interp_types.h"
#include "dose/ppval.h"
#include "dose/pwchcore.h"
#include "dose/spline.h"
#include "dose/flip.h"
#include "dose/interp1024_4096.h"
#include "dose/interp1024_4096_initialize.h"
#include "dose/interp1024_4096_terminate.h"
#include "dose/interp1024_4096_types.h"
#include "dose/interp2048_4096.h"
#include "dose/interp8192_4096.h"
#include "dose/peakfindczt.h"
#include "dose/peakfindczt_types.h"
#include "netmsg.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QxKeyBoard *xkeypad;
    void createDateBaseFile();
    void SQL_Add_data( float JLL );
    void SQL_Add_data_Rz(int flag);
signals:

     void test_cal(void);

public slots:

    void KeyBoardShow(void *pthis);
    void login_fail();

private:
    Ui::MainWindow *ui;
    QTimer * timer_xstart;
    QTimer * timer_brush_data;
    QTimer * connect_tt;
    QTimer * sendcommd;
    QTimer * timer_cs;
    QTimer * brush_battery;
    QTimer * charger_battery;
    QTimer * web_connect_timer;
    QTimer * bruse_ui;
    int bat_mA = 0;
    int bat_mV = 0;
    qint64 cnt_bar =2;
    QDateTime Current_data_time;
    sys_start *xstart;
    CsysLogin *xlogin;
    Power_Off *ui_off;
    Set_Wait *set_wait_ui;
    Low_Power *low_power_ui;
    QFileDialog *fileDialog;
    QString path;
    QString path1;
    QString path2;
    QString path3;
    QString path4;
   // QString path_setconf = "/home/lts/SetConf/set.conf";
    QString path_setconf = "/SetConf/set.conf";
    QPixmap pix;
    QPixmap pix_sound;
    QPixmap pix_sound_on;
    QPixmap pix_battery;
    QPixmap pix_Tt;
    QPixmap pix_Gb;
    QPixmap pix_Db;
    QSqlDatabase datebase;
    //QString file_np_path = "/home/lts/npjl/";
    QString file_np_path = "/npjl/";
    int flags_set2 = 0;
    int flags_db = 0;
    int flags_gb = 0;
    int flags_cs = 0;
    int flags_hssb = 0;
    int fl = 0;
    int flags_cs1 = 1;
    int flags_sendcomd = 0;
    int flags_JLL = 1;
    QTcpSocket *  socket;
    QString IP="192.168.1.230";
    int PORT=2000;
    QWebSocket * webscoket1;
    QWebSocket * webscoket2;
    int webport = 7681;
//曲线
    QCPGraph * curGraph;
    QCPGraph * curGraph1;
    char data_power[100]={};
//能普记录
    double count_jl[4096] = {};
    double energy_jl[4096] = {};
//报警参数
    QString db ="1000";
    QString gb ="10000";
//通道参数
    int ch1_mcjx;
    int ch2_mcjx;
    int ch1_zds ;
    int ch2_zds ;
    float ch1_fd;
    float ch2_fd;
    float ch1_yz;
    float ch2_yz;
    float ch1_sh_time;
    float ch2_sh_time;
    float ch1_sp_time;
    float ch2_sp_time;
    QString nlkd1;
    QString nlkd2;
    float gy;
    QString jllke;
    QString hsk;
    double rising_speed1 = 1;
    double rising_speed2 = 1;
    int nal1 = 0;
    int nal2 = 0;
    int baseline_restorer1 = 1;
    int baseline_restorer2 = 1;
    int decay_time_constant1 = 1;
    int decay_time_constant2 = 1;
    struct mca_param Mca_Param1;
    struct mca_param Mca_Param2;

//计算参数
    double jll;
    double jlls;
    double jll_data[400]= {};
    int time_ph = 30;
    double jll_tmp = 0;
    float ch1_sz[4096] = {};
    float ch2_sz[4096] = {};
    float ch1_coe_E1;
    float ch1_coe_E2;
    float ch1_coe_E3;
    float ch2_coe_E1;
    float ch2_coe_E2;
    float ch2_coe_E3;
    double eng_std[3000] = {};
    double ge_std[3000] = {};
    float count1[4096] = {}; //探头1数据
    float count2[4096] = {}; //探头2数据
    float count1_cz[4096] = {}; //探头1数据插值结果
    float count2_cz[4096] = {}; //探头2数据插值结果
    float count1_1024[1024] = {};
    float count1_2048[2048] = {};
    float count1_4096[4096] = {};
//    float count1_8192[8192] = {};
    float count2_1024[1024] = {};
    float count2_2048[2048] = {};
    float count2_4096[4096] = {};
//    float count2_8192[8192] = {};
    float count2_interp[4096] = {};
    float count2_interp_hssb[4096] = {};
 //   float count_hb[4096] = {};
 //   float count_hb_hssb[4096] = {};
    float energy1[4096] = {};
    float energy2[4096] = {};
    float energy1_1024[1024] = {};
    float energy1_2048[2048] = {};
    float energy1_4096[4096] = {};
//    float energy1_8192[8192] = {};
    float energy2_1024[1024] = {};
    float energy2_2048[2048] = {};
    float energy2_4096[4096] = {};
//    float energy2_8192[8192] = {};
    float energy1_cz[4096] = {};//能量刻度1插值结果
    float energy2_cz[4096] = {};//能量刻度2插值结果
//    float count1_lj[4096] ={};
//    float count2_lj[4096] ={};

//能谱累加
    float count1_nplj[4096] ={};
    float count2_nplj[4096] ={};
    float count1_npljcz[4096] ={};
    float count2_npljcz[4096] ={};
    float count1_npljcz_4[4096] ={};
    float count2_npljcz_4[4096] ={};
    float count2_npljinterp[4096] ={};
    float count_npljhb[4096] ={};
//json解析出通道采集时间
    double dd1 = 0.0;
    double dd2 = 0.0;
    double dd3 = 0.0;
    double dd4 = 0.0;
    float  ch1_live =0.0;
    float  ch1_real = 0.0;
    float  ch2_live =0.0;
    float  ch2_real = 0.0;
//核素识别时间计数
    QString Probability[30] = {};
    float Energy_MeV[30] = {};
    QString Energy_MeV_str[30] = {};
    QString Nuclide[30] ={};
    QString str_hsk_line;
    QString str_hsk1;
    QString str_hsk2;
    QString str_hsk3;
    int hsk_data_s =0;  //库文件参数条数；
    float peakm[100] = {};
    double count_chart1[512] = {};
    double energy_chart1[512] = {};
    float count_chart2[512] = {};
    float energy_chart2[512] = {};
    double ge_user[4096] = {};
    double eng_user[4096] = {};
    double spe_user[4096] ={};
    float test_time = 0.0;

protected:
    void sleep(unsigned int msec);
    void socket_data(void);
    void power_off(void);

private slots:
    void timeout_xstart(void);
    void Brush_Time(void);
    void Brush_data_commd(void);
    void Test_cal(void);
    void Brush_Battery(void);
    void Charger_Battery(void);
    void Bruse_Ui(void);
    void hssb_cal(void);

    void FileDialog_Npjl(void);
    void FileDialog_Jlkd(void);
    void FileDialog_Nlkd_1(void);
    void FileDialog_Nlke_2(void);
    void FileDialog_Hsk(void);
    void LineEdit_Gb_Change (void);
    void LineEdit_Db_Change (void);
    void socket_read1(QString mm1);
    void socket_read2(QString mm2);

    void websocket_connect(void);
    void websocket_on_connect(void);
    void websocket_dis_connect(void);

    void on_Button_Root_clicked();
    void on_tabWidget_tabBarClicked(int index);
    void on_tabWidget_2_tabBarClicked();
    void on_Button_Tt_clicked();
    void on_Button_Db_clicked();
    void on_Button_Gb_clicked();
    void on_Button_Jll_clicked();
    void on_Button_Rz_clicked();
    void on_Button_Set2_clicked();
    void on_Button_Set1_clicked();
    void on_Button_Cs_clicked();
    void on_Button_npjl_clicked();

};

#endif // MAINWINDOW_H











