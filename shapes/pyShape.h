#ifndef PYSHAPE_H
#define PYSHAPE_H
#include "../shape.h"

#include <Python.h>
#include <vector>

class PyShape: public Shape {
  public:
    /**
     * PyShape constructor
     * @param state State to be applied to particles within this shape. state = 0 will remove particle from output
     * @param p1 Lower-left corner of the shapes bounding box in cartesian coordinates
     * @param p2 Upper-right corner of the shapes bounding box in cartesian coordinates
     * @param PyFunc Python callback defining the shape. Takes 3 arguments, x, y, and z, coordinates of a point. Returns true if a particle is inside the shape and false otherwise
     * @param invert Inverts the shape to tag particles outside the shape instead of inside
     */
    PyShape(int state, std::vector<double> p1, std::vector<double> p2, PyObject *PyFunc, bool invert=false);
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
