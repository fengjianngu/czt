#ifndef HS_SB_H
#define HS_SB_H

#include <QWidget>
#include "qxkeypad/QxKeyBoard.h"
namespace Ui {
class Hs_sb;
}

class Hs_sb : public QWidget
{
    Q_OBJECT

public:
    explicit Hs_sb(QWidget *parent = 0);
    ~Hs_sb();

private:
    Ui::Hs_sb *ui;
};

#endif // HS_SB_H
