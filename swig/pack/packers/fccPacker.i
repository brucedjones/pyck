%module FccPacker

%{
#include "../pack/packers/fccPacker.h"
%}

class FccPacker : public Packer {

  public:
    FccPacker(std::vector<double> doubleLenIn, double h, std::vector<double> offset=std::vector<double>());
    std::vector<double> GetPeriodicExtent();
    double GetParticleVolume();
};