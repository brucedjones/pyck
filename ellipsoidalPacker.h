
#ifndef ELLIPSOIDALPACKER_H
#define ELLIPSOIDALPACKER_H


class EllipsoidalPacker
{
public:
  
  EllipsoidalPacker(double *c, double r, double ratio,double h, int state, double tolerance_angle = 0.001, double tolerance_h = 0.55, bool random_startingpoint = true, bool adjust_h = true);
  EllipsoidalPacker(double *c, double r, double ratio, double *l, double h, int state, double tolerance_angle = 0.001, double tolerance_h = 0.55, bool random_startingpoint = true, bool adjust_h = true);
  EllipsoidalPacker(double *c, double r, double ratioY, double ratioZ, double h, int state, double tolerance_angle = 0.001, double tolerance_h = 0.55, bool random_startingpoint = true, bool adjust_h = true);
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
