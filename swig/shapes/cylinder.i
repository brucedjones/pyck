%module Cylinder

%{
#include "../shapes/cylinder.h"
%}

class Cylinder : public Shape {

  public:
    Cylinder(int state, double *xyz, double r, double *xyz);
};
