#ifndef CONVEXHULL2D_H
#define CONVEXHULL2D_H
#include "../shape.h"
#include <vector>
//#include <cmath>

class ConvexHull2D: public Shape {
  public:
    /**
     * ConvexHull2D constructor
     * @param state State to be applied to particles within this shape. state = 0 will remove particle from output
     * @param vp Vertices of the convex hull, a vector of n points each with an x y z coordinate, listed in either clockwise or counter-clockwise order.
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
    std::vector<std::vector<double> > vp; /**< Vertices which define the convex hull */
    double convexArea; /**< Area of the convex hull */
   
};

#endif
