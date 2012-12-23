#ifndef QMYBUTTON_H
#define QMYBUTTON_H

#include <qpushbutton.h>

class QMyButton:public QPushButton {
    Q_OBJECT public:
    QMyButton(QWidget *);
    ~QMyButton();

    void setKeyCode(unsigned int keycode);
	unsigned int getKeyCode();
    QColor color;
                
public slots:
	void sendKey();

    
private:
	bool press;
	bool inrpt;

protected:
    	unsigned int keycode;
    virtual void enterEvent(QEvent *);
    virtual void leaveEvent(QEvent *);
    void timerEvent ( QTimerEvent * );
                                     
protected slots:
	void mousePressEvent(QMouseEvent *e);
	void mouseReleaseEvent(QMouseEvent *e);
    
signals:
	void keyClick(unsigned int keycode);    
};

#endif

