%module model

%{
#include "../model.h"
%}

%include "std_string.i"

class Model {
  public:

    Model();

    Model(Pack *pack);

    Model(double *positions, int *states, long numParticles, int dim);

    ~Model();

    void AddPack(Pack *pack);

    void AddPack(double *positions, int *states, long numParticles, int dim);

    int CreateIntField(std::string name, int dim);

    int CreateDoubleField(std::string name, int dim);

    void SetIntField(int handle, int state, int *iprop);

    void SetDoubleField(int handle, int state, double *dprop);

    void AddParameter(std::string key, std::string value);

    void Serialize(std::string fname, Writer *writer);

};
