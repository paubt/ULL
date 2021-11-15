//
// Created by pau on 8/11/21.
//

#ifndef ASTULL_EVOALGO_H
#define ASTULL_EVOALGO_H

#include <string>
#include <list>

#include "Board.h"


template<int Mean, int Std, int Sec>
class StringIndividual {
    std::string genotype;
    const int mean;
    const int std;
    const int sec;
public:
    StringIndividual();
    // creat new individual
    void creatNewGenotype();
    // getter function's // note these are const's
    int getMean() const;
    int getStd() const;
    int getSec() const;
};

template<int Mean, int Std, int Sec>
StringIndividual<Mean, Std, Sec>::StringIndividual(): mean(Mean), std(Std), sec(Sec){
    genotype.clear();
}

template<int Mean, int Std, int Sec>
int StringIndividual<Mean, Std, Sec>::getMean() const {
    return mean;
}

template<int Mean, int Std, int Sec>
int StringIndividual<Mean, Std, Sec>::getStd() const {
    return std;
}

template<int Mean, int Std, int Sec>
int StringIndividual<Mean, Std, Sec>::getSec() const {
    return sec;
}

template<int Mean, int Std, int Sec>
void StringIndividual<Mean, Std, Sec>::creatNewGenotype() {

}


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
EvoAlgo<Individual>::EvoAlgo(Board &board, bool verbose, int mu, int lambda, int searchTime): Board(board),
                             verbose(verbose), mu(mu), lambda(lambda), searchTime(searchTime) {

}


#endif //ASTULL_EVOALGO_H
