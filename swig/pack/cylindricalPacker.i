%module CylindricalPacker

%{
#include "../pack/cylindricalPacker.h"
%}

class CylindricalPacker : Pack
{
public:

  CylindricalPacker(double *xyz, double r, double ratio, double h, int state, double num_div = 3.0);
  CylindricalPacker(double *xyz, double r, double ratio, double *xyz, double h, int state, double num_div = 3.0);
  CylindricalPacker(double *xyz, double r, double ratioY, double ratioZ, double h, int state, double num_div = 3.0);

  void AddShape(Shape *shape);
  void Process();
  void updateStates(double *xyz, double r,double ratio, int state);
  void updateStates(double *xyz, double r,double ratioY, double ratioZ, int state);

  double *getPositions();
  int *getStates();
  long GetNumParticles();
  long GetNumParticlesByState(int state);
  int getDim();
};
