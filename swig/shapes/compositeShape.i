%module CompositeShape

%{
#include "../shapes/compositeShape.h"
%}

namespace std {
    %template(ShapeVector) vector<Shape*>;
}

class CompositeShape: public Shape {

  public:
    CompositeShape(int state, std::vector<Shape*> shapes, bool invert=false);
};