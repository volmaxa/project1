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
    connect(ui->webView,SIGNAL(loadFinished(bool)),this,SLOT(doMouseLeftClick()));
    connect(ui->webView,SIGNAL(loadFinished(bool)),this,SLOT(doMouseLeftClick()));
}

void MainWindow::doMouseLeftClick(){
    Display *display = XOpenDisplay(0);
    Window root = DefaultRootWindow(display);
    XWarpPointer(display, None, root, 0, 0, 0, 0, 0,0);
    mouseClick(Button1);
    XFlush(display);
    XCloseDisplay(display);
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

void MainWindow::sendKey( unsigned int keycode, bool press, bool release )
{
        Q_UNUSED(press);
        Q_UNUSED(release);
        Window curr_focus;
        int revert_to;

        XGetInputFocus( display, &curr_focus, &revert_to );

        for ( int a = 0; a < modKeys.size(); a++ ) {
                if ( modKeys[a]->isChecked() ) {
                        XTestFakeKeyEvent( display, modKeys[a]->getKeyCode(), true, 0 );
                }
        }

        XTestFakeKeyEvent( display, keycode, true,1 );
        XTestFakeKeyEvent( display, keycode, false, 2 );

        for ( int a = 0; a < modKeys.size(); a++ ) {
                if ( modKeys[a]->isChecked() ) {
                        XTestFakeKeyEvent( display, modKeys[a]->getKeyCode(), false, 2 );
                }
        }

        XFlush( display );
}




MainWindow::~MainWindow()
{
    delete ui;
}
