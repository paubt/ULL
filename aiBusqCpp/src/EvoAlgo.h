//
// Created by pau on 8/11/21.
//

#ifndef ASTULL_EVOALGO_H
#define ASTULL_EVOALGO_H

#include <string>
#include <list>

#include <thread>

#include "Board.h"


template<int Mean, int Std, int Sec, int CTBF, int CEBF, int CTID, int CI, int CD, int MID, int StdID>
class StringIndividual {
public:
    std::string genotype;
    // aka. fitness
    double phenotype;
    const int mean;
    const int std;
    const int sec;
    // the weighs for the fitness function all between 0-999
    // chance for the  bit-flip/direction-flip mutation
    const int chanceToBitFlip;
    // chance for each bit-flip at the position
    const int chanceEachBitFlip;
    // chance for the insert and delete mutation
    const int chanceToInsertDelete;
    // chance for the number of inserts
    const int chanceInsert;
    // chance for the number of deletes
    const int chanceDelete;
    // mean and standard deviation of the insert/delete pieces
    const int meanInsertDelete;
    const int stdInsertDelete;
    // constructor
    StringIndividual();
    // getter function's // note these are const's
    int getMean() const;
    int getStd() const;
    int getSec() const;
    std::string getGenotype() const;
    double getFitness() const;
    // functions to set string and fitness
    void setGenotype(const std::string& newGenotype);
    void setFitness(double newFitness);
};

// chances (C in beginning) are 0-999
template<int Mean, int Std, int Sec, int CTBF, int CEBF, int CTID, int CI, int CD, int MID, int StdID>
StringIndividual<Mean, Std, Sec, CTBF, CEBF, CTID, CI, CD, MID, StdID>::StringIndividual(): mean(Mean), std(Std),
                sec(Sec), chanceToBitFlip(CTBF), chanceEachBitFlip(CEBF), chanceToInsertDelete(CTID), chanceInsert(CI),
                chanceDelete(CD), meanInsertDelete(MID), stdInsertDelete(StdID){
    genotype.clear();
}

template<int Mean, int Std, int Sec, int CTBF, int CEBF, int CTID, int CI, int CD, int MID, int StdID>
int StringIndividual<Mean, Std, Sec, CTBF, CEBF, CTID, CI, CD, MID, StdID>::getMean() const {
    return mean;
}

template<int Mean, int Std, int Sec, int CTBF, int CEBF, int CTID, int CI, int CD, int MID, int StdID>
int StringIndividual<Mean, Std, Sec, CTBF, CEBF, CTID, CI, CD, MID, StdID>::getStd() const {
    return std;
}

template<int Mean, int Std, int Sec, int CTBF, int CEBF, int CTID, int CI, int CD, int MID, int StdID>
int StringIndividual<Mean, Std, Sec, CTBF, CEBF, CTID, CI, CD, MID, StdID>::getSec() const {
    return sec;
}

template<int Mean, int Std, int Sec, int CTBF, int CEBF, int CTID, int CI, int CD, int MID, int StdID>
std::string StringIndividual<Mean, Std, Sec, CTBF, CEBF, CTID, CI, CD, MID, StdID>::getGenotype() const {
    return genotype;
}

template<int Mean, int Std, int Sec, int CTBF, int CEBF, int CTID, int CI, int CD, int MID, int StdID>
double StringIndividual<Mean, Std, Sec, CTBF, CEBF, CTID, CI, CD, MID, StdID>::getFitness() const {
    return phenotype;
}

template<int Mean, int Std, int Sec, int CTBF, int CEBF, int CTID, int CI, int CD, int MID, int StdID>
void StringIndividual<Mean, Std, Sec, CTBF, CEBF, CTID, CI, CD, MID, StdID>::setGenotype(const std::string& newGenotype) {
    genotype = newGenotype;
}

template<int Mean, int Std, int Sec, int CTBF, int CEBF, int CTID, int CI, int CD, int MID, int StdID>
void StringIndividual<Mean, Std, Sec, CTBF, CEBF, CTID, CI, CD, MID, StdID>::setFitness(double newFitness) {
    phenotype = newFitness;
}




// class template that takes as template parameters a class individual's
template <class Individual>
class EvoAlgo: public Board{
public:
    // the population is a list with elements of the type individuals
    std::list<Individual*> population;
    // mu is the population size
    const int mu;
    // lambda is the parent size
    // warning mu mod lambda should be 0
    const int lambda;
    // bool if talk much or noting
    const bool verbose;
    // time to search in seconds
    const int searchTime;
    // weights for the fitness function
    const float weightDistance;
    const float weightLengthOfGenotype;

public:
    EvoAlgo(Board &board, bool verbose,int mu, int lambda,
              // the time the algorithm will search
              int searchTime, float weightDistance, float weightLenghtOfGenotype);
    // the main muCommaLambda loop
    void muCommaLambda();
    // the main muPlusLambda loop
    void muPlusLambda(int maxGenerations);

    // private helper functions
private:
    // allocates n new Individuals and push's them into the population list doing a random walk for each;
    void createInitialPopulation();
    // determine the walk length and performs a walk returning the encoded sequence as a string (see README for explanation)
    std::vector<int> randomWalk(bool &found, const int walkLength, const int walkTime);
    //position after n Steps returned as reference
    void findPositionAfterNSteps(Individual* individual, int nStepsToTake, int& positionHeight, int& positionWidth);
    // check if a walk sequence of an individual goes out of the grid or over an obstacle or a visited place return false if so
    bool checkIfLegalWalk(Individual* individual);
    // calculate the manhattan distance / taxi cab distance
    int manhattanDistance(int height, int width, int maxHeight, int maxWidth);
    // uses length, the distance of the end and the fact that it found the goal to calculate the fitness
    // and then saves it inside the individual
    void assesFitness(Individual* individual);
    // updates/asses all the fitness's of all individuals inside the population
    void assesAllFitnessInPopulation();
    // bit flip / direction flip function
    void bitFlipMutation(Individual* individual);
    // delete-insert mutation
    void insertDeleteMutation(Individual* individual);
    // individual mutation
    void mutateIndividual(Individual* individual);
    // mutate the whole population
    void mutatePopulation();
    // find the best individual, based on fitness, and save its characteristics into the
    // return ture if a new best is found
    bool checkForBest(std::string &bestGenotype, double &bestFitness);
};

template<class Individual>
EvoAlgo<Individual>::EvoAlgo(Board &board, bool verbose, int mu, int lambda, int searchTime,
                             float weightDistance, float weightLengthOfGenotype):
                             Board(board), verbose(verbose), mu(mu), lambda(lambda), searchTime(searchTime),
                             weightDistance(weightDistance), weightLengthOfGenotype(weightLengthOfGenotype){
}


template<class Individual>
void EvoAlgo<Individual>::createInitialPopulation() {
    // found variable
    bool found = false;
    // walk length
    int walkLength = 0;
    // walk time
    int walkTime = 0;
    // pointer to individual with a Individual just to extract the mean and standard deviation for the normal distribution and the walk time
    Individual* pTempIndividual = new Individual;
    // the normal distribution with the values of a individual
    std::normal_distribution<float> nDistribution(pTempIndividual->getMean(), pTempIndividual->getStd());
    // set the walk time
    walkTime = pTempIndividual->getSec();
    // now we delete the individual again
    delete pTempIndividual;
    pTempIndividual = nullptr;
    // walk sequence as a vector of int and as string
    std::vector<int> vecWalkSequence;
    std::string stringWalkSequence;
    // repeat until the start population is full
    while (population.size() < mu) {
        // allocate a new Individual
        pTempIndividual = new Individual;
        // draw a random float length from the normal distribution and cast it to integer
        walkLength = static_cast<int>(nDistribution(generator));
        found = false;
        vecWalkSequence = randomWalk(found, walkLength, walkTime);
        // erase the last walk sequence from the string
        stringWalkSequence.clear();
        // transform the vector to a string
        // iterate through the vector and append the content as char to the string
        for (auto c: vecWalkSequence){
            stringWalkSequence += std::to_string(c);
        }
        // insert the walk sequence as string into the genotype of the Individual (object)
        pTempIndividual->setGenotype(stringWalkSequence);
        // push the Individual into the population
        population.push_back(pTempIndividual);
    }
}

template<class Individual>
std::vector<int> EvoAlgo<Individual>::randomWalk(bool &found, const int walkLength, const int walkTime) {
    // set found variable to false
    found = false;
    // make a hard copy of the array
    // using the = operator specified in Board; this is allowed cause in place of a Board type a children type(here algo) can take his place
    Board tempBoard = *this;
    // we specify the code with which we mark visited positions
    const int visitedPosition = 5;
    // the walk sequence
    // the current position height und width initialized with zero
    int positionHeight = 0, positionWidth = 0;
    // direction options
    std::vector<int> directionOptions;
    // the walk sequence
    std::vector<int> walkSequence;
    // the walk direction choose
    int nextStepDirection;
    // calculate the max time it should take
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    int timeDifference = 0;
    while (true) {
        // clear the directionsOptions
        directionOptions.clear();
        // go through each option/direction we could take and
        // check if goal it's the goal
            // if so add direction to walk sequence and return the sequence
        // check if it is free and not already visited
            // if so add it to possible direction options
        // south
        if (positionHeight < tempBoard.height - 1) {
            // check for goal
            if (tempBoard.array[positionHeight + 1][positionWidth] == 3) {
                walkSequence.push_back(4);
                found = true;
                return walkSequence;
            }
            // check if it is free
            if (tempBoard.array[positionHeight + 1][positionWidth] == 0) {
                directionOptions.push_back(4);
            }
        }
        // north
        if (positionHeight > 0) {
            // check for goal
            if (tempBoard.array[positionHeight - 1][positionWidth] == 3) {
                walkSequence.push_back(0);
                found = true;
                return walkSequence;
            }
            // check if it is free
            if (tempBoard.array[positionHeight - 1][positionWidth] == 0) {
                directionOptions.push_back(0);
            }
        }
        // east
        if (positionWidth < tempBoard.width - 1) {
            // check for goal
            if (tempBoard.array[positionHeight][positionWidth + 1] == 3) {
                walkSequence.push_back(2);
                found = true;
                return walkSequence;
            }
            // check if it is free
            if (tempBoard.array[positionHeight][positionWidth + 1] == 0) {
                directionOptions.push_back(2);
            }
        }
        // west
        if (positionWidth > 0) {
            // check for goal
            if (tempBoard.array[positionHeight][positionWidth - 1] == 3) {
                walkSequence.push_back(6);
                found = true;
                return walkSequence;
            }
            // check if it is free
            if (tempBoard.array[positionHeight][positionWidth - 1] == 0) {
                directionOptions.push_back(6);
            }
        }
        // northwest
        if ((positionWidth > 0) && (positionHeight >0)){
            // check for goal
            if (tempBoard.array[positionHeight - 1][positionWidth - 1] == 3) {
                walkSequence.push_back(7);
                found = true;
                return walkSequence;
            }
            // check if it is free
            if (tempBoard.array[positionHeight - 1][positionWidth - 1] == 0) {
                directionOptions.push_back(7);
            }
        }
        // northeast
        if ((positionWidth < tempBoard.width - 1) && (positionHeight > 0)){
            // check for goal
            if (tempBoard.array[positionHeight - 1][positionWidth + 1] == 3) {
                walkSequence.push_back(1);
                found = true;
                return walkSequence;
            }
            // check if it is free
            if (tempBoard.array[positionHeight - 1][positionWidth + 1] == 0) {
                directionOptions.push_back(1);
            }

        }
        // southwest
        if ((positionWidth > 0) && (positionHeight < tempBoard.height - 1)){
            // check for goal
            if (tempBoard.array[positionHeight + 1][positionWidth - 1] == 3) {
                walkSequence.push_back(5);
                found = true;
                return walkSequence;
            }
            // check if it is free
            if (tempBoard.array[positionHeight + 1][positionWidth - 1] == 0) {
                directionOptions.push_back(5);
            }
        }
        // southeast
        if ((positionWidth < tempBoard.width - 1) && (positionHeight < tempBoard.height - 1)){
            // check for goal
            if (tempBoard.array[positionHeight + 1][positionWidth + 1] == 3) {
                walkSequence.push_back(3);
                found = true;
                return walkSequence;
            }
            // check if it is free
            if (tempBoard.array[positionHeight + 1][positionWidth + 1] == 0) {
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
        tempBoard.array[positionHeight][positionWidth] = visitedPosition;
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

        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        timeDifference = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
        // if the sequence reached the limit length given as input parameters or run out of time it terminates the search
        if ((walkLength == walkSequence.size()) && (timeDifference > walkTime)) {
            break;
        }
    }
    return walkSequence;
}

template<class Individual>
void EvoAlgo<Individual>::findPositionAfterNSteps(Individual *individual, int nStepsToTake, int &positionHeight,
                                                  int &positionWidth) {
    // set the references past as arguments to zero
    positionHeight = 0;
    positionWidth = 0;
    // extract the genotype out of the individual as walk sequence string
    std::string walkSequence = individual->getGenotype();
    // temporal holder for the direction
    int tempDirection = 0;
    // assert if the input of the steps to take is in an undefined range
    assert(nStepsToTake > 0);
    // if the Steps to take are larger than the individual length

    // repeat for the specified n steps or until the walk sequence is empty (end of sequence)
    while ((nStepsToTake-- > 0) && (!walkSequence.empty())) {
        // read the first character from the walk sequence and rest 48 to get from ascii to normal value
        tempDirection = walkSequence[0] -48;
        // delete the first element from the walk sequence
        walkSequence.erase(0,1);
        // increase the positions based on the direction
        switch (tempDirection) {
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
            default:
                std::cout << tempDirection << "there is a masiv error in the genotype/ unexpected value detected in switch of findPositionAfterNSteps " << std::endl;
                break;
        }
    }

}

template<class Individual>
bool EvoAlgo<Individual>::checkIfLegalWalk(Individual *individual) {
    // make a hard copy of the array
    // using the = operator specified in Board; this is allowed cause in place of a Board type a children type(here algo) can take his place
    Board tempBoard = *this;
    // we specify the code with which we mark visited positions
    const int visitedPosition = 5;
    // the current position height und width initialized with zero
    int positionHeight = 0, positionWidth = 0;
    // do a pre-check to see if the start position is a obstacle

    // main check loop allying the steps and assuring correctness
    for(int i = 0; i < (individual->getGenotype()).size(); i++){
        // set the current position as visited
        tempBoard.array[positionHeight][positionWidth] = visitedPosition;
        // read out the character out of the genotype in position i and with minus 48 go from ascii to decimal
        // increment the position's based on the direction in the string
        switch (individual->getGenotype()[i] - 48) {
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
            default:
                std::cout << individual->getGenotype()[i] - 48 <<  " there is a massive error in the genotype/ unexpected value detected in switch of checkIfLegalWalk " << std::endl;
                break;
        }
        // check if out of grid
        if ((positionHeight < 0) || (positionHeight >= getHeight()) || (positionWidth < 0) || (positionWidth >= getWidth())) {
            return false;
        }
        // check if on top of a obstacle or an already visited place
        if ((tempBoard.array[positionHeight][positionWidth] == 5) || (tempBoard.array[positionHeight][positionWidth] == 1)) {
            return false;
        }
    }
    return true;
}

template<class Individual>
int EvoAlgo<Individual>::manhattanDistance(int height, int width, int maxHeight, int maxWidth) {
    // make sure that height is in range: 0 <= height < maxHeight
    assert(height >= 0);
    assert(height < maxHeight);
    // make sure that width is in range: 0 <= width < maxWidth
    assert(width >= 0);
    assert(width < maxWidth);
    // calculate the distance and return it
    return abs(maxHeight - height) + abs(maxWidth - maxWidth);
}

template<class Individual>
void EvoAlgo<Individual>::assesFitness(Individual *individual) {
    // get the length of the genotype
    int genotypeLength = (individual->getGenotype()).size();
    // variable for the end positions
    int endPositionHeight = 0;
    int endPositionWidth = 0;
    // calculate the end positions
    findPositionAfterNSteps(individual, genotypeLength, endPositionHeight, endPositionWidth);
    // use the end position's to calculate the Manhattan distance
    int manhattanD = manhattanDistance(endPositionHeight, endPositionWidth, getHeight(), getWidth());
    // if the manhattan distance != 0, meaning the individual doesn't end at the goal, it gets extra penalized
    bool extraPenalty = false;
    if (manhattanD != 0) {
        extraPenalty = true;
    }
    // calculate the fitness
    double fitness = static_cast<float>(extraPenalty * 50) + (weightDistance * static_cast<float>(manhattanD)) +
            (weightLengthOfGenotype * static_cast<float>(genotypeLength));
    // update the fitness in the individual
    individual->setFitness(fitness);
}

template<class Individual>
void EvoAlgo<Individual>::assesAllFitnessInPopulation() {
    // iterate through the population
    for (auto it = population.begin(); it != population.end(); it++) {
        // call the fitness asses function which updates the fitness
        assesFitness(*it);
    }
}

template<class Individual>
void EvoAlgo<Individual>::bitFlipMutation(Individual *individual) {
    // the genotype
    std::string genotype = individual->getGenotype();
    // iterate though the individuals genotype
    for (int i = 0; i < (individual->getGenotype()).size(); i++) {
        if (individual->chanceEachBitFlip > (rand() % 1000)) {
            // a random number between 0 and 7
            // then we add 48 to get the ascii encoding and typecast to char
            genotype[i] = static_cast<char>((rand() % 8) + 48);
        }
    }
    // set the new genotype into the individual
    individual->setGenotype(genotype);
}

template<class Individual>
void EvoAlgo<Individual>::insertDeleteMutation(Individual *individual) {
    // get the genotype
    std::string genotype = individual->getGenotype();
    // normal distribution for the length of the insert/delete pieces
    std::normal_distribution<float> nDistribution(individual->meanInsertDelete, individual->stdInsertDelete);
    // variables
    int insertIndex = 0;
    int insertLength = 0;
    int deleteLength = 0;
    int deleteIndex = 0;
    std::string insertString;
    // the random number;
    int random = rand() % 1000;
    // insert loop
    // loop check if chance is larger than the random number
    while(individual->chanceInsert > random) {
        // determines the position where to insert
        insertIndex = rand() % (genotype.size() + 1);
        // determines the length of the piece to insert
        insertLength = static_cast<int>(nDistribution(generator));
        // create the insertString
        insertString.clear();
        for (int i = 0; i < insertLength; i++) {
            // append a random direction to the insertString
            insertString += static_cast<char>((rand() % 8) + 48);
        }
        // insert the input string into the genotype
        genotype.insert(insertIndex,insertString);
        // draw a new random number
        random = rand() % 1000;
    }
    random = rand() % 1000;
    // delete loop
    while (individual->chanceDelete > random) {
        // determine the delete length
        deleteLength = static_cast<int>(nDistribution(generator));
        // break if delete length is longer than the genotype length
        if (deleteLength >= genotype.size()) {
            break;
        }
        // determine where the delete-position to start
        deleteIndex = rand() & (genotype.size() - deleteLength);
        // erase the deleteLength starting from deleteIndex
        genotype.erase(deleteIndex, deleteLength);
        // draw new random number
        random = rand() % 1000;
    }
    // update the genotype in the individual
    individual->setGenotype(genotype);
}

template<class Individual>
void EvoAlgo<Individual>::mutateIndividual(Individual *individual) {
    //determine if we apply the bit-flip mutation
    if (individual->chanceToBitFlip > (rand() % 1000)) {
        // call the bit-flip mutation
        bitFlipMutation(individual);
    }
    // determine if we apply the insert-delete mutation
    if (individual->chanceToInsertDelete > (rand() % 1000)) {
        insertDeleteMutation(individual);
    }
}

template<class Individual>
void EvoAlgo<Individual>::mutatePopulation() {
    // iterate through the population
    for (auto it = population.begin(); it != population.end(); it++) {
        mutateIndividual(*it);
    }
}

template<class Individual>
void EvoAlgo<Individual>::muCommaLambda() {

}

template<class Individual>
void EvoAlgo<Individual>::muPlusLambda(int maxGenerations) {
    // the current generation
    int generation = 0;
    // the parent list
    std::list<Individual*> parents;
    // stuff for sort : temp parent, currentBest,
    int index = 0;
    int currentBestIndex = 0;
    double currentBestFitness = 0;
    Individual* pCurrentBestIndividual = nullptr;
    Individual* pTempIndividual = nullptr;
    Individual* pMutateIndividual = nullptr;
    // create a initial population
    createInitialPopulation();
    // the fitness and genotype of the best individual
    double bestFitness = DBL_MAX;
    std::string bestGenotype;
    bool newBestFound = false;

    // start time
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    // difference counted in seconds
    long timeDifference = 0;

    // main generation loop
    do {
        //asses the fitness of the population
        assesAllFitnessInPopulation();
        // check for new best
        newBestFound = checkForBest(bestGenotype, bestFitness);
        if (newBestFound && verbose) {
            std::cout << "new best in generation: " << generation << std::endl;
            newBestFound = false;
        }
        // first clear parents list
        parents.clear();
        // try to sort
        //
        // pass the lambda's best Individuals as pointers to the parent population and then delete the pointer in the
        // population. Then we delete the rest of the Individuals.
        for (int i = 0; i < lambda; i++) {
            index = 0;
            currentBestFitness = DBL_MAX ;
            // iterate through the remaining population
            for (auto it = population.begin(); it != population.end(); it++) {
                // if a new best is found save it
                if ((*it)->getFitness() < currentBestFitness) {
                    currentBestFitness = (*it)->getFitness();
                    pCurrentBestIndividual = *it;
                }
            }
            // copy the best one found to the parent population
            parents.push_back(pCurrentBestIndividual);
            // delete the best form the population
            population.remove(pCurrentBestIndividual);
        }
        // clear the population of the individuals that to bad
        population.clear();
        // iterate through the parent list
        for (auto it = parents.begin(); it != parents.end(); it++) {
            // add the parent automatically to the next generation
            pTempIndividual = *it;
            population.push_back(pTempIndividual);
            // do for each parent mu/lambda times :
            for (int i = 0; i < mu/lambda; i++) {
                // create a new individual and get the genotype
                pMutateIndividual = new Individual;
                pMutateIndividual->setGenotype(pTempIndividual->getGenotype());
                for(int j = 0; i < 10; j++) {
                    // do the mutation
                    mutateIndividual(pMutateIndividual);
                    // check if a legal walk -> break for loop
                    if (checkIfLegalWalk(pMutateIndividual)) {
                        break;
                    // else if end of loop set genotype again to the parents one and break
                    } else if (i == 9) {
                        pMutateIndividual->setGenotype(pTempIndividual->getGenotype());
                        break;
                    }
                }
                population.push_back(pMutateIndividual);


            }

        }
        // clear parent
        // if verbose true print some info's
        if (verbose) {
            std::cout << "Generation: " << generation << std::endl;
            // print the population
            index = 0;
            for (auto it = population.begin(); it != population.end(); it++) {
                std::cout << index++ << " - " << (*it)->getGenotype() << std::endl;
            }
        }
        // increment generation
        ++generation;
        // calculate difference from start to end
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        timeDifference = std::chrono::duration_cast<std::chrono::seconds>(end - begin).count();
        std::cout << timeDifference << std::endl;
        // stop if difference in time is larger than allowed or the maxGeneration is hit
    } while ((searchTime > timeDifference) && (generation < maxGenerations));

}

template<class Individual>
bool EvoAlgo<Individual>::checkForBest(std::string &bestGenotype, double &bestFitness) {
    bool newBest = false;
    // iterate through the population
    for (auto it = population.begin(); it != population.end(); it++) {
        if ((*it)->getFitness() > bestFitness) {
            bestFitness = (*it)->getFitness();
            bestGenotype = (*it)->getGenotype();
            newBest = true;
        }
    }
    return newBest;
}


#endif //ASTULL_EVOALGO_H
