#include <iostream>

#include "boundingBox.h"
#include "domain.h"

BoundingBox::BoundingBox(float *p1, float *p2, Domain *domain)
{

  // Enforce lower left corner is p1 and upper right is p2
  for(int i=0; i<3; i++)
  {
    if(p1[i]>p2[i])
    {
      float tmp = p1[i];
      p1[i] = p2[i];
      p2[i] = tmp;
    }
  }

  // Convert to domain indexes
  this->p1 = new long[3];
  this->p2 = new long[3];

  // Get the ijk extent
  // Third argument "floors" the ijk indexes (lower left corner) if true
  // "ceils" the ijk indexes (upper right corner) if false
  domain->Pos2IDX(p1, this->p1, true);
  domain->Pos2IDX(p2, this->p2, false);
}

BoundingBox::~BoundingBox()
{
  delete [] p1;
  delete [] p2;
}
