#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	/* Configure our Window */
	this->setWindowTitle("ft_gtkrellm");
	ui->logBrowser->setStyleSheet("background-color:lightgray; border:none;");
	ui->textBrowser->setStyleSheet("background-color:lightgray; border:none;");
}

MainWindow::~MainWindow()
{
    delete ui;
}
