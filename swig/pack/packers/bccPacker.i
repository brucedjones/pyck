%module BccPacker

%{
#include "../pack/packers/bccPacker.h"
%}

class BccPacker : public Packer {

  public:
    BccPacker(std::vector<double> doubleLenIn, double h, std::vector<double> offset=std::vector<double>());
    std::vector<double> GetPeriodicExtent();
    double GetParticleVolume();
};
