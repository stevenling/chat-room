
#include "ui_login.h"
#include "mainwindow.h"
#include "login.h"
#include"manage.h"
#include <QDesktopServices>
#include <QUrl>
#include <QNetworkReply>
#include <QNetworkRequest>//网络请求
#include <QJsonDocument>
#include <QJsonParseError>
#include <QDebug>
#include <QMessageBox>
QString user;//全局变量
class Manage;
Login::Login(QWidget *parent, Manage *p) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    this->man = p;//man 是manage类的一个对象，因此它能够调用ChatStart
    ui->setupUi(this);
    setWindowTitle("登录界面");

    manager = new QNetworkAccessManager(this);//声明一个对象，实现post
    request = new QNetworkRequest();

    connect(manager, SIGNAL(finished(QNetworkReply*)),
             this, SLOT(finishedSlot(QNetworkReply*)));
    //connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(ChatStart()));
}
Login::~Login()
{
    delete ui;
}

void Login::finishedSlot(QNetworkReply *reply)
{
     // Reading attributes of the reply
     // e.g. the HTTP status code
     QVariant statusCodeV =  reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
     // Or the target URL if it was a redirect:
     QVariant redirectionTargetUrl =
     reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
     // see CS001432 on how to handle this

     // no error received?
     if (reply->error() == QNetworkReply::NoError)
     {
         // read data from QNetworkReply here

         // Example 1: Creating QImage from the reply
         //QImageReader imageReader(reply);
         //QImage pic = imageReader.read();

         // Example 2: Reading bytes form the reply
         QByteArray bytes = reply->readAll();  // 接受
         //QString string(bytes); // string
         QString string = QString::fromUtf8(bytes);
         if(string == "true")
            {
                ChatStart();      
            }
         else
         {
             //QTextCodec::setCodecForTr( QTextCodec::codecForName("GBK") );
                    QMessageBox::warning(this,tr("警告"),tr("用户名或密码错误!"),QMessageBox::Yes);
                    this->ui->lineEdit->clear();
                    this->ui->lineEdit_2->clear();
                    this->ui->lineEdit->setFocus();
         }
         //ui->textEdit->setText(string);
     }
     // Some http error received
     else
     {
         // handle errors here
     }
     // We receive ownership of the reply object
     // and therefore need to handle deletion.
     reply->deleteLater();
}
void Login::on_pushButton_clicked()
{

   // QUrl url("http://172.22.1.1/2.php");//待获取的网页
   //  QUrl url("http://172.22.1.1/accept.php");//待获取的网页
     //request = new QNetworkRequest();
    // request->setHeader(QNetworkRequest::UserAgentHeader,"Mozilla/5.0 (Macintosh;");
   //  request->setHeader();
     //request->setHeader( QNetworkRequest::ContentTypeHeader, "some/type" );
     request->setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

     //request->setUrl(QUrl("http://172.22.1.1/validate.php"));//树莓派上的
     request->setUrl(QUrl("http://123.207.251.200/validate.php")); //yunhu腾讯云

     //request->setUrl(QUrl("http://123.206.186.185/validate.php")); //leyiweb腾讯云


     user = ui->lineEdit->text();//获取到username
    QString pass = ui->lineEdit_2->text();//获取到password

    QString str = "username=" + user + "&password=" + pass;
    qDebug() << str;
    //qDebug() <<user;

    QByteArray postData;
    postData.append(str);
     reply = manager->post(*request, postData);
    /*if()
    {
       // accept();
        //manager->get(QNetworkRequest(QUrl("http://172.22.1.1/register.html")));//请求结果
    }*/
    /*else
    {
       // QTextCodec::setCodecForTr( QTextCodec::codecForName("GBK") );
        QMessageBox::warning(this,tr("警告"),tr("用户名或密码错误!"),QMessageBox::Yes);
        this->ui->lineEdit->clear();
        this->ui->lineEdit_2->clear();
        this->ui->lineEdit->setFocus();
    }*/

}

void Login::on_pushButton_2_clicked()//注册
{
   // QDesktopServices::openUrl(QUrl(QLatin1String("http://172.22.1.1/register.html")));//树莓派注册
    //QDesktopServices::openUrl(QUrl(QLatin1String("http://123.206.186.185/register.html")));//leyiweb腾讯云注册
    QDesktopServices::openUrl(QUrl(QLatin1String("http://123.207.251.200/register.html")));//yunhu腾讯云注册


    //QDesktopServices::openUrl(QUrl(QLatin1String("http://zhihu.com“)));
}
void Login::ChatStart()
{
    man->ChatStart();
}


