%module HcpPacker

%{
#include "../packers/hcpPacker.h"
%}

class HcpPacker : public Packer {

  public:
    HcpPacker(double *xyz, double h);
};
