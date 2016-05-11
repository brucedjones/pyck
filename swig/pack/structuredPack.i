%module StructuredPack

%{
#include "../pack/structuredPack.h"
#include <vector>
%}

%include "std_vector.i"


%typemap(out) std::vector<double> {
  int i;
  $result = PyList_New(3);
  for (i = 0; i < 3; i++) {
    std::vector<double> res = (std::vector<double>)$1;
    PyObject *o = PyFloat_FromDouble(res[i]);
    PyList_SetItem($result,i,o);
  }
}

class StructuredPack : Pack {
  public:
    StructuredPack(Packer *packer);
    void AddShape(Shape *shape);
    void Process();
    long GetNumParticles();
    long GetNumParticlesByState(int state);
    std::vector<double> GetClosestParticlePosition(double *xyz);
};
