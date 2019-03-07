%module BinaryWriter

%{
#include "../writers/binaryWriter.h"
%}

class BinaryWriter : public Writer {
  public:
    BinaryWriter();
};
