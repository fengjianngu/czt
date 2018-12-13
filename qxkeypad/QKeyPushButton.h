/* Adapted by Tony Feng from QKeyPushButton.h (widgetKeyBoard) */
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
 
#include <QPushButton>

#if _MSC_VER >= 1600                        // Modify By XinTinG
#pragma execution_character_set("utf-8")
#endif

#ifndef _QKEYPUSHBUTTON_H
#define _QKEYPUSHBUTTON_H

#define DEFAULT_BACKGROUND_BUTTON	"background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 rgb(218, 228, 238), stop: 1 rgb(108, 118, 128));"
#define CHANGED_BACKGROUND_BUTTON	"background:lightgray;color:darkred;"
#define DEFAULT_STYLE_BUTTON        "color:white;border: 1px solid #000000;border-radius:6px;"
#define STYLE_FOCUS_TEXT            "background-color:rgb(212, 212, 212);border: 1px solid green;"
#define STYLE_DEFAULT_TEXT          "QLineEdit:focus{background-color:rgb(212, 212, 212);}"

#define EMBEDDED_KEYBOARD           " font-size:24px;"
#define WIDTH_ZOOM_KEY              20
#define HEIGHT_ZOOM_KEY             WIDTH_ZOOM_KEY

#define KEY_TAB				        tr("TAB")
#define KEY_CAPS			        tr("CAPS")
#define KEY_BACKSPACE			    tr("X")
#define KEY_BACKSPACE_EMBEDDED		tr("DEL")
#define KEY_RETURN			        tr("ESC")
#define KEY_SPACE                   " "
#define KEY_WIDTH_EMBEDDED          26
#define KEY_HEIGHT_EMBEDDED         22

#define IS_KEY(keyTextPressed, keyValCompare)   (keyTextPressed).contains((keyValCompare), Qt::CaseInsensitive)

#define IS_TAB(text)                            IS_KEY(text, KEY_TAB)
#define IS_CAPS(text)                           IS_KEY(text, KEY_CAPS)
#define IS_BACK(text)                           IS_KEY(text, KEY_BACKSPACE)
#define IS_BACK_EMB(text)                       IS_KEY(text, KEY_BACKSPACE_EMBEDDED)
#define IS_RETURN(text)                         IS_KEY(text, KEY_RETURN)
#define IS_SPACE(text)                          IS_KEY(text, KEY_SPACE)
#define NO_SPECIAL_KEY(text)                    ((text).length() == 1)

class QKeyPushButton : public QPushButton {
    Q_OBJECT

public:
    QKeyPushButton(QWidget *parent = 0);

private slots:
	void getKeyPress(bool statusCaps);

signals:
    void pressedKey(bool statusCaps);

private:
	QWidget *m_parent;
    QString style_embedded;
    int m_oldYKey;

protected:
    void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
};

#endif // _QKEYPUSHBUTTON_H
