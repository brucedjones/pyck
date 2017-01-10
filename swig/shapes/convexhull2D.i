%module ConvexHull2D

%{
#include "../shapes/convexhull2D.h"
%}

class ConvexHull2D : public Shape {

  public:
    ConvexHull2D(int state, std::vector<std::vector<double> > vp, bool invert=false);
};
