#include <iostream>

#include "cuboid.h"

Cuboid::Cuboid(int state, double *p1, double *p2) : Shape(state)
{
  this->p1 = new double[3];
  this->p2 = new double[3];
  this->p1[0] = p1[0]; this->p1[1] = p1[1]; this->p1[2] = p1[2];
  this->p2[0] = p2[0]; this->p2[1] = p2[1]; this->p2[2] = p2[2];

  this->boundingBox = new BoundingBox(this->p1,this->p2);
}

Cuboid::~Cuboid(){
  delete [] this->p1;
  delete [] this->p2;
}

bool Cuboid::IsInside(double *pt)
{
  bool isInside = true;
  for(int i=0; i<3; i++){
    if(pt[i]<p1[i]) isInside = false;
    if(pt[i]>p2[i]) isInside = false;
  }

  return isInside;
}
