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

    /* Historic search config */
    this->hist_size = 0;
    this->hist = new t_hist;
    this->hist->prev = nullptr;
    this->hist->data.clear();
    this->hist->next = nullptr;
    this->head = this->hist;
    this->tail = this->head;
    this->hist_fd.setFileName("/tmp/.Matt_hist");
    if (this->hist_fd.open(QIODevice::ReadWrite | QIODevice::Text)) {
        while (!this->hist_fd.atEnd() && this->hist_size < BEN_HIST_SIZE) {
            this->hist->data = this->hist_fd.readLine();
            if (this->hist->data.size() == 1)
                continue ;
            this->hist->data[this->hist->data.size() - 1] = '\0';
            this->hist = new t_hist;
            this->hist->prev = nullptr;
            this->hist->data.clear();
            this->hist->next = this->head;
            this->head->prev = this->hist;
            this->head = this->hist;
            this->hist_size++;
        }
    }
    /* Status Bar message */
    ui->statusBar->showMessage("Hello friend !");
}

BenWindow::~BenWindow()
{
    t_hist      *tmp;
    if (this->hist_fd.exists())
        this->hist_fd.remove();
    this->hist_fd.setFileName("/tmp/.Matt_hist");
    if (this->hist_fd.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QTextStream     histfile(&this->hist_fd);
        while (this->tail) {
            tmp = this->tail;
            if (this->tail->data.size() > 0)
                histfile << this->tail->data << "\n";
            this->tail = this->tail->prev;
            delete tmp;
        }
    }
    delete this->socket;
    delete ui;
}

bool    BenWindow::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == ui->addressField || watched == ui->portField) {
        if (event->type() == QEvent::KeyPress) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
            if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter) {
                if (this->socket->state() == QAbstractSocket::UnconnectedState)
                    BenWindow::connectClient();
                return (true);
            }
        }
        return (false);
    }
    if (watched == ui->sendField) {
        if (event->type() == QEvent::KeyPress) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
            if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter) {
                BenWindow::sendText();
                return (true);
            }
            if (keyEvent->key() == Qt::Key_Up) {
                if (this->head->next == nullptr)
                    return (true);
                this->head->data = ui->sendField->toPlainText().toUtf8();
                this->head = this->head->next;
                ui->sendField->clear();
                ui->sendField->append(this->head->data);
                return (true);
            }
            if (keyEvent->key() == Qt::Key_Down) {
                if (this->head->prev == nullptr)
                    return (true);
                this->head->data = ui->sendField->toPlainText().toUtf8();
                this->head = this->head->prev;
                ui->sendField->clear();
                ui->sendField->append(this->head->data);
                return (true);
            }
        }
        return (false);
    }
    return QMainWindow::eventFilter(watched, event);
}

void    BenWindow::connectClient()
{
    QString         addr = ui->addressField->text();
    QString         port = ui->portField->text();

    if (addr == nullptr) {
        ui->addressField->setStyleSheet("background-color:red;");
        return ui->statusBar->showMessage("ERROR: Address missing.");
    }
    ui->addressField->setStyleSheet("background-color:white;");
    if (port == nullptr) {
        ui->portField->setStyleSheet("background-color:red;");
        return ui->statusBar->showMessage("ERROR: Port missing.");
    }
    ui->portField->setStyleSheet("background-color:white;");
    ui->statusBar->showMessage("Establishing connection...");
    ui->ConnectButton->setEnabled(false);
    this->socket->abort();
    this->socket->connectToHost(addr, port.toUShort(nullptr, 10));
    this->socket->waitForConnected(5000);
}

void    BenWindow::quitClient()
{
    this->socket->disconnectFromHost();
}

void    BenWindow::sockConnected()
{
    ui->logBrowser->setStyleSheet("background-color:none; border=5px");
    ui->textBrowser->setStyleSheet("background-color:none; border=5px");
    ui->statusBar->showMessage(tr("-- Connected to ") + ui->addressField->text() + tr(":") + ui->portField->text() + tr(" --"));
    ui->QuitButton->setEnabled(true);
    ui->SendButton->setEnabled(true);
}

void    BenWindow::sockDisconnected()
{
    ui->textBrowser->setStyleSheet("background-color:lightgray; border=none");
    ui->logBrowser->setStyleSheet("background-color:lightgray; border=none");
    ui->statusBar->showMessage("-- Disconnected from server. --");
    ui->ConnectButton->setEnabled(true);
    ui->QuitButton->setEnabled(false);
    ui->SendButton->setEnabled(false);
}

void    BenWindow::sockRead()
{
    QDataStream rcv(this->socket);
    int         ret;
    QByteArray  data;

    do {
        ret = rcv.readRawData(reinterpret_cast<char *>(&this->hdr), sizeof(this->hdr));
        if (ret <= 0) {
            ui->logBrowser->append("Server disconnected.");
            QString msg = "Read ret: " + QString::number(ret) + "\n";
            msg += "Magic: " + QString::number(this->hdr.magic) + "\n";
            msg += "Crypted: " + QString::number(this->hdr.crypted) + "\n";
            msg += "Datalen: " + QString::number(this->hdr.datalen) + "\n";
            msg += "Data: " + QString(this->hdr.data);
            return ui->logBrowser->append(msg);
        }
        if (this->hdr.magic != DAEMON_MAGIC) {
            ui->logBrowser->append("Wrong Header received.");
            QString msg = "Read ret: " + QString::number(ret) + "\n";
            msg += "Magic: " + QString::number(this->hdr.magic) + "\n";
            msg += "Crypted: " + QString::number(this->hdr.crypted) + "\n";
            msg += "Datalen: " + QString::number(this->hdr.datalen) + "\n";
            msg += "Data: " + QString(this->hdr.data);
            return ui->logBrowser->append(msg);
        }
        data += this->hdr.data;
    } while (this->hdr.datalen > mystrlen(this->hdr.data));
    ui->logBrowser->clear();
    if (!this->hdr.crypted) {
        char     *decrypt = new char[Base64decode_len(data.data())];
        Base64decode(decrypt, data.data());
        ui->logBrowser->append(decrypt);
        delete [] decrypt;
    }
    else
        ui->logBrowser->append(data);
}

void    BenWindow::sockError(QAbstractSocket::SocketError erreur)
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

void    BenWindow::sendText()
{
    if (this->socket->state() == QAbstractSocket::ConnectedState) {

        QByteArray      message = ui->sendField->toPlainText().toUtf8();
        int             len = 0;

        if (message.isEmpty() || message.isNull())
            return ;
        BenWindow::AddToHist(message);
        ui->textBrowser->append(message);
        ui->sendField->clear();
        message.append('\n');
        if (!this->hdr.crypted) {
            int sendLen = Base64encode_len(message.length());
            char *tosend = new char[sendLen];
            Base64encode(tosend, message.data(), message.length());
            do {
                this->hdr.datalen = mystrlen(&tosend[len]);
                strncpy(this->hdr.data, &tosend[len], DAEMON_BUFF - 1);
                this->socket->write(reinterpret_cast<char *>(&this->hdr), sizeof(this->hdr));
                len += DAEMON_BUFF;
                this->socket->waitForBytesWritten();
            } while (sendLen > len);
            delete [] tosend;
        } else {
                this->socket->write(message, message.length());
                this->socket->waitForBytesWritten();
        }
    }
}

void    BenWindow::clearText()
{
    ui->textBrowser->clear();
}

void    BenWindow::clearLog()
{
    ui->logBrowser->clear();
}

void    BenWindow::AddToHist(QByteArray &message) {
    this->head = this->hist;
    if (this->hist->next && this->hist->next->data == message) {
        this->hist->data.clear();
        return ;
    }
    this->hist->data = message;
    this->hist = new t_hist;
    this->hist->prev = nullptr;
    this->hist->data.clear();
    this->hist->next = this->head;
    this->head->prev = this->hist;
    this->head = this->hist;
    if (this->hist_size >= BEN_HIST_SIZE) {
        this->tail = this->tail->prev;
        delete this->tail->next;
        this->tail->next = nullptr;
        return ;
    }
    this->hist_size++;
}

size_t  BenWindow::mystrlen(char *buff)
{
    char        *ptr = buff;

    if (!ptr)
        return 0;
    while (*ptr)
        ptr++;
    return static_cast<size_t>(ptr - buff);
}
