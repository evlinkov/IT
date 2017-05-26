#include "Map.h"

Map::Map(int complexity) {
    if (complexity == 0) {
        // новичок
        rows = Parameters::DEFAULT_NOOB_MODE_ROWS;
        columns = Parameters::DEFAULT_NOOB_MODE_COLUMNS;
        generateMap(Parameters::DEFAULT_NOOB_MODE_BOMBS);
    }
    if (complexity == 1) {
        // любитель
        rows = Parameters::DEFAULT_AMATEUR_MODE_ROWS;
        columns = Parameters::DEFAULT_AMATEUR_MODE_COLUMNS;
        generateMap(Parameters::DEFAULT_AMATEUR_MODE_BOMBS);
    }
    if (complexity >= 2) {
        // профессионал
        rows = Parameters::DEFAULT_PROFESSIONAL_MODE_ROWS;
        columns = Parameters::DEFAULT_PROFESSIONAL_MODE_COLUMNS;
        generateMap(Parameters::DEFAULT_PROFESSIONAL_MODE_BOMBS);
    }
}

std::pair<int,int> *Map::getCellsForBombs(int numberOfBombs) {
    int *numbers = new int[rows * columns];
    for (int i = 0; i < rows * columns; ++i) {
        numbers[i] = i;
    }
    std::random_shuffle(numbers, numbers + rows * columns);
    std::pair<int,int> *cellsForBombs = new std::pair<int,int> [numberOfBombs];
    for (int bomb = 0; bomb < numberOfBombs; ++bomb) {
        std::pair<int,int> coordinates;
        // number = row * columns + column
        coordinates.first = numbers[bomb] / columns;
        coordinates.second = numbers[bomb] % columns;
        cellsForBombs[bomb] = coordinates;
    }
    return cellsForBombs;
};

bool Map::isBomb(int row, int column) {
    if (row < 0 || column < 0) {
        return false;
    }
    if (row == rows || column == columns) {
        return false;
    }
    return cells[row][column].getIsBomb();
}

bool Map::getShowToUser(int row, int column) {
    return cells[row][column].getShowToUser();
}

int Map::getNumberOfBombs(int row, int column) {
    return cells[row][column].getNumberOfBombs();
}

bool Map::getUserTag(int row, int column) {
    return cells[row][column].getUserTag();
}

int Map::countNumberOfBombs(int row, int column) {
    int answer = 0;
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx * dx + dy * dy != 0) {
                answer += isBomb(row + dx, column + dy);
            }
        }
    }
    return answer;
}

void Map::generateMap(int numberOfBombs) {
    cells = new Cell* [rows];
    for (int row = 0; row < rows; ++row) {
        cells[row] = new Cell[columns];
    }
    std::pair<int,int> *cellsForBombs = getCellsForBombs(numberOfBombs);
    for (int i = 0; i < numberOfBombs; ++i) {
        int row = cellsForBombs[i].first;
        int column = cellsForBombs[i].second;
        cells[row][column].setIsBomb(true);
    }
    for (int row = 0; row < rows; ++row) {
        for (int column = 0; column < columns; ++column) {
            cells[row][column].setNumberOfBombs(countNumberOfBombs(row, column));
        }
    }
}

void Map::updateCell(int row, int column) {
    if (!cells[row][column].getUserTag()) {
        cells[row][column].changeShowToUser();
    }
}

Map::~Map() {
    for (int row = 0; row < rows; ++row) {
        delete(cells[row]);
    }
    delete(cells);
}
