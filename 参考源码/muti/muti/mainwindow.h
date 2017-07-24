#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork/QTcpSocket>
#include <QMainWindow>
#include <QtNetwork/QTcpSocket>
#include <sys/types.h>
#include <QThread>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void on_pushButton_clicked();
    void readClient();

    void on_senBtnMuti_clicked();

private:
    Ui::MainWindow *ui;
    QTcpSocket *client;
};

#endif // MAINWINDOW_H
