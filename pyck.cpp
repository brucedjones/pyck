#include <iostream>

#include "pyck.h"
#include "packers/fccPacker.h"
#include "packers/hcpPacker.h"
#include "packers/bccPacker.h"
#include "packers/cubicPacker.h"
#include "domain.h"
#include "shapes/cuboid.h"
#include "shapes/sphere.h"
#include "shapes/cylinder.h"
#include "writers/sparkWriter.h"

int main()
{
  double size[3];
  size[0] = 1; size[1] = 1; size[2] = 0.0;

  double h = 0.05;

  // Sphere properties
  double r = 0.2;
  double c[3];
  c[0] = 0.5; c[1] = 0.5; c[2] = 0.0;


  // Cylinder properties
  double l[3];
  l[0] = 0.0; l[1] = 0.0; l[2] = 0.1;
  double rc = 0.1;
  double cc[3];
  cc[0] = 0.5; cc[1] = 0.5; cc[2] = 0.0;
  /*  double l2[3];
  l2[0] = 0.0; l2[1] = -0.2; l2[2] = 0.0;*/


  // Cuboid properties
  double p1[3], p2[3], p3[3], p4[3];
  p1[0] = 0.3; p1[1] = 0.1; p1[2] = -0.2;
  p2[0] = 0.7; p2[1] = 0.9; p2[2] = 0.8;
  p3[0] = 0.4; p3[1] = 0.4; p4[2] = -0.2;
  p4[0] = 0.6; p4[1] = 0.6; p3[2] = 0.8;

  // Create a new packer
  CubicPacker *packer = new CubicPacker(size,h);

  // Create a new writer
  SparkWriter *sw = new SparkWriter();
  // Create a new domain
  Domain *domain = new Domain(packer,sw);

  // Create and pack a shape
  Cuboid *box = new Cuboid(1,p1,p2);
  Sphere *sphere = new Sphere(2,c,r);
  Cylinder *cylinder = new Cylinder(3,cc,rc,l);

  domain->AddShape(box);
  domain->AddShape(sphere);
  domain->AddShape(cylinder);
  domain->Pack();

  int stateField = domain->CreateIntField("STATE",1);
  int desiredState[1];
  desiredState[0] = 10;
  domain->SetIntField(stateField,1,desiredState);

  int velocityField = domain->CreateDoubleField("VELOCITY",3);
  double desiredVelocity[3];
  desiredVelocity[0]=5.0; desiredVelocity[1]=7.0; desiredVelocity[2]=9.0;
  domain->SetDoubleField(velocityField,1,desiredVelocity);

  domain->AddParameter("TestParam1","0.1");
  domain->AddParameter("TestParam2","0.2");
  domain->AddParameter("TestParam3","0.6");


  domain->Serialize("sw_test.csv");

  std::cout << "Packing Complete\n";
  //std::cout << "File " << filename << " generated" << std::endl;
  delete box;
  delete sphere;
  delete cylinder;
  delete packer;
  delete domain;
}
