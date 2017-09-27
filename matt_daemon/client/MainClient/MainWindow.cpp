#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textBrowser->setStyleSheet("background-color: lightgrey; border: none;");
    QObject::connect(ui->ConnectButton, SIGNAL(released()), this, SLOT(connectClient(void)));
    QObject::connect(ui->QuitButton, SIGNAL(released()), this, SLOT(quitClient(void)));
    QObject::connect(ui->SendButton, SIGNAL(released()), this, SLOT(sendText(void)));
    ui->sendField->installEventFilter(this);
    ui->addressField->installEventFilter(this);
    ui->portField->installEventFilter(this);
    ui->QuitButton->setEnabled(false);
    ui->SendButton->setEnabled(false);

    this->socket = new QTcpSocket(this);
    connect(socket, SIGNAL(connected()), this, SLOT(sockConnected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(sockDisconnected()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(sockError(QAbstractSocket::SocketError)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == ui->sendField || watched == ui->addressField || watched == ui->portField) {
        if (event->type() == QEvent::KeyPress) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
            if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter) {
                if (watched == ui->sendField)
                    MainWindow::sendText();
                else
                    MainWindow::connectClient();
                return (true);
            }
        }
        return (false);
    }
    return QMainWindow::eventFilter(watched, event);
}

void MainWindow::connectClient()
{
    QString         addr = ui->addressField->text();
    QString         port = ui->portField->text();

    if (addr == NULL) {
        ui->addressField->setStyleSheet("background-color: red;");
        return ui->textBrowser->setText("<center>Address missing.</center>");
    }
    ui->addressField->setStyleSheet("background-color: white;");
    if (port == NULL) {
        ui->portField->setStyleSheet("background-color: red;");
        return ui->textBrowser->setText("<center>Port missing.</center>");
    }
    ui->portField->setStyleSheet("background-color: white;");
    ui->textBrowser->setText("<center>Establishing connection...\n</center>");
    ui->ConnectButton->setEnabled(false);
    this->socket->abort();
    this->socket->connectToHost(addr, port.toUShort(NULL, 10));
}

void MainWindow::quitClient()
{
    this->socket->disconnectFromHost();
//    MainWindow::sockDisconnected();
}

void MainWindow::sockConnected()
{
    ui->textBrowser->setText("<center>~ Connected ~</center>");
    ui->QuitButton->setEnabled(true);
    ui->SendButton->setEnabled(true);
}

void MainWindow::sockDisconnected()
{
    ui->textBrowser->append("<center>~ Disconnected ~</center>");
    ui->ConnectButton->setEnabled(true);
    ui->QuitButton->setEnabled(false);
    ui->SendButton->setEnabled(false);
}

void MainWindow::sockError(QAbstractSocket::SocketError erreur)
{
    switch (erreur)
    {
        case QAbstractSocket::HostNotFoundError:
            ui->textBrowser->append("<center>Can't establish connection to server.</center>");
            break ;
        case QAbstractSocket::ConnectionRefusedError:
            ui->textBrowser->append("<center>Server refused the connection.</center>");
            break ;
        case QAbstractSocket::RemoteHostClosedError:
            ui->textBrowser->append("<center>Server closed the connection.</center>");
            break ;
        default:
            ui->textBrowser->append(tr("<center>") + this->socket->errorString() + tr("</center>"));
    }
    ui->ConnectButton->setEnabled(true);
    ui->QuitButton->setEnabled(false);
    ui->SendButton->setEnabled(false);
}

void MainWindow::sendText()
{
    QByteArray  packet;
    QDataStream out(&packet, QIODevice::WriteOnly);
    QString     message = ui->sendField->toPlainText();

    if (!this->socket->isOpen() || message == NULL)
        return ;
    out << (quint16) 0;
    out << message;
    out.device()->seek(0);
    out << (quint16)(packet.size() - sizeof(quint16));
    this->socket->write(packet);
    ui->textBrowser->append(message);
    ui->sendField->clear();
}
