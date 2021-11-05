import numpy as np
import math

"""base class for the board class storing all the parameters"""


class MetaParameter:
    # constructor
    def __init__(self, height, width, obstacleCode, emptySpaceCode, goalCode, startCode):
        # init the class variables
        self.height = height
        self.width = width
        self.obstacleCode = obstacleCode
        self.emptySpaceCode = emptySpaceCode
        self.goalCode = goalCode
        self.startCode = startCode


class Board(MetaParameter):
    # constructor
    def __init__(self, height, width, obstacleCode, emptySpaceCode, goalCode, startCode,
                 obstacleRatio, possibleToSolve):
        super().__init__(height, width, obstacleCode, emptySpaceCode, goalCode, startCode)
        self.obstacleRatio = float(obstacleRatio)
        self.possibleToSolve = possibleToSolve

        # create a grid and fill it with obstacles
        self.df = self.createObstacleGrid()
        self.df[0, 0] = self.startCode
        self.df[height-1, width-1] = self.goalCode

    #
    def redistributeObstacles(self):
        newDf = self.createObstacleGrid()
        self.df = newDf
        self.df[0, 0] = self.startCode
        self.df[self.height - 1, self.width - 1] = self.goalCode

    # used in the init function for df creation
    def createObstacleGrid(self):
        df = np.zeros((self.height, self.width))
        counter = 0
        # we need to calculate the obstacleNumber from the obstacleRatio
        obstacleNumber = self.height * self.width * self.obstacleRatio
        while counter < obstacleNumber:
            x = np.random.randint(0, len(df))
            y = np.random.randint(0, len(df[0]))
            if df[x, y] != 1:
                df[x, y] = 1
                counter += 1

        return df

    # for manual obstacle distribution in the grit
    def placeObstacles(self):
        df = np.zeros((self.height, self.width))
        obstacleNumber = int(self.height * self.width + self.obstacleRatio)
        counter = 0
        while counter < obstacleNumber:
            row = int(input("in which row do you want to put the obstacle?"))
            column = int(input("in which column do you want to put the obstacle?"))
            df[row - 1, column - 1] = 1
            counter += 1
        return df

    # prints the grid ( layout copied from wikipedia)
    # holy shit what a mess, if there is a cleaner way please change
    # or better implement a plot function using matplotlib
    def printGrid(self):
        # print width in decimal scale
        if self.width >= 10:
            for i in range(math.ceil(self.width / 10)):
                if i == 0:
                    print(" " * 21, end="")
                else:
                    print(str(i) + "0", end="")
                    print(" " * 18, end="")
        print("\n  ", end="")
        # print width in one digit scale
        for i in range(self.width):
            if (i % 10) == 0:
                if i == 0:
                    print(i, end=" ")
                else:
                    print(" ", end=" ")
            else:
                print(i % 10, end=" ")
        print("")
        # prints rows of X's for the frame
        for i in range(self.width + 2):
            print("X", end=" ")
        print("")
        # iterates through rows of the dataframe putting a X in the beginning and a X and the row number at the end
        i = 0
        for row in self.df:
            print("X", end=" ")
            for item in row:
                if item == 1:
                    print(self.obstacleCode, end=" ")
                elif item == 0:
                    print(self.emptySpaceCode, end=" ")
                elif item == 2:
                    print(self.goalCode, end=" ")
                elif item == 5:
                    print("5", end=" ")
                else:
                    print(self.startCode, end=" ")
            print("X " + str(i))
            i += 1
        # prints a row of X's for the frame
        for i in range(self.width + 2):
            print("X", end=" ")
        print("")
