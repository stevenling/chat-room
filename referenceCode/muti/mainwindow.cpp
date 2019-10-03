#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);;
    char *data="hello qt!";
    client = new QTcpSocket(this);
    client->connectToHost("192.168.137.5", 400);
    connect(client, SIGNAL(readyRead()), this, SLOT(readClient()));
    ui->label->setText("尝试连接服务器");
      ui->textEdit->setFocus();
      ui->senBtnMuti->setShortcut( Qt::Key_Enter);
      connect(ui->textEdit, SIGNAL(returnPressed()), ui->senBtnMuti, SIGNAL(on_pushButton_clicked()), Qt::UniqueConnection);
   //   connect(ui->textEdit, SIGNAL(returnPressed()), on_pushButton_clicked, SIGNAL(clicked()), Qt::UniqueConnection);
//    connect(client, SIGNAL(readyRead()), this, SLOT(readClient()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::readClient()
{
//    QString str = client->readAll();
    //或者
    char buf[1024];
    char per[100];
    client->read(buf,1024);
//    QDebug << buf;
    qDebug("readString = %s",buf);
    QString str = QString::fromLocal8Bit(buf);
    if(buf[0]=='u' || buf[0]=='h') {
        ui->textBrowser->append(" ");
        ui->textBrowser->setAlignment(Qt::AlignLeft);
        ui->textBrowser->append(str);
    }else{
        ui->label->setAlignment(Qt::AlignCenter);
        strcpy(per,"当前在线人数：");
        strcat(per,buf);
        ui->label->setText(per);
    }
}

void MainWindow::on_pushButton_clicked()
{
    char buf[1024];
    client->read(buf,1024);
//    QDebug << buf;
    qDebug("readString = %s",buf);
}

void MainWindow::on_senBtnMuti_clicked()
{
        QString str = ui->textEdit->toPlainText();
        int len = str.length();
        qDebug("readString = %s",qPrintable(str));
    //qDebug<<a;
        QByteArray datasend = str.toLocal8Bit();
        client->write(datasend);

         ui->textBrowser->append(" ");
         ui->textBrowser->setAlignment(Qt::AlignRight);
         ui->textBrowser->append(str);
         ui->textEdit->clear();
         ui->textEdit->setFocus();
}
