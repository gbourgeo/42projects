#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QKeyEvent>
#include <QTcpSocket>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    bool    eventFilter(QObject *watched, QEvent *event);

private slots:
    void    connectClient();
    void    quitClient();
    void    sockConnected();
    void    sockDisconnected();
    void    sockError(QAbstractSocket::SocketError erreur);
    void    sendText();

private:
    Ui::MainWindow  *ui;
    QTcpSocket      *socket;
};

#endif // MAINWINDOW_HPP
