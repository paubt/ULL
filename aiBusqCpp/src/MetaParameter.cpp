//
// Created by pau on 27/10/21.
//

#include "MetaParameter.h"


MetaParameter::MetaParameter(int h, int w, int oC, int eC, int tC): height(h), width(w),
                            obstacleCode(oC), emptySpaceCode(eC), taxiCode(tC){
    generator.seed(42);
}

MetaParameter::MetaParameter(const MetaParameter &metaParameterToCopy) {
    height            = metaParameterToCopy.getHeight();
    width             = metaParameterToCopy.getWidth();
    obstacleCode      = metaParameterToCopy.getObstacleCode();
    emptySpaceCode    = metaParameterToCopy.getEmptySpaceCode();
    taxiCode          = metaParameterToCopy.getTaxiCode();
    generator.seed(42);
}

void MetaParameter::setHeight(int newHeight) {
    height = newHeight;
}

void MetaParameter::setWidth(int newWidth) {
    width = newWidth;
}

int MetaParameter::getHeight() const {
    return height;
}

int MetaParameter::getWidth() const {
    return width;
}

int MetaParameter::getObstacleCode() const {
    return obstacleCode;
}

int MetaParameter::getEmptySpaceCode() const {
    return emptySpaceCode;
}

int MetaParameter::getTaxiCode() const {
    return taxiCode;
}

// warning this assignment operator doesn't transfer the generator state

MetaParameter &MetaParameter::operator=(const MetaParameter &other) {
    height = other.getHeight();
    width = other.getWidth();
    obstacleCode = other.getObstacleCode();
    emptySpaceCode = other.getEmptySpaceCode();
    taxiCode = other.getTaxiCode();
    generator.seed(42);
    return *this;
}
