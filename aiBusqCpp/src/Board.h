//
// Created by pau on 27/10/21.
//

#ifndef ASTULL_BOARD_H
#define ASTULL_BOARD_H

#include "MetaParameter.h"
#include "iostream"
#include "cmath"


class Board: public MetaParameter{
public:
    float obstacleRatio;
    // the array is basically a pointer to pointers (list of lists)
    int **array{};

    Board(MetaParameter &metaParameter, float oRatio);
    Board(int h, int w, int oC, int eC, int tC, float oRatio);
    //copy constructor
    Board(Board const& oldBoard);
    // assiment operator
    Board& operator=(const Board& other);
    ~Board();

    void printBoard();
    void updateTaxiPosition();
    void redistributeObstaclesRandom();
    void redistributeObstaclesRandom(float oRatio);
    void redistributeObstaclesManually();
    float getObstacleRatio() const;

private:
    //helperFunctions
    //sets the whole board to
    void setWholeBoardTo(int x);
    // delete/ free up the board
    void deleteBoard();
    // allocate / create a the space for the new board
    void allocateBoard();
    // fist delete old board then create new and copy the state form other into the new one
    void copyBoard(const Board &other);
};


#endif //ASTULL_BOARD_H
