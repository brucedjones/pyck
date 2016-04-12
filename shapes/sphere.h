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
     * @param domain Domain in which this shape will be mapped
     */
    Sphere(int state, float *c, float r);
    ~Sphere();

    /**
     * Check if given coordinate is inside this shape
     * @param  pt Coordinates to check
     * @return    True if coordinate is inside shape, false otherwise
     */
    bool IsInside(float *pt);

  private:
    float *c; /**< Center of the sphere in cartesian coordinates */
    float r; /**< Radius of the sphere */
};

#endif
