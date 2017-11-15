%module CubicPacker

%{
#include "../pack/packers/cubicPacker.h"
%}

class CubicPacker : public Packer {

  public:
    CubicPacker(std::vector<double> doubleLenIn, double h, std::vector<double> offset=std::vector<double>());
    std::vector<double> GetPeriodicExtent();
    double GetParticleVolume();
};
