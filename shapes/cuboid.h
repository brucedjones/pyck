#ifndef CUBOID_H
#define CUBOID_H

#include "../shape.h"

#include <vector>

class Cuboid: public Shape {
  public:
    /**
     * Cuboid constructor
     * @param state State to be applied to particles within this shape. state = 0 will remove particle from output
     * @param p1 Lower-left corner of cuboid in cartesian coordinates
     * @param p2 Upper-right corner of cuboid in cartesian coordinates
     * @param invert Inverts the shape to tag particles outside the shape instead of inside
     */
    Cuboid(int state, std::vector<double> p1, std::vector<double> p2, bool invert = false);
    ~Cuboid();

    /**
     * Check if given coordinate is inside this shape
     * @param  pt Coordinates to check
     * @return    True if coordinate is inside shape, false otherwise
     */
    bool IsInside(double *pt);

  private:
    std::vector<double> p1; /**< Lower-left corner of cuboid in cartesian coordinates */
    std::vector<double> p2; /**< Upper-right corner of cuboid in cartesian coordinates */
};

#endif
