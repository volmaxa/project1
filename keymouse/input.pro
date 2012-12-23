#-------------------------------------------------
#
# Project created by QtCreator 2012-12-22T20:56:27
#
#-------------------------------------------------

QT       += core gui X11

TARGET = input
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qmybutton.cpp

HEADERS  += mainwindow.h \
    qmybutton.h

FORMS    += mainwindow.ui
LIBS += -lXtst
