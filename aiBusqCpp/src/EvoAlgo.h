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
public:
    std::string genotype;
    // aka. fitness
    double phenotype;
    const int mean;
    const int std;
    const int sec;
    // as
    StringIndividual();
    // getter function's // note these are const's
    int getMean() const;
    int getStd() const;
    int getSec() const;
    std::string getGenotype() const;
    double getFitness() const;
    // functions to set string an fitness
    void setGenotype(const std::string& newGenotype);
    void setFitness(double newFitness);
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
std::string StringIndividual<Mean, Std, Sec>::getGenotype() const {
    return genotype;
}

template<int Mean, int Std, int Sec>
double StringIndividual<Mean, Std, Sec>::getFitness() const {
    return phenotype;
}

template<int Mean, int Std, int Sec>
void StringIndividual<Mean, Std, Sec>::setGenotype(const std::string& newGenotype) {
    genotype = newGenotype;
}

template<int Mean, int Std, int Sec>
void StringIndividual<Mean, Std, Sec>::setFitness(double newFitness) {
    phenotype = newFitness;
}


// class template that takes as template parameters a class individual's
template <class Individual>
class EvoAlgo: public Board{
public:
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
    // function so create a new individual
    // std::string createNewIndividual(int mean, );
public:
    EvoAlgo(Board &board, bool verbose,int mu, int lambda,
              // the time the algorithm will search
              int searchTime);
};

template<class Individual>
EvoAlgo<Individual>::EvoAlgo(Board &board, bool verbose, int mu, int lambda, int searchTime): Board(board),
                             verbose(verbose), mu(mu), lambda(lambda), searchTime(searchTime) {
    Individual  pTestIndividual;
    population.push_back(pTestIndividual);

    for(class std::list<Individual>::iterator it= population.begin(); it != population.end(); it++)
        std::cout << it->getMean();

}


#endif //ASTULL_EVOALGO_H
