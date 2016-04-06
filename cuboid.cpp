#include "cuboid.h"

Cuboid::Cuboid(int state, float *p1, float *p2, Domain *domain) : Shape(state)
{
  this->p1 = p1;
  this->p2 = p2;

  this->boundingBox = new BoundingBox(p1,p2,domain);
}

Cuboid::~Cuboid(){}

bool Cuboid::IsInside(float *pt)
{
  bool isInside = true;
  for(int i=0; i<3; i++){
    if(pt[i]<=p1[i]) isInside = false;
    if(pt[i]>=p2[i]) isInside = false;
  }

  return isInside;
}
