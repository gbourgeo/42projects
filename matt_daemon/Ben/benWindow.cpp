#include "benWindow.hpp"
#include "ui_benWindow.h"

BenWindow::BenWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BenWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Ben_AFK");
    ui->textBrowser->setStyleSheet("background-color:lightgray; border:none;");

    /* Connect the buttons to their appropriate fields */
    QObject::connect(ui->ConnectButton, SIGNAL(released()), this, SLOT(connectClient(void)));
    QObject::connect(ui->QuitButton, SIGNAL(released()), this, SLOT(quitClient(void)));
    QObject::connect(ui->SendButton, SIGNAL(released()), this, SLOT(sendText(void)));

    /* Event filter for Address, Port and Text field when the user press Enter */
    ui->sendField->installEventFilter(this);
    ui->addressField->installEventFilter(this);
    ui->portField->installEventFilter(this);

    ui->QuitButton->setEnabled(false);
    ui->SendButton->setEnabled(false);

    /* Configure the socket */
    this->socket = new QTcpSocket(this);
    connect(socket, SIGNAL(connected()), this, SLOT(sockConnected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(sockDisconnected()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(sockError(QAbstractSocket::SocketError)));

    /* Status Bar message */
    ui->statusBar->showMessage("Hello friend !");
}

BenWindow::~BenWindow()
{
    delete this->socket;
    delete ui;
}

bool BenWindow::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == ui->sendField || watched == ui->addressField || watched == ui->portField) {
        if (event->type() == QEvent::KeyPress) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
            if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter) {
                if (watched == ui->sendField)
                    BenWindow::sendText();
                else if (this->socket->state() == QAbstractSocket::UnconnectedState)
                    BenWindow::connectClient();
                return (true);
            }
        }
        return (false);
    }
    return QMainWindow::eventFilter(watched, event);
}

void BenWindow::connectClient()
{
    QString         addr = ui->addressField->text();
    QString         port = ui->portField->text();

    if (addr == NULL) {
        ui->addressField->setStyleSheet("background-color:red;");
        return ui->statusBar->showMessage("ERROR: Address missing.");
    }
    ui->addressField->setStyleSheet("background-color:white;");
    if (port == NULL) {
        ui->portField->setStyleSheet("background-color:red;");
        return ui->statusBar->showMessage("ERROR: Port missing.");
    }
    ui->portField->setStyleSheet("background-color:white;");
    ui->statusBar->showMessage("Establishing connection...");
    ui->ConnectButton->setEnabled(false);
    this->socket->abort();
    this->socket->connectToHost(addr, port.toUShort(NULL, 10));
}

void BenWindow::quitClient()
{
    this->socket->disconnectFromHost();
}

void BenWindow::sockConnected()
{
    ui->textBrowser->setStyleSheet("background-color:none; border=5px");
    ui->statusBar->showMessage(tr("-- Connected to ") + ui->addressField->text() + tr(":") + ui->portField->text());
    ui->QuitButton->setEnabled(true);
    ui->SendButton->setEnabled(true);
}

void BenWindow::sockDisconnected()
{
    ui->textBrowser->setStyleSheet("background-color:lightgray; border=none");
    ui->statusBar->showMessage("-- Disconnected from server --");
    ui->ConnectButton->setEnabled(true);
    ui->QuitButton->setEnabled(false);
    ui->SendButton->setEnabled(false);
}

void BenWindow::sockError(QAbstractSocket::SocketError erreur)
{
    switch (erreur)
    {
        case QAbstractSocket::HostNotFoundError:
            ui->statusBar->showMessage("ERROR: Address not found.");
            break ;
        case QAbstractSocket::ConnectionRefusedError:
            ui->statusBar->showMessage("ERROR: Connection refused.");
            break ;
        case QAbstractSocket::RemoteHostClosedError:
            ui->statusBar->showMessage("ERROR: Connection closed.");
            break ;
        default:
            ui->statusBar->showMessage(tr("<center>") + this->socket->errorString() + tr("</center>"));
    }
    ui->ConnectButton->setEnabled(true);
    ui->QuitButton->setEnabled(false);
    ui->SendButton->setEnabled(false);
}

void BenWindow::sendText()
{
    QByteArray      message = ui->sendField->toPlainText().toUtf8();

    if (!this->socket->isOpen() || message.isEmpty() || message.isNull())
        return ;
    this->socket->write(message.data());
    this->socket->waitForBytesWritten(1000);
    ui->textBrowser->append(message);
    ui->sendField->clear();
}
