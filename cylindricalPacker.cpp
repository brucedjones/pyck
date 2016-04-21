#define M_PI 3.14159265358979323846264338327

#include <iostream>
#include <omp.h>
#include <math.h>
#include <algorithm>
#include <vector>
#include "cylindricalPacker.h"
#include "elliptic_integral_secondform.cpp"

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
  double halfcircle_number_of_divisions = 4.0; // number of divisions of a half circle

  std::vector<particle> p,pfinal,pexclu;

  p.push_back(make_particle(0.0,0.0,0.0,state));

  double ra = h;
  double dr = h;
  double dth = 0.0;
  double th = 0.0;
  double th0 = 0.0;
  double curvmax = 0.0;
  double curv = 0.0;
  double rat = 0.0;
  long number_of_particles = 1;
  particle temp1,temp2, temp3;
  double dist;
  double xcurrent, xmax, thetamax, xmaxtemp, thetamaxtemp, ymax;
  int count;
  double tolh = 0.9;
  double toldth = 0.0001;
  double randomstart = 1.0;
if(r != 0.0)
{

  if(ratio == 1.0) ratio = 0.9999999;


  ra = r; //h*floor(r/h);

  xmax = ra;
  ymax = ra*ratio;
  double eccentricity = sqrt(1-(ymax*ymax)/(xmax*xmax));
  double circumference = 4 * xmax * Legendre_Elliptic_Integral_Second_Kind(M_PI/2,'k', eccentricity);
  dr = circumference/round(circumference/h);
  // std::cout << "Packing ellipse of radius :" << ra << " with dx=" << dr << " (" << number_of_particles << ")"<< std::endl;


  dth=M_PI*sqrt(dr*dr*ratio)/(halfcircle_number_of_divisions*(sqrt(ra*ra*ratio)));
  p.push_back(make_particle((ra)*cos(th),(ra*ratio)*sin(th),0.0,state));
  temp3 = p.back();
  number_of_particles=number_of_particles+1; 
  while(th<= 2*M_PI-dth/2)
  {

    dth = 0.0;
    temp1 = make_particle((ra)*cos(th+dth),(ra*ratio)*sin(th+dth),0.0,state);
    temp2 = temp3;
    dist = sqrt((temp1.x-temp2.x)*(temp1.x-temp2.x) + (temp1.y-temp2.y)*(temp1.y-temp2.y)+ (temp1.z-temp2.z)*(temp1.z-temp2.z));

    while(dist <= dr )
    {
      dth+= toldth;

      temp1 = make_particle((ra)*cos(th+dth),(ra*ratio)*sin(th+dth),0.0,state);
      dist = sqrt((temp1.x-temp2.x)*(temp1.x-temp2.x) + (temp1.y-temp2.y)*(temp1.y-temp2.y)+ (temp1.z-temp2.z)*(temp1.z-temp2.z));
    }

    count = 1;
    for(int v = 0;v<(p.size()-1);v++)
    {
      temp2 = p[v];
      // std::cout << "Checking point " << temp1.x << " " << temp1.y << " " << temp1.z << " with point "<<  v << " " << temp2.x << " " << temp2.y << " " << temp2.z << std::endl;
      
      dist = sqrt((temp1.x-temp2.x)*(temp1.x-temp2.x) + (temp1.y-temp2.y)*(temp1.y-temp2.y)+ (temp1.z-temp2.z)*(temp1.z-temp2.z)); 

      if(dist < tolh*dr)
      {
        // std::cout <<"Exclu " << dist << std::endl;
        count = 0;
        break;
      } 
    }
    if(count == 1) 
    {
      p.push_back(temp1);
      temp3 = temp1;
      th=th+dth;
      number_of_particles=number_of_particles+1; 
    }
    else
    {
      temp3 = temp2;
      if(dth == 0.0) dth = toldth;
      th=th+dth;
    } 
  }


  double kk = 0;
  while(kk<=(std::min(ra,ratio*ra)-h))  
  {
    kk = kk + h;


    if(kk >= ((ratio*ratio*ra*ra) / ra))
    {
      thetamax = asin(sqrt((((ra*ra*kk*kk)/(ratio*ratio*ra*ra)) - (ratio*ratio*ra*ra)) / (ra*ra-ratio*ratio*ra*ra)));
      xmax = ra*cos(thetamax)- (ra*ratio*kk*cos(thetamax)) / sqrt(ra*ra*sin(thetamax)*sin(thetamax)+ra*ratio*ratio*ra*cos(thetamax)*cos(thetamax));
      ymax = ra*ratio*sin(M_PI/2)- (ra*kk*sin(M_PI/2)) / sqrt(ra*ra*sin(M_PI/2)*sin(M_PI/2)+ra*ratio*ratio*ra*cos(M_PI/2)*cos(M_PI/2));
    }
    else
    {
      xmax = ra-kk;
      ymax = ra*ratio*sin(M_PI/2)- (ra*kk*sin(M_PI/2)) / sqrt(ra*ra*sin(M_PI/2)*sin(M_PI/2)+ra*ratio*ratio*ra*cos(M_PI/2)*cos(M_PI/2));
    }
    if( thetamax !=thetamax)
    {
      dr = h;
    }
    else
    {
      double eccentricity = sqrt(1-(ymax*ymax)/(xmax*xmax));
      double circumference = 4 * xmax * Legendre_Elliptic_Integral_Second_Kind(M_PI/2,'k', eccentricity);
      dr = circumference/round(circumference/h);
    }

    // std::cout << "Packing ellipse of radius :" << xmax << " with dx=" << dr << " (" << number_of_particles << ")" <<std::endl;


    dth=M_PI*sqrt(dr*dr*ratio)/(halfcircle_number_of_divisions*(sqrt(ra*ra*ratio)));
    
    th0 = randomstart*2*M_PI*((double) rand() / (RAND_MAX));
    if( (kk >= ((ratio*ratio*ra*ra) / ra)) && (fabs(th0) > fabs(thetamax)) ) th0 = thetamax;
    th=th0;
    p.push_back(make_particle(ra*cos(th)- (ra*ratio*kk*cos(th)) / sqrt(ra*ra*sin(th)*sin(th)+ra*ratio*ratio*ra*cos(th)*cos(th)),ra*ratio*sin(th)- (ra*kk*sin(th)) / sqrt(ra*ra*sin(th)*sin(th)+ra*ratio*ratio*ra*cos(th)*cos(th)),0.0,state));
    temp3 = p.back();
    number_of_particles=number_of_particles+1; 

    while((th-th0)<= 2*M_PI-dth/2)
    {

      dth = 0.0;
      temp1 = make_particle(ra*cos(th+dth)- (ra*ratio*kk*cos(th+dth)) / sqrt(ra*ra*sin(th+dth)*sin(th+dth)+ra*ratio*ratio*ra*cos(th+dth)*cos(th+dth)),ra*ratio*sin(th+dth)- (ra*kk*sin(th+dth)) / sqrt(ra*ra*sin(th+dth)*sin(th+dth)+ra*ratio*ratio*ra*cos(th+dth)*cos(th+dth)),0.0,state);
      temp2 = temp3;
      dist = sqrt((temp1.x-temp2.x)*(temp1.x-temp2.x) + (temp1.y-temp2.y)*(temp1.y-temp2.y)+ (temp1.z-temp2.z)*(temp1.z-temp2.z));

      while(dist <= dr )
      {
        dth+= toldth;
        temp1 = make_particle(ra*cos(th+dth)- (ra*ratio*kk*cos(th+dth)) / sqrt(ra*ra*sin(th+dth)*sin(th+dth)+ra*ratio*ratio*ra*cos(th+dth)*cos(th+dth)),ra*ratio*sin(th+dth)- (ra*kk*sin(th+dth)) / sqrt(ra*ra*sin(th+dth)*sin(th+dth)+ra*ratio*ratio*ra*cos(th+dth)*cos(th+dth)),0.0,state);
        dist = sqrt((temp1.x-temp2.x)*(temp1.x-temp2.x) + (temp1.y-temp2.y)*(temp1.y-temp2.y)+ (temp1.z-temp2.z)*(temp1.z-temp2.z));
      }


      if(kk >= ((ratio*ratio*ra*ra) / ra))
      {
        xcurrent = temp1.x;

        if( fabs(xcurrent) <= 1.05*std::max(xmax,xmax))
        {
          count = 1;
          for(int v = 0;v<(p.size()-1);v++)
          {
            temp2 = p[v];
            dist = sqrt((temp1.x-temp2.x)*(temp1.x-temp2.x) + (temp1.y-temp2.y)*(temp1.y-temp2.y)+ (temp1.z-temp2.z)*(temp1.z-temp2.z)); 
            if(dist < tolh*dr)
            {
              count = 0;
              break;
            } 
          }
          if(count == 1) 
          {
            p.push_back(temp1);
            temp3 = temp1;
            th=th+dth;
            number_of_particles=number_of_particles+1; 
          }
          else
          {
            temp3 = temp2;
            if(dth == 0.0) dth = toldth;
            th=th+dth;
          }

        }
        else
        {
          temp3 = temp2;
          if(dth == 0.0) dth = toldth;
          th=th+dth;
        }
      }
      else
      {
        count = 1;
        for(int v = 0;v<(p.size()-1);v++)
        {
          temp2 = p[v];
          dist = sqrt((temp1.x-temp2.x)*(temp1.x-temp2.x) + (temp1.y-temp2.y)*(temp1.y-temp2.y)+ (temp1.z-temp2.z)*(temp1.z-temp2.z)); 
          if(dist < tolh*dr)
          {
            count = 0;
            break;
          } 
        }
        if(count == 1) 
        {
          p.push_back(temp1);
          temp3 = temp1;
          th=th+dth;
          number_of_particles=number_of_particles+1; 
        }
        else
        {
          temp3 = temp2;
          if(dth == 0.0) dth = toldth;
          th=th+dth;
        }
      }
    }
  }

  thetamaxtemp = asin(sqrt((((ra*ra*(kk)*(kk))/(ratio*ratio*ra*ra)) - (ratio*ratio*ra*ra)) / (ra*ra-ratio*ratio*ra*ra)));
  xmaxtemp = ra*cos(thetamax)- (ra*ratio*(kk)*cos(thetamaxtemp)) / sqrt(ra*ra*sin(thetamaxtemp)*sin(thetamaxtemp)+ra*ratio*ratio*ra*cos(thetamaxtemp)*cos(thetamaxtemp));
  for(int jj = 0;jj<floor(xmaxtemp/h);jj++)
  {
    temp1 = make_particle(jj*h,0.0,0.0,state);
    count = 1;
    for(int v = 0;v<(p.size()-1);v++)
    {
      temp2 = p[v];
      dist = sqrt((temp1.x-temp2.x)*(temp1.x-temp2.x) + (temp1.y-temp2.y)*(temp1.y-temp2.y)+ (temp1.z-temp2.z)*(temp1.z-temp2.z)); 
      if(dist < std::min(1.5*tolh*h,h))
      {
        count = 0;
        break;
      } 
    }
    if(count == 1) 
    {
      p.push_back(temp1);
      number_of_particles=number_of_particles+1; 
    }


    temp1 = make_particle(-jj*h,0.0,0.0,state);
    count = 1;
    for(int v = 0;v<(p.size()-1);v++)
    {
      temp2 = p[v];
      dist = sqrt((temp1.x-temp2.x)*(temp1.x-temp2.x) + (temp1.y-temp2.y)*(temp1.y-temp2.y)+ (temp1.z-temp2.z)*(temp1.z-temp2.z)); 
      if(dist < std::min(1.5*tolh*h,h))
      {
        count = 0;
        break;
      } 
    }
    if(count == 1) 
    {
      p.push_back(temp1);
      number_of_particles=number_of_particles+1; 
    }

  }

  }
  
std::cout << "Packing for r=" << r << " finished with " << number_of_particles << " point(s) "<< std::endl;

  while(p.size() > 0)
  {

    for(int u = 0;u<(p.size());u++)
    {
      temp1 = p[u];
            


      count = 1;
      for(int v = 0;v<(p.size());v++)
      {
        
        temp2 = p[v];
        dist = sqrt((temp1.x-temp2.x)*(temp1.x-temp2.x) + (temp1.y-temp2.y)*(temp1.y-temp2.y)+ (temp1.z-temp2.z)*(temp1.z-temp2.z)); 
        if((dist < tolh*h) && (u!=v))
        {
          count = 0;
          break;
        } 
      }
      if(count == 1)
      {
        p.erase(p.begin()+u);
        pfinal.push_back(temp1);
        break;
      }
      if(count == 0)
      {
        number_of_particles=number_of_particles-1;
        p.erase(p.begin()+u);
        pexclu.push_back(temp1);
        break;
      }
    }

  }


  std::cout << "Final number of points : " << number_of_particles  <<  " (" << pexclu.size() << " points excluded)" << std::endl;


  states = new int[number_of_particles];
  positions = new double[number_of_particles*3];

  for(long i = 0; i < number_of_particles; i++)
  {
    positions[3*i + 0] = pfinal[i].x + c[0];
    positions[3*i + 1] = pfinal[i].y + c[1];
    positions[3*i + 2] = pfinal[i].z + c[2];
    states[i] = pfinal[i].state;
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

std::vector<particle> p;
CylindricalPacker *pack  = new CylindricalPacker(h, state, c, r, ratio);

for(int u = 0; u<pack->getNumParticles();u++)
{
p.push_back(make_particle(pack->getPositions()[3*u+0],pack->getPositions()[3*u+1],pack->getPositions()[3*u+2],pack->getStates()[u]));
}
long number_of_particles = pack->getNumParticles();
delete pack;

  // double halfcircle_number_of_divisions = 3.0; // number of divisions of a half circle

  // std::vector<particle> p;

  // p.push_back(make_particle(0.0,0.0,0.0,state));

  // double ra = h;
  // double dr = h;
  // double dth = 0.0;
  // double th = 0.0;
  // double curvmax = 0.0;
  // double curv = 0.0;
  // double rat = 0.0;
  // long number_of_particles = 1;

  // while(ra <= r)
  // {
  //   dth=M_PI*sqrt(dr*dr*ratio)/(halfcircle_number_of_divisions*(sqrt(ra*ra*ratio)));
  //   th=0.0;
  //   curvmax = std::max(ra/(ra*ra*ratio*ratio),(ra*ratio)/(ra*ra));

  //   while(th<= 2*M_PI-dth/2)
  //   {
  //     curv = (ra*ra*ratio) / pow(sqrt(ra*ra*sin(th)*sin(th)+ra*ratio*ratio*ra*cos(th)*cos(th)),3.0);
  //     rat = curv/curvmax;

  //     if(l[0] != 0.0 && l[1] == 0.0 && l[2] == 0.0)
  //     {
  //       p.push_back(make_particle(0.0,(ra)*cos(th),(ra*ratio)*sin(th),state));

  //     }
  //     else if(l[0] == 0.0 && l[1] != 0.0 && l[2] == 0.0)
  //     {
  //       p.push_back(make_particle((ra*ratio)*sin(th),0.0,(ra)*cos(th),state));
  //     }
  //     else if(l[0] == 0.0 && l[1] == 0.0 && l[2] != 0.0)
  //     {
  //       p.push_back(make_particle((ra)*cos(th),(ra*ratio)*sin(th),0.0,state));
  //     }
      

  //     th=th+dth;
  //     number_of_particles=number_of_particles+1;   
  //   }
  //   ra=ra+dr;
  // }

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
  long number_of_particles = 0;
  double current_radius;


  for(double z = -(r*ratioZ)+h/2;z<=(r*ratioZ);z+=h)
  {


    ratio = ratioY;
    current_radius = r * sqrt(1-((z*z)/(r*ratioZ*r*ratioZ)));

    double ctemp[3] = { 0.0,0.0,z }; 
    std::cout << "[Ellipsoid] Packing at z= "<<z<< " with r=" << current_radius << " and ratio=" << ratio << " ..."<<std::endl;
CylindricalPacker *pack  = new CylindricalPacker(h, state, ctemp, current_radius, ratio);


for(int u = 0; u<pack->getNumParticles();u++)
{
p.push_back(make_particle(pack->getPositions()[3*u+0],pack->getPositions()[3*u+1],pack->getPositions()[3*u+2],pack->getStates()[u]));
}
number_of_particles += pack->getNumParticles();

std::cout << "[Ellipsoid] Packing at z= "<<z<< " finished. "<< number_of_particles << " point(s)" << std::endl;
delete pack;

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
