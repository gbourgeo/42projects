/********************************************************************************
** Form generated from reading UI file 'benWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BENWINDOW_H
#define UI_BENWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BenWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *addressLayout;
    QLabel *addressLabel;
    QLineEdit *addressField;
    QPushButton *ConnectButton;
    QHBoxLayout *portLayout;
    QLabel *portLabel;
    QSpinBox *portField;
    QSpacerItem *spacer;
    QPushButton *QuitButton;
    QHBoxLayout *textLayout;
    QTextBrowser *textBrowser;
    QTextBrowser *logBrowser;
    QHBoxLayout *clearLayout;
    QLabel *clearTextLabel;
    QSpacerItem *horizontalSpacer;
    QLabel *clearLogLabel;
    QHBoxLayout *sendLayout;
    QTextEdit *sendField;
    QPushButton *SendButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *BenWindow)
    {
        if (BenWindow->objectName().isEmpty())
            BenWindow->setObjectName(QStringLiteral("BenWindow"));
        BenWindow->setWindowModality(Qt::WindowModal);
        BenWindow->setEnabled(true);
        BenWindow->resize(800, 600);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(BenWindow->sizePolicy().hasHeightForWidth());
        BenWindow->setSizePolicy(sizePolicy);
        BenWindow->setMinimumSize(QSize(800, 600));
        BenWindow->setMaximumSize(QSize(800, 600));
        BenWindow->setLayoutDirection(Qt::LeftToRight);
        BenWindow->setIconSize(QSize(24, 24));
        centralWidget = new QWidget(BenWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        centralWidget->setMinimumSize(QSize(800, 542));
        centralWidget->setMaximumSize(QSize(800, 542));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(3);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMinimumSize);
        verticalLayout->setContentsMargins(3, 3, 3, 3);
        addressLayout = new QHBoxLayout();
        addressLayout->setSpacing(6);
        addressLayout->setObjectName(QStringLiteral("addressLayout"));
        addressLayout->setSizeConstraint(QLayout::SetFixedSize);
        addressLabel = new QLabel(centralWidget);
        addressLabel->setObjectName(QStringLiteral("addressLabel"));
        addressLabel->setMinimumSize(QSize(0, 0));

        addressLayout->addWidget(addressLabel);

        addressField = new QLineEdit(centralWidget);
        addressField->setObjectName(QStringLiteral("addressField"));

        addressLayout->addWidget(addressField);

        ConnectButton = new QPushButton(centralWidget);
        ConnectButton->setObjectName(QStringLiteral("ConnectButton"));

        addressLayout->addWidget(ConnectButton);


        verticalLayout->addLayout(addressLayout);

        portLayout = new QHBoxLayout();
        portLayout->setSpacing(6);
        portLayout->setObjectName(QStringLiteral("portLayout"));
        portLabel = new QLabel(centralWidget);
        portLabel->setObjectName(QStringLiteral("portLabel"));

        portLayout->addWidget(portLabel);

        portField = new QSpinBox(centralWidget);
        portField->setObjectName(QStringLiteral("portField"));
        portField->setMinimumSize(QSize(80, 0));
        portField->setMinimum(1);
        portField->setMaximum(65536);
        portField->setValue(4242);

        portLayout->addWidget(portField);

        spacer = new QSpacerItem(10, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        portLayout->addItem(spacer);

        QuitButton = new QPushButton(centralWidget);
        QuitButton->setObjectName(QStringLiteral("QuitButton"));

        portLayout->addWidget(QuitButton);


        verticalLayout->addLayout(portLayout);

        textLayout = new QHBoxLayout();
        textLayout->setSpacing(6);
        textLayout->setObjectName(QStringLiteral("textLayout"));
        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setMinimumSize(QSize(0, 350));

        textLayout->addWidget(textBrowser);

        logBrowser = new QTextBrowser(centralWidget);
        logBrowser->setObjectName(QStringLiteral("logBrowser"));
        logBrowser->setMinimumSize(QSize(500, 350));

        textLayout->addWidget(logBrowser);


        verticalLayout->addLayout(textLayout);

        clearLayout = new QHBoxLayout();
        clearLayout->setSpacing(6);
        clearLayout->setObjectName(QStringLiteral("clearLayout"));
        clearTextLabel = new QLabel(centralWidget);
        clearTextLabel->setObjectName(QStringLiteral("clearTextLabel"));

        clearLayout->addWidget(clearTextLabel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        clearLayout->addItem(horizontalSpacer);

        clearLogLabel = new QLabel(centralWidget);
        clearLogLabel->setObjectName(QStringLiteral("clearLogLabel"));

        clearLayout->addWidget(clearLogLabel);


        verticalLayout->addLayout(clearLayout);

        sendLayout = new QHBoxLayout();
        sendLayout->setSpacing(6);
        sendLayout->setObjectName(QStringLiteral("sendLayout"));
        sendField = new QTextEdit(centralWidget);
        sendField->setObjectName(QStringLiteral("sendField"));
        sendField->setMinimumSize(QSize(500, 100));
        sendField->setMaximumSize(QSize(700, 100));

        sendLayout->addWidget(sendField);

        SendButton = new QPushButton(centralWidget);
        SendButton->setObjectName(QStringLiteral("SendButton"));
        SendButton->setMinimumSize(QSize(0, 100));

        sendLayout->addWidget(SendButton);


        verticalLayout->addLayout(sendLayout);

        BenWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(BenWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 19));
        BenWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(BenWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        mainToolBar->setEnabled(false);
        BenWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(BenWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        BenWindow->setStatusBar(statusBar);

        retranslateUi(BenWindow);
        QObject::connect(SendButton, SIGNAL(clicked()), sendField, SLOT(clear()));

        QMetaObject::connectSlotsByName(BenWindow);
    } // setupUi

    void retranslateUi(QMainWindow *BenWindow)
    {
        BenWindow->setWindowTitle(QApplication::translate("BenWindow", "MainWindow", Q_NULLPTR));
        addressLabel->setText(QApplication::translate("BenWindow", "Address :", Q_NULLPTR));
        addressField->setText(QApplication::translate("BenWindow", "localhost", Q_NULLPTR));
        ConnectButton->setText(QApplication::translate("BenWindow", "Connect", Q_NULLPTR));
        portLabel->setText(QApplication::translate("BenWindow", "Port       :", Q_NULLPTR));
        QuitButton->setText(QApplication::translate("BenWindow", "Quit", Q_NULLPTR));
        clearTextLabel->setText(QApplication::translate("BenWindow", "clear", Q_NULLPTR));
        clearLogLabel->setText(QApplication::translate("BenWindow", "clear", Q_NULLPTR));
        SendButton->setText(QApplication::translate("BenWindow", "Send", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class BenWindow: public Ui_BenWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BENWINDOW_H
