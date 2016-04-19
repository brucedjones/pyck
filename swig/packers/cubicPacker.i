%module CubicPacker

%{
#include "../packers/cubicPacker.h"
%}

class CubicPacker : public Packer {

  public:
    CubicPacker(double *xyz, double h);
};
