#include <iostream>

#include "MetaParameter.h"
#include "Board.h"
#include "EvoAlgo.h"

int main() {
    std::cout << "-------------test----MetaParameter--------------" << std::endl;
    MetaParameter testMp(3, 5);
    std::cout << "-------------test----Board----------------------" << std::endl;
    Board testB(testMp, 0.1);
    std::cout << "-------------test----Individuals----------------" << std::endl;
    StringIndividual<10, 14, 1,500,900,500,200,200,3,1> testIndividual;

    std::cout << "-------------test----EvoAlgo--------------------" << std::endl;


    EvoAlgo<StringIndividual<10,10, 1,500,100,500,300,150,3,1>> testAlgo(testB, true, 10, 5, 1,
                                                  1, 1);
    testAlgo.printBoard();

    testAlgo.muPlusLambda(1);

    return 0;
}
