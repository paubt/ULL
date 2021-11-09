#include <iostream>
#include <chrono>

#include "MetaParameter.h"
#include "Board.h"
#include "EvoAlgo.h"

int main() {
    std::cout << "-------------test---MetaParameter--------------" << std::endl;
    MetaParameter testMp(15, 15);
    MetaParameter test2Mp(10,10);
    std::cout << testMp.getHeight() << std::endl;
    testMp = test2Mp;
    std::cout << testMp.getHeight() << std::endl;

    std::cout << "-------------test----Board----------------------" << std::endl;
    // time begin
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    Board testB(testMp, 0.2);
    // time end
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    // print the board
    testB.printBoard();
    // calculate differance of begin and end and print it
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;

    std::cout << "------------test----EvoAlgo--------------------" << std::endl;
    int mu = 10;
    int lambda = 5;
    int verbose = true;
    int searchTime = 2;
    EvoAlgo<stringIndividual> testEvoAlgo(testB, verbose, mu, lambda, searchTime);
    testEvoAlgo.printBoard();

    return 0;
};
