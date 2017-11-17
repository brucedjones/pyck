#include "sphere.h"

#include<vector>

Sphere::Sphere(int state, std::vector<double> c, double r, bool invert) : Shape(state,invert)
{
  this->c = c;

  this->r = r;

  std::vector<double> p1(3);
  std::vector<double> p2(3);

  for(size_t i=0; i<p1.size();i++){
    p1[i] = c[i] + r;
    p2[i] = c[i] - r;
  }

  this->boundingBox = new BoundingBox(p1.data(),p2.data());
}

Sphere::~Sphere(){}

bool Sphere::IsInside(double *pt)
{
  bool isInside = true;

  if((pt[0]-c[0])*(pt[0]-c[0])+(pt[1]-c[1])*(pt[1]-c[1])+(pt[2]-c[2])*(pt[2]-c[2]) > (r*r)) isInside = false;

  return isInside;
}
