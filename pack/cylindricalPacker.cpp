#define M_PI 3.14159265358979323846264338327

#include <iostream>
#include <omp.h>
#include <math.h>
#include <algorithm>
#include <vector>
#include "cylindricalPacker.h"
#include "../shape.h"
#include "../progressBar.h"

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

CylindricalPacker::CylindricalPacker(std::vector<double> c, double r, double ratio, double h, int state, double num_div)
{

  double halfcircle_number_of_divisions = num_div; // number of divisions of a half circle

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

CylindricalPacker::CylindricalPacker(std::vector<double> c, double r, double ratio, std::vector<double> l, double h, int state, double num_div)
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


  double halfcircle_number_of_divisions = num_div; // number of divisions of a half circle

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

CylindricalPacker::CylindricalPacker(std::vector<double> c, double r, double ratioY, double ratioZ, double h, int state, double num_div)
{
  double halfcircle_number_of_divisions = num_div; // number of divisions of a half circle

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

void CylindricalPacker::updateStates(std::vector<double> c, double r,double ratio, int state)
{
  double x,y,z,equation;
  for(long j = 0; j < numParticles; j++)
  {
    x = positions[3*j + 0] - c[0];
    y = positions[3*j + 1] - c[1];
    z = positions[3*j + 2] - c[2];

    equation = ((x*x)/(r*r)) + ((y*y)/(ratio*ratio*r*r));

    if(equation > 1) states[j] = state;
  }
}


void CylindricalPacker::updateStates(std::vector<double> c, double r,double ratioY, double ratioZ, int state)
{
  double x,y,z,equation;
  for(long j = 0; j < numParticles; j++)
  {
    x = positions[3*j + 0] - c[0];
    y = positions[3*j + 1] - c[1];
    z = positions[3*j + 2] - c[2];

    equation = ((x*x)/(r*r)) + ((y*y)/(ratioY*ratioY*r*r)) + ((z*z)/(ratioZ*ratioZ*r*r));

    if(equation > 1) states[j] = state;
  }
}

double* CylindricalPacker::getPositions()
{
  return positions;
}
int* CylindricalPacker::getStates()
{
  return states;
}

int CylindricalPacker::getDim()
{
  return dim;
}

void CylindricalPacker::MapShape(Shape *shape)
{
  int numThreads = omp_get_max_threads();
  if(!shape->parallel) numThreads = 1;

  long progress = 0;
  ProgressBar pb(numParticles, "Mapping shape");

  #pragma omp parallel for num_threads(numThreads) schedule(static)
  for(long i=0; i<numParticles; i++){
    double thisPos[3];
    thisPos[0] = positions[i*3];
    thisPos[1] = positions[i*3+1];
    thisPos[2] = positions[i*3+2];
    if(shape->IsInside(thisPos)){
      states[i] = shape->state;
    }

    // Progress Reporting
    #pragma omp atomic
      progress++;
    if(omp_get_thread_num()==0) pb.UpdateProgress(i);
  }

  pb.Finish();
}

void CylindricalPacker::Process()
{
  MapShapes();
  int numParticles_temp = ComputeNumParticles();
  double *positions_temp = CreatePositions(numParticles_temp);
  int *states_temp = CreateStates(numParticles_temp);
  numParticles = numParticles_temp;

  delete[] positions;
  delete[] states;

  positions = positions_temp;
  states = states_temp;

  std::cout << "Processing CylindricalPack...complete (" << numParticles << " particles)" << std::endl;;
}
long CylindricalPacker::ComputeNumParticles(){

  long n = 0;
  for(long i=0;i<numParticles;i++){
    if(this->states[i]!=0) n++;
  }

  return n;
}

double* CylindricalPacker::CreatePositions(long numParticles_temp)
{
  double *positions = new double[numParticles_temp*3];

  long particle = 0;

  for(long i=0;i<numParticles;i++){
    if(this->states[i]!=0){
      long thisIDX = i*3;
      positions[particle] = this->positions[thisIDX];
      positions[particle+1] = this->positions[thisIDX+1];
      if(dim>2)
      {
        positions[particle+2] = this->positions[thisIDX+2];
      } else {
        positions[particle+2] = 0.0;
      }
      particle+=3;
    }
  }

  return positions;
}

int* CylindricalPacker::CreateStates(long numParticles_temp)
{
  int *states = new int[numParticles_temp];

  long particle = 0;
  for(long i=0;i<numParticles;i++){
    if(this->states[i]!=0){
      states[particle] = this->states[i];
      particle++;
    }
  }

  return states;
}
