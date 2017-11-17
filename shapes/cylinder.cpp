#include "cylinder.h"
#include <iostream>
#include <math.h>
#include <vector>

Cylinder::Cylinder(int state, std::vector<double> c, double r, std::vector<double> l, bool invert) : Shape(state,invert)
{
  this->c = c;
  this->l = l;

  this->r = r;

  std::vector<double> p1(3);
  std::vector<double> p2(3);

  if(l[0] != 0.0 && l[1] == 0.0 && l[2] == 0.0)
  {
    p1[0] = c[0] + l[0]; p1[1] = c[1] + r; p1[2] = c[2] + r;
    p2[0] = c[0];        p2[1] = c[1] - r; p2[2] = c[2] - r;

  }
  else if(l[0] == 0.0 && l[1] != 0.0 && l[2] == 0.0)
  {
    p1[0] = c[0] + r; p1[1] = c[1] + l[1]; p1[2] = c[2] + r;
    p2[0] = c[0] - r; p2[1] = c[1];        p2[2] = c[2] - r;
  }
  else if(l[0] == 0.0 && l[1] == 0.0 && l[2] != 0.0)
  {
    p1[0] = c[0] + r; p1[1] = c[1] + r; p1[2] = c[2] + l[2];
    p2[0] = c[0] - r; p2[1] = c[1] - r; p2[2] = c[2];
  }
  else
  {
     std::cout << "Incorrect input format for the length of the cylinder. Should be (l,0,0) or (0,l,0) or (0,0,l).\n";
  }


  this->boundingBox = new BoundingBox(p1.data(),p2.data());
}

Cylinder::~Cylinder(){}

bool Cylinder::IsInside(double *pt)
{
  bool isInside = true;

  if(l[0] != 0.0 && l[1] == 0.0 && l[2] == 0.0)
  {
     if((pt[1]-c[1])*(pt[1]-c[1])+(pt[2]-c[2])*(pt[2]-c[2]) > (r*r)) isInside = false;
     // if(fabs(pt[0]-c[0]) > fabs(l[0])) isInside = false;
     if( (pt[0] < c[0]) || (pt[0] > (c[0]+l[0])) )  isInside = false;
  }
  else if(l[0] == 0.0 && l[1] != 0.0 && l[2] == 0.0)
  {
    if((pt[0]-c[0])*(pt[0]-c[0])+(pt[2]-c[2])*(pt[2]-c[2]) > (r*r)) isInside = false;
    // if(fabs(pt[1]-c[1]) > fabs(l[1])) isInside = false;
 if( (pt[1] < c[1]) || (pt[1] > (c[1]+l[1])) )  isInside = false;
  }
  else if(l[0] == 0.0 && l[1] == 0.0 && l[2] != 0.0)
  {
     if((pt[0]-c[0])*(pt[0]-c[0])+(pt[1]-c[1])*(pt[1]-c[1]) > (r*r)) isInside = false;
     // if(fabs(pt[2]-c[2]) > fabs(l[2])) isInside = false;
      if( (pt[2] < c[2]) || (pt[2] > (c[2]+l[2])) )  isInside = false;
  }

  return isInside;
}
