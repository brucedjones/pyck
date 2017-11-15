%module Hcp2dPacker

%{
#include "../pack/packers/hcp2dPacker.h"
%}

class Hcp2dPacker : public Packer {

  public:
    Hcp2dPacker(double *xyz, double h, bool rotate90=false, double *xyz=NULL);
    std::vector<double> GetPeriodicExtent();
    double GetParticleVolume();
};
