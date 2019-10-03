#include "mainwindow.h"
#include"login.h"
#include "ui_mainwindow.h"
#include <QListWidget>
#include <QListWidgetItem>
#include <QWidget>
#include <QVBoxLayout>
#include <QDebug>

extern QString user;      //声明外部变量

MainWindow::MainWindow(QWidget *parent, Manage *p) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    this->man = p;
    ui->setupUi(this);
    showlist(); 
    connect(ui->widget,SIGNAL(itemSelectionChanged()),this,SLOT(sendtouser()));// 改变会触发槽函数sendtouser
     QObject::connect(listWidget, SIGNAL(currentTextChanged(QString)), this,SLOT(seek()));
    setWindowTitle("客户端");
    init();
    connect(ui->sendBtn,SIGNAL(clicked(bool)),SLOT(onSendMessage()));//按下发送按钮调用onSendMessage函数
    //connect(ui->listWidget,SIGNAL(itemSelectionChanged()),this,SLOT(sendtouser()));// 改变会触发槽函数sendtouser
}
void MainWindow::seek()//拿到数据了
{
     m = ui->label_4->text();
    qDebug()<<m;
}
void MainWindow::showlist()//显示好友列表
{
    QVBoxLayout* layout = new QVBoxLayout;
        listWidget = new QListWidget(this);

        QListWidgetItem* lst1 = new QListWidgetItem("all", listWidget);
        QListWidgetItem* lst2 = new QListWidgetItem("abc", listWidget);
        QListWidgetItem* lst3 = new QListWidgetItem("leyiweb", listWidget);
        QListWidgetItem* lst4 = new QListWidgetItem("pjc", listWidget);
        QListWidgetItem* lst5 = new QListWidgetItem("wei2014", listWidget);
        QListWidgetItem* lst6 = new QListWidgetItem("google", listWidget);
        QListWidgetItem* lst7 = new QListWidgetItem("tencent", listWidget);
        QListWidgetItem* lst8 = new QListWidgetItem("123456", listWidget);
        listWidget->insertItem(1, lst1);
        listWidget->insertItem(2, lst2);
        listWidget->insertItem(3, lst3);
        listWidget->insertItem(4, lst4);
        listWidget->insertItem(5, lst5);
        listWidget->insertItem(6, lst6);
        listWidget->insertItem(7, lst7);
        listWidget->insertItem(8, lst8);
        listWidget->show();
        layout->addWidget(listWidget);
        ui->widget->setLayout(layout);
        ui->widget->show();
        QObject::connect(listWidget, SIGNAL(currentTextChanged(QString)), ui->label_4, SLOT(setText(QString)));
     //   QObject::connect(listWidget, SIGNAL(currentTextChanged(QString)), this,SLOT(seek()));

}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    //newTcpConnect();
    tcpSocket = new QTcpSocket;//初始化的时候建立socket
    connect(tcpSocket,SIGNAL(readyRead()),SLOT(onReciveData()));
}

void MainWindow::newTcpConnect()//第一次发送请求
{

     tcpSocket->connectToHost("172.22.1.1",400);//连接树莓派服务器
     //tcpSocket->connectToHost("123.206.186.185",400);//连接腾讯云服务器
     QString suser = userdata;//发送端的用户名
     QString ruser = m;//接收端的用户名
     QByteArray showui;
     //showui += (suser + "send" + textEdit2 + ruser);
     showui.append("connect succuss!");
     QByteArray result;
     //result += ('A'+'#' + suser + '#' + ruser + '#' + textEdit2);
     QString resultstr="A";
     resultstr.append("#" + suser + "#" + ruser+ "NULL" + "#");
     result = resultstr.toUtf8();
     ui->textEdit->setText(showui);
     tcpSocket->write(result);
     //tcpSocket->waitForReadyRead(1000);

    /*QByteArray byteuserdata;//发送初始化数据
     byteuserdata += "1#leyiweb#NULL#NULL";
     tcpSocket->write(byteuserdata);
     tcpSocket->waitForReadyRead(1000);*/
    //tcpSocket->abort();//断开socket

   /* tcpSocket->connectToHost("172.22.1.1",
                             403);*/
    //tcpSocket->connectToHost(ui->hostlineEdit->text(),
   //                          ui->portlineEdit->text().toInt());
}

void MainWindow::onReciveData()//接收数据
{

    QString data = tcpSocket->readAll();
    char *ch;
    char *begin;
    char user[50];
    QByteArray ba = data.toLatin1();
    ch=ba.data();//ch 就是data的char *
    if(data[0] == 'E')//服务器发给我的
    {
        begin = strstr(ch,"#");
        begin++;
        char * next = strstr(begin,"#");
        memcpy(user,begin,next-begin);
        user[next-begin] = '\0';
        begin = next;
        begin++;
        QByteArray byte;
        byte = QByteArray(user);
        QByteArray beg;
        beg = QByteArray(begin);
        //byte += QByteArray(begin);
        mChat.append("Recv: "  + QString::fromLocal8Bit("Time: ") + QTime::currentTime().toString()+"\n" + byte +":  "+ beg+ "\n");
    }
    else if(data[0] == 'D')
    {

    }

    ui->textEdit->setText(mChat);
}

void MainWindow::onSendMessage()//发送数据
{
    if(i == 1)
    {
        newTcpConnect();//运行一次
        i = 2;
        return;
    }
    int flag = 2; //标识符
    QString suser = userdata;//发送端的用户名
    QString ruser = m;//接收端的用户名
    QString textEdit = ui->lineEdit->text();//数据
    QString textEdit2 = textEdit.toUtf8();//正确编码的数据
    //QByteArray showui;
    showui.append( "send: "  + QString::fromLocal8Bit("Time: ") + QTime::currentTime().toString()+ "\n" + ruser+ ":  " +textEdit2+"\n");
    QByteArray result;
    //result += ('A'+'#' + suser + '#' + ruser + '#' + textEdit2);
    if(ruser == "all")
    {
        resultstr="B";
    }
    else
    {
        resultstr="C";
    }

    resultstr.append("#" + suser + "#" + ruser + "#" + textEdit2);

    qDebug()<<resultstr;
    result = resultstr.toUtf8();
    qDebug()<<result;
    //result += ( textEdit2 + ruser);
    ui->textEdit->setText(showui);
    tcpSocket->write(result);


    //QString strData =QString::fromLocal8Bit("Time: ") + QTime::currentTime().toString() + "\n" + textEdit.toUtf8() +"\n";
   /* QString strData = textEdit.toUtf8()+"\n";
    QByteArray sendMessage = strData.toUtf8();
    mChat+= ("Send " + sendMessage);
    ui->textEdit->setText(mChat);
    tcpSocket->write(sendMessage);*/
}
void MainWindow::sendtouser()//发送指定用户数据
{
    QByteArray senduser;//定义一个发送的最终数据
     QString textEdit = ui->lineEdit->text();//获取要输入的文本
     QString strData = textEdit.toUtf8()+"\n";
     QByteArray sendMessage = strData.toUtf8();//得到想要的输入
     //senduser += (ui->widget->curr->text()+sendMessage);//输入的文本+选中的文本
    // senduser +=
     //    ui->textEdit->setText(mChat);
     ui->textEdit->setText(senduser);
     tcpSocket->write(senduser);
}
void MainWindow::on_pushButton_clicked()//返回
{
    BackToLog();
}
void MainWindow::BackToLog()//重写返回登录界面
{
    man->BackToLog();
}

void MainWindow::on_pushButton_2_clicked()//显示用户名
{
     userdata = user;
    ui->lineEdit_2->setText(user);
}
void MainWindow::onShowError(QAbstractSocket::SocketError)
{
    qDebug()<<tcpSocket->errorString();
    tcpSocket->close();
}
