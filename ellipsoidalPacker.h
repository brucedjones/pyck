
#ifndef ELLIPSOIDALPACKER_H
#define ELLIPSOIDALPACKER_H


class EllipsoidalPacker
{
public:
  
  EllipsoidalPacker(double h, int state, double *c, double r, double ratioY, double ratioZ);
  ~EllipsoidalPacker();
  
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
