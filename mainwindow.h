#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "myserver.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MyServer *myServer;
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;
    void performSignalConnections();

private slots:
    void on_btRun_clicked();

public slots:
    void changeBtnRunState(bool running);
    void outputMessage(QString message);
};

#endif // MAINWINDOW_H
