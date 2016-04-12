#include "sphere.h"

Sphere::Sphere(int state, float *c, float r) : Shape(state)
{
  this->c = c;
  this->r = r;

  float *p1 = new float[3];
  float *p2 = new float[3];
  p1[0] = c[0] + r; p1[1] = c[1] + r; p1[2] = c[2] + r;
  p2[0] = c[0] - r; p2[1] = c[1] - r; p2[2] = c[2] - r;

  this->boundingBox = new BoundingBox(p1,p2);
}

Sphere::~Sphere(){}

bool Sphere::IsInside(float *pt)
{
  bool isInside = true;
  
  if((pt[0]-c[0])*(pt[0]-c[0])+(pt[1]-c[1])*(pt[1]-c[1])+(pt[2]-c[2])*(pt[2]-c[2]) > (r*r)) isInside = false;

  return isInside;
}
