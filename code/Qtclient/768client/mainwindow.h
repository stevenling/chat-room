#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<manage.h>
#include <QMainWindow>
#include<QtNetwork/QtNetwork>
#include <QListWidget>
namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0, Manage *p = 0);
    ~MainWindow();
public:
    void init();
    void newTcpConnect();
    Manage* man;//manage类的一个对象
    QString userdata;
    //Login *k;
    int i = 1;
    QString m;//想要通信的好友
    QListWidget *listWidget; //聊天室控件
    QString resultstr;
    QByteArray showui;
private slots:
    void onReciveData();
    void onSendMessage();
    void onShowError(QAbstractSocket::SocketError);
    void on_pushButton_clicked();
    void BackToLog();
    void sendtouser();//发送数据给用户
    void seek();
    void on_pushButton_2_clicked();
    void showlist();

private:
    QTcpSocket *tcpSocket;
    QByteArray mChat;


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
