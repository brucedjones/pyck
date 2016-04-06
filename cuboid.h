#ifndef CUBOID_H
#define CUBOID_H
#include "shape.h"

class Cuboid: public Shape {
  public:
    Cuboid(int state, float *p1, float *p2, Domain *domain);
    ~Cuboid();

    bool IsInside(float *pt);

  private:
    float *p1, *p2;
};

#endif
