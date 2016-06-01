%module StlShape

%{
#include "../shapes/stlShape.h"
%}

%include "std_string.i"

class StlShape : public Shape {

  public:
    StlShape(int state, std::string fname, double *xyz=NULL, double scale=1.0, double *xyz=NULL, double rot_angle=0.0);
};
