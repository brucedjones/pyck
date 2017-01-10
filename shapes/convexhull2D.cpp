#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>
#include "convexhull2D.h"

ConvexHull2D::ConvexHull2D(int state, std::vector<std::vector<double> > vp, bool invert) : Shape(state, invert)
{
  this->vp=vp;
  int np = vp.size();
  double *p1 = new double[3];
  double *p2 = new double[3];
  p1[0] = vp[0][0]; p1[1] = vp[0][1]; p1[2] = vp[0][2];
  p2[0] = vp[0][0]; p2[1] = vp[0][1]; p2[2] = vp[0][2];
  
  
  for (int i = 0; i < vp.size(); i++)
  {
    for (int d = 0; d < 3; d++)
    {
      if(vp[i][d] < p1[d]) p1[d] = vp[i][d];
      if(vp[i][d] > p2[d]) p2[d] = vp[i][d];
    }
  }
  double  convexArea=0.0;
  int j = vp.size() - 1;
  for (int i=0; i<vp.size(); i++){convexArea += (vp[j][0] + vp[i][0]) * (vp[j][1] - vp[i][1]); j=i;}
  this->convexArea = 0.5*fabs(convexArea);

  // pointer to array for first point: &vp[0][0]
  this->boundingBox = new BoundingBox(p1,p2);
  
  delete [] p1;
  delete [] p2;
}

bool ConvexHull2D::IsInside(double *pt)
{
  bool isInside = true;

  double  TriSum =0.0;
  int j = vp.size() - 1;
  
  for (int i=0; i<vp.size(); i++){
    TriSum += 0.5* fabs((vp[j][0] - pt[0])*(vp[i][1] - vp[j][1]) - (vp[j][0]- vp[i][0])*(pt[1] - vp[j][1])); 
    j=i;
  }

  if(fabs(TriSum - convexArea) > convexArea*1e-15) isInside = false;

  return isInside;
}