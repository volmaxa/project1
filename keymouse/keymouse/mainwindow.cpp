#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/extensions/xtestconst.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/keysymdef.h>

#include <X11/extensions/XTest.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/keysymdef.h>

#include <QX11Info>
#include <QCursor>
#include <QEvent>
#include <QMouseEvent>

#include <X11/Xlib.h>
#include<stdio.h>
#include<unistd.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include <QtNetwork/QNetworkRequest>

Display *display;
unsigned int keycode;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->webView->load(QNetworkRequest(QUrl("http://m.facebook.com")));
    connect(ui->webView,SIGNAL(loadFinished(bool)),this,SLOT(doMouseLeftClick1()));
    connect(ui->webView,SIGNAL(loadFinished(bool)),this,SLOT(doMouseLeftClick2()));


}

void MainWindow::doMouseLeftClick1(){
    Display *display = XOpenDisplay(0);
    Window root = DefaultRootWindow(display);
    XWarpPointer(display, None, root, 0, 0, 0, 0, 170,150);
    mouseClick(Button1);
    XFlush(display);
    XCloseDisplay(display);
}
void MainWindow::doMouseLeftClick2(){
    Display *display = XOpenDisplay(0);
    Window root = DefaultRootWindow(display);
    XWarpPointer(display, None, root, 0, 0, 0, 0, 170,150);
    mouseClick(Button1);
    XFlush(display);
    XCloseDisplay(display);
    //sendKey(42,true,true);
    keyPress(40);
}


void MainWindow::keyPress(int key) {
    Display *display;
    display = XOpenDisplay(0);

    XTestFakeKeyEvent(display, key, true, 0);
    XTestFakeKeyEvent(display, key, false, 0);
    XFlush(display);
}

void MainWindow::mouseClick(int button){
        Display *display = XOpenDisplay(NULL);

        XEvent event;

        if(display == NULL)
        {
                fprintf(stderr, "Errore nell'apertura del Display !!!\n");
                exit(EXIT_FAILURE);
        }

        memset(&event, 0x00, sizeof(event));

        event.type = ButtonPress;
        event.xbutton.button = button;
        event.xbutton.same_screen = True;

        XQueryPointer(display, RootWindow(display, DefaultScreen(display)), &event.xbutton.root, &event.xbutton.window, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);

        event.xbutton.subwindow = event.xbutton.window;

        while(event.xbutton.subwindow)
        {
                event.xbutton.window = event.xbutton.subwindow;

                XQueryPointer(display, event.xbutton.window, &event.xbutton.root, &event.xbutton.subwindow, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);
        }

        if(XSendEvent(display, PointerWindow, True, 0xfff, &event) == 0) fprintf(stderr, "Error\n");

        XFlush(display);

        usleep(100000);

        event.type = ButtonRelease;
        event.xbutton.state = 0x100;

        if(XSendEvent(display, PointerWindow, True, 0xfff, &event) == 0) fprintf(stderr, "Error\n");

        XFlush(display);

        XCloseDisplay(display);
}

MainWindow::~MainWindow()
{
    delete ui;
}
