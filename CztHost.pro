#-------------------------------------------------
#
# Project created by QtCreator 2018-08-14T11:44:53
#
#-------------------------------------------------

QT       += core gui serialport charts network
QT += websockets
QT += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CztHost
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    sys_start.cpp \
    csys_login.cpp \
    qxkeypad\QxKeyBoard.cpp \
    qxkeypad\QKeyPushButton.cpp \
    mylineedit.cpp \
    dose\doseFromGeStd.cpp \
    dose\doseFromGeStd_initialize.cpp \
    dose\doseFromGeStd_terminate.cpp \
    dose\rtGetInf.cpp \
    dose\rtGetNaN.cpp \
    dose\rt_nonfinite.cpp \
    dose\fliplr.cpp \
    dose\interp.cpp \
    dose\interp1.cpp \
    dose\interp_initialize.cpp \
    dose\interp_terminate.cpp \
    dose\ppval.cpp \
    dose\pwchcore.cpp \
    dose\spline.cpp \
    dose\peakfindczt.cpp \
    dose\flip.cpp \
    dose\interp1024_4096.cpp \
    dose\interp1024_4096_initialize.cpp \
    dose\interp1024_4096_terminate.cpp \
    dose\interp2048_4096.cpp \
    dose\interp8192_4096.cpp \
    set_wait.cpp \
    low_power.cpp \
    qcustomplot.cpp \
    power_off.cpp


HEADERS  += mainwindow.h \
    sys_start.h \
    csys_login.h \
    qxkeypad\QxKeyBoard.h \
    qxkeypad\QKeyPushButton.h \
    mylineedit.h \
    dose\doseFromGeStd.h \
    dose\doseFromGeStd_initialize.h \
    dose\doseFromGeStd_terminate.h \
    dose\doseFromGeStd_types.h \
    dose\rtGetInf.h \
    dose\rtGetNaN.h \
    dose\rt_nonfinite.h \
    dose\rtwtypes.h \
    dose\fliplr.h \
    dose\interp.h \
    dose\interp1.h \
    dose\interp_initialize.h \
    dose\interp_terminate.h \
    dose\ppval.h \
    dose\pwchcore.h \
    dose\spline.h  \
    dose\interp1024_4096.h \
    dose\interp1024_4096_initialize.h \
    dose\interp1024_4096_terminate.h \
    dose\interp1024_4096_types.h \
    dose\interp2048_4096.h \
    dose\interp8192_4096.h \
    netmsg.h \
    set_wait.h \
    low_power.h \
    qcustomplot.h \
    power_off.h



FORMS    += mainwindow.ui \
    sys_start.ui \
    csys_login.ui \
    set_wait.ui \
    low_power.ui \
    power_off.ui

RESOURCES += \
    img.qrc

QT        += sql
//LIBS += -L/home/lts/Qt5.8.0/myssl
