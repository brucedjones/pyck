%module CylindricalPacker

%{
#include "../cylindricalPacker.h"
%}

class CylindricalPacker
{
public:

  CylindricalPacker(double h, int state, double *xyz, double r, double ratio);
  //CylindricalPacker(double h, int state, double *xyz, double r, double ratio, double *xyz);
  //CylindricalPacker(double h, int state, double *xyz, double r, double ratioY, double ratioZ);

  double *getPositions();
  int *getStates();
  long getNumParticles();
  int getDim();
};
