%module StructuredPack

%{
#include "../pack/structuredPack.h"
%}

class StructuredPack : Pack {
  public:
    StructuredPack(Packer *packer);
    void AddShape(Shape *shape);
    void Process();
    long GetNumParticles();
    double * GetPositions();
    long GetNumParticlesByState(int state);
    std::vector<double> GetClosestParticlePosition(std::vector<double> pos);
};
