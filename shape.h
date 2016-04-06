#ifndef SHAPE_H
#define SHAPE_H

#include "boundingBox.h"

/**
 * Abstract class defining a shape to be mapped to the domain
 */
class Shape {
  public:
    /**
     * Shape base constructor
     * @param state The state which will be assigned to particles contained in this shape. state = 0 will remove any previously assigned particles
     */
    Shape(int state);
    ~Shape();

    /**
     * Check if given coordinate is inside this shape
     * @param  pt Coordinates to check
     * @return    True if coordinate is inside shape, false otherwise
     */
    virtual bool IsInside(float *pt)=0;

    BoundingBox *boundingBox; /**< Bounding box which will be iterated over to map the shape */

    int state;  /**< State to be applied on a particle when mapping the shape. state = 0 will remove particle from output.*/
};

#endif
