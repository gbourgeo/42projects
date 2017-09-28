#include "benWindow.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BenWindow w;
    w.show();

    return a.exec();
}
