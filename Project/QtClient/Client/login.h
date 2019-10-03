#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QNetworkReply>
#include <QNetworkRequest>//网络请求
#include<QtNetwork/QtNetwork>


class MainWindow;
class Manage;

namespace Ui {
class Login;
}

class Login : public QMainWindow
{
    Q_OBJECT
public:
    explicit Login(QWidget *parent = 0, Manage *p = 0);
    ~Login();
    QNetworkReply *reply;
    QNetworkAccessManager *manager;
    Manage* man;
    QNetworkRequest *request;

signals:
    void sig();
    void display();
public slots:
    void finishedSlot(QNetworkReply *reply);
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();  // 登录
    void ChatStart();

private:
    Ui::Login *ui;
    MainWindow *ma; // 聊天界面的一个指针
};

#endif // LOGIN_H
