#ifndef SPARK_WRITER_H
#define SPARK_WRITER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

#include "../intField.h"
#include "../doubleField.h"
#include "../writer.h"

#define VTP_BINARY_BLOCK_SIZE (1<<30)

class SparkWriter : public Writer{
  public:
    SparkWriter();
    ~SparkWriter();

    void Write(std::string fname,
      std::map<std::string, std::string> parameters,
      double *positions,
      std::vector<IntField*> intFields,
      std::vector<DoubleField*> doubleFields,
      int dim,
      long numParticles
    );
  private:
    void WriteEncodedString(void *data, long numParticles, int dim, int numBytes, std::ofstream *outfile);
};

#endif
