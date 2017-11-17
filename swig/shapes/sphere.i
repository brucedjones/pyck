%module Sphere

%{
#include "../shapes/sphere.h"
%}

class Sphere : public Shape {

  public:
    Sphere(int state, std::vector<double> c, double r, bool invert=false);
};
