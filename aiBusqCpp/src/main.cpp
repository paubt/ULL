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
    StringIndividual<10, 14, 1> testIndividual;

    std::cout << "-------------test----EvoAlgo--------------------" << std::endl;
    EvoAlgo<StringIndividual<10, 10, 1>> testAlgo(testB, true, 5, 10, 2);
    for (auto it = testAlgo.population.begin(); it != testAlgo.population.end(); it++)
        std::cout << (*it)->getGenotype() << std::endl;

    return 0;
}
