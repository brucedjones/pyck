%module Sphere

%{
#include "../shapes/sphere.h"
%}

class Sphere : public Shape {

  public:
    Sphere(int state, double *xyz, double r, bool invert=false);
};
