#-------------------------------------------------
#
# Project created by QtCreator 2012-12-23T23:06:39
#
#-------------------------------------------------

QT       += core gui X11 webkit

TARGET = keymouse
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qmybutton.cpp

HEADERS  += mainwindow.h \
    qmybutton.h

FORMS    += mainwindow.ui

LIBS += -lXtst
