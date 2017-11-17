%module Cylinder

%{
#include "../shapes/cylinder.h"
%}

class Cylinder : public Shape {

  public:
    Cylinder(int state, std::vector<double> c, double r, std::vector<double> l, bool invert=false);
};
