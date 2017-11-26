#ifndef BENWINDOW_HPP
#define BENWINDOW_HPP

#include <QMainWindow>
#include <QKeyEvent>
#include <QTcpSocket>
#include <QDataStream>
#include "../Common/common.hpp"

#define BEN_HIST_SIZE   50

namespace Ui {
class BenWindow;
}

typedef struct      s_hist
{
    struct s_hist   *prev;
    QByteArray      data;
    struct s_hist   *next;
}                   t_hist;

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
    QFile           hist_fd;
    t_hist          *hist;
    t_hist          *head;
    t_hist          *tail;
    size_t          hist_size;

    void   AddToHist(QByteArray &message);
    size_t mystrlen(char *buff);
};

#endif // BENWINDOW_HPP
