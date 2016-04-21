
#ifndef CYLINDRICALPACKER_H
#define CYLINDRICALPACKER_H


class CylindricalPacker
{
public:
  
  CylindricalPacker(double *c, double r, double ratio, double h, int state, double num_div = 3.0);
  CylindricalPacker(double *c, double r, double ratio, double *l, double h, int state, double num_div = 3.0);
  CylindricalPacker(double *c, double r, double ratioY, double ratioZ, double h, int state, double num_div = 3.0);
  ~CylindricalPacker();
  

  void updateStates(double *c, double r,double ratio, int state);
  void updateStates(double *c, double r,double ratioY, double ratioZ, int state);


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
