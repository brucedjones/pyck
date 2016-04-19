%module CubicPacker

%{
#include "packers/cubicPacker.h"
%}

%typemap(in) (double *xyz) {
 int i;
 if (!PySequence_Check($input)) {
   PyErr_SetString(PyExc_ValueError,"Expected a sequence");
   return NULL;
 }

 $1 = (double *) malloc(3*sizeof(double));

 for (i = 0; i < 3; i++) {
   PyObject *s = PyList_GetItem($input,i);
   $1[i] = (double) PyFloat_AsDouble(s);
 }
}

%typemap(freearg) (double *xyz) {
  if ($1) free($1);
}

class CubicPacker {

  public:
    CubicPacker(double *xyz, double h);
};
