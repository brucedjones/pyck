%module AsciiWriter

%{
#include "../writers/asciiWriter.h"
%}

class AsciiWriter : public Writer {
  public:
    AsciiWriter();
};
