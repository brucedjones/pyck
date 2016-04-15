#ifndef SPARK_WRITER_H
#define SPARK_WRITER_H

#include <string>
#include <vector>
#include <map>

#include "../intField.h"
#include "../doubleField.h"
#include "../writer.h"

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
      int numParticles
    );
};

#endif
