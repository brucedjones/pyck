#define M_PI 3.14159265358979323846264338327

#include <iostream>
#include <omp.h>
#include <math.h>
#include <algorithm>
#include <vector>
#include "ellipsoidalPacker.h"
#include "elliptic_integral_firstform.cpp"
#include "elliptic_integral_secondform.cpp"

struct part
{
  double x;
  double y;
  double z;
  int state;
};

part make_part(double x, double y, double z, int state)
{
  part p = {x, y, z, state};
  return p;
};

void swap(double &x, double &y){
    double tmp = x;
    x = y;
    y = tmp;
    return;
}

void sort(double &a, double &b, double &c){
    if(c>b){
        swap(c,b);
    }
    if(c>a){
        swap(c,a);
    }
    if(b>a){
        swap(b,a);
    }
    return;
}

std::vector<part> calculateEllipse(double x, double y, double a, double b, double angle, long stepsA, double h, int state)
{

  // linspace MATLAB function
  double alpha[stepsA];
  double beta;
  double alphastep; 
  if(stepsA != 1)
  {
    alphastep = 360 / (stepsA -1);
    for(long i = 0;i<stepsA;i++)
    {
      alpha[i] = i*alphastep * (M_PI / 180);
    }
  }
  else
  {
    alphastep = 360;
    alpha[stepsA] = alphastep * (M_PI / 180);
  }

  beta =  -angle * (M_PI / 180);



  // meshgrid MATLAB function
  double alpha2[stepsA][1];
  double beta2[stepsA][1];

  for(long m=0;m<stepsA;m++)
  {
     alpha2[m][0]=alpha[m];
     beta2[m][0]=beta;
 }

 // creation of the points
 double X[stepsA][1];
 double Y[stepsA][1];
 double Z[stepsA][1];
 for(long m=0;m<stepsA;m++)
 { 
    X[m][0] = x + (a * cos(alpha2[m][0]) * cos(beta2[m][0]) - b * sin(alpha2[m][0]) * sin(beta2[m][0]));
    Y[m][0] = y + (a * cos(alpha2[m][0]) * sin(beta2[m][0]) + b * sin(alpha2[m][0]) * cos(beta2[m][0]));
    Z[m][0] = 0.0;
}

  // conversion to 1D arrays
std::vector<part> p;

for(long m=0;m<stepsA;m++)
{
    p.push_back(make_part(X[m][0],Y[m][0],Z[m][0],state));
}

    // exclusion of redondant points
bool debut = true;
bool currentpointok;
bool neighborpointok;
std::vector<int> e;
std::vector<part> q;
double xc,xn;
double yc,yn;
double zc,zn;
double dist;
// std::cout << "Nbre points before loop :" << p.size() << std::endl;
while(debut == true || e.size() > 0)
{
  if(debut == false)
  {
    if(e.size() > 0) p.erase(p.begin() + e[0]);
    std::cout << "Point(" << e[0] << ") excluded" << std::endl;
  }
  std::cout << "Nbre points :" << p.size() << std::endl;
  

  debut = false;

  e.clear();
  q.clear();
  
  for(long k = 0;k<p.size();k++)
  {
    xc = p[k].x;
    yc = p[k].y;
    zc = p[k].z;
    currentpointok = true;

    for(long l = 0;l<e.size();l++)
    {
      if(k == e[l])
      {
        currentpointok = false;
        break;
      }
    }

    if(currentpointok == true)
    {
      for(long m = 0;m<p.size();m++)
      {
        xn = p[m].x;
        yn = p[m].y;
        zn = p[m].z;
        neighborpointok = true;

        if(xc == xn && yc == yn && zc == zn)
        {
          neighborpointok = false;
          break;
        }
        for(long n = 0;n<e.size();n++)
        {
          if(m == e[n])
          {
            neighborpointok = false;
            break;
          }
        }

        if(neighborpointok == true)
        {
          dist = sqrt((xc-xn)*(xc-xn)+(yc-yn)*(yc-yn)+(zc-zn)*(zc-zn));
          if(dist < 0*0.1*h)
          {
            e.push_back(k);
            currentpointok = false;
          }
        }
      }
    }

    if(currentpointok == true)
    {
      q.push_back(make_part(xc,yc,zc,state));
    }
  }
}

return q;
};


std::vector<part> calculateEllipsoid(double x, double y, double z, double a, double b, double c, double angle, long stepsA, long stepsB, double h, int state)
{

  // linspace MATLAB function
  double alpha[stepsA];
  double beta[stepsB];
  double alphastep; 
  double betastep;
  if(stepsA != 1)
  {
    alphastep = 360 / (stepsA -1);
    for(long i = 0;i<stepsA;i++)
    {
      alpha[i] = i*alphastep * (M_PI / 180);
    }
  }
  else
  {
    alphastep = 360;
    alpha[stepsA] = alphastep * (M_PI / 180);
  }

  if(stepsB != 1)
  {
    betastep = 180 / (stepsB -1);
    for(long j = 0;j<stepsB;j++)
    {
      beta[j] = j*betastep * (M_PI / 180);
    }
  }
  else
  {
    betastep = 180;
    beta[stepsB] = betastep * (M_PI / 180);
  }


  // meshgrid MATLAB function
  double alpha2[stepsA][stepsB];
  double beta2[stepsA][stepsB];

  for(long m=0;m<stepsA;m++)
  {
    for(long n=0;n<stepsB;n++)
    {
     alpha2[m][n]=alpha[m];
     beta2[m][n]=beta[n];
   }
 }

 // creation of the points
 double X[stepsA][stepsB];
 double Y[stepsA][stepsB];
 double Z[stepsA][stepsB];
 for(long m=0;m<stepsA;m++)
 {
  for(long n=0;n<stepsB;n++)
  {
    X[m][n] = x + a * cos(alpha2[m][n]) * sin(beta2[m][n]);
    Y[m][n] = y + b * sin(alpha2[m][n]) * sin(beta2[m][n]);
    Z[m][n] = z + c * cos(beta2[m][n]);
  }
}

  // conversion to 1D arrays
std::vector<part> p;

for(long m=0;m<stepsA;m++)
{
  for(long n=0;n<stepsB;n++)
  {
    p.push_back(make_part(X[m][n],Y[m][n],Z[m][n],state));
  }
}

    // exclusion of redondant points
bool debut = true;
bool currentpointok;
bool neighborpointok;
std::vector<int> e;
std::vector<part> q;
double xc,xn;
double yc,yn;
double zc,zn;
double dist;
// std::cout << "Nbre points before loop :" << p.size() << std::endl;
while(debut == true || e.size() > 0)
{
  if(debut == false)
  {
    if(e.size() > 0) p.erase(p.begin() + e[0]);
    std::cout << "Point(" << e[0] << ") excluded" << std::endl;
  }
  std::cout << "Nbre points :" << p.size() << std::endl;
  

  debut = false;

  e.clear();
  q.clear();
  
  for(long k = 0;k<p.size();k++)
  {
    xc = p[k].x;
    yc = p[k].y;
    zc = p[k].z;
    currentpointok = true;

    for(long l = 0;l<e.size();l++)
    {
      if(k == e[l])
      {
        currentpointok = false;
        break;
      }
    }

    if(currentpointok == true)
    {
      for(long m = 0;m<p.size();m++)
      {
        xn = p[m].x;
        yn = p[m].y;
        zn = p[m].z;
        neighborpointok = true;

        if(xc == xn && yc == yn && zc == zn)
        {
          neighborpointok = false;
          break;
        }
        for(long n = 0;n<e.size();n++)
        {
          if(m == e[n])
          {
            neighborpointok = false;
            break;
          }
        }

        if(neighborpointok == true)
        {
          dist = sqrt((xc-xn)*(xc-xn)+(yc-yn)*(yc-yn)+(zc-zn)*(zc-zn));
          if(dist < h)
          {
            e.push_back(k);
            currentpointok = false;
          }
        }
      }
    }

    if(currentpointok == true)
    {
      q.push_back(make_part(xc,yc,zc,state));
    }
  }
}

return q;
};


EllipsoidalPacker::EllipsoidalPacker(double h, int state, double *c, double r, double ratio)
{

  double min_radius = 0.0;
  double max_radius =r;
  int number_of_parts = 0;
  long npts = 0;
  std::vector<part> p;
  std::vector<part> temp;

  // #pragma omp parallel for private(temp,radiusX,radiusY,radiusZ,a0,b0,c0,surface_area,npts) schedule(dynamic) //reduction(+:nprimes)
  for(double radius = min_radius;radius <= max_radius;radius+=h)
  {

    if(radius == 0)
    {
      npts = 1;
    }
    else
    {
      npts = ceil( (2 * M_PI) / asin(h / radius) );
    }

      temp = calculateEllipse(0.0,0.0,radius,ratio*radius,0.0,npts,h,state);
      
      // #pragma omp critical 
      for(long u = 0; u<temp.size();u++)
      {
        p.push_back(temp[u]);
      }

    // #pragma omp critical
    number_of_parts = number_of_parts + temp.size();
  }


  states = new int[number_of_parts];
  positions = new double[number_of_parts*3];

  for(long i = 0; i < number_of_parts; i++)
  {
    positions[3*i + 0] = p[i].x + c[0];
    positions[3*i + 1] = p[i].y + c[1];
    positions[3*i + 2] = p[i].z + c[2];
    states[i] = p[i].state;
  }

  this->numParticles = number_of_parts;
  this->dim = 2;

  return;
}


EllipsoidalPacker::EllipsoidalPacker(double h, int state, double *c, double r, double ratioY, double ratioZ)
{

  double min_radius = 0.0;
  double max_radius =r;
  double radiusX = 0.0;
  double radiusY = 0.0;
  double radiusZ = 0.0;
  int number_of_parts = 0;
  double k = 1.6075;
  double a0 = 0.0;
  double b0 = 0.0;
  double c0 = 0.0;
  double a1 = 0.0;
  double b1 = 0.0;
  double c1 = 0.0;
  double surface_area = 0.0;
  long npts = 0;
  double phi = 0;
  double kk = 0;
  std::vector<part> p;
  std::vector<part> temp;

  // #pragma omp parallel for private(temp,radiusX,radiusY,radiusZ,a0,b0,c0,surface_area,npts) schedule(dynamic) //reduction(+:nprimes)
  for(double radius = min_radius;radius <= max_radius;radius+=h)
  {
    if(radius == min_radius)
    {
      radiusX = radius;
      radiusY = ratioY*(radiusX - h) + h;
      radiusZ = ratioZ*(radiusX - h) + h;
    }
    else if(radius == h)
    {
      radiusX = radius;
      radiusY = ratioY*(radius) + h;
      radiusZ = ratioZ*(radius) + h;
    }
    else
    {
      radiusZ = ratioZ * radiusX + h;
      radiusY = ratioY * radiusX + h;
      radiusX = radius;
    }


    // if(radiusX == radiusY || radiusY == radiusZ || radiusX == radiusZ )
    // {
    a0 = radiusX;
    b0 = radiusY;
    c0 = radiusZ;
    surface_area = 4 * M_PI * pow((pow(a0*b0,k) + pow(a0*c0,k) + pow(c0*b0,k))/3, 1/k);
    // }
    // else
    // {
    // a1 = radiusX;
    // b1 = radiusY;
    // c1 = radiusZ;
    // sort(a1,b1,c1);
    // phi = acos(c1/a1);
    // kk = sqrt((a1*a1*(b1*b1-c1*c1)) / (b1*b1*(a1*a1-c1*c1)));
    // surface_area = 2*M_PI*c1*c1 + ((2*M_PI*a1*b1)/sin(phi))*(Legendre_Elliptic_Integral_First_Kind(phi,'k',kk)*cos(phi)*cos(phi) + Legendre_Elliptic_Integral_Second_Kind(phi,'k',kk)*sin(phi)*sin(phi));
    // std::cout << surface_area << " " << 4 * M_PI * pow((pow(a1*b1,k) + pow(a1*c1,k) + pow(c1*b1,k))/3, 1/k) << std::endl;
    // }
    

    if(radius == 0)
    {
      npts = 1;
    }
    else
    {
      npts = ceil(1.2146 * sqrt(surface_area / (M_PI * pow(h/2,2))));
    }

    if(npts == 1)
    {
      temp = calculateEllipsoid(0.0,0.0,0.0,a0,b0,c0,0,npts,npts,h,state);
      
      // #pragma omp critical 
      for(long u = 0; u<temp.size();u++)
      {
        p.push_back(temp[u]);
      }
    }
    else
    {
      temp = calculateEllipsoid(0.0,0.0,0.0,a0,b0,c0,0,npts,npts/2,h,state);
      
      // #pragma omp critical 
      for(long u = 0; u<temp.size();u++)
      {
        p.push_back(temp[u]);
      }
    }
    // #pragma omp critical
    number_of_parts = number_of_parts + temp.size();
  }


  states = new int[number_of_parts];
  positions = new double[number_of_parts*3];

  for(long i = 0; i < number_of_parts; i++)
  {
    positions[3*i + 0] = p[i].x + c[0];
    positions[3*i + 1] = p[i].y + c[1];
    positions[3*i + 2] = p[i].z + c[2];
    states[i] = p[i].state;
  }

  this->numParticles = number_of_parts;
  this->dim = 3;

  return;
}


EllipsoidalPacker::~EllipsoidalPacker()
{
  delete [] positions;
  delete [] states;
}


double* EllipsoidalPacker::getPositions()
{
  return positions;
}
int* EllipsoidalPacker::getStates()
{
  return states;
}

long EllipsoidalPacker::getNumParticles()
{
  return numParticles;
}

int EllipsoidalPacker::getDim()
{
  return dim;
}
