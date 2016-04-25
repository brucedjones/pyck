#include "triprism.h"
#include <iostream>
#include <math.h>

TriPrism::TriPrism(int state, double *pt1, double *pt2, double *pt3, double l) : Shape(state)
{

  this->pt1 = pt1;
  this->pt2 = pt2;
  this->pt3 = pt3;
  this->l   = l;


  double *p1 = new double[3];
  double *p2 = new double[3];

  p1[0] = pt3[0]; p1[1]=pt2[1]; p1[2]=pt3[2];
  p2[0] = pt2[0]; p2[1]=pt2[1]; p2[2]=pt2[2]+l;

  this->boundingBox = new BoundingBox(p1,p2);
}

TriPrism::~TriPrism(){}

bool TriPrism::IsInside(double *pt)
{
  // Different to the "same side" methof from the c# code, should be faster this way
  bool isInside = true;
  // Create vectors
  double *v0= new double[3];
  v0[0] = pt2[0] - pt3[0]; v0[1] = pt2[0] - pt3[0]; v0[2] = pt2[0] - pt3[0];
  double *v1= new double[3];
  v1[0] = pt1[0] - pt3[0];  v1[1] = pt1[1] - pt3[1];  v1[2] = pt1[2] - pt3[2];
  double *v2= new double[3];
  v2[0] = pt[0] - pt3[0];v2[1] = pt[1] - pt3[1];v2[2] = pt[2] - pt3[2];

  std::cout << "test" << std::endl;
  // Compute dot products
  double dot00;
  dot00 = v0[0]*v0[0] + v0[1]*v0[1] + v0[2]*v0[2]; 
  double dot01;
  dot01 = v0[0]*v1[0] + v0[1]*v1[1] + v0[2]*v1[2]; 
  double dot02;
  dot02 = v0[0]*v2[0] + v0[1]*v2[1] + v0[2]*v2[2]; 
  double dot11;
  dot11 = v1[0]*v1[0] + v1[1]*v1[1] + v1[2]*v1[2]; 
  double dot12;
  dot12 = v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2]; 
  
  double invDenom = 1 / ( (dot00*dot11)-(dot01-dot01) );
  double u = ((dot11*dot01)-(dot01*dot12))*invDenom;
  double v = ((dot00*dot12)-(dot01*dot02))*invDenom;
 if(!(((u>0) && (v>0) && ((u+v)<1))&&(pt[2]<(pt1[2]+l)))) isInside = false;

 delete [] v0;
 delete [] v1;
 delete [] v2;
//delete v0,v1,v2,dot00,dot01,dot01,dot11,dot12,invDenom,u,v;


  return isInside;
}
