%module model

%{
#include "../model.h"
%}

%include "std_string.i"
%include "std_map.i"
namespace std {
%template(Parameters) map<string, string>;
}

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

    void SetParameter(std::string key, std::string value);

    void SetParameters(std::map<std::string, std::string> &parameters);

    void Serialize(std::string fname, Writer *writer);

};
