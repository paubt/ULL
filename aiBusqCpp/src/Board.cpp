//
// Created by pau on 27/10/21.
//

#include "Board.h"

// constructor with all parameters explicit
Board::Board(int h, int w, int oC, int eC, int tC, float oRatio = 0.2) : MetaParameter(h, w, oC, eC, tC), obstacleRatio(oRatio) {
    // initialize array with null pointer for safety
    array = nullptr;
    // allocate space for the grid
    allocateBoard();
    // set some values in the gird to obstacles
    redistributeObstaclesRandom();
}

// constructor with a existing MetaParameter Object
Board::Board(MetaParameter &mP, float oRatio = 0.2): MetaParameter(mP), obstacleRatio(oRatio) {
    // initialize array with null pointer for safety
    array = nullptr;
    // allocate space for the grid
    allocateBoard();
    // set some values in the gird to obstacles
    redistributeObstaclesRandom();
}

// copy constructor
Board::Board(const Board &oldBoard): MetaParameter(oldBoard.height, oldBoard.width, oldBoard.obstacleCode,
                                                   oldBoard.emptySpaceCode, oldBoard.taxiCode),
                                     obstacleRatio(oldBoard.obstacleRatio) {
    // we also need to copy the grid (array of array's) from the oldBoard
    copyBoard(oldBoard);
}

// assignment operator
Board &Board::operator=(const Board &other) {
    height = other.getHeight();
    height = other.getHeight();
    width = other.getWidth();
    obstacleCode = other.getObstacleCode();
    emptySpaceCode = other.getEmptySpaceCode();
    taxiCode = other.getTaxiCode();
    generator = other.generator;

    obstacleRatio = other.obstacleRatio;
    copyBoard(other);
    return *this;
}



// destructor calls the deleteBoard function to free up space
Board::~Board() {
    deleteBoard();
}

// print's the board        bruh
void Board::printBoard() {
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            std::cout << array[i][j] << " ";
        }
        std::cout << std::endl;
    }
     std::cout << std::endl;
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
    // repeatedly add new obstacles into the grid
    do {
        randomRow = distributionRow(generator);
        randomColumn = distributionColumn(generator);
        // if the point in the array is false (false == 0)
        if ((array[randomRow][randomColumn]) == 0) {
            // set the array point to 1 for obstacle and increment number of present obstacles by 1
            array[randomRow][randomColumn] = 1;
            numberOfObstaclesPresent++;
        }
    // until we have added enough
    }while(numberOfObstaclesPresent < numberOfObstaclesWanted);
}

// after updating the new value it calls the base case function redistributeObstaclesRandom()
void Board::redistributeObstaclesRandom(float oRatio) {
    obstacleRatio = oRatio;
    redistributeObstaclesRandom();
}

// still needs to be implemented
// note: I see no need for manual distribution of obstacles
void Board::redistributeObstaclesManually() {

}

// goes through the whole board and sets all values to the argument past into the function
void Board::setWholeBoardTo(int x) {
    // iterate through columns
    for(int i = 0; i < width; i++){
        // iterate through rows
        for(int j = 0; j < height; j++){
            // set value in specific row and column to x
            array[i][j] = x;
        }
    }
}

// getter function
float Board::getObstacleRatio() const {
    return obstacleRatio;
}

// helper function that deletes/free's up the space allocated for the grid
void Board::deleteBoard() {
    delete[] array;
}

// copys the values form another board into ours //
void Board::copyBoard(const Board &other) {
    // first we delete the old board
    deleteBoard();
    // we allocate a the new space for the board with new function
    allocateBoard();
    // now we copy the value's form the "other" grid to "this" grid
    for(int i = 0; i < width; i++) {
        for(int j = 0; j < height; j++) {
            array[i][j] = other.array[i][j];
        }
    }
}

// allocate the space for the grid with new
void Board::allocateBoard() {
    // dynamically allocating rows as list of list's
    array = new int*[width];
    // dynamically allocating a column for each row
    for(int i = 0; i < width; i++) {
        array[i] = new int[height];
    }
}
