#define M_PI 3.14159265358979323846264338327

#include <iostream>
#include <omp.h>
#include <math.h>
#include <algorithm>
#include <vector>
#include "cylindricalPacker.h"

struct particle
{
  double x;
  double y;
  double z;
  int state;
};

particle make_particle(double x, double y, double z, int state)
{
  particle p = {x, y, z, state};
  return p;
}

CylindricalPacker::CylindricalPacker(double h, int state, double *c, double r, double ratio)
{

  double halfcircle_number_of_divisions = 3.0; // number of divisions of a half circle

  std::vector<particle> p;

  p.push_back(make_particle(0.0,0.0,0.0,state));

  double ra = h;
  double dr = h;
  double dth = 0.0;
  double th = 0.0;
  double curvmax = 0.0;
  double curv = 0.0;
  double rat = 0.0;
  long number_of_particles = 1;

  while(ra <= r)
  {
    dth=M_PI*sqrt(dr*dr*ratio)/(halfcircle_number_of_divisions*(sqrt(ra*ra*ratio)));
    th=0.0;
    curvmax = std::max(ra/(ra*ra*ratio*ratio),(ra*ratio)/(ra*ra));

    while(th<= 2*M_PI-dth/2)
    {
      curv = (ra*ra*ratio) / pow(sqrt(ra*ra*sin(th)*sin(th)+ra*ratio*ratio*ra*cos(th)*cos(th)),3.0);
      rat = curv/curvmax;

      p.push_back(make_particle((ra)*cos(th),(ra*ratio)*sin(th),0.0,state));

      th=th+dth;
      number_of_particles=number_of_particles+1;   
    }
    ra=ra+dr;
  }

  states = new int[number_of_particles];
  positions = new double[number_of_particles*3];

  for(long i = 0; i < number_of_particles; i++)
  {
    positions[3*i + 0] = p[i].x + c[0];
    positions[3*i + 1] = p[i].y + c[1];
    positions[3*i + 2] = p[i].z + c[2];
    states[i] = p[i].state;
  }

  this->numParticles = number_of_particles;
  this->dim = 2;

  return;
}

CylindricalPacker::CylindricalPacker(double h, int state, double *c, double r, double ratio, double *l)
{

  double L = 0.0;
  if(l[0] == 0.0 && l[1] == 0.0 && l[2] == 0.0)
  {
    std::cout << "Incorrect input format for the length of the cylinder. Should be (l,0,0) or (0,l,0) or (0,0,l).\n";
  }
  if(l[0] != 0.0 && l[1] == 0.0 && l[2] == 0.0)
  {
    L = l[1];
  }
  else if(l[0] == 0.0 && l[1] != 0.0 && l[2] == 0.0)
  {
    L = l[1];
  }
  else if(l[0] == 0.0 && l[1] == 0.0 && l[2] != 0.0)
  {
    L = l[2];
  }


  double halfcircle_number_of_divisions = 3.0; // number of divisions of a half circle

  std::vector<particle> p;

  p.push_back(make_particle(0.0,0.0,0.0,state));

  double ra = h;
  double dr = h;
  double dth = 0.0;
  double th = 0.0;
  double curvmax = 0.0;
  double curv = 0.0;
  double rat = 0.0;
  long number_of_particles = 1;

  while(ra <= r)
  {
    dth=M_PI*sqrt(dr*dr*ratio)/(halfcircle_number_of_divisions*(sqrt(ra*ra*ratio)));
    th=0.0;
    curvmax = std::max(ra/(ra*ra*ratio*ratio),(ra*ratio)/(ra*ra));

    while(th<= 2*M_PI-dth/2)
    {
      curv = (ra*ra*ratio) / pow(sqrt(ra*ra*sin(th)*sin(th)+ra*ratio*ratio*ra*cos(th)*cos(th)),3.0);
      rat = curv/curvmax;

      if(l[0] != 0.0 && l[1] == 0.0 && l[2] == 0.0)
      {
        p.push_back(make_particle(0.0,(ra)*cos(th),(ra*ratio)*sin(th),state));

      }
      else if(l[0] == 0.0 && l[1] != 0.0 && l[2] == 0.0)
      {
        p.push_back(make_particle((ra*ratio)*sin(th),0.0,(ra)*cos(th),state));
      }
      else if(l[0] == 0.0 && l[1] == 0.0 && l[2] != 0.0)
      {
        p.push_back(make_particle((ra)*cos(th),(ra*ratio)*sin(th),0.0,state));
      }
      

      th=th+dth;
      number_of_particles=number_of_particles+1;   
    }
    ra=ra+dr;
  }

  double htemp;
  long numparttemp = number_of_particles;
  if (L > 0.0)
  {
    htemp = h;
  }
  else
  {
    htemp = -h;
  }


  for(long n = 1; n <= ceil(fabs(L / htemp)); n++)
  {
    for(long i = 0; i < numparttemp; i++)
    {
      if(l[0] != 0.0 && l[1] == 0.0 && l[2] == 0.0)
      {
        p.push_back(make_particle(p[i].x + n * htemp,p[i].y,p[i].z,state));

      }
      else if(l[0] == 0.0 && l[1] != 0.0 && l[2] == 0.0)
      {
        p.push_back(make_particle(p[i].x,p[i].y + n * htemp,p[i].z + n * h,state));
      }
      else if(l[0] == 0.0 && l[1] == 0.0 && l[2] != 0.0)
      {
        p.push_back(make_particle(p[i].x,p[i].y,p[i].z + n * htemp,state));
      }
      number_of_particles=number_of_particles+1;
    }

  }

  states = new int[number_of_particles];
  positions = new double[number_of_particles*3];

  for(long j = 0; j < number_of_particles; j++)
  {
    positions[3*j + 0] = p[j].x + c[0];
    positions[3*j + 1] = p[j].y + c[1];
    positions[3*j + 2] = p[j].z + c[2];
    states[j] = p[j].state;
  }

  this->numParticles = number_of_particles;
  this->dim = 3;

  return;
}

CylindricalPacker::CylindricalPacker(double h, int state, double *c, double r, double ratioY, double ratioZ)
{
  double halfcircle_number_of_divisions = 3.0; // number of divisions of a half circle

  std::vector<particle> p;


  double ra;
  double dr;
  double dth;
  double th;
  double curvmax;
  double curv;
  double rat;
  double ratio;
  long number_of_particles = 1;
  double current_radius;

  for(double z = -(r*ratioZ);z<=(r*ratioZ);z+=h)
  {
    ra = h;
    dr = h;
    dth = 0.0;
    th = 0.0;
    curvmax = 0.0;
    curv = 0.0;
    rat = 0.0;
    ratio = ratioY;
    current_radius = r * sqrt(1-((z*z)/(r*ratioZ*r*ratioZ)));

      if(current_radius != 0.0) p.push_back(make_particle(0.0,0.0,z,state));
      while(ra <= current_radius)
      {
        dth=M_PI*sqrt(dr*dr*ratio)/(halfcircle_number_of_divisions*(sqrt(ra*ra*ratio)));
        th=0.0;
        curvmax = std::max(ra/(ra*ra*ratio*ratio),(ra*ratio)/(ra*ra));

        while(th<= 2*M_PI-dth/2)
        {
          curv = (ra*ra*ratio) / pow(sqrt(ra*ra*sin(th)*sin(th)+ra*ratio*ratio*ra*cos(th)*cos(th)),3.0);
          rat = curv/curvmax;

          p.push_back(make_particle((ra)*cos(th),(ra*ratio)*sin(th),z,state));

          th=th+dth;
          number_of_particles=number_of_particles+1;   
        }
        ra=ra+dr;
      }
  }


  states = new int[number_of_particles];
  positions = new double[number_of_particles*3];

  for(long j = 0; j < number_of_particles; j++)
  {
    positions[3*j + 0] = p[j].x + c[0];
    positions[3*j + 1] = p[j].y + c[1];
    positions[3*j + 2] = p[j].z + c[2];
    states[j] = p[j].state;
  }

  this->numParticles = number_of_particles;
  this->dim = 3;

  return;
}

CylindricalPacker::~CylindricalPacker()
{
  delete [] positions;
  delete [] states;
}


double* CylindricalPacker::getPositions()
{
  return positions;
}
int* CylindricalPacker::getStates()
{
  return states;
}

long CylindricalPacker::getNumParticles()
{
  return numParticles;
}

int CylindricalPacker::getDim()
{
  return dim;
}
