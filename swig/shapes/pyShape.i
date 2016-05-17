%module pyShape

%{
#include "../shapes/pyShape.h"
%}

%typemap(in) PyObject *PyFunc {
  if (!PyCallable_Check($input)) {
      PyErr_SetString(PyExc_TypeError, "Need a callable object!");
      return NULL;
  }
  $1 = $input;
}

class PyShape : public Shape {

  public:
    PyShape(double *p1, double *p2, PyObject *PyFunc);
};
