#ifndef CUBOID_H
#define CUBOID_H
#include "../shape.h"

class Cuboid: public Shape {
  public:
    /**
     * Cuboid constructor
     * @param state State to be applied to particles within this shape. state = 0 will remove particle from output
     * @param p1 Lower-left corner of cuboid in cartesian coordinates
     * @param p2 Upper-right corner of cuboid in cartesian coordinates
     */
    Cuboid(int state, double *p1, double *p2);
    ~Cuboid();

    /**
     * Check if given coordinate is inside this shape
     * @param  pt Coordinates to check
     * @return    True if coordinate is inside shape, false otherwise
     */
    bool IsInside(double *pt);

  private:
    double *p1; /**< Lower-left corner of cuboid in cartesian coordinates */
    double *p2; /**< Upper-right corner of cuboid in cartesian coordinates */
};

#endif
