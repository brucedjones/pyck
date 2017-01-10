#ifndef CONVEXHULL2D_H
#define CONVEXHULL2D_H
#include "../shape.h"
#include <vector>
//#include <cmath>

class ConvexHull2D: public Shape {
  public:
    /**
     * Sphere constructor
     * @param state State to be applied to particles within this shape. state = 0 will remove particle from output
     * @param c Center of the sphere in cartesian coordinates
     * @param r Radius of the sphere
     * @param invert Inverts the shape to tag particles outside the shape instead of inside
     */
    ConvexHull2D(int state, std::vector<std::vector<double> > vp, bool invert = false);
    ~ConvexHull2D(){};

    /**
     * Check if given coordinate is inside this shape
     * @param  pt Coordinates to check
     * @return    True if coordinate is inside shape, false otherwise
     */
    bool IsInside(double *pt);

  private:
    std::vector<std::vector<double> > vp ;
    double convexArea;
   
};

#endif
