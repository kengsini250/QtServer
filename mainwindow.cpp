#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->cclean, &QAbstractButton::clicked, [=]() {
        ui->textBrowser->clear();
        //ui->listWidget->clear();
    });

    myServer=new MyServer(this);
    ui->textBrowser->append("Max Users : "+QString::number(myServer->maxPendingConnections())+"\n");

    connect(myServer,&MyServer::newClient,[=]() {
        ui->textBrowser->append("connecting : " + QString::number(myServer->getConnectingClient()));
        ui->textBrowser->append("--new  client---\n\n");
    });
    connect(myServer,&MyServer::setText,[&](QString&str){
        ui->textBrowser->append(str);
    });

    connect(myServer,&MyServer::disconnectClient,[=]{
        ui->textBrowser->append("--Client disconnect--   now :" + QString::number(myServer->getConnectingClient()));
        ui->listWidget->takeItem(0);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

