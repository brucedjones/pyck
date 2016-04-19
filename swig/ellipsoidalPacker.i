%module EllipsoidalPacker

%{
#include "../ellipsoidalPacker.h"
%}

class EllipsoidalPacker
{
public:

  EllipsoidalPacker(double h, int state, double *xyz, double r, double ratioY, double ratioZ);
  ~EllipsoidalPacker();

  double *getPositions();
  int *getStates();
  long getNumParticles();
  int getDim();
};
