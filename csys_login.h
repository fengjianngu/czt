#ifndef CSYS_LOGIN_H
#define CSYS_LOGIN_H

#include <QDialog>
#include <QLineEdit>
#include <QFile>
#include <QKeyEvent>
#include "mylineedit.h"

#include "ui_csys_login.h"

namespace Ui {
	class XLoginWidget;
}

class CsysLogin : public QDialog
{
    Q_OBJECT

public:
	explicit CsysLogin(QWidget *parent = 0);
	~CsysLogin();
	
	void keyPressEvent(QKeyEvent  *event);

    void usr_show( int index);

signals:
	void XloginPro(qint32 mode);
	void XloginMsg(void);
    void mySignal(void *pthis);
  
public slots:
	void on_pushButton_return_clicked();

    void keyboardshow(void *pthis);

private slots:

	void on_pushButton_login_clicked();



private:
	Ui::XLoginWidget *ui;

};

#endif
