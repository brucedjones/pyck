%module model

%{
#include "../model.h"
#include "../intField.h"
#include "../doubleField.h"
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

    Model(std::vector<double> positions, std::vector<int> states, long numParticles, int dim);

    ~Model();

    void AddPack(Pack *pack);

    void AddPack(double *positions, int *states, long numParticles, int dim);
    
    void AddPack(std::vector<double> positions, std::vector<int> states, long numParticles, int dim);

    int CreateIntField(std::string name, int dim);

    int CreateDoubleField(std::string name, int dim);

    void SetIntField(int handle, int state, int val);

    void SetIntField(int handle, int state, std::vector<int> val);

    %rename SetIntField SetIntFieldCallback;
    void SetIntField(int handle, int state, PyObject *PyFunc);

    IntField *GetIntField(int handle);

    void SetDoubleField(int handle, int state, double val);

    void SetDoubleField(int handle, int state, std::vector<double> val);

    %rename SetDoubleField SetDoubleFieldCallback;
    void SetDoubleField(int handle, int state, PyObject *PyFunc);

    DoubleField *GetDoubleField(int handle);

    void SetParameter(std::string key, std::string value);

    void SetParameters(std::map<std::string, std::string> &parameters);

    int ReadSingleIntegerParameter(std::string key);

    std::vector<double> Model::ReadMultipleDoubleParameter(std::string key, int n);

    void Serialize(std::string fname, Writer *writer);

};
