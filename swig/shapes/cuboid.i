%module Cuboid

%{
#include "../shapes/cuboid.h"
%}

class Cuboid : public Shape {

  public:
    Cuboid(int state, double *xyz, double *xyz);
};
