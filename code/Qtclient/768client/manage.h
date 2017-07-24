#ifndef MANAGE_H
#define MANAGE_H

#include <QObject>
//extern QString user;
class Login;
class MainWindow;
class Manage
{
public:
    Manage();

public slots:
    void ChatStart();//开启聊天界面
    void BackToLog();//返回登录界面
    //void gameExit();
private:
    Login *log;
    MainWindow *chat;
};

#endif // MANAGE_H
