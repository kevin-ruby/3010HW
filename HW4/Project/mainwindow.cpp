#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cell.h"

#include <iostream>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>

#include <stdlib.h>
#include <time.h>
#include <QTimer>


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::TakeTurn()
{
    //Only do if current turn is < max turn defined by user
    if (turn_ < max_turn_)
    {
        //Colors of cells
        QColor red(Qt::red); //Alive
        QColor white(Qt::white); //Dead

        turn_++; //Add one to the value of turn

        //Update label
        ui->TurnLabel->setText(QString("Turn: ") + QString::number(turn_));

        //Will be a 2D vector which will be the next turn
        vector<vector<Cell*>> to_update = g.getCellGrid();

        //Each cell's alive neighbors
        int aliveNeighbors = 0;

        int count= 0;
        int add = 0;
        //Rows...
        for (int i = 0; i < 10; i++)
        {
            //Columns...
            for (int j = 0; j < 20; j++)
            {
              //Cell is equal to the current cell we are on in cell grid
              Cell* tmp = to_update[i][j];
              aliveNeighbors = g.checkAliveAround(tmp);

              //If cell is alive...
              if (tmp->get_alive() == true)
              {
                  //Kill it next turn
                  if (aliveNeighbors < 2)
                  {
                    tmp->setNextAlive(false);
                    tmp->setColor(white);
                    to_update[i][j] = tmp;
                  }
                  //Stays a live next turn
                  if (aliveNeighbors ==2 || aliveNeighbors == 3)
                  {
                    continue;
                  }
                  //Kill it next turn
                  if (aliveNeighbors > 3 )
                  {
                      tmp->setNextAlive(false);
                      tmp->setColor(white);
                      to_update[i][j] = tmp;
                  }
              }
              //If cell is dead...
              else
              {
                  //Becomes alive
                  if (aliveNeighbors == 3 )
                  {
                      tmp->setNextAlive(true);
                      tmp->setColor(red);
                      to_update[i][j] = tmp;
                  }
              }
            }
        }

        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 20; j++)
            {
                bool set_cell_state = to_update[i][j]->get_alive_next();
                to_update[i][j]->setAlive(set_cell_state);
            }
        }


        //qDebug() << checkPopulation();
        currentPopulation_ = checkPopulation();
        makeBarChart();
        g.setCellGrid(to_update);
        ui->PopLabel->setText(QString("Population: ") + QString::number(currentPopulation_) + QString(" (") + QString::number((currentPopulation_ * 100) / 200) + QString("%)"));

        cellScene_->update();
    }
}

void MainWindow::onSpeedSliderSliderMoved(int position)
{
        //qDebug() << "Slider Moved";
        speed_ = 1-(position / 100.0);
        ui->SpeeLabel->setText(QString("Speed: ") + QString::number(speed_, 'f', 6));
        //qDebug() << speed_;
}

void MainWindow::onStepButtonClicked()
{
    //qDebug() << "step pressed!";
    TakeTurn();
}

void MainWindow::onPlayButtonClicked()
{
    TakeTurn();
    timer_->start(speed_ * 1000);
}

void MainWindow::onPauseButtonClicked()
{
    timer_->stop();
}

void MainWindow::makeBarChart()
{

    //qDebug() << currentPopulation_;
    QPen outlinePen(Qt::white);

    if (bars_[19] != 0.0)
    {
        barScene_->clear();
        barScene_->update();
        for (int i = 0; i < 19; i++)
        {
            bars_[i] = bars_[i+1];
            barScene_->addRect(i*(bw_/20), (bh_)*(1-(bars_[i])), bw_/20 , bh_,outlinePen);
        }
        bars_[19] = currentPopulation_/200.0;
        barScene_->addRect(19*(bw_/20), (bh_)*(1-(bars_[19])), bw_/20 , bh_);

        return;
    }

    for (int i = 0; i < 20; i++)
    {
        if (bars_[i] == 0.0)
        {
            bars_[i] = currentPopulation_ / 200.0;
            barScene_->addRect(i * (bw_ / 20), (bh_) * (1-(bars_[i])), bw_ / 20 , bh_,outlinePen);

            return;
        }
    }
}

int MainWindow::checkPopulation()
{
    vector<vector<Cell *>> tmp = g.getCellGrid();
    int count = 0;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            Cell* c = tmp[i][j];
            if (c->get_alive() == true)
            {
                count++;
            }
        }
    }

    return count;
}

void MainWindow::LeftClickSlot(Cell* click)
{
    //qDebug() << "LEFT CLICK !";

    click->setAlive(true);
    cellScene_->update();
    currentPopulation_ =  checkPopulation();
    ui->PopLabel->setText(QString("Population: ") + QString::number(currentPopulation_) + QString(" (") + QString::number((currentPopulation_ * 100) / 200) + QString("%)"));
}

void MainWindow::RightClickSlot(Cell *click)
{
    //qDebug() << "RIGHT CLICK !";
    click->setAlive(false);
    cellScene_->update();
    currentPopulation_ =  checkPopulation();
    ui->PopLabel->setText(QString("Population: ") + QString::number(currentPopulation_) + QString(" (") + QString::number((currentPopulation_ * 100) / 200) + QString("%)"));
}

void MainWindow::onResetButtonClicked()
{
    //First clear the board and stop the timer then set turns to 0
    cellScene_->clear();
    timer_->stop();
    turn_ = 0;

    //Call the makeWindow function
    makeWindow();
}

void MainWindow::onMaxTurnsValueChanged(int input)
{
    //qDebug() << "GETTING SIGNAL";

    //Sets a max range, here is [0, INT_MAX]
    ui->MaxTurns->setRange(0, INT_MAX);

    max_turn_ = input;
}

//Makes the whole window
void MainWindow::makeWindow()
{
    //Need to set up the ui before we draw on our scene
    ui->setupUi(this);

    //for CELLS scene
    cellScene_ = new QGraphicsScene;
    QGraphicsView* cellView = ui->cellView;
    cellView->setScene(cellScene_);
    cellView->setSceneRect(0,0,cellView->frameSize().width()-20,cellView->frameSize().height()-20);


    //for BAR GRAPH
    barScene_ = new QGraphicsScene;
    QGraphicsView* barView = ui->graphCell;
    barView->setScene(barScene_);
    int barHeight_ = barView->frameSize().height() - 20;
    int barWidth_ = barView->frameSize().width() - 20;
    bh_ = barHeight_;
    bw_ = barWidth_;
    barView->setSceneRect(0,0,barWidth_,barHeight_);

    //initialize the bar array to zero
    for (int i = 0 ; i < 20;i++)
    {
        bars_[i]=0.0;
    }




    g = Grid(cellScene_, cellView);
    currentPopulation_ = g.getPopulation();
    makeBarChart();


    //connect left click feature to all cells ???********NEEDS TO CHANGE to correct LC feature ************
    vector<vector<Cell*>>  tmp = g.getCellGrid();
    for (vector<Cell*> v : tmp)
    {
        for (Cell* c : v)
        {
            connect(c, &Cell::LeftClick, this, &MainWindow::LeftClickSlot);
            connect(c, &Cell::RightClick, this, &MainWindow::RightClickSlot);
        }
    }

    //Connecting the signals and the slots
    connect(ui->StepButton, &QAbstractButton::clicked, this, &MainWindow::onStepButtonClicked);
    connect(ui->PlayButton, &QAbstractButton::clicked, this, &MainWindow::onPlayButtonClicked);
    connect(ui->PauseButton, &QAbstractButton::clicked, this, &MainWindow::onPauseButtonClicked);
    connect(ui->ResetButton, &QAbstractButton::clicked, this, &MainWindow::onResetButtonClicked);
    connect(ui->SpeedSlider, &QSlider::valueChanged, this, &MainWindow::onSpeedSliderSliderMoved);

    //connect(ui->MaxTurns, &QSpinBox::setValue, this, &MainWindow::onMaxTurnsValueChanged);
    connect(ui->MaxTurns, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::onMaxTurnsValueChanged);

    //update labels
    ui->TurnLabel->setText(QString("Turn: 0"));

    ui->PopLabel->setText(QString("Population: ") + QString::number(currentPopulation_) + QString(" (") + QString::number((currentPopulation_*100)/200) + QString("%)"));


    //for play button..
    srand(time(0));
    speed_ = 1.0;
    timer_ = new QTimer;
    connect(timer_, SIGNAL(timeout()), this, SLOT(onPlayButtonClicked()));

    //Will update the baord
    cellScene_->update();
}

//Constructor
MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    turn_ = 0;
    max_turn_ = INT_MAX; //Initialize to a very large number
    makeWindow();
}
