#include "csys_login.h"
#include <QTextStream>

#if _MSC_VER >= 1600                        // Modify By XinTinG
#pragma execution_character_set("utf-8")
#endif

CsysLogin::CsysLogin(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::XLoginWidget)
{
    ui->setupUi(this);


	ui->lineEdit_passwd->clear();
	ui->lineEdit_passwd->setEchoMode(QLineEdit::Password);

    QPixmap pixmap(1, 50);
    pixmap.fill(Qt::transparent);
    QIcon icon(pixmap);

    ui->comboBox->setIconSize(QSize(1, 50));
//    ui->comboBox->addItem(icon,"操作员");
//    ui->comboBox->addItem(icon,"管理员");
    ui->comboBox->addItem(icon,"User");

    ui->comboBox->setCurrentIndex( 0);
}

CsysLogin::~CsysLogin()
{
    delete ui;
}


void CsysLogin::keyPressEvent(QKeyEvent  *event)
{
    emit XloginMsg();

	if ((event->key() == Qt::Key_PageUp)/*||(event->key() == Qt::Key_Up)*/)
	{
		ui->lineEdit_passwd->setFocus();
	}

	if ((event->key() == Qt::Key_PageDown)/*||(event->key() == Qt::Key_Down)*/)
	{
		ui->lineEdit_passwd->setFocus();
	}
}

void CsysLogin::on_pushButton_login_clicked()
{
   // emit XloginMsg();

    QString userPassword;
    QFile userPassWordFile;

    userPassWordFile.setFileName("./user_pwd.txt");

 /*   if(ui->comboBox->currentIndex() == 0)           // 操作人员
    {
        if(!userPassWordFile.open(QIODevice::ReadOnly))
            userPassword = "1234";
        else
        {
            QTextStream usepassWdString(&userPassWordFile);
            userPassword=usepassWdString.readAll();
            userPassWordFile.close();
        }
    }
    else if(ui->comboBox->currentIndex() == 1)      // 管理人员
        userPassword = "2345";
    else                     */                       // 超级管理人员
        userPassword = "345678";

    if (ui->lineEdit_passwd->text() == userPassword)
    {
        emit XloginPro( ui->comboBox->currentIndex());

        ui->lineEdit_passwd->clear();
        ui->label_login_sts->clear();
        ui->comboBox->setCurrentIndex( 0);

        this->close();
    }
    else
    {
        ui->label_login_sts->setStyleSheet("QLabel{color:red;};");
        ui->label_login_sts->setText("         密码错误!");
    }
}

void CsysLogin::on_pushButton_return_clicked()
{
    emit XloginMsg();

    ui->lineEdit_passwd->clear();
    ui->label_login_sts->clear();

    ui->comboBox->setCurrentIndex( 0);

    emit XloginPro(10);

    this->close();
}

void CsysLogin::usr_show( int index)
{
    ui->lineEdit_passwd->clear();
    ui->label_login_sts->clear();
    ui->comboBox->setCurrentIndex( index);

    this->show();
}

void CsysLogin::keyboardshow(void *pthis)
{
    emit mySignal( pthis);

}
//void CsysLogin::mousePressEvent()
