#ifndef BINARY_WRITER_H
#define BINARY_WRITER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

#include "../intField.h"
#include "../doubleField.h"
#include "../writer.h"

#define VTP_BINARY_BLOCK_SIZE (1<<30)

class BinaryWriter : public Writer{
  public:
    BinaryWriter();
    ~BinaryWriter();

    void Write(std::string fname,
      std::map<std::string, std::string> parameters,
      double *positions,
      std::vector<IntField*> intFields,
      std::vector<DoubleField*> doubleFields,
      int dim,
      long numParticles
    );
};

#endif
