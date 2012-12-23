#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qmybutton.h>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QString currentFont;
    QVector<QMyButton *> buttons;
    QVector<QMyButton *> modKeys;
public slots:
    void sendKey(unsigned int keycode, bool press, bool release);
    void mouseClick(int button);
};

#endif // MAINWINDOW_H
