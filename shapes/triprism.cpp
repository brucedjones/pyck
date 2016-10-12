#include "triprism.h"
#include <iostream>
#include <math.h>
#include <algorithm>

TriPrism::TriPrism(int state, double *pt1, double *pt2, double *pt3, double l, bool invert) : Shape(state,invert)
{

  this->l   = l;
  this->pt1 = new double[3];
  this->pt2 =new double[3];
  this->pt3 = new double[3];
  this->pt1[0] = pt1[0]; this->pt1[1] = pt1[1]; this->pt1[2] = pt1[2];
  this->pt2[0] = pt2[0]; this->pt2[1] = pt2[1]; this->pt2[2] = pt2[2];
  this->pt3[0] = pt3[0]; this->pt3[1] = pt3[1]; this->pt3[2] = pt3[2];

  double *p1 = new double[3];
  double *p2 = new double[3];

  p1[0] = std::min(pt1[0],std::min(pt2[0],pt3[0])); p1[1]=std::min(pt1[1],std::min(pt2[1],pt3[1])); p1[2]=std::min(pt1[2],std::min(pt2[2],pt3[2]));
  p2[0] = std::max(pt1[0],std::max(pt2[0],pt3[0])); p2[1]=std::max(pt1[1],std::max(pt2[1],pt3[1])); p2[2]=p1[2]+l;

  this->boundingBox = new BoundingBox(p1,p2);
}

TriPrism::~TriPrism(){
 delete [] pt1;
 delete [] pt2;
 delete [] pt3;
}

bool TriPrism::IsInside(double *pt)
{
  // barycentric method http://www.blackpawn.com/texts/pointinpoly/
  // Create vectors
  double v0[3];
  double v1[3];
  double v2[3];

  v0[0] = pt2[0] - pt3[0];
  v0[1] = pt2[1] - pt3[1];
  v0[2] = pt2[2] - pt3[2];

  v1[0] = pt1[0] - pt3[0];
  v1[1] = pt1[1] - pt3[1];
  v1[2] = pt1[2] - pt3[2];

  v2[0] = pt[0] - pt3[0];
  v2[1] = pt[1] - pt3[1];
  v2[2] = pt[2] - pt3[2];


  // Compute dot products
  double dot00;
  dot00 = (v0[0]*v0[0]) + (v0[1]*v0[1]) + (v0[2]*v0[2]);
  double dot01;
  dot01 = (v0[0]*v1[0]) + (v0[1]*v1[1]) + (v0[2]*v1[2]);
  double dot02;
  dot02 = (v0[0]*v2[0]) + (v0[1]*v2[1]) + (v0[2]*v2[2]);
  double dot11;
  dot11 = (v1[0]*v1[0]) + (v1[1]*v1[1]) + (v1[2]*v1[2]);
  double dot12;
  dot12 = (v1[0]*v2[0]) + (v1[1]*v2[1]) + (v1[2]*v2[2]);
  double u;
  double v;
  double invDenom = 1 / ( (dot00*dot11)-(dot01*dot01) );
  u = ((dot11*dot02)-(dot01*dot12))*invDenom;
  v = ((dot00*dot12)-(dot01*dot02))*invDenom;

  return ( (u>=0) && (v>=0) && ((u+v)<1) && (pt[2]<=(pt1[2]+l)));
}
