#ifndef PLOTWINDOW_H
#define PLOTWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>

namespace Ui {
class PlotWindow;
}

class PlotWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PlotWindow(QWidget *parent = 0);
    ~PlotWindow();

private slots:
    // default signal -> default slot
    void on_randomButton_clicked();

    // default signal -> custom slot
    // 1. implement SlotTest
    // 2. connect to a signal
    void SlotTest();

    void AddPoint();

    void PointClickedSlot(int x, int y);

private:
    Ui::PlotWindow *ui;

    QGraphicsScene *scene;

    static int random_clicks_;
};

#endif // PLOTWINDOW_H
