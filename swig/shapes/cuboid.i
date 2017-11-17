%module Cuboid

%{
#include "../shapes/cuboid.h"
%}

class Cuboid : public Shape {

  public:
    Cuboid(int state, std::vector<double> p1, std::vector<double> p2, bool invert = false);
};
