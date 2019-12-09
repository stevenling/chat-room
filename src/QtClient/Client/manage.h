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
    /// @brief 开启聊天界面
    void ChatStart();

    /// @brief 返回登录界面
    void BackToLog();
    
private:
    Login *log;
    MainWindow *chat;
};

#endif // MANAGE_H
