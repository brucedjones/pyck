#ifndef PYSHAPE_H
#define PYSHAPE_H
#include "../shape.h"

#include <Python.h>

class PyShape: public Shape {
  public:
    /**
     * PyShape constructor
     * @param state State to be applied to particles within this shape. state = 0 will remove particle from output
     * @param p1 Lower-left corner of the shapes bounding box in cartesian coordinates
     * @param p2 Upper-right corner of the shapes bounding box in cartesian coordinates
     * @param PyFunc Python callback defining the shape. Takes 3 arguments, x, y, and z, coordinates of a point. Returns true if a particle is inside the shape and false otherwsie
     */
    PyShape(int state, double *p1, double *p2, PyObject *PyFunc);
    ~PyShape();

    /**
     * Check if given coordinate is inside this shape
     * @param  pt Coordinates to check
     * @return    True if coordinate is inside shape, false otherwise
     */
    bool IsInside(double *pt);

  private:
    PyObject *pyCallback;
};

#endif
