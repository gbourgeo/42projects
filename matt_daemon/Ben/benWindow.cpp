#include "benWindow.hpp"
#include "ui_benWindow.h"

BenWindow::BenWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BenWindow)
{
    ui->setupUi(this);

    /* Configure our Window */
    this->setWindowTitle("Ben_AFK");
    ui->logBrowser->setStyleSheet("background-color:lightgray; border:none;");
    ui->textBrowser->setStyleSheet("background-color:lightgray; border:none;");

    /* Configure the 'clear' Labels to be clickable */
    ui->clearLogLabel->setText("<a href=\"clear logs\">clear</a>");
    ui->clearLogLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
    ui->clearTextLabel->setText("<a href=\"clear text\">clear</a>");
    ui->clearTextLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);

    /* Connect the buttons to their appropriate fields */
    QObject::connect(ui->ConnectButton, SIGNAL(released()), this, SLOT(connectClient(void)));
    QObject::connect(ui->QuitButton, SIGNAL(released()), this, SLOT(quitClient(void)));
    QObject::connect(ui->SendButton, SIGNAL(released()), this, SLOT(sendText(void)));
    QObject::connect(ui->clearTextLabel, SIGNAL(linkActivated(QString)), this, SLOT(clearText()));
    QObject::connect(ui->clearLogLabel, SIGNAL(linkActivated(QString)), this, SLOT(clearLog()));

    /* Event filter for Address, Port and Text field when the user press Enter */
    ui->sendField->installEventFilter(this);
    ui->addressField->installEventFilter(this);
    ui->portField->installEventFilter(this);

    ui->QuitButton->setEnabled(false);
    ui->SendButton->setEnabled(false);

    /* Create and Configure the socket */
    this->socket = new QTcpSocket(this);
    connect(socket, SIGNAL(connected()), this, SLOT(sockConnected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(sockDisconnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(sockRead()));
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
                if (this->socket->state() == QAbstractSocket::UnconnectedState)
                    BenWindow::connectClient();
                else if (watched == ui->sendField)
                    BenWindow::sendText();
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
    this->socket->waitForConnected(5000);
}

void BenWindow::quitClient()
{
    this->socket->disconnectFromHost();
}

void BenWindow::sockConnected()
{
    ui->logBrowser->setStyleSheet("background-color:none; border=5px");
    ui->textBrowser->setStyleSheet("background-color:none; border=5px");
    ui->statusBar->showMessage(tr("-- Connected to ") + ui->addressField->text() + tr(":") + ui->portField->text() + tr(" --"));
    ui->QuitButton->setEnabled(true);
    ui->SendButton->setEnabled(true);
}

void BenWindow::sockDisconnected()
{
    ui->textBrowser->setStyleSheet("background-color:lightgray; border=none");
    ui->logBrowser->setStyleSheet("background-color:lightgray; border=none");
    ui->statusBar->showMessage("-- Disconnected from server. --");
    ui->ConnectButton->setEnabled(true);
    ui->QuitButton->setEnabled(false);
    ui->SendButton->setEnabled(false);
}

void BenWindow::sockRead()
{
    QTextStream     data(this->socket);

    ui->logBrowser->clear();
    ui->logBrowser->append(data.readAll());
}

void BenWindow::sockError(QAbstractSocket::SocketError erreur)
{
    switch (erreur)
    {
        case QAbstractSocket::HostNotFoundError:
            ui->statusBar->showMessage("--ERROR: Address not found. --");
            break ;
        case QAbstractSocket::ConnectionRefusedError:
            ui->statusBar->showMessage("--ERROR: Connection refused. --");
            break ;
        case QAbstractSocket::RemoteHostClosedError:
            ui->statusBar->showMessage("--ERROR: Connection closed. --");
            break ;
        default:
            ui->statusBar->showMessage(tr("<center>-- ") + this->socket->errorString() + tr(" --</center>"));
    }
    ui->ConnectButton->setEnabled(true);
    ui->QuitButton->setEnabled(false);
    ui->SendButton->setEnabled(false);
}

void BenWindow::sendText()
{
    if (this->socket->state() == QAbstractSocket::ConnectedState) {

        QByteArray      message = ui->sendField->toPlainText().toUtf8();

        if (message.isEmpty() || message.isNull())
            return ;
        this->socket->write(message.data());
        this->socket->write("\n");
        this->socket->waitForBytesWritten(1000);
        ui->textBrowser->append(message);
        ui->sendField->clear();
    }
}

void BenWindow::clearText()
{
    ui->textBrowser->clear();
}

void BenWindow::clearLog()
{
    ui->logBrowser->clear();
}
