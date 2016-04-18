
#ifndef CYLINDRICALPACKER_H
#define CYLINDRICALPACKER_H


class CylindricalPacker
{
public:
  
  CylindricalPacker(double h, int state, double *c, double r, double ratio);
  CylindricalPacker(double h, int state, double *c, double r, double ratio, double *l);
  ~CylindricalPacker();
  
  double *getPositions();
  int *getStates();
  long getNumParticles();
  int getDim();


private: 
  double *positions;
  int *states;
  long numParticles;
  int dim;
};

#endif
