#include <iostream>

#include "cuboid.h"

#include <vector>

Cuboid::Cuboid(int state, std::vector<double> p1, std::vector<double> p2, bool invert) : Shape(state,invert)
{
  this->p1 = p1;
  this->p2 = p2;

  this->boundingBox = new BoundingBox(p1.data(),p2.data());
}

Cuboid::~Cuboid(){}

bool Cuboid::IsInside(double *pt)
{
  bool isInside = true;
  for(int i=0; i<3; i++){
    if(pt[i]<p1[i]) isInside = false;
    if(pt[i]>p2[i]) isInside = false;
  }

  return isInside;
}
