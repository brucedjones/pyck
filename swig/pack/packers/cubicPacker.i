%module CubicPacker

%{
#include "../pack/packers/cubicPacker.h"
%}

class CubicPacker : public Packer {

  public:
    CubicPacker(double *xyz, double h);
    std::vector<double> GetPeriodicExtent();
};
