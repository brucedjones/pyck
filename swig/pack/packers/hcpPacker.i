%module HcpPacker

%{
#include "../pack/packers/hcpPacker.h"
%}

class HcpPacker : public Packer {

  public:
    HcpPacker(double *xyz, double h, bool rotate90=false);
    std::vector<double> GetPeriodicExtent();
};
