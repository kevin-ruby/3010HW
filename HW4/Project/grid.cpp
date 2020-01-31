#include "grid.h"

#include <stdlib.h>
#include <time.h>
#include <qDebug>
#include <QString>



//Constructor, randomely creates a grib of alive and dead cells
Grid::Grid(QGraphicsScene* scene, QGraphicsView* view)
{
    //Seeds it. Do once
    srand (time(NULL));

    int aliveProb = 0;

    total_population_ = 0;

    bool alive = false;
    bool next_alive = false;

    //Colors of cells
    QColor red(Qt::red); //Alive
    QColor white(Qt::white); //Dead

    //Will be the color of the cell I create
    QColor cell_color;



    //Traverses row
    for (int i = 0; i < 10; i++)
    {
        //Column
        vector<Cell*> temp_row;
        for (int j = 0; j < 20; j++)
        {

            aliveProb = rand() % 10; //Random number [0, 10]

            //Alive cell...
            if (aliveProb < 5)
            {
                cell_color = red;
                alive = true;
                total_population_++;
            }
            //Dead cell...
            else
            {
                cell_color = white;
                alive = false;
            }

            //Create a new cell
            Cell* newCell = new Cell(cell_color, j, i, alive, next_alive);

            //Add each new cell in row to remp_row
            temp_row.push_back(newCell);
            scene->addItem(newCell);
        }


        //Once its gone through the whole row, add to final cell_grid_
        cell_grid_.push_back(temp_row);
    }


}

int Grid::checkAliveAround(Cell* current_cell)
{
    int neighbor_alive = 0;

    int column = current_cell->get_x()/ 36;
    int row = current_cell->get_y()/ 30;

    vector<Cell*> vec;

    //look up
    int temp_row = (row == 0 ? 9 : row - 1);
    Cell* up = cell_grid_[temp_row][column];
    vec.push_back(up);

    //Look right
    int temp_column = (column == 19 ? 0 : column + 1);
    Cell* right = cell_grid_[row][temp_column];
    vec.push_back(right);

    //Look down
    temp_row = (row == 9 ? 0 : row + 1);
    Cell* down = cell_grid_[temp_row][column];
    vec.push_back(down);

    //Look left
    temp_column = column == 0 ? 19 : column - 1;
    Cell* left = cell_grid_[row][temp_column];
    vec.push_back(left);

    //Look diagonal left and up
    temp_column = column == 0 ? 19 : column - 1;
    temp_row = row == 0 ? 9: row - 1;
    Cell* dLeftUp = cell_grid_[temp_row][ temp_column];
    vec.push_back(dLeftUp);

    //Look diagonal right and up
    temp_column = column == 19 ? 0 : column + 1;
    temp_row = row == 0 ? 9 : row - 1;
    Cell* dRightUp = cell_grid_[temp_row][ temp_column];
    vec.push_back(dRightUp);

    //Look diagonal left and down
    temp_column= column == 0 ? 19 : column - 1;
    temp_row = row == 9 ? 0 : row + 1;
    Cell* dLeftDown = cell_grid_[temp_row][ temp_column];
    vec.push_back(dLeftDown);

    //Look diagonal right and down
    temp_column = column == 19 ? 0 : column + 1;
    temp_row = row == 9 ? 0 : row + 1;
    Cell* dRightDown = cell_grid_[temp_row][ temp_column];
    vec.push_back(dRightDown);


    //Vector of all neighbor cells
    for (int i = 0; i < vec.size(); i++)
    {
        Cell* tmp = vec[i];

        //If neighbors are alive...
        if (tmp->get_alive() == true)
        {
            //Increment count of alive neighbors
            neighbor_alive++;
        }
    }

    //Return total amount of live neighbors for each cell
    return neighbor_alive;

}
