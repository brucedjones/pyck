#include "pyShape.h"

#include <Python.h>
#include <vector>

PyShape::PyShape(int state, std::vector<double> p1, std::vector<double> p2, PyObject *PyFunc, bool invert) : Shape(state,invert)
{
  this->parallel = false;
  this->boundingBox = new BoundingBox(p1.data(),p2.data());

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

  #if PY_MAJOR_VERSION < 3
    if(PyObject_Compare(result,Py_False)) isInside = true;
  #else
    if(PyObject_RichCompareBool(result,Py_True,Py_EQ)) isInside = true;
  #endif

  Py_DECREF(arglist);
  Py_XDECREF(result);

  return isInside;
}
