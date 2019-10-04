#include "ui_login.h"
#include "mainwindow.h"
#include "login.h"
#include"manage.h"
#include <QDesktopServices>
#include <QUrl>
#include <QNetworkReply>
#include <QNetworkRequest> // 网络请求
#include <QJsonDocument>
#include <QJsonParseError>
#include <QDebug>
#include <QMessageBox>

QString user;   // 全局变量

class Manage;

//-------------------------------------------------------
Login::Login(QWidget *parent, Manage *p) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    this->man = p;  // man 是 manage 类的一个对象，因此它能够调用 ChatStart
    ui->setupUi(this);
    setWindowTitle("登录界面");

    manager = new QNetworkAccessManager(this);  // 声明一个对象，实现 post
    request = new QNetworkRequest();

    connect(manager, SIGNAL(finished(QNetworkReply*)),
             this, SLOT(finishedSlot(QNetworkReply*)));
}

//-------------------------------------------------------
Login::~Login()
{
    delete ui;
}

//-------------------------------------------------------
void Login::finishedSlot(QNetworkReply *reply)
{

     QVariant statusCodeV =  reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
     QVariant redirectionTargetUrl =
     reply->attribute(QNetworkRequest::RedirectionTargetAttribute);

     if (reply->error() == QNetworkReply::NoError)
     {
         QByteArray bytes = reply->readAll();  // 接受
         
         QString string = QString::fromUtf8(bytes);
        if(string == "true") 
        {
            // 登录成功
            ChatStart();      
        }
        else 
        {
            // 登录失败
            QMessageBox::warning(this,tr("警告"),tr("用户名或密码错误!"),QMessageBox::Yes);
            this->ui->lineEdit->clear();
            this->ui->lineEdit_2->clear();
            this->ui->lineEdit->setFocus();
        }
     }
     else
     {
     }
     reply->deleteLater();
}

//-------------------------------------------------------
void Login::on_pushButton_clicked()
{
    request->setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

    // request->setUrl(QUrl("http://172.22.1.1/validate.php"));      // 树莓派上的、
    // request->setUrl(QUrl("http://123.206.186.185/validate.php")); // leyiweb腾讯云
    request->setUrl(QUrl("http://123.207.251.200/validate.php"));    // yunhu腾讯云

    user = ui->lineEdit->text();            // 获取到username
    QString pass = ui->lineEdit_2->text();  // 获取到password

    QString str = "username=" + user + "&password=" + pass;
    qDebug() << str;

    QByteArray postData;
    postData.append(str);
    reply = manager->post(*request, postData);
}

//--------------------------------------------------------
void Login::on_pushButton_2_clicked()// 注册
{
    // QDesktopServices::openUrl(QUrl(QLatin1String("http://172.22.1.1/register.html")));       // 树莓派注册
    // QDesktopServices::openUrl(QUrl(QLatin1String("http://123.206.186.185/register.html")));  // leyiweb腾讯云注册
    QDesktopServices::openUrl(QUrl(QLatin1String("http://123.207.251.200/register.html")));     // yunhu腾讯云注册
}

//-------------------------------------------------------
void Login::ChatStart()
{
    man->ChatStart();
}


