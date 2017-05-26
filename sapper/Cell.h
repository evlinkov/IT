#ifndef CELL_H
#define CELL_H

class Cell {

public:

    Cell();

    void setNumberOfBombs(int numberOfBombs);

    int getNumberOfBombs();

    void changeUserTag();

    bool getUserTag();

    void changeShowToUser();

    bool getShowToUser();

    void setIsBomb(bool isBomb);

    bool getIsBomb();

private:

    int numberOfBombs;
    bool userTag;
    bool showToUser;
    bool isBomb;

};

#endif
