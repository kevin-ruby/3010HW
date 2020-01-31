#ifndef GRID_H
#define GRID_H

#include "cell.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>
#include <vector>

using namespace std;


class Grid
{
public:
    //Constructor, on creation, will go through board and randomely create alive and dead cells
    Grid(QGraphicsScene* scene, QGraphicsView* view);

    //Defualt constructor
    Grid() {}

    //Alters the cell_grid_ 2D vector with the new values for the cells after applying the given algo
    //Takes input of current cell we are on in the map
    int checkAliveAround(Cell* current_cell);

    //Returns cell_gri_
    vector<vector<Cell*>> getCellGrid() {return cell_grid_;}

    //Returns the total population of the grid (count of alive cells)
    int getPopulation() {return total_population_;}

    //Sets cell_grid_ equal to input paramater
    void setCellGrid(vector<vector<Cell*>> cell_grid) {cell_grid_ = cell_grid;}

private:
    vector<vector<Cell*>> cell_grid_; //Is a 2D vector that will contain pointers of all the cells in the game
    int total_population_; //Holds the total population of the board
};

#endif // GRID_H
