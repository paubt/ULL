from board import Board

import numpy.random
import random
import time
import math
import sys


class Algorithm(Board):
    def __init__(self, height, width, obstacleCode, emptySpaceCode, goalCode, startCode, obstacleRatio,
                 possibleToSolve):
        super().__init__(height, width, obstacleCode, emptySpaceCode, goalCode, startCode, obstacleRatio,
                         possibleToSolve)


def randomWalk(board, length):
    # some variables are defined
    # hard copy of the board df to be manipulated safely
    grid = board.df.copy()
    # int to mark the already visited spots on the grid
    visitedPosition = 5
    # list with the sequence of directions in which to take a step
    walkSequence = list()
    # starting positions of the random walk
    positionHeight, positionWidth = 0, 0
    while True:
        # check if the goal is in the neighborhood
        # if true go there and return the walk sequence
        if positionHeight < board.height - 1:
            if grid[positionHeight + 1, positionWidth] == 2:
                walkSequence.append("S")
                return walkSequence, True
        # check north
        if positionHeight > 0:
            if grid[positionHeight - 1, positionWidth] == 2:
                walkSequence.append("N")
                return walkSequence, True
        # check west
        if positionWidth > 0:
            if grid[positionHeight, positionWidth - 1] == 2:
                walkSequence.append("W")
                return walkSequence, True
        # check east
        if positionWidth < board.width - 1:
            if int(grid[positionHeight, positionWidth + 1]) == 2:
                walkSequence.append("E")
                return walkSequence, True
        # defining a set to store the possible options in the neighborhood
        options = set()
        # checking out the empty space not visited options that are available
        # check south
        if positionHeight < board.height - 1:
            if grid[positionHeight + 1, positionWidth] == 0:
                options.add("S")
        # check north
        if positionHeight > 0:
            if grid[positionHeight - 1, positionWidth] == 0:
                options.add("N")
        # check west
        if positionWidth > 0:
            if grid[positionHeight, positionWidth - 1] == 0:
                options.add("W")
        # check east
        if positionWidth < board.width - 1:
            if int(grid[positionHeight, positionWidth + 1]) == 0:
                options.add("E")
        # if there are no options available the search terminates and returns with false
        if len(options) == 0:
            return walkSequence, False

        # choosing a random walk direction to do the step
        randomChoice = random.choice(list(options))
        # saving the walk step in the walkSequence
        walkSequence.append(randomChoice)
        # mark the current pos as visited
        grid[positionHeight, positionWidth] = visitedPosition
        # update the current position based on the direction chosen prior
        if randomChoice == "N":
            positionHeight -= 1
        elif randomChoice == "W":
            positionWidth -= 1
        elif randomChoice == "S":
            positionHeight += 1
        elif randomChoice == "E":
            positionWidth += 1
        # if the sequence reached the limit length given as input parameters it terminates the search
        if length == len(walkSequence):
            break
    print(grid)
    return walkSequence, False


def createRandomIndividual(board, mean, standardDeviation, secondsToSearch):
    # init the random number generator
    numpy.random.seed(1)
    # draw a random length from a normal distribution
    length = abs(numpy.random.normal(mean, standardDeviation, 1))
    # calculate end time
    endTime = time.time() + secondsToSearch
    while True:
        # create a new individual with a random walk
        individual, foundGoal = randomWalk(board, length)
        # if a walk sequence ends at the goal we terminate the search and pass the individual on marking found as true
        if foundGoal:
            return individual, foundGoal
        # if the length of the walk is almost as long as the mandated walk length or if we run out of time
        # it terminates the search and passes on the sub optimal individual
        elif (len(individual) >= length - 2) or time.time() < endTime:
            return individual, foundGoal
        # if prior condition are not meet we start again
        else:
            print()


def findPositionAfterNSteps(genotype, nStepsToTake):
    positionHeight, positionWidth = 0, 0
    # if input is in undefined range it sets itself to list length
    if nStepsToTake == 0 or nStepsToTake >= len(genotype):
        nStepsToTake = len(genotype)
    # repeat for the prior specified n steps
    while nStepsToTake > 0:
        # pop first item form the list and change the positions based on the direction
        nextDirection = genotype.pop(0)
        if nextDirection == "N":
            positionHeight -= 1
        if nextDirection == "S":
            positionHeight += 1
        if nextDirection == "E":
            positionWidth += 1
        if nextDirection == "W":
            positionWidth -= 1
        nStepsToTake -= 1
    return positionHeight, positionWidth


# returns the Manhattan distance between two points
def taxiCabDistance(height, width, maxHeight, maxWidth):
    distance = abs(maxHeight - height) + abs(maxWidth - width)
    return distance


""" this duality of genotype representation in form of a list and a string is major fuck upç
    in retrospective it would be smarter just stick with one """


# list genotype to string genotype
def listToString(inputList):
    outputString = ""
    for x in inputList:
        outputString += x
    return outputString


# string genotype to list
def stringToList(inputString):
    outputList = list(inputString)
    return outputList


def assessFitness(board, genotype, weightDistance, weightLengthOfGenotype):
    length = len(genotype)
    # find the end position of the walk
    endPositionHeight, endPositionWidth = findPositionAfterNSteps(genotype, length)
    # calculate the manhatten distance between end of walk and goal
    manhattenDistance = taxiCabDistance(endPositionHeight, endPositionWidth, board.height - 1, board.width - 1)
    # if manhatten distance != 0 meaning he doesn't end's at the goal give him an extra penetly of
    if manhattenDistance != 0:
        extraPenalty = True
    else:
        extraPenalty = False
    # fitness defined as function of
    fitness = extraPenalty * 50 + weightDistance * manhattenDistance + weightLengthOfGenotype * length
    return fitness


# takes in a string and by chance changes it with another
def bitFlipMutation(genotype, chanceBitFlip):
    # dictionary of directions to chose
    directionsDictionary = ["N", "S", "W", "E"]
    newGenotype = ""
    # go through the string
    for c in genotype:
        # if a random chance is meet replace the character else keep the old character
        if random.random() < chanceBitFlip:
            newGenotype = newGenotype + random.choice(directionsDictionary)
        else:
            newGenotype = newGenotype + c
    return newGenotype


# takes a string an inserts subsequences (of mean and str) while random < chanceInsert
def insertDeleteMutation(genotype, chanceInsert, chanceDelete, meanInsDel, stdInsDel):
    # dictionary of directions to chose
    directionsDictionary = ["N", "S", "W", "E"]
    # go through the insert loop x times
    while random.random() < chanceInsert:
        # draw a random number where to split the string
        i = int(random.uniform(0, len(genotype) + 1))
        # split the genotype string into two parts using prior drawn i
        leftPart = genotype[:i]
        rightPart = genotype[i:]
        # draw a random number from ND to specify input length
        inputLength = math.floor(abs(numpy.random.normal(meanInsDel, stdInsDel, 1)))
        innerPart = ""
        # chooses inputLength's times a character from the dictionary and appends it to the innerPart string
        for x in range(inputLength):
            innerPart = innerPart + random.choice(directionsDictionary)
        # puts the string together
        genotype = leftPart + innerPart + rightPart
    # go though the delete loop x times
    while random.random() < chanceDelete:
        deleteLength = math.floor(abs(numpy.random.normal(meanInsDel, stdInsDel, 1)))
        if deleteLength >= len(genotype) - 1:
            break
        i = int(random.uniform(0, len(genotype) - deleteLength))
        leftPart = genotype[:i]
        rightPart = genotype[i+deleteLength:]
        genotype = leftPart + rightPart
    return genotype


# all chances should be 0 <= p <= 1
def mutateGenotype(genotype, chanceToBitFlip, chanceBitFlip, chanceToInsertDelete, chanceInsert, chanceDelete,
                   meanInsDel, stdInsDel):
    # call the "bitFlip" mutation
    if random.random() < chanceToBitFlip:
        genotype = bitFlipMutation(genotype, chanceBitFlip)
    # call the "insertDelete" mutation function
    if random.random() < chanceToInsertDelete:
        genotype = insertDeleteMutation(genotype, chanceInsert, chanceDelete, meanInsDel, stdInsDel)
    return genotype


# go through the sequence and find if it passes an obstacle or a goes into the wall
def checkIfLegalWalk(board, genotype):
    # hard copy of the board df to be manipulated safely
    grid = board.df.copy()
    # int to mark the already visited spots on the grid
    visitedPosition = 5
    positionHeight, positionWidth = 0, 0
    genotypeList = stringToList(genotype)
    # pre loop preparation !!!! cleanup if possible
    # check if out of the grid
    if positionHeight < 0 or positionHeight > board.height or positionWidth < 0 or positionWidth > board.width:
        return False
    # check if on top of obstacle or already visited place
    if grid[positionHeight][positionWidth] == 5 or grid[positionHeight][positionWidth] == 1:
        return False
    # mark the current pos as visited
    grid[positionHeight, positionWidth] = visitedPosition
    # main check loop
    while len(genotypeList) > 0:
        # get the next step from the genotype
        nextStep = genotypeList.pop(0)
        # mark the current pos as visited
        if nextStep == "N":
            positionHeight -= 1
        elif nextStep == "W":
            positionWidth -= 1
        elif nextStep == "S":
            positionHeight += 1
        elif nextStep == "E":
            positionWidth += 1
        # check if out of the grid
        if positionHeight < 0 or positionHeight >= board.height or positionWidth < 0 or positionWidth >= board.width:
            return False
        # check if on top of obstacle or already visited place
        if grid[positionHeight][positionWidth] == 5 or grid[positionHeight][positionWidth] == 1:
            return False
        grid[positionHeight, positionWidth] = visitedPosition
        # update the current position based on the direction chosen prior
    return True


def muCommaLambda(board,secToRun, verbose, populationSize, parentSize, meanForCreation, stdForCreation,
                  secToSearchCreation, w1distance, w2length):
    # Warning: populationSize / parentSize should be integer !!!!!
    # if verbose true the function is more talkative
    if verbose:
        print("start the evolutionary Algorithm with following board and  parameters:")
        board.printGrid()
        print("Population size =", populationSize )
        print("Parameters for the creation of the Population: mean =", meanForCreation, ",std =", stdForCreation,
              ",time =", secToSearchCreation)
    # init the variables
    generation = 0
    newBestInThisGeneration = True
    startPopulation = list()
    population = list()
    bestString = ""
    bestFitness = sys.maxsize
    endTime = time.time() + secToRun
    # repeat populationSize times
    for x in range(populationSize):
        # create a new individual at random
        individualAsList, foundGoal = createRandomIndividual(board,meanForCreation, stdForCreation, secToSearchCreation)
        # transform the individualAsList to a string for storage
        individualAsString = listToString(individualAsList)
        # append the new individual to the population
        startPopulation.append(individualAsString)
    # make a list containing the fitness's of the individuals
    fitnessList = list()
    for i in startPopulation:
        fitnessList.append(assessFitness(board, stringToList(i), w1distance, w2length))
    # combine the fitness and the individual list in one
    startPopulation = list(zip(startPopulation, fitnessList))
    # store the best individual
    for s, f in startPopulation:
        if f < bestFitness:
            bestFitness = f
            bestString = s
            newBestInThisGeneration = True
    # create the population to start the main loop
    for s, f in startPopulation:
        population.append(s)
    # start the main loop until we run out of time
    while time.time() < endTime:
        # asses the fitness of the population
        fitnessList = list()
        for i in population:
            fitnessList.append(assessFitness(board, stringToList(i), w1distance, w2length))
        # combine the fitness and the individual list in one
        population = list(zip(population, fitnessList))
        # store the best individual
        for s, f in population:
            if f < bestFitness:
                bestFitness = f
                bestString = s
                newBestInThisGeneration = True
        generation += 1
        if verbose:
            if newBestInThisGeneration:
                print("Gen:", generation, "new best individual has fitness =", bestFitness, "and the genotype:", bestString)
        newBestInThisGeneration = False
        # create a empty list for the new population
        parentPopulation = list()
        # select the mu (parentSize) individuals with the greatest fitness
        for i in range(parentSize):
            index = 0
            currentBestIndex = 0
            currentBestFitness = sys.maxsize
            for s, f in population:
                if f < currentBestFitness:
                    currentBestIndex = index
                    currentBestFitness = f
                    currentBestString = s
                index += 1
            # append the remaining best to the temporary population
            parentPopulation.append(population[currentBestIndex])
            # remove the remaining best form the population
            del population[currentBestIndex]
        # clear the population in order to be filled with new mutated individuals
        population.clear()
        # for each individual chosen as parent we insert populationSize/parentSize many mutated "offsprings into
        # here we differ from the muPlusLambda
        # iterate through the parentList
        for parent, f in parentPopulation:
            # for each parent we produce his corresponding port ( being popultion size / parent size
            for i in range(int(populationSize/parentSize)):
                x = mutateGenotype(parent, 0.5, 0.1, 0.5, 0.5, 0.3, 2, 6)
                # check if the mutation is not legal (goes over wall)
                if checkIfLegalWalk(board, x):
                    # if legal genotype append to new population
                    population.append(x)
                else:
                    # else just put the old one in the new population
                    population.append(parent)
    # check if the final solution hits the goal
    h, w = findPositionAfterNSteps(stringToList(bestString), 0)
    if h == board.height - 1 and w == board.width - 1:
        foundGoal = True
    else:
        foundGoal = False
    # prints and returns final solution
    if verbose:
        print("solution is :", bestString, "with fitness:", bestFitness, "and it found goal:", foundGoal)
    return bestString, bestFitness, foundGoal


def muPlusLambda(board,secToRun, verbose, populationSize, parentSize, meanForCreation, stdForCreation,
                  secToSearchCreation, w1distance, w2length):
    # Warning: populationSize / parentSize should be integer !!!!!
    # if verbose true the function is more talkative
    if verbose:
        print("start the evolutionary Algorithm with following board and  parameters:")
        board.printGrid()
        print("Population size =", populationSize )
        print("Parameters for the creation of the Population: mean =", meanForCreation, ",std =", stdForCreation,
              ",time =", secToSearchCreation)
    # init the variables
    generation = 0
    newBestInThisGeneration = True
    startPopulation = list()
    population = list()
    bestString = ""
    bestFitness = sys.maxsize
    endTime = time.time() + secToRun
    # repeat populationSize times
    for x in range(populationSize):
        # create a new individual at random
        individualAsList, foundGoal = createRandomIndividual(board,meanForCreation, stdForCreation, secToSearchCreation)
        # transform the individualAsList to a string for storage
        individualAsString = listToString(individualAsList)
        # append the new individual to the population
        startPopulation.append(individualAsString)
    # make a list containing the fitness's of the individuals
    fitnessList = list()
    for i in startPopulation:
        fitnessList.append(assessFitness(board, stringToList(i), w1distance, w2length))
    # combine the fitness and the individual list in one
    startPopulation = list(zip(startPopulation, fitnessList))
    # store the best individual
    for s, f in startPopulation:
        if f < bestFitness:
            bestFitness = f
            bestString = s
            newBestInThisGeneration = True
    # create the population to start the main loop
    for s, f in startPopulation:
        population.append(s)
    # start the main loop until we run out of time
    while time.time() < endTime:
        # asses the fitness of the population
        fitnessList = list()
        for i in population:
            fitnessList.append(assessFitness(board, stringToList(i), w1distance, w2length))
        # combine the fitness and the individual list in one
        population = list(zip(population, fitnessList))
        # store the best individual
        for s, f in population:
            if f < bestFitness:
                bestFitness = f
                bestString = s
                newBestInThisGeneration = True
        generation += 1
        if verbose:
            if newBestInThisGeneration:
                print("Gen:", generation, "new best individual has fitness =", bestFitness, "and the genotype:", bestString)
        newBestInThisGeneration = False
        # create a empty list for the new population
        parentPopulation = list()
        # select the mu (parentSize) individuals with the greatest fitness
        for i in range(parentSize):
            index = 0
            currentBestIndex = 0
            currentBestFitness = sys.maxsize
            for s, f in population:
                if f < currentBestFitness:
                    currentBestIndex = index
                    currentBestFitness = f
                    currentBestString = s
                index += 1
            # append the remaining best to the temporary population
            parentPopulation.append(population[currentBestIndex])
            # remove the remaining best form the population
            del population[currentBestIndex]
        # clear the population in order to be filled with new mutated individuals
        population.clear()
        # for each individual chosen as parent we insert populationSize/parentSize many mutated "offsprings into
        # population
        # iterate through the parentList
        for parent, f in parentPopulation:
            # here we differ from muCommaLambda in that we add the parents direct to the next generation
            population.append(parent)
            # for each parent we produce his corresponding port ( being popultion size / parent size
            for i in range(int(populationSize/parentSize)):
                foundALegalMutation = False
                maxTime = time.time() + 0.1
                while not foundALegalMutation:
                    x = mutateGenotype(parent, 0.5, 0.1, 0.5, 0.5, 0.3, 2, 6)
                    # check if the mutation is not legal (goes over wall)
                    if checkIfLegalWalk(board, x):
                        # if legal genotype append to new population and go for the next
                        population.append(x)
                        foundALegalMutation = True
                    # if we are overtime we just append the parent again
                    if time.time() < maxTime:
                        # else just put the old one in the new population and go for the next
                        population.append(parent)
                        foundALegalMutation = True
    # check if the final solution hits the goal
    h, w = findPositionAfterNSteps(stringToList(bestString), 0)
    if h == board.height - 1 and w == board.width - 1:
        foundGoal = True
    else:
        foundGoal = False
    # prints and returns final solution
    if verbose:
        print("solution is :", bestString, "with fitness:", bestFitness, "and it found goal:", foundGoal)
    return bestString, bestFitness, foundGoal