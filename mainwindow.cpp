#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    myServer = new MyServer;
    this->performSignalConnections();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete myServer;
}

void MainWindow::performSignalConnections()
{
    QObject::connect(myServer, SIGNAL(situationChanged(bool)),this, SLOT(changeBtnRunState(bool)));
    QObject::connect(myServer, SIGNAL(sendMainWindowMessage(QString)),this, SLOT(outputMessage(QString)));
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::on_btRun_clicked()
{
    myServer->runServer();
}

void MainWindow::changeBtnRunState(bool running)
{
    if (running){
        ui->btRun->setText("Stop");
    }
    else {
        ui->btRun->setText("Run");
    }
}

void MainWindow::outputMessage(QString message)
{
    ui->txtOutput->append(message);
}
