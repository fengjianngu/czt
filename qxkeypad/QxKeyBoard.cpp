/* Adapted by Tony Feng from widgetKeyBoard.cpp (widgetKeyBoard) */
/***************************************************************************
 *   Copyright (C) 2015 by Tony Feng <fqheda@263.net >                     *
 *                                                                         *
 *   This program may be distributed under the terms of the Q Public       *
 *   License as defined by Trolltech AS of Norway and appearing in the     *
 *   file LICENSE.QPL included in the packaging of this file.              *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                  *
 ***************************************************************************/
 
#include <QGuiApplication>
#include <QLayout>
#include <QScreen>
#include <QKeyEvent>

#include <QTimer>


#if _MSC_VER >= 1600                        // Modify By XinTinG
#pragma execution_character_set("utf-8")
#endif

#include "QxKeyBoard.h"

bool QxKeyBoard::m_created = false;

QxKeyBoard::QxKeyBoard(bool embeddedKeyboard, QWidget *activeForm, QWidget *parent) : QWidget(parent), 
    m_embeddedKeyboard(embeddedKeyboard),
    m_zoomFacilityEmbedded(false)
{
    this->setStyleSheet("background-color:gray;border-radius:15px;");   // Modify By XinTinG
}

QxKeyBoard::~QxKeyBoard()
{
}

bool QxKeyBoard::isEmbeddedKeyboard(void)
{
    return (this->m_embeddedKeyboard);
}

void QxKeyBoard::setZoomFacility(bool active)
{
    this->m_zoomFacilityEmbedded = active;
}

bool QxKeyBoard::isZoomFacilityEnable(void)
{
    return (this->m_zoomFacilityEmbedded);
}

QKeyPushButton * QxKeyBoard::createNewKey(QString keyValue)
{
    QKeyPushButton * tmp = new QKeyPushButton(this);
    QString style = QString(DEFAULT_STYLE_BUTTON) + QString(DEFAULT_BACKGROUND_BUTTON);
    QSize imageDim;
    int width = 0, height = 0;

    if (this->isEmbeddedKeyboard() == true)
	{
        imageDim.setWidth(55);
        imageDim.setHeight(70);
    }
    else
	{
        imageDim.setWidth(55);
        imageDim.setHeight(70);
    }

    tmp->setText(keyValue);
    style += QString(EMBEDDED_KEYBOARD);
    if (this->isEmbeddedKeyboard() == true)
	{
        width = KEY_WIDTH_EMBEDDED;
        height = KEY_HEIGHT_EMBEDDED;
    }
    else
	{
/*
        width = 45;
        height = 50;
*/
        width = 55;
        height = 70;
    }
    tmp->setObjectName(keyValue);
    tmp->setMinimumSize(width, height);
    //tmp->setMaximumSize(width, height);
    tmp->setStyleSheet(style);
    tmp->setVisible(true);

    return (tmp);
}

void QxKeyBoard::receiptChildKey(QKeyEvent *event, QLineEdit *focusThisControl, bool reset)
{
    QString newKey = event->text();
    QString tmpReceiptString = m_noFocusPalette.text();
    int tmpPos = m_noFocusPalette.cursorPosition();

    if (NO_SPECIAL_KEY(newKey) == false)            // 特殊功能按钮
	{
        if (IS_RETURN(newKey) == true || IS_TAB(newKey) == true)    // 退出按钮
        {
            QTimer::singleShot( 300, this, SLOT(delay_close()));
        }
        else if (newKey == "OK")                    // OK 按钮
        {
            m_currentLineEdit = this->setDefaultTextStyle(m_currentLineEdit);
            m_currentLineEdit->deselect();
            m_currentLineEdit->setFocusPolicy(Qt::ClickFocus);

            m_currentLineEdit->setText( tmpReceiptString);

            this->hide();
        }
        else if (IS_BACK(newKey) == true || IS_BACK_EMB(newKey) == true)
		{
            if (tmpPos-1 >= 0)
			{
                tmpReceiptString = tmpReceiptString.remove(tmpPos-1, 1);
                m_noFocusPalette.setText(tmpReceiptString);
                m_noFocusPalette.setCursorPosition(tmpPos-1);
                //nextInput->setSelection(tmpPos-2, 1);
            }
        }
    }
    else
	{
        tmpReceiptString = tmpReceiptString.insert(tmpPos, newKey);
        m_noFocusPalette.setText(tmpReceiptString);
        m_noFocusPalette.setCursorPosition(tmpPos+1);
        //nextInput->setSelection(tmpPos, 1);
    }
}

myLineEdit * QxKeyBoard::setDefaultTextStyle(myLineEdit *control)
{
    //control->setStyleSheet(this->m_noFocusPalette.styleSheet());
	control->setStyleSheet(STYLE_DEFAULT_TEXT);
    return (control);
}

void QxKeyBoard::show(myLineEdit *pthis, QString Name)
{
    this->m_currentLineEdit = pthis;
    m_noFocusPalette.setText( this->m_currentLineEdit->text());
    m_ParaLabel.setText( Name );
    QWidget::show();
}

void QxKeyBoard::createKeyboard(void)      // Modify By Fengqinghua
{
    QVBoxLayout * tmpVLayout = new QVBoxLayout;
    QHBoxLayout * tmpHLayout = new QHBoxLayout;

	if (QxKeyBoard::m_created == true)
	{
		return;
	}
	QxKeyBoard::m_created = true;
    
    m_noFocusPalette.setStyleSheet("background-color: rgb(255, 255, 255); border: 1px solid rgb( 0, 50, 100);border-radius:5px;font-size:24px;");
    m_noFocusPalette.setMinimumHeight( 60);
    m_noFocusPalette.setMaximumWidth( 540);

    m_ParaLabel.setStyleSheet("color:rgb(255,255,255);font-size:25px;");

    tmpHLayout->addWidget( (QWidget *) &m_ParaLabel);
    tmpHLayout->addWidget( (QWidget *) &m_noFocusPalette);
    //tmpHLayout->addWidget();
    tmpVLayout->insertLayout(0, tmpHLayout);

    tmpHLayout = new QHBoxLayout;

	tmpHLayout->addWidget(createNewKey(tr("1")));
	tmpHLayout->addWidget(createNewKey(tr("2")));
	tmpHLayout->addWidget(createNewKey(tr("3")));
	tmpHLayout->addWidget(createNewKey(tr(".")));

    tmpVLayout->insertLayout(1, tmpHLayout);

	tmpHLayout = new QHBoxLayout;

	tmpHLayout->addWidget(createNewKey(tr("4")));
	tmpHLayout->addWidget(createNewKey(tr("5")));
	tmpHLayout->addWidget(createNewKey(tr("6")));
	tmpHLayout->addWidget(createNewKey(tr(":")));

    tmpVLayout->insertLayout(2, tmpHLayout);

	tmpHLayout = new QHBoxLayout;

	tmpHLayout->addWidget(createNewKey(tr("7")));
	tmpHLayout->addWidget(createNewKey(tr("8")));
	tmpHLayout->addWidget(createNewKey(tr("9")));
	tmpHLayout->addWidget(createNewKey(tr("-")));

    tmpVLayout->insertLayout(3, tmpHLayout);
    
	tmpHLayout = new QHBoxLayout;

	tmpHLayout->addWidget(createNewKey(KEY_RETURN));
	tmpHLayout->addWidget(createNewKey(tr("0")));
    tmpHLayout->addWidget(createNewKey(tr("OK")));
	tmpHLayout->addWidget(createNewKey(KEY_BACKSPACE_EMBEDDED));

    tmpVLayout->insertLayout(4, tmpHLayout);
    
    this->setLayout(tmpVLayout);
    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

void QxKeyBoard::delay_close()
{
    this->close();
}
