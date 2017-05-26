#ifndef MAP_H
#define MAP_H

#include <iostream>
#include "Cell.h"
#include "Parameters.h"

class Map {

public:

    explicit Map(int complexity);

    bool isBomb(int row, int column);

    void updateCell(int row, int column);

    bool getUserTag(int row, int column);

    bool getShowToUser(int row, int column);

    int getNumberOfBombs(int row, int column);

    ~Map();

private:

    Cell **cells;
    int rows, columns;

    void generateMap(int numberOfBombs);

    int countNumberOfBombs(int row, int column);

    std::pair<int,int> *getCellsForBombs(int numberOfBombs);

};

#endif
