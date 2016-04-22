
#ifndef CYLINDRICALPACKER_H
#define CYLINDRICALPACKER_H

#include "../pack.h"
#include "../shape.h"

class CylindricalPacker : public Pack
{
public:

  CylindricalPacker(double *c, double r, double ratio, double h, int state, double num_div = 3.0);
  CylindricalPacker(double *c, double r, double ratio, double *l, double h, int state, double num_div = 3.0);
  CylindricalPacker(double *c, double r, double ratioY, double ratioZ, double h, int state, double num_div = 3.0);
  ~CylindricalPacker();


  void updateStates(double *c, double r,double ratio, int state);
  void updateStates(double *c, double r,double ratioY, double ratioZ, int state);

  void MapShape(Shape *shape);

  double *getPositions();
  int *getStates();
  long getNumParticles();
  int getDim();
};

#endif
