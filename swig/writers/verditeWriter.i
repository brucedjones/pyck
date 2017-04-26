%module VerditeWriter

%{
#include "../writers/verditeWriter.h"
%}

class VerditeWriter : public Writer {
  public:
    VerditeWriter();
};
