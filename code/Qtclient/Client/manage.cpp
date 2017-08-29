#include "manage.h"
#include"login.h"
#include"mainwindow.h"
//user = "";
Manage::Manage()//登录界面显示，聊天界面关闭
{
    log = new Login( NULL,this);
    chat = new MainWindow(NULL,this);
   // log->show();
   // chat->hide();
    //测试
    log->hide();
    chat->show();
}
void Manage::ChatStart()//开启聊天
{
    log->hide();
    chat->show();
}

void Manage::BackToLog()//返回登录界面
{
    chat->hide();
    log->show();
}
