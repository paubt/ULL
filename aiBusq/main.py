import time

import algorithm
from board import Board


def game():
    gridRows = int(input("How many rows would you like to have in your grid?"))
    gridColumns = int(input("How many columns would you like to have in your grid?"))
    obstacleRatio = input("What obstacle ratio would you like to have in your grid?")
    board = Board(gridRows, gridColumns, 1, 0, 2, obstacleRatio, True)
    if int(input("Do you want to put the obstacles automatically or manually?\n(0) automatically\n(1) manually")) == 1:
        grid = board.placeObstacles()
    x = int(input("in which row do you like to place the taxi?"))
    y = int(input("in which column do you like to place the taxi?"))
    grid = board.placeGoal(x, y)
    print("Your starting grid:\n", grid)


def evaluationSmall(nTimes):
    testBoard = Board(20, 20, "X", "·", 2, 3, 0.2, True)
    # talk a bit
    print("Small Evaluation\n")
    print("start the evolutionary Algorithms with following board and algorithm parameters:")
    print("board size:", testBoard.height, testBoard.width, "with obstacle ratio:", testBoard.obstacleRatio,
          "and time to run", 5)
    print("Algorithm muCommaLambda \npopulation size is 500 and the parent size is", 100)
    print("Algorithm muPlusLambda \npopulation size is 500 and the parent size is", 10)
    print("Parameters for the creation of both Populations: mean =", 20, ",std =", 10,
          ",time =", 1)
    # common algorithm parameter
    timeToRun = 5
    # output
    mclRatioC = 0
    mclRatioP = 0
    avgSolutionLengthC = 0
    avgSolutionLengthP = 0
    avgDistanceLeftIfNotFoundC = 0
    avgDistanceLeftIfNotFoundP = 0
    # repeat n times
    for i in range(nTimes):
        # testBoard.printGrid()
        # execute the search algorithm 1
        s1, f1, g1 = algorithm.muCommaLambda(testBoard,timeToRun, verbose=True, populationSize=500, parentSize=100,
                                          meanForCreation=20    , stdForCreation=10, secToSearchCreation=1,
                                          w1distance=2, w2length=1)
        # if the algo found a path to the goal add one for the ratio
        if g1:
            mclRatioC += 1
            avgSolutionLengthC += len(s1)
        else:
            x, y = algorithm.findPositionAfterNSteps(algorithm.stringToList(s1), 0)
            avgDistanceLeftIfNotFoundC += avgDistanceLeftIfNotFoundC + algorithm.taxiCabDistance(x, y, testBoard.height-1, testBoard.width - 1)
        # execute the search algorithm 1
        s2, f2, g2 = algorithm.muPlusLambda(testBoard, timeToRun, verbose=True, populationSize=500, parentSize=10,
                                             meanForCreation=50, stdForCreation=10, secToSearchCreation=1,
                                             w1distance=2, w2length=1)
        # if the algo found a path to the goal add one for the ratio
        if g2:
            mclRatioP += 1
            avgSolutionLengthP += len(s2)
        else:
            x, y = algorithm.findPositionAfterNSteps(algorithm.stringToList(s2), 0)
            avgDistanceLeftIfNotFoundP += avgDistanceLeftIfNotFoundP + algorithm.taxiCabDistance(x, y, testBoard.height-1, testBoard.width - 1)

        testBoard.redistributeObstacles()
        # print some stuff
        if True:
            print("board number", i)
            print("muCommaLambda found a solution:", g1, " with fitness:", f1, "and string:", s1)
            print("muPLusLambda found a solution:", g2, " with fitness:", f2, "and string:", s2, "\n")
    if mclRatioC == 0:
        avgSolutionLengthC = 0
    else:
        avgSolutionLengthC = avgSolutionLengthC/mclRatioC
    if mclRatioP == 0:
        avgSolutionLengthP = 0
    else:
        avgSolutionLengthP = avgSolutionLengthP/mclRatioP

    if nTimes == mclRatioC:
        avgDistanceLeftIfNotFoundC = 0
    else:
        avgDistanceLeftIfNotFoundC = avgDistanceLeftIfNotFoundC / (nTimes - mclRatioC)
    if nTimes == mclRatioP:
        avgDistanceLeftIfNotFoundP = 0
    else:
        avgDistanceLeftIfNotFoundP = avgDistanceLeftIfNotFoundP / (nTimes - mclRatioP)

    print("mcl ratio for comma", mclRatioC / nTimes, ", average solution length:", avgSolutionLengthC, end=" ")
    print("and a average distance missing to the solution of ", avgDistanceLeftIfNotFoundC)
    print("mcl ratio for  plus", mclRatioP / nTimes, ", average solution length:", avgSolutionLengthP, end=" ")
    print("and a average distance missing to the solution of ", avgDistanceLeftIfNotFoundP)


def evaluationBig(nTimes):
    testBoard = Board(50, 50, "X", "·", 2, 3, 0.2, True)
    # talk a bit
    print("big evaluation\n")
    print("start the evolutionary Algorithms with following board and algorithm parameters:")
    print("board size:", testBoard.height, testBoard.width, "with obstacle ratio:", testBoard.obstacleRatio,
          "and time to run", 10)
    print("Algorithm muCommaLambda \npopulation size is 500 and the parent size is", 100)
    print("Algorithm muPlusLambda \npopulation size is 500 and the parent size is", 10)
    print("Parameters for the creation of both Populations: mean =", 60, ",std =", 30,
          ",time =", 1)
    # common algorithm parameter
    timeToRun = 60
    # output
    mclRatioC = 0
    mclRatioP = 0
    avgSolutionLengthC = 0
    avgSolutionLengthP = 0
    avgDistanceLeftIfNotFoundC = 0
    avgDistanceLeftIfNotFoundP = 0

    # repeat n times
    for i in range(nTimes):
        # testBoard.printGrid()
        # execute the search algorithm 1
        s1, f1, g1 = algorithm.muCommaLambda(testBoard, timeToRun, verbose=False, populationSize=500, parentSize=100,
                                             meanForCreation=100, stdForCreation=50, secToSearchCreation=1,
                                             w1distance=2, w2length=1)
        # if the algo found a path to the goal add one for the ratio
        if g1:
            mclRatioC += 1
            avgSolutionLengthC += len(s1)
        else:
            x, y = algorithm.findPositionAfterNSteps(algorithm.stringToList(s1), 0)
            avgDistanceLeftIfNotFoundC += avgDistanceLeftIfNotFoundC + algorithm.taxiCabDistance(x, y, testBoard.height-1, testBoard.width - 1)
        # execute the search algorithm 1
        s2, f2, g2 = algorithm.muPlusLambda(testBoard, timeToRun, verbose=False, populationSize=500, parentSize=10,
                                            meanForCreation=100, stdForCreation=50, secToSearchCreation=1,
                                            w1distance=3, w2length=1)
        # if the algo found a path to the goal add one for the ratio
        if g2:
            mclRatioP += 1
            avgSolutionLengthP += len(s2)
        else:
            x, y = algorithm.findPositionAfterNSteps(algorithm.stringToList(s2), 0)
            avgDistanceLeftIfNotFoundP += avgDistanceLeftIfNotFoundP + algorithm.taxiCabDistance(x, y, testBoard.height-1, testBoard.width - 1)

        testBoard.redistributeObstacles()

        # print some stuff
        if True:
            print("board number", i)
            print("muCommaLambda found a solution:", g1, " with fitness:", f1, "and string:", s1)
            print("muPLusLambda found a solution:", g2, " with fitness:", f2, "and string:", s2, "\n")

    if mclRatioC == 0:
        avgSolutionLengthC = 0
    else:
        avgSolutionLengthC = avgSolutionLengthC / mclRatioC
    if mclRatioP == 0:
        avgSolutionLengthP = 0
    else:
        avgSolutionLengthP = avgSolutionLengthP / mclRatioP
    if nTimes == mclRatioC:
        avgDistanceLeftIfNotFoundC = 0
    else:
        avgDistanceLeftIfNotFoundC = avgDistanceLeftIfNotFoundC / (nTimes - mclRatioC)
    if nTimes == mclRatioP:
        avgDistanceLeftIfNotFoundP = 0
    else:
        avgDistanceLeftIfNotFoundP = avgDistanceLeftIfNotFoundP / (nTimes - mclRatioP)
    print("mcl ratio for comma", mclRatioC / nTimes, ", average solution length:", avgSolutionLengthC, end=" ")
    print("and a average distance missing to the solution of ", avgDistanceLeftIfNotFoundC)
    print("mcl ratio for  plus", mclRatioP / nTimes, ", average solution length:", avgSolutionLengthP, end=" ")
    print("and a average distance missing to the solution of ", avgDistanceLeftIfNotFoundP)


if __name__ == '__main__':
    timeStart = time.time()
    evaluationSmall(1)
    timeStop = time.time()
    print("the small took :", timeStop-timeStart, "seconds\n\n")
    timeStart = time.time()
    #evaluationBig(20)
    timeStop = time.time()
    print("the small took :", timeStop - timeStart, "seconds\n\n")