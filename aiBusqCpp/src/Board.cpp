//
// Created by pau on 27/10/21.
//

#include "Board.h"

Board::Board(int h, int w, int oC, int eC, int tC, float oRatio = 0.2) : MetaParameter(h, w, oC, eC, tC), obstacleRatio(oRatio) {
    // dynamically allocating row all rows as list's list
    array = new int*[w];
    // dynamically allocating a column for each row
    for(int i = 0; i < w; i++) {
        array[i] = new int[h];
    }
    redistributeObstaclesRandom();
}

Board::Board(MetaParameter &mP, float oRatio = 0.2): MetaParameter(mP), obstacleRatio(oRatio) {
    // dynamically allocating row all rows as list's list
    array = new int*[width];
    // dynamically allocating a column for each row
    for(int i = 0; i < width; i++) {
        array[i] = new int[height];
    }
    redistributeObstaclesRandom();
}



Board::~Board() {
    delete[] array;
}

void Board::printBoard() {
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            std::cout << array[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void Board::updateTaxiPosition() {

}

void Board::redistributeObstaclesRandom() {
    // resets array to all zero's
    setWholeBoardTo(0);
    // initialize the random generator
    std::uniform_int_distribution<int> distributionRow(0, getWidth() - 1);
    std::uniform_int_distribution<int> distributionColumn(0, getHeight() - 1);
    // calculate how many obstacles have to be placed into the array to satisfy the obstacle ratio
    int numberOfObstaclesWanted = floor((getHeight()*getWidth())*getObstacleRatio());
    int numberOfObstaclesPresent = 0;
    int randomRow = 0;
    int randomColumn = 0;
    do {
        randomRow = distributionRow(generator);
        randomColumn = distributionColumn(generator);
        // if the point in the array is false (false == 0)
        if ((array[randomRow][randomColumn]) == 0) {
            // set the array point to 1 for obstacle and increment number of present obstacles by 1
            array[randomRow][randomColumn] = 1;
            numberOfObstaclesPresent++;
        }
    }while(numberOfObstaclesPresent < numberOfObstaclesWanted);
}

void Board::redistributeObstaclesRandom(float oRatio) {
    obstacleRatio = oRatio;
    redistributeObstaclesRandom();
}

void Board::redistributeObstaclesManually() {

}

void Board::setWholeBoardTo(int x) {
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            array[i][j] = x;
        }
    }
}

float Board::getObstacleRatio() const {
    return obstacleRatio;
}

Board::Board(const Board &oldBoard): MetaParameter(oldBoard.height, oldBoard.width, oldBoard.obstacleCode,
                                                   oldBoard.emptySpaceCode, oldBoard.taxiCode),
                                     obstacleRatio(oldBoard.obstacleRatio) {

}

Board &Board::operator=(const Board &other) {

    return *this;
}
