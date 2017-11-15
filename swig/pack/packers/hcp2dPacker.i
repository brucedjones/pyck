%module Hcp2dPacker

%{
#include "../pack/packers/hcp2dPacker.h"
%}

class Hcp2dPacker : public Packer {

  public:
    Hcp2dPacker(std::vector<double> doubleLenIn, double h, bool rotate90=false, std::vector<double> offset=std::vector<double>());
    std::vector<double> GetPeriodicExtent();
    double GetParticleVolume();
};
