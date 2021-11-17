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
    std::list<Individual*> Population;
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
    // allocates n new Individuals and push's them into the population list doing a random walk for each;
    void createInitialPopulation();
    // determine the walk length and performs a walk returning the encoded sequence as a string (see README for explanation)
    std::vector<int> randomWalk(bool &found, const int walkLength, const int walkTime);
    //
};

template<class Individual>
EvoAlgo<Individual>::EvoAlgo(Board &board, bool verbose, int mu, int lambda, int searchTime): Board(board),
                             verbose(verbose), mu(mu), lambda(lambda), searchTime(searchTime) {
    /*
    Individual* pTempIndividual = new Individual;

    Population.push_back(pTempIndividual);

    for(auto it = Population.begin(); it != Population.end(); it++)
        std::cout << (*it)->getMean() << std::endl;

    Individual* pTemp = nullptr;

    pTemp = Population.back();

    std::cout << pTemp->getMean();
    */

    createInitialPopulation();
}


template<class Individual>
void EvoAlgo<Individual>::createInitialPopulation() {
    // found variable
    bool found = false;
    //
    std::vector<int> t = randomWalk(found,5,1);
}

template<class Individual>
std::vector<int> EvoAlgo<Individual>::randomWalk(bool &found, const int walkLength, const int walkTime) {
    // set found variable to false
    found = false;
    // make a hard copy of the array
    // using the = operator specified in Board; this is allowed cause in place of a Board type a children type(here algo) can take his place
    Board* tempBoard = this;
    // we specify the code with which we mark visited positions
    const int visitedPosition = 5;
    // the walk sequence
    // the current position height und width initialized with zero
    int positionHeight, positionWidth = 0;
    // direction options
    std::vector<int> directionOptions;
    // the walk sequence
    std::vector<int> walkSequence;
    // the walk direction choose
    int nextStepDirection;
    // calculate the max time it should take
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    std::chrono::steady_clock::time_point
    while (true) {
        // clear the directionsOptions
        directionOptions.clear();
        // go through each option/direction we could take and
        // check if goal it's the goal
            // if so add direction to walk sequence and return the sequence
        // check if it is free and not already visited
            // if so add it to possible direction options
        // south
        if (positionHeight < tempBoard->height - 1) {
            // check for goal
            if (tempBoard->array[positionHeight + 1][positionWidth] == 3) {
                walkSequence.push_back(4);
                found = true;
                return walkSequence;
            }
            // check if it is free
            if (tempBoard->array[positionHeight + 1][positionWidth] == 0) {
                directionOptions.push_back(4);
            }
        }
        // north
        if (positionHeight > 0) {
            // check for goal
            if (tempBoard->array[positionHeight - 1][positionWidth] == 3) {
                walkSequence.push_back(0);
                found = true;
                return walkSequence;
            }
            // check if it is free
            if (tempBoard->array[positionHeight - 1][positionWidth] == 0) {
                directionOptions.push_back(0);
            }
        }
        // east
        if (positionWidth < tempBoard->width - 1) {
            // check for goal
            if (tempBoard->array[positionHeight][positionWidth + 1] == 3) {
                walkSequence.push_back(2);
                found = true;
                return walkSequence;
            }
            // check if it is free
            if (tempBoard->array[positionHeight][positionWidth + 1] == 0) {
                directionOptions.push_back(2);
            }
        }
        // west
        if (positionWidth > 0) {
            // check for goal
            if (tempBoard->array[positionHeight][positionWidth - 1] == 3) {
                walkSequence.push_back(6);
                found = true;
                return walkSequence;
            }
            // check if it is free
            if (tempBoard->array[positionHeight][positionWidth - 1] == 0) {
                directionOptions.push_back(6);
            }
        }
        // northwest
        if ((positionWidth > 0) && (positionHeight >0)){
            // check for goal
            if (tempBoard->array[positionHeight - 1][positionWidth - 1] == 3) {
                walkSequence.push_back(7);
                found = true;
                return walkSequence;
            }
            // check if it is free
            if (tempBoard->array[positionHeight - 1][positionWidth - 1] == 0) {
                directionOptions.push_back(7);
            }
        }
        // northeast
        if ((positionWidth < tempBoard->width - 1) && (positionHeight > 0)){
            // check for goal
            if (tempBoard->array[positionHeight - 1][positionWidth + 1] == 3) {
                walkSequence.push_back(1);
                found = true;
                return walkSequence;
            }
            // check if it is free
            if (tempBoard->array[positionHeight - 1][positionWidth + 1] == 0) {
                directionOptions.push_back(1);
            }

        }
        // southwest
        if ((positionWidth > 0) && (positionHeight < tempBoard->height - 1)){
            // check for goal
            if (tempBoard->array[positionHeight + 1][positionWidth - 1] == 3) {
                walkSequence.push_back(5);
                found = true;
                return walkSequence;
            }
            // check if it is free
            if (tempBoard->array[positionHeight + 1][positionWidth - 1] == 0) {
                directionOptions.push_back(5);
            }
        }
        // southeast
        if ((positionWidth < tempBoard->width - 1) && (positionHeight < tempBoard->height - 1)){
            // check for goal
            if (tempBoard->array[positionHeight + 1][positionWidth + 1] == 3) {
                walkSequence.push_back(3);
                found = true;
                return walkSequence;
            }
            // check if it is free
            if (tempBoard->array[positionHeight + 1][positionWidth + 1] == 0) {
                directionOptions.push_back(3);
            }
        }
        // if there are no options available the search terminates and returns with false
        if (directionOptions.empty()){
            found = false;
            return walkSequence;
        }
        // choose a random directions from the directions vector
        nextStepDirection = directionOptions[rand() % directionOptions.size()];
        // append the step direction to the walk sequence
        walkSequence.push_back(nextStepDirection);
        // mark the current place as visited by overwriting the position with 5
        tempBoard->array[positionHeight][positionWidth] = visitedPosition;
        // update the current position
        switch (nextStepDirection) {
            case 0:
                --positionHeight;
                break;
            case 1:
                --positionHeight;
                ++positionWidth;
                break;
            case 2:
                ++positionWidth;
                break;
            case 3:
                ++positionHeight;
                ++positionWidth;
                break;
            case 4:
                ++positionHeight;
                break;
            case 5:
                ++positionHeight;
                --positionWidth;
                break;
            case 6:
                --positionWidth;
                break;
            case 7:
                --positionHeight;
                --positionWidth;
                break;
            // if we have another value we messed up somewhere
            default:
                std::cout << "logic error" << nextStepDirection << std::endl;
                found = false;
                return walkSequence;
        }
        // if the sequence reached the limit length given as input parameters it terminates the search
        if (walkLength == walkSequence.size()) {
            break;
        }

    }
    return walkSequence;
}



#endif //ASTULL_EVOALGO_H
