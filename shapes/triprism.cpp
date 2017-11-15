#include "triprism.h"
#include <iostream>
#include <math.h>
#include <algorithm>

TriPrism::TriPrism(int state, std::vector<double> pt1, std::vector<double> pt2, std::vector<double> pt3, double l, bool invert) : Shape(state,invert)
{

  this->l   = l;
  this->pt1 = pt1;
  this->pt2 = pt2;
  this->pt3 = pt3;

  std::vector<double> p1(3);
  std::vector<double> p2(3);

  if(pt1.size() != pt2.size() && pt1.size() != pt3.size()) std::cout << "Error: Inconsistent dimensions specified for Triangular Prism" << std::endl;
  else {
    for(size_t i=0; i<pt1.size();i++) p1[i] = std::min(pt1[i],std::min(pt2[i],pt3[i]));
    for(size_t i=0; i<pt1.size();i++) p2[i] = std::max(pt1[i],std::max(pt2[i],pt3[i]));
  }

  this->boundingBox = new BoundingBox(p1.data(),p2.data());
}

TriPrism::~TriPrism(){}

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
