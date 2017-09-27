/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

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
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
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
    QLineEdit *portField;
    QPushButton *QuitButton;
    QTextBrowser *textBrowser;
    QHBoxLayout *sendTextLayout;
    QTextEdit *sendField;
    QPushButton *SendButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setWindowModality(Qt::WindowModal);
        MainWindow->setEnabled(true);
        MainWindow->resize(800, 600);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(800, 600));
        MainWindow->setMaximumSize(QSize(800, 600));
        MainWindow->setLayoutDirection(Qt::LeftToRight);
        MainWindow->setIconSize(QSize(24, 24));
        centralWidget = new QWidget(MainWindow);
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

        portField = new QLineEdit(centralWidget);
        portField->setObjectName(QStringLiteral("portField"));

        portLayout->addWidget(portField);

        QuitButton = new QPushButton(centralWidget);
        QuitButton->setObjectName(QStringLiteral("QuitButton"));

        portLayout->addWidget(QuitButton);


        verticalLayout->addLayout(portLayout);

        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setMinimumSize(QSize(0, 370));
        textBrowser->setAutoFillBackground(false);

        verticalLayout->addWidget(textBrowser);

        sendTextLayout = new QHBoxLayout();
        sendTextLayout->setSpacing(6);
        sendTextLayout->setObjectName(QStringLiteral("sendTextLayout"));
        sendField = new QTextEdit(centralWidget);
        sendField->setObjectName(QStringLiteral("sendField"));
        sendField->setMinimumSize(QSize(500, 100));
        sendField->setMaximumSize(QSize(700, 100));

        sendTextLayout->addWidget(sendField);

        SendButton = new QPushButton(centralWidget);
        SendButton->setObjectName(QStringLiteral("SendButton"));

        sendTextLayout->addWidget(SendButton);


        verticalLayout->addLayout(sendTextLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 19));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        mainToolBar->setEnabled(false);
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);
        QObject::connect(SendButton, SIGNAL(clicked()), sendField, SLOT(clear()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        addressLabel->setText(QApplication::translate("MainWindow", "Address :", Q_NULLPTR));
        ConnectButton->setText(QApplication::translate("MainWindow", "Connect", Q_NULLPTR));
        portLabel->setText(QApplication::translate("MainWindow", "Port       :", Q_NULLPTR));
        QuitButton->setText(QApplication::translate("MainWindow", "Quit", Q_NULLPTR));
        textBrowser->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", Q_NULLPTR));
        SendButton->setText(QApplication::translate("MainWindow", "Send", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
