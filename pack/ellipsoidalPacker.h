
#ifndef ELLIPSOIDALPACKER_H
#define ELLIPSOIDALPACKER_H

#include "../pack.h"
#include "../shape.h"

class EllipsoidalPacker : public Pack
{
public:

  EllipsoidalPacker(double *c, double r, double ratio,double h, int state, double tolerance_angle = 0.001, double tolerance_h = 0.55, bool random_startingpoint = true, bool adjust_h = true);
  EllipsoidalPacker(double *c, double r, double ratio, double *l, double h, int state, double tolerance_angle = 0.001, double tolerance_h = 0.55, bool random_startingpoint = true, bool adjust_h = true);
  EllipsoidalPacker(double *c, double r, double ratioY, double ratioZ, double h, int state, double tolerance_angle = 0.001, double tolerance_h = 0.55, bool random_startingpoint = true, bool adjust_h = true);
  ~EllipsoidalPacker();

  void updateStates(double *c, double r0, double h, double r,double ratio, int state);
  void updateStates(double *c, double r0, double h, double r,double ratioY, double ratioZ, int state);

  void MapShape(Shape *shape);

  double *getPositions();
  int *getStates();
  long getNumParticles();
  int getDim();

private:
};

#endif
