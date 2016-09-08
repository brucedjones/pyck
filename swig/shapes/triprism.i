%module TriPrism

%{
#include "../shapes/triprism.h"
%}

class TriPrism : public Shape {

  public:
    TriPrism(int state, double *xyz, double *xyz, double *xyz, double l, bool invert=false);
};
