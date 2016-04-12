#include <iostream>

#include "pyck.h"
#include "packers/fccPacker.h"
#include "domain.h"
#include "shapes/cuboid.h"
#include "shapes/sphere.h"
#include "shapes/cylinder.h"

int main()
{
  float size[3];
  size[0] = 1; size[1] = 1; size[2] = 1;

  float h = 0.01;

  // Sphere properties
  float r = 0.2;
  float c[3];
  c[0] = 0.5; c[1] = 0.5; c[2] = 0.5;


  // Cylinder properties
  float l[3];
  l[0] = 0.0; l[1] = 0.2; l[2] = 0.0;
    float l2[3];
  l2[0] = 0.0; l2[1] = -0.2; l2[2] = 0.0;


  // Cuboid properties
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
  // Cuboid *box = new Cuboid(1,p1,p2);
  // Sphere *box = new Sphere(1,c,r);
  Cylinder *box = new Cylinder(1,c,r,l);
  Cylinder *box2 = new Cylinder(2,c,r,l2);
  // Cuboid *clearbox = new Cuboid(2,p3,p4);
  domain->MapShape(box);
  domain->MapShape(box2);
  // domain->MapShape(clearbox);

  // Write domain to a CSV
  std::string filename = "packing.txt";
  domain->Serialize((char*)filename.c_str());

  std::cout << "Packing Complete\n";
  std::cout << "File " << filename << " generated" << std::endl;
  delete box;
  delete box2;
  delete domain;
}
