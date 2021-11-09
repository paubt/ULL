//
// Created by pau on 27/10/21.
//

#ifndef ASTULL_METAPARAMETER_H
#define ASTULL_METAPARAMETER_H

#include "random"

class MetaParameter {
public:
    int height;
    int width;
    int obstacleCode;
    int emptySpaceCode;
    int taxiCode;
    std::default_random_engine generator;
    // constructor
    MetaParameter(int h, int w, int oC = 1, int eC = 0, int tC = 2);
    // copy constructor
    MetaParameter(MetaParameter const& metaParameterToCopy);
    // assignment operator
    MetaParameter& operator=(const MetaParameter& other);

    //setter for parameter
    void setHeight(int newHeight);
    void setWidth(int newWidth);
    //getter for parameter
    int  getHeight() const;
    int  getWidth() const;
    int  getObstacleCode() const;
    int  getEmptySpaceCode() const;
    int  getTaxiCode() const;
};


#endif //ASTULL_METAPARAMETER_H
