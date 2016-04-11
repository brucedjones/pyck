#include <iostream>

#include "pyck.h"
#include "fccPacker.h"
#include "domain.h"
#include "cuboid.h"

int main()
{
  float size[3];
  size[0] = 1; size[1] = 1; size[2] = 1;

  float h = 0.1;

  float p1[3], p2[3], p3[3], p4[3];
  p1[0] = 0.2; p1[1] = 0.2; p1[2] = 0.2;
  p2[0] = 0.8; p2[1] = 0.8; p2[2] = 0.8;
  p3[0] = 0.4; p3[1] = 0.4; p4[2] = 0.2;
  p4[0] = 0.6; p4[1] = 0.6; p3[2] = 0.8;

  // Create a new packer
  FccPacker *packer = new FccPacker(size,h);

  // Create a new domain
  Domain *domain = new Domain(packer);

  // Create and pack a shape
  Cuboid *box = new Cuboid(1,p1,p2);
  Cuboid *clearbox = new Cuboid(2,p3,p4);
  domain->MapShape(box);
  domain->MapShape(clearbox);

  // Write domain to a CSV
  domain->Serialize("particles4.csv");

  std::cout << "Packing Complete\n";
  delete box;
  delete domain;
}
