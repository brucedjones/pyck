#include "pyShape.h"

#include <Python.h>

PyShape::PyShape(int state, double *p1, double *p2, PyObject *PyFunc) : Shape(state)
{
  this->parallel = false;
  this->boundingBox = new BoundingBox(p1,p2);

  pyCallback = PyFunc;
  Py_XINCREF(pyCallback);
}

PyShape::~PyShape(){
  Py_XDECREF(pyCallback);
  delete boundingBox;
}

bool PyShape::IsInside(double *pt)
{
  bool isInside = false;

  PyObject *func, *arglist;
  PyObject *result;

  func = pyCallback;
  arglist = Py_BuildValue("(ddd)",pt[0],pt[1],pt[2]);
  result =  PyEval_CallObject(func, arglist);

  if(PyObject_Compare(result,Py_False)){
    isInside = true;
  }

  Py_DECREF(arglist);
  Py_XDECREF(result);

  return isInside;
}
