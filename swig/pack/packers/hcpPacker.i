%module HcpPacker

%{
#include "../pack/packers/hcpPacker.h"
%}

class HcpPacker : public Packer {
  public:
    HcpPacker(std::vector<double> doubleLenIn, double h, bool rotate90=false, std::vector<double> offset=std::vector<double>());
    std::vector<double> GetPeriodicExtent();
    double GetParticleVolume();
};
