#ifndef SHAPE_H
#define SHAPE_H

#include "boundingBox.h"

class Shape {
  public:
    Shape(int state);
    ~Shape();

    virtual bool IsInside(float *pt)=0;
    BoundingBox *boundingBox;

    int state;
};

#endif
