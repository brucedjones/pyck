%module SparkWriter

%{
#include "../writers/sparkWriter.h"
%}

class SparkWriter : public Writer {
  public:
    SparkWriter();
};
