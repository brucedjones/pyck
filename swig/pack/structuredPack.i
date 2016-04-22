%module StructuredPack

%{
#include "../pack/structuredPack.h"
%}

class StructuredPack : Pack {
  public:
    StructuredPack(Packer *packer);
    void AddShape(Shape *shape);
    void Process();
};
