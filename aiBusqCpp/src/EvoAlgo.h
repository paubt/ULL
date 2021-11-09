//
// Created by pau on 8/11/21.
//

#ifndef ASTULL_EVOALGO_H
#define ASTULL_EVOALGO_H

#include <string>
#include <list>

#include "Board.h"


// struct for the individuals
struct stringIndividual {
    // genotype is a string of direction sequence
    std::string genotype;
    // phenotype is the fitness of the genotype
    float phenotype;
    // fitness function
    float fitness();
    // set individual to random sequence
    void createNewGenotype();
    // mutation Function
    stringIndividual mutate();
};


// class template that takes as template parameters a class individual's
template <class Individual>
class EvoAlgo: public Board{
    // the population is a list with elements of the type individuals
    std::list<Individual> population;
    // mu is the population size
    const int mu;
    // lambda is the parent size
    // warning mu mod lambda should be 0
    const int lambda;
    // bool if talk much or noting
    const bool verbose;
    // time to search in seconds
    const int searchTime;
public:
    EvoAlgo(Board &board, bool verbose,int mu, int lambda,
              // the time the algorithm will search
              int searchTime);
};

template<class Individual>
EvoAlgo<Individual>::EvoAlgo(Board &board, bool verbose, int mu, int lambda, int searchTime):
        Board(board), verbose(verbose), mu(mu), lambda(lambda), searchTime(searchTime){

}


#endif //ASTULL_EVOALGO_H
