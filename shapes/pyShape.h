#ifndef PYSHAPE_H
#define PYSHAPE_H
#include "../shape.h"

#include <Python.h>

class PyShape: public Shape {
  public:
    /**
     * PyShape constructor
     * @param state State to be applied to particles within this shape. state = 0 will remove particle from output
     * @param c Center of the sphere in cartesian coordinates
     * @param r Radius of the sphere
     * @param domain Domain in which this shape will be mapped
     */
    PyShape(double *p1, double *p2, PyObject *PyFunc);
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
