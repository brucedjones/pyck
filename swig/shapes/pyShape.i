%module pyShape

%{
#include "../shapes/pyShape.h"
%}

class PyShape : public Shape {

  public:
    PyShape(int state, double *xyz, double *xyz, PyObject *PyFunc, bool invert=false);
};
