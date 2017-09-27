#include "MainWindow.hpp"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textBrowser->setStyleSheet("background-color: lightgray; border: none;");

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
}

MainWindow::~MainWindow()
{
    delete this->socket;
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
                else if (!this->socket->isOpen())
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
}

void MainWindow::sockConnected()
{
    ui->textBrowser->setStyleSheet("background-color: none; border=1px");
    ui->textBrowser->setText(tr("--Connected to ") + ui->addressField->text() + tr(":") + ui->portField->text() + tr("--\n"));
    ui->QuitButton->setEnabled(true);
    ui->SendButton->setEnabled(true);
}

void MainWindow::sockDisconnected()
{
    ui->textBrowser->setStyleSheet("background-color: lightgray; border= none");
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
            ui->textBrowser->append("<center>~ Address not found ~</center>");
            break ;
        case QAbstractSocket::ConnectionRefusedError:
            ui->textBrowser->append("<center>~ Connection refused ~</center>");
            break ;
        case QAbstractSocket::RemoteHostClosedError:
            ui->textBrowser->append("<center>~ Connection closed ~</center>");
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
    QByteArray      message = ui->sendField->toPlainText().toUtf8();
    int             len = ui->sendField->toPlainText().size();

    if (!this->socket->isOpen() || message.isEmpty() || message.isNull())
        return ;
    message.insert(len, '\0');
    this->socket->write(message.data());
    this->socket->waitForBytesWritten(1000);
    ui->textBrowser->append(message);
    ui->sendField->clear();
}
