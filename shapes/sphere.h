#ifndef SPHERE_H
#define SPHERE_H
#include "../shape.h"

class Sphere: public Shape {
  public:
    /**
     * Sphere constructor
     * @param state State to be applied to particles within this shape. state = 0 will remove particle from output
     * @param c Center of the sphere in cartesian coordinates
     * @param r Radius of the sphere
     */
    Sphere(int state, double *c, double r);
    ~Sphere();

    /**
     * Check if given coordinate is inside this shape
     * @param  pt Coordinates to check
     * @return    True if coordinate is inside shape, false otherwise
     */
    bool IsInside(double *pt);

  private:
    double *c; /**< Center of the sphere in cartesian coordinates */
    double r; /**< Radius of the sphere */
};

#endif
