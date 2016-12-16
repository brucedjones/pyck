#include <vector>
#include <algorithm>

#include "compositeShape.h"

CompositeShape::CompositeShape(int state, std::vector<Shape*> shapes, bool invert) : Shape(state,invert)
{
  this->shapes = shapes;
  
  double *p1 = new double[3];
  double *p2 = new double[3];

  p1[0] = 999999999999999; p1[1] = 999999999999999; p1[2] = 999999999999999;
  p2[0] = -999999999999999; p2[1] = -999999999999999; p2[2] = -999999999999999;

  for(int i = 0; i<shapes.size(); i++)
  {
      for(int d = 0; d<3; d++)
      {
          p1[d] = std::min(p1[d],shapes[i]->boundingBox->p1[d]);
          p2[d] = std::max(p2[d],shapes[i]->boundingBox->p2[d]);
      }
  }

  this->boundingBox = new BoundingBox(p1,p2);

  delete [] p1;
  delete [] p2;
}

CompositeShape::~CompositeShape()
{
    //delete shapes;
}

bool CompositeShape::IsInside(double *pt)
{
  bool isInside = true;

  for (int i=0; i<shapes.size(); i++)
  {
      if(!shapes[i]->IsInside(pt)) isInside = false;
  }

  return isInside;
}
