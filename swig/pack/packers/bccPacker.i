%module BccPacker

%{
#include "../pack/packers/bccPacker.h"
%}

class BccPacker : public Packer {

  public:
    BccPacker(double *xyz, double h, double *xyz=nullptr);
    std::vector<double> GetPeriodicExtent();
    double GetParticleVolume();
};
