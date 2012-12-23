#include "qmybutton.h"
#include <QDebug>
QMyButton::QMyButton(QWidget * parent):
QPushButton(parent)
{
     QPalette p = this->palette();
     color = p.color( QPalette::Background);
};

QMyButton::~QMyButton()
{
}

void QMyButton::enterEvent(QEvent *)
{
    QColor color2;
    color2.setNamedColor( "#a6ce39");
    //color2.setNamedColor( "#EED2B4");
//    setPaletteBackgroundColor(color2 /*Qt::yellow*/);
    QPalette palette;
    palette.setColor( this->backgroundRole(), color2);
    this->setPalette(palette);
 

}

void QMyButton::leaveEvent(QEvent *)
{
    //   setPaletteBackgroundColor(color);
        QPalette palette;
    palette.setColor( this->backgroundRole(), color);
    this->setPalette(palette);
 
}


void QMyButton::setKeyCode(unsigned int keycode)
{
	this->keycode = keycode;
	
}
unsigned int QMyButton::getKeyCode()
{
	return this->keycode;
}
void QMyButton::sendKey()
{
	emit keyClick(keycode);
}

void QMyButton::mousePressEvent(QMouseEvent * e)
{
	press = true;
	QPushButton::mousePressEvent(e);
	sendKey();
	startTimer(500);
}

void QMyButton::mouseReleaseEvent(QMouseEvent * e)
{
	press = false;
	QPushButton::mouseReleaseEvent(e);
//	killTimers();
	inrpt = false;                                                                        
}

void QMyButton::timerEvent(QTimerEvent *)
{
	if (!press){
		inrpt = false;
		return;
	}
	if (press && !inrpt) {
		inrpt = true;
        //	startTimer(120);
		return;
	}
	sendKey();
}
