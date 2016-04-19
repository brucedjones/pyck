%module BccPacker

%{
#include "../packers/bccPacker.h"
%}

class BccPacker : public Packer {

  public:
    BccPacker(double *xyz, double h);
};
