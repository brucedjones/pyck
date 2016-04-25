#include "boundingBox.h"
BoundingBox::BoundingBox(double *p1, double *p2)
{
  // Enforce lower left corner is p1 and upper right is p2
  for(int i=0; i<3; i++)
  {
    if(p1[i]>p2[i])
    {
      double tmp = p1[i];
      p1[i] = p2[i];
      p2[i] = tmp;
    }
  }

  this->p1 = new double[3];
  this->p1[0] = p1[0];
  this->p1[1] = p1[1];
  this->p1[2] = p1[2];

  this->p2 = new double[3];
  this->p2[0] = p2[0];
  this->p2[1] = p2[1];
  this->p2[2] = p2[2];
}

BoundingBox::~BoundingBox()
{
  delete [] p1;
  delete [] p2;
}
