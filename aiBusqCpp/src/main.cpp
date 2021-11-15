#include <iostream>
#include <chrono>

#include "MetaParameter.h"
#include "Board.h"
#include "EvoAlgo.h"

int main() {
    std::cout << "-------------test---MetaParameter--------------" << std::endl;
    MetaParameter testMp(10, 10);
    std::cout << testMp.getHeight();
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



    std::cout << "----------test----Individuals------------------" << std::endl;

    StringIndividual<10, 14, 1> testIndi;
    std::cout << testIndi.getMean() << std::endl;
    std::cout << "------------test----EvoAlgo--------------------" << std::endl;


    return 0;
};
