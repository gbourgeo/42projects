#include "GraphDisplay.hpp"
#include "ui_GraphDisplay.h"

GraphDisplay::GraphDisplay(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GraphDisplay)
{
    ui->setupUi(this);
}

GraphDisplay::~GraphDisplay()
{
    delete ui;
}
