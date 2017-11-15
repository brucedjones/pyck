%module TriPrism

%{
#include "../shapes/triprism.h"
%}

class TriPrism : public Shape {

  public:
    TriPrism(int state, std::vector<double> pt1, std::vector<double> pt2, std::vector<double> pt3, double l, bool invert=false);
};
