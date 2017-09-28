#ifndef BENWINDOW_HPP
#define BENWINDOW_HPP

#include <QMainWindow>
#include <QKeyEvent>
#include <QTcpSocket>

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

private:
    Ui::BenWindow   *ui;
    QTcpSocket      *socket;
};

#endif // BENWINDOW_HPP
