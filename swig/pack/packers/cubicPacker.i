%module CubicPacker

%{
#include "../pack/packers/cubicPacker.h"
%}

class CubicPacker : public Packer {

  public:
    CubicPacker(double *xyz, double h, double *xyz=nullptr);
    std::vector<double> GetPeriodicExtent();
    double GetParticleVolume();
};
