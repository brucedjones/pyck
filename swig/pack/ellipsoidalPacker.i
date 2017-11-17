%module EllipsoidalPacker

%{
#include "../pack/ellipsoidalPacker.h"
%}

class EllipsoidalPacker : Pack
{
public:

  EllipsoidalPacker(std::vector<double> c, double r, double ratio,double h, int state, double tolerance_angle = 0.001, double tolerance_h = 0.55, bool random_startingpoint = true, bool adjust_h = true);
  EllipsoidalPacker(std::vector<double> c, double r, double ratio, std::vector<double> l, double h, int state, double tolerance_angle = 0.001, double tolerance_h = 0.55, bool random_startingpoint = true, bool adjust_h = true);
  EllipsoidalPacker(std::vector<double> c, double r, double ratioY, double ratioZ, double h, int state, double tolerance_angle = 0.001, double tolerance_h = 0.55, bool random_startingpoint = true, bool adjust_h = true);
  void AddShape(Shape *shape);
  void Process();
  void updateStates(std::vector<double> c, double r0, double h, double r,double ratio, int state);
  void updateStates(std::vector<double> c, double r0, double h, double r,double ratioY, double ratioZ, int state);

  double *getPositions();
  int *getStates();
  long GetNumParticles();
  long GetNumParticlesByState(int state);
  int getDim();
};
