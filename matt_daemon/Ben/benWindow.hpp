#ifndef BENWINDOW_HPP
#define BENWINDOW_HPP

#include <QMainWindow>
#include <QKeyEvent>
#include <QTcpSocket>
#include <QDataStream>
#include "../Common/common.hpp"

namespace Ui {
class BenWindow;
}

class BenWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit BenWindow(QWidget *parent = 0);
    ~BenWindow();

protected:
    bool    eventFilter(QObject *watched, QEvent *event);

private slots:
    void    connectClient();
    void    quitClient();
    void    sockConnected();
    void    sockDisconnected();
    void    sockError(QAbstractSocket::SocketError erreur);
    void    sendText();
    void    sockRead();
    void    clearText();
    void    clearLog();

private:
    Ui::BenWindow   *ui;
    QTcpSocket      *socket;
    t_hdr           hdr;
};

#endif // BENWINDOW_HPP
