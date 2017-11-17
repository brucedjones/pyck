#ifndef CYLINDER_H
#define CYLINDER_H

#include "../shape.h"

#include <vector>

class Cylinder: public Shape {
  public:
    /**
     * Cylinder constructor
     * @param state State to be applied to particles within this shape. state = 0 will remove particle from output
     * @param c Center of the cylinder in cartesian coordinates
     * @param r Radius of the cylinder
     * @param l Length of the cylinder in cartesian coordinates, (0,0,l) or (0,l,0) or (l,0,0) indicates the direction
     * @param domain Domain in which this shape will be mapped
     * @param invert Inverts the shape to tag particles outside the shape instead of inside
     */
    Cylinder(int state, std::vector<double> c, double r, std::vector<double> l, bool invert=false);
    ~Cylinder();

    /**
     * Check if given coordinate is inside this shape
     * @param  pt Coordinates to check
     * @return    True if coordinate is inside shape, false otherwise
     */
    bool IsInside(double *pt);

  private:
    std::vector<double> c; /**< Center of the cylinder in cartesian coordinates */
    double r; /**< Radius of the cylinder */
    std::vector<double> l; /**< Length of the cylinder */
};

#endif
