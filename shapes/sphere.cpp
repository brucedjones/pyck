#include "sphere.h"

Sphere::Sphere(int state, double *c, double r) : Shape(state)
{
  this->c = new double[3];
  this->c[0] = c[0];
  this->c[1] = c[1];
  this->c[2] = c[2];

  this->r = r;

  double *p1 = new double[3];
  double *p2 = new double[3];
  p1[0] = c[0] + r; p1[1] = c[1] + r; p1[2] = c[2] + r;
  p2[0] = c[0] - r; p2[1] = c[1] - r; p2[2] = c[2] - r;

  this->boundingBox = new BoundingBox(p1,p2);

  delete [] p1;
  delete [] p2;
}

Sphere::~Sphere(){
  delete [] c;
}

bool Sphere::IsInside(double *pt)
{
  bool isInside = true;

  if((pt[0]-c[0])*(pt[0]-c[0])+(pt[1]-c[1])*(pt[1]-c[1])+(pt[2]-c[2])*(pt[2]-c[2]) > (r*r)) isInside = false;

  return isInside;
}
