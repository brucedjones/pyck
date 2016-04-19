%module Pack

%{
#include "../pack.h"
%}

class Pack {
  public:
    Pack(Packer *packer);
    void AddShape(Shape *shape);
    void Process();
};
