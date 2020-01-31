#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsScene>
#include <QMainWindow>
#include <cell.h>

#include "grid.h"

namespace Ui
{
class MainWindow;
}

//Subclass of QMainWindow
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow(); //Deconstructor

    void TakeTurn(); //Changes state of grid and bar chart after each turn
    void makeBarChart(); //Makes the bar chart
    int checkPopulation(); //Sums the total pop
    void makeWindow(); //Helper function to make everything the user sees

//Left and right click
public slots:
    void LeftClickSlot(Cell* click);
    void RightClickSlot(Cell * click);

//Different components
private:
    Ui::MainWindow* ui;
    QGraphicsScene* cellScene_;
    QGraphicsScene* barScene_;


    Grid g; //Makes an instance of the board with pointers scene and view
    int turn_; //Turn we are on
    int max_turn_; //Input entered field which determines the number of max turns
    int currentPopulation_;
    QTimer* timer_;
    double speed_;
    double bars_[20];
    int bh_;
    int bw_;

//SLOTS
private slots:
    void onSpeedSliderSliderMoved(int position);
    void onStepButtonClicked();
    void onPlayButtonClicked();
    void onPauseButtonClicked();
    void onResetButtonClicked();
    void onMaxTurnsValueChanged(int input);
};

#endif
