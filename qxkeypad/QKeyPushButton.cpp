/* Adapted by Tony Feng from QKeyPushButton.cpp (widgetKeyBoard) */
/***************************************************************************
 *   Copyright (C) 2015 Tony Feng <fqheda@263.net >                        *
 *                                                                         *
 *   This program may be distributed under the terms of the Q Public       *
 *   License as defined by Trolltech AS of Norway and appearing in the     *
 *   file LICENSE.QPL included in the packaging of this file.              *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                  *
 ***************************************************************************/
 
#include "QKeyPushButton.h"
#include "QxKeyBoard.h"

#include <QKeyEvent>
#include <QCoreApplication>

#if _MSC_VER >= 1600                        // Modify By XinTinG
#pragma execution_character_set("utf-8")
#endif

QKeyPushButton::QKeyPushButton(QWidget *parent) : QPushButton(parent), m_parent(parent)
{
	this->setStyleSheet(QString(DEFAULT_STYLE_BUTTON) + QString(DEFAULT_BACKGROUND_BUTTON));
	
	connect(this, SIGNAL(pressedKey(bool)), SLOT(getKeyPress(bool)));
	if ((static_cast<QxKeyBoard *> (parent))->isEmbeddedKeyboard() == true)
	{
		this->style_embedded = QString(EMBEDDED_KEYBOARD);
	}
	
    this->style_embedded = QString(EMBEDDED_KEYBOARD);
	this->setFocusPolicy(Qt::NoFocus);   // Modify By XinTinG
}

void QKeyPushButton::getKeyPress(bool capsStatus)
{
	int 		keyCode = 0;
	QKeyEvent	*key = NULL;
	QString		text = this->text();

	if (NO_SPECIAL_KEY(text) == false && (IS_BACK(text) == true || IS_BACK_EMB(text) == true || IS_TAB(text) == true || IS_RETURN(text) == true ))
	{
		key = new QKeyEvent(QEvent::KeyPress, keyCode, Qt::NoModifier, text);
	}
	else 
	{
        keyCode = text.toUtf8()[0];
        if (capsStatus == false) 
		{
            if (keyCode >= tr("A")[0] && keyCode <= tr("Z")[0]) 
			{
                keyCode += 32;
                text = (char ) keyCode;
            }
            key = new QKeyEvent(QEvent::KeyPress, keyCode, Qt::NoModifier, text);
		}
		else
            key = new QKeyEvent(QEvent::KeyPress, keyCode, Qt::ShiftModifier, text);
	}
    ((QxKeyBoard *) this->m_parent)->receiptChildKey(key, NULL);
	QCoreApplication::processEvents();
}

void QKeyPushButton::mousePressEvent(QMouseEvent * /*event */)
{
    static bool m_capsActive = true;
	QxKeyBoard  *tmpKeyBoard = (QxKeyBoard *) this->m_parent;
    static int  yMarginKeyboard = tmpKeyBoard->rect().y();
	QString	text = this->text();
    short adjustZoomedKey = HEIGHT_ZOOM_KEY;
    QString defaultStyleButton = QString(DEFAULT_STYLE_BUTTON);
    QString changedColorButton = QString(CHANGED_BACKGROUND_BUTTON);

    if (IS_CAPS(text) == true)
	{
		if (m_capsActive == false)
		{
			m_capsActive = true;
		}
		else
		{
            changedColorButton = QString(DEFAULT_BACKGROUND_BUTTON);
			m_capsActive = false;
		}
        this->setStyleSheet(defaultStyleButton + changedColorButton + this->style_embedded);
		this->repaint();
		QCoreApplication::processEvents();
	}
	else
	{
        this->setStyleSheet(defaultStyleButton + changedColorButton + this->style_embedded);
		this->repaint();
		QCoreApplication::processEvents();
		emit pressedKey(m_capsActive);
	}

    this->m_oldYKey = 0;
    if (tmpKeyBoard->isEmbeddedKeyboard() == true && tmpKeyBoard->isZoomFacilityEnable() 
	    && NO_SPECIAL_KEY(text) && text.trimmed().length() != 0)
	{
        tmpKeyBoard->setCursor(Qt::BlankCursor);
		if (this->y() - adjustZoomedKey - KEY_HEIGHT_EMBEDDED < yMarginKeyboard)
		{
			this->m_oldYKey = this->y();
		}
		else
		{
			adjustZoomedKey = -HEIGHT_ZOOM_KEY;
		}
        this->setGeometry(this->x() - 10, this->y() + adjustZoomedKey - KEY_HEIGHT_EMBEDDED, 
			              KEY_WIDTH_EMBEDDED + WIDTH_ZOOM_KEY, KEY_HEIGHT_EMBEDDED + HEIGHT_ZOOM_KEY);
        this->setStyleSheet(changedColorButton + defaultStyleButton  + this->style_embedded);
        QCoreApplication::processEvents();
    }
}

void QKeyPushButton::mouseReleaseEvent(QMouseEvent * /* event */)
{
	QxKeyBoard  *tmpKeyBoard = (QxKeyBoard *) this->m_parent;

    if (IS_CAPS(this->text()) == false)
	{
        if (tmpKeyBoard->isEmbeddedKeyboard() == true && tmpKeyBoard->isZoomFacilityEnable() 
			&& NO_SPECIAL_KEY(this->text())  && this->text().trimmed().length() != 0) 
		{
            tmpKeyBoard->setCursor(Qt::ArrowCursor);
			if (this->m_oldYKey != 0)
			{
				this->setGeometry(this->x() + 10, this->m_oldYKey, KEY_WIDTH_EMBEDDED, KEY_HEIGHT_EMBEDDED);
			}
			else
			{
				this->setGeometry(this->x() + 10, this->y() + HEIGHT_ZOOM_KEY + KEY_HEIGHT_EMBEDDED, KEY_WIDTH_EMBEDDED, KEY_HEIGHT_EMBEDDED);
			}
            this->m_oldYKey = 0;
            QCoreApplication::processEvents();
        }
        this->setStyleSheet(QString(DEFAULT_STYLE_BUTTON) + QString(DEFAULT_BACKGROUND_BUTTON) + this->style_embedded);
    }
}
