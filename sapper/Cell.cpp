#include "Cell.h"

Cell::Cell() : numberOfBombs(0), userTag(false), showToUser(false), isBomb(false) { }

int Cell::getNumberOfBombs() {
    return numberOfBombs;
}

void Cell::setNumberOfBombs(int numberOfBombs) {
    this->numberOfBombs = numberOfBombs;
}

void Cell::changeUserTag() {
    userTag = !userTag;
}

bool Cell::getUserTag() {
    return userTag;
}

void Cell::changeShowToUser() {
    showToUser = !showToUser;
}

bool Cell::getShowToUser() {
    return showToUser;
}

void Cell::setIsBomb(bool isBomb) {
    this->isBomb = isBomb;
}

bool Cell::getIsBomb() {
    return isBomb;
}
