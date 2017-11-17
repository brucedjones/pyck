%module StlShape

%{
#include "../shapes/stlShape.h"
%}

%include "std_string.i"

class StlShape : public Shape {

  public:
    StlShape(int state, std::string fname, std::vector<double> translation = std::vector<double>(), double scale=1.0, std::vector<double> rot_axis = std::vector<double>(), double rot_angle=0.0, bool invert=false);
};
