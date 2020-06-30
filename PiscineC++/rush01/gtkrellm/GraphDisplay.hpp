#ifndef GRAPHDISPLAY_HPP
#define GRAPHDISPLAY_HPP

#include <QMainWindow>

namespace Ui {
class GraphDisplay;
}

class GraphDisplay : public QMainWindow
{
    Q_OBJECT

public:
    explicit GraphDisplay(QWidget *parent = 0);
    ~GraphDisplay();

private:
    Ui::GraphDisplay *ui;
};

#endif // GRAPHDISPLAY_HPP
