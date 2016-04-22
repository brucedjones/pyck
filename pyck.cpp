#include <iostream>

#include "pyck.h"
#include "packers/fccPacker.h"
#include "packers/hcpPacker.h"
#include "packers/bccPacker.h"
#include "packers/cubicPacker.h"
#include "shapes/cuboid.h"
#include "shapes/sphere.h"
#include "shapes/cylinder.h"
#include "writers/sparkWriter.h"
#include "pack.h"
#include "model.h"
#include "cylindricalPacker.h"
#include "ellipsoidalPacker.h"

int main()
{
  double *size = new double[3];
  size[0] = 1; size[1] = 1; size[2] = 1.0;

  double h = 0.005;

  // Sphere properties
  double r = 0.2;
  double *c = new double[3];
  c[0] = 0.5; c[1] = 0.5; c[2] = 0.5;


  // Cylinder properties
  double *l = new double[3];
  l[0] = 0.0; l[1] = 0.0; l[2] = 0.4;
  double rc = 0.1;
  double *cc = new double[3];
  cc[0] = 0.5; cc[1] = 0.5; cc[2] = 0.0;
  /*  double l2[3];
  l2[0] = 0.0; l2[1] = -0.2; l2[2] = 0.0;*/


  // Cuboid properties
  double *p1 = new double[3];
  double *p2 = new double[3];
  double *p3 = new double[3];
  double *p4 = new double[3];

  p1[0] = 0.3; p1[1] = 0.1; p1[2] = -0.2;
  p2[0] = 0.7; p2[1] = 0.9; p2[2] = 0.8;
  p3[0] = 0.0; p3[1] = 0.0; p4[2] = 0.0;
  p4[0] = 0.3; p4[1] = 0.3; p3[2] = 0.3;

  // Create a new packer
  // CubicPacker *packer = new CubicPacker(size,h);
  // // Create a new pack
  // Pack *pack = new Pack(packer);
  // Pack *pack2 = new Pack(packer);

  // // Create and pack a shape
  // Cuboid *box = new Cuboid(1,p1,p2);
  // Cuboid *box2 = new Cuboid(5,p3,p4);
  // Sphere *sphere = new Sphere(2,c,r);
  // Cylinder *cylinder = new Cylinder(3,cc,rc,l);

  // pack->AddShape(box);
  // pack->AddShape(sphere);
  // pack->AddShape(cylinder);
  // pack->Process();

  // pack2->AddShape(box2);
  // pack2->Process();


  CylindricalPacker *radialpack2D  = new CylindricalPacker(c, r, 0.4,h, 1, 4.0);
  // CylindricalPacker *radialpack3D  = new CylindricalPacker(h, 1, c, r, 0.8,l);
  // CylindricalPacker *radialpack3D2  = new CylindricalPacker(h, 1, c, r, 0.2,0.4);
  EllipsoidalPacker *ellipsoid3D  = new EllipsoidalPacker(c, r, 0.4,h, 1, 0.000001,0.65);
  // EllipsoidalPacker *ellipsoid3D  = new EllipsoidalPacker(h, 1, c, r, 0.4);

// Model *model = new Model();
 // Model *model = new Model(radialpack2D->getPositions(),radialpack2D->getStates(),radialpack2D->getNumParticles(),radialpack2D->getDim());
 // Model *model = new Model(radialpack3D->getPositions(),radialpack3D->getStates(),radialpack3D->getNumParticles(),radialpack3D->getDim());
 // Model *model = new Model(radialpack3D2->getPositions(),radialpack3D2->getStates(),radialpack3D2->getNumParticles(),radialpack3D2->getDim());
 Model *model = new Model(ellipsoid3D->getPositions(),ellipsoid3D->getStates(),ellipsoid3D->getNumParticles(),ellipsoid3D->getDim());

  // model->AddPack(pack2);

  int stateField = model->CreateIntField("State",1);
  int desiredState[1];
  desiredState[0] = 10;
  model->SetIntField(stateField,1,desiredState);

  int velocityField = model->CreateDoubleField("Velocity",1);
  double desiredVelocity[3];
  desiredVelocity[0]=5.0; desiredVelocity[1]=7.0; desiredVelocity[2]=9.0;
  model->SetDoubleField(velocityField,1,desiredVelocity);

  model->SetParameter("TestParam1","0.1");
  model->SetParameter("TestParam2","0.2");
  model->SetParameter("TestParam3","0.6");

  // Create a new writer
  model->Serialize("sw_test.vtp", new SparkWriter());

  std::cout << "Packing Complete\n";
  //std::cout << "File " << filename << " generated" << std::endl;
  // delete box;
  // delete sphere;
  // delete cylinder;
  delete radialpack2D;
  // delete radialpack3D;
  // delete radialpack3D2;
  delete ellipsoid3D;
  // delete packer;
  // delete pack;
  delete model;
}
