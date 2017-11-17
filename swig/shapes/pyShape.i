%module pyShape

%{
#include "../shapes/pyShape.h"
%}

class PyShape : public Shape {

  public:
    PyShape(int state, std::vector<double> p1, std::vector<double> p2, PyObject *PyFunc, bool invert=false);
};
