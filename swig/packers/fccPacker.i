%module FccPacker

%{
#include "../packers/fccPacker.h"
%}

class FccPacker : public Packer {

  public:
    FccPacker(double *xyz, double h);
};
