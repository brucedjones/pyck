%module StlShape

%{
#include "../shapes/stlShape.h"
%}

%include "std_string.i"

class StlShape : public Shape {

  public:
    StlShape(int state, std::string fname, double *xyz, double scale);
};
