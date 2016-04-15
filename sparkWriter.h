#ifndef SPARK_WRITER_H
#define SPARK_WRITER_H

#include <vector>
#include <string>
#include <map>

#include "domain.h"
#include "intField.h"
#include "doubleField.h"

class SparkWriter {
  public:
    SparkWriter(Domain *domain);
    ~SparkWriter();

    int CreateIntField(std::string name, int dim);
    int CreateDoubleField(std::string name, int dim);
    void SetIntField(int handle, int state, int *val);
    void SetDoubleField(int handle, int state, double *val);
    void Serialize(std::string fname);
    void AddParameter(std::string key, std::string value);

  private:
    Domain *domain;
    long numParticles;
    int domDim;
    double *pos;
    int *domState;
    std::vector<IntField*> intFields;
    std::vector<DoubleField*> doubleFields;
    std::map<std::string, std::string> parameters;
};

#endif
