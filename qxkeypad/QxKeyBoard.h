#ifndef _QXKEYBOARD_H
#define _QXKEYBOARD_H

#include "QKeyPushButton.h"
#include <QLineEdit>
#include <QClipboard>

#include "mylineedit.h"
#include <QLabel>

class QxKeyBoard : public QWidget {
    Q_OBJECT

public:
    QxKeyBoard(bool embeddedKeyboard = false, QWidget *activeForm = NULL, QWidget *parent = NULL);
    ~QxKeyBoard();

    void createKeyboard(void);
    bool isEmbeddedKeyboard(void);
    void setZoomFacility(bool active);
    bool isZoomFacilityEnable(void);
    void receiptChildKey(QKeyEvent *event, QLineEdit *focusThisControl, bool reset = false);

public slots:
    void show(myLineEdit *pthis, QString Name);

    void delay_close();

private:
    QxKeyBoard(const QxKeyBoard&);
	QxKeyBoard& operator=(const QxKeyBoard&);

    myLineEdit * setDefaultTextStyle(myLineEdit *control);
    QKeyPushButton * createNewKey(QString keyValue);

private:
    QLineEdit m_noFocusPalette;
    QLabel    m_ParaLabel;

    static bool m_created;
    bool m_embeddedKeyboard;
    bool m_zoomFacilityEmbedded;

    myLineEdit *m_currentLineEdit;
};

#endif // _QXKEYBOARD_H
