#ifndef WRITER_H
#define WRITER_H

#include <string>
#include <vector>
#include <map>

#include "intField.h"
#include "doubleField.h"

class Writer {
  public:
    Writer();
    ~Writer();

    virtual void Write(std::string fname,
      std::map<std::string, std::string> parameters,
      double *positions,
      std::vector<IntField*> intFields,
      std::vector<DoubleField*> doubleFields,
      int dim,
      int numParticles
    )=0;
};

#endif
