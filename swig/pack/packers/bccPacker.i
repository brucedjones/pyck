%module BccPacker

%{
#include "../pack/packers/bccPacker.h"
%}

class BccPacker : public Packer {

  public:
    BccPacker(double *xyz, double h);
    std::vector<double> GetPeriodicExtent();
    double GetParticleVolume();
};
