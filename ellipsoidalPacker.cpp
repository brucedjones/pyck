#define M_PI 3.14159265358979323846264338327

#include <iostream>
#include <omp.h>
#include <math.h>
#include <algorithm>
#include <vector>
#include "ellipsoidalPacker.h"
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
}

EllipsoidalPacker::EllipsoidalPacker(double *c, double r, double ratio,double h, int state, double tolerance_angle, double tolerance_h, bool random_startingpoint, bool adjust_h)
{
  std::vector<part> p,pfinal,pexclu;

  p.push_back(make_part(0.0,0.0,0.0,state));

  double ra = h;
  double dr = h;
  double dth = 0.0;
  double th = 0.0;
  double th0 = 0.0;
  double curvmax = 0.0;
  double curv = 0.0;
  double rat = 0.0;
  long number_of_parts = 1;
  part temp1,temp2, temp3;
  double dist;
  double xcurrent, xmax, thetamax, xmaxtemp, thetamaxtemp, ymax;
  int count;
  double tolh = tolerance_h;//0.55; // tolerance for the requested spacing
  double toldth = tolerance_angle;//0.000001; //tolerance on the angle, big impact on performance
  bool randomstart = random_startingpoint;
  bool h_correction = adjust_h;
  double eccentricity,circumference;
  if(r != 0.0) // if r=0, skip everything as p already contains the initital point
  {

    if(ratio == 1.0) ratio = 0.9999999; // there is a singularity for circles/spheres so ratio has to be adjusted


    // ******** Start : Creation of the outer ellipse ******** //
    ra = r-h/2;
    // Adjusting h to be able to close the ellipse
    xmax = ra;
    ymax = ra*ratio;
    if(h_correction)
    {
      eccentricity = sqrt(1-(ymax*ymax)/(xmax*xmax));
      circumference = 4 * xmax * Legendre_Elliptic_Integral_Second_Kind(M_PI/2,'k', eccentricity);
      dr = circumference/round(circumference/h);
    }
    else
    {
      dr = h;
    }
    
    // std::cout << "Packing ellipse of radius :" << xmax << " with dx=" << dr << " (" << number_of_parts << ")"<< std::endl;

    // Adding the first point for theta = 0
    p.push_back(make_part((ra)*cos(th),(ra*ratio)*sin(th),0.0,state));
    temp3 = p.back(); // Storing the last point in p
    number_of_parts=number_of_parts+1; // Updating number of parts
    while(th<= 2*M_PI-dth/2) //until 2PI
    {

      // Defining position fo the next point so that the distance from the previous point is exactly dr
      dth = 0.0;
      temp1 = make_part((ra)*cos(th+dth),(ra*ratio)*sin(th+dth),0.0,state);
      temp2 = temp3;
      dist = sqrt((temp1.x-temp2.x)*(temp1.x-temp2.x) + (temp1.y-temp2.y)*(temp1.y-temp2.y)+ (temp1.z-temp2.z)*(temp1.z-temp2.z));

      while(dist <= dr )
      {
        dth+= toldth;

        temp1 = make_part((ra)*cos(th+dth),(ra*ratio)*sin(th+dth),0.0,state);
        dist = sqrt((temp1.x-temp2.x)*(temp1.x-temp2.x) + (temp1.y-temp2.y)*(temp1.y-temp2.y)+ (temp1.z-temp2.z)*(temp1.z-temp2.z));
      }


      // Test if the point is too close from another point, if yes it is deleted otherwise it is kept
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
        number_of_parts=number_of_parts+1; 
      }
      else
      {
        temp3 = temp2;
        if(dth == 0.0) dth = toldth;
        th=th+dth;
      } 
    }
    // ******** End : Creation of the outer ellipse ******** //

    // ******** Start : Creation of the inner parallel curves (ressembling Talbot's curves - http://mathworld.wolfram.com/EllipseParallelCurves.html) ******** //
    double kk = 0; // kk is the offset of the parallel curve from the ellipse towards its center
    while(kk<=(std::min(ra,ratio*ra)-h))  
    {
      kk = kk + h;

      // Adjusting h to be able to close the parallel curve (approximatiom : assuming circumference is the same as for ellipses)
      if(kk >= ((ratio*ratio*ra*ra) / ra)) //critical value for kk obtained by solving y(t) = 0
      {
        thetamax = asin(sqrt((((ra*ra*kk*kk)/(ratio*ratio*ra*ra)) - (ratio*ratio*ra*ra)) / (ra*ra-ratio*ratio*ra*ra))); //
        xmax = ra*cos(thetamax)- (ra*ratio*kk*cos(thetamax)) / sqrt(ra*ra*sin(thetamax)*sin(thetamax)+ra*ratio*ratio*ra*cos(thetamax)*cos(thetamax)); // Talbot's curve (inner) intersection point with the y axis
        ymax = ra*ratio*sin(M_PI/2)- (ra*kk*sin(M_PI/2)) / sqrt(ra*ra*sin(M_PI/2)*sin(M_PI/2)+ra*ratio*ratio*ra*cos(M_PI/2)*cos(M_PI/2)); // max y for Talbot's curve
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
        if(h_correction)
        {
          eccentricity = sqrt(1-(ymax*ymax)/(xmax*xmax));
          circumference = 4 * xmax * Legendre_Elliptic_Integral_Second_Kind(M_PI/2,'k', eccentricity);
          dr = circumference/round(circumference/h);
        }
        else
        {
          dr = h;
        }
      }

      std::cout << "Packing ellipse of radius :" << xmax << " with dx=" << dr << " (" << number_of_parts << ")" <<std::endl;

      // Adding the first point for a random theta
      if(randomstart)
      {
        th0 = 2*M_PI*((double) rand() / (RAND_MAX));
      }
      else
      {
        th0 = 0.0;
      }
      if( (kk >= ((ratio*ratio*ra*ra) / ra)) && (fabs(th0) > fabs(thetamax)) ) th0 = thetamax;
      th=th0;
      p.push_back(make_part(ra*cos(th)- (ra*ratio*kk*cos(th)) / sqrt(ra*ra*sin(th)*sin(th)+ra*ratio*ratio*ra*cos(th)*cos(th)),ra*ratio*sin(th)- (ra*kk*sin(th)) / sqrt(ra*ra*sin(th)*sin(th)+ra*ratio*ratio*ra*cos(th)*cos(th)),0.0,state));
      temp3 = p.back();
      number_of_parts=number_of_parts+1; 
      while((th-th0)<= 2*M_PI-dth/2)
      {
        // Defining position fo the next point so that the distance from the previous point is exactly dr
        dth = 0.0;
        temp1 = make_part(ra*cos(th+dth)- (ra*ratio*kk*cos(th+dth)) / sqrt(ra*ra*sin(th+dth)*sin(th+dth)+ra*ratio*ratio*ra*cos(th+dth)*cos(th+dth)),ra*ratio*sin(th+dth)- (ra*kk*sin(th+dth)) / sqrt(ra*ra*sin(th+dth)*sin(th+dth)+ra*ratio*ratio*ra*cos(th+dth)*cos(th+dth)),0.0,state);
        temp2 = temp3;
        dist = sqrt((temp1.x-temp2.x)*(temp1.x-temp2.x) + (temp1.y-temp2.y)*(temp1.y-temp2.y)+ (temp1.z-temp2.z)*(temp1.z-temp2.z));

        while(dist <= dr )
        {
          dth+= toldth;
          temp1 = make_part(ra*cos(th+dth)- (ra*ratio*kk*cos(th+dth)) / sqrt(ra*ra*sin(th+dth)*sin(th+dth)+ra*ratio*ratio*ra*cos(th+dth)*cos(th+dth)),ra*ratio*sin(th+dth)- (ra*kk*sin(th+dth)) / sqrt(ra*ra*sin(th+dth)*sin(th+dth)+ra*ratio*ratio*ra*cos(th+dth)*cos(th+dth)),0.0,state);
          dist = sqrt((temp1.x-temp2.x)*(temp1.x-temp2.x) + (temp1.y-temp2.y)*(temp1.y-temp2.y)+ (temp1.z-temp2.z)*(temp1.z-temp2.z));
        }


        if(kk >= ((ratio*ratio*ra*ra) / ra)) //critical value for kk obtained by solving y(t) = 0
        {
          xcurrent = temp1.x;

          // Test if the point is outside the intersection points of Talbot's curve
          if( fabs(xcurrent) <= 1.01*std::max(xmax,xmax))
          {
            // Test if the point is too close from another point, if yes it is deleted otherwise it is kept
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
              number_of_parts=number_of_parts+1; 
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
          // Test if the point is too close from another point, if yes it is deleted otherwise it is kept
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
            number_of_parts=number_of_parts+1; 
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
    // ******** End : Creation of the inner parallel curves ******** //
    
    // ******** Start : Housecleaning of the packing ******** //
    //Adding a line of points in the middle of the ellipse
    thetamaxtemp = asin(sqrt((((ra*ra*(kk)*(kk))/(ratio*ratio*ra*ra)) - (ratio*ratio*ra*ra)) / (ra*ra-ratio*ratio*ra*ra)));
    xmaxtemp = ra*cos(thetamax)- (ra*ratio*(kk)*cos(thetamaxtemp)) / sqrt(ra*ra*sin(thetamaxtemp)*sin(thetamaxtemp)+ra*ratio*ratio*ra*cos(thetamaxtemp)*cos(thetamaxtemp));
    for(int jj = 0;jj<floor(xmaxtemp/h);jj++)
    {
      // towards x>0
      temp1 = make_part(jj*h,0.0,0.0,state);
      // Test if the point is too close from another point, if yes it is deleted otherwise it is kept
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
        number_of_parts=number_of_parts+1; 
      }

      // towards x<0
      temp1 = make_part(-jj*h,0.0,0.0,state);
      // Test if the point is too close from another point, if yes it is deleted otherwise it is kept
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
        number_of_parts=number_of_parts+1; 
      }

    }

  }
  
  std::cout << "Packing for r=" << r << " finished with " << number_of_parts << " point(s) "<< std::endl;

  // Test if any point is too close from another point, if yes it is deleted otherwise it is kept
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
        number_of_parts=number_of_parts-1;
        p.erase(p.begin()+u);
        pexclu.push_back(temp1);
        break;
      }
    }

  }
  // ******** End : Housecleaning of the packing ******** //


  std::cout << "Final number of points : " << number_of_parts  <<  " (" << pexclu.size() << " points excluded)" << std::endl;

  // Reorganisation of the data to be used in pyck
  states = new int[number_of_parts];
  positions = new double[number_of_parts*3];

  for(long i = 0; i < number_of_parts; i++)
  {
    positions[3*i + 0] = pfinal[i].x + c[0];
    positions[3*i + 1] = pfinal[i].y + c[1];
    positions[3*i + 2] = pfinal[i].z + c[2];
    states[i] = pfinal[i].state;
  }

  this->numParticles = number_of_parts;
  this->dim = 2;

  return;
}

EllipsoidalPacker::EllipsoidalPacker(double *c, double r, double ratio, double *l, double h, int state, double tolerance_angle, double tolerance_h, bool random_startingpoint, bool adjust_h)
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

  std::vector<part> p;
  EllipsoidalPacker *pack  = new EllipsoidalPacker(c, r, ratio,h, state,tolerance_angle,tolerance_h,random_startingpoint,adjust_h);

  for(int u = 0; u<pack->getNumParticles();u++)
  {
    p.push_back(make_part(pack->getPositions()[3*u+0],pack->getPositions()[3*u+1],pack->getPositions()[3*u+2],pack->getStates()[u]));
  }
  long number_of_parts = pack->getNumParticles();
  delete pack;

  double htemp;
  long numparttemp = number_of_parts;
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
        p.push_back(make_part(p[i].x + n * htemp,p[i].y,p[i].z,state));

      }
      else if(l[0] == 0.0 && l[1] != 0.0 && l[2] == 0.0)
      {
        p.push_back(make_part(p[i].x,p[i].y + n * htemp,p[i].z + n * h,state));
      }
      else if(l[0] == 0.0 && l[1] == 0.0 && l[2] != 0.0)
      {
        p.push_back(make_part(p[i].x,p[i].y,p[i].z + n * htemp,state));
      }
      number_of_parts=number_of_parts+1;
    }

  }

  states = new int[number_of_parts];
  positions = new double[number_of_parts*3];

  for(long j = 0; j < number_of_parts; j++)
  {
    positions[3*j + 0] = p[j].x + c[0];
    positions[3*j + 1] = p[j].y + c[1];
    positions[3*j + 2] = p[j].z + c[2];
    states[j] = p[j].state;
  }

  this->numParticles = number_of_parts;
  this->dim = 3;

  return;
}

EllipsoidalPacker::EllipsoidalPacker(double *c, double r, double ratioY, double ratioZ, double h, int state, double tolerance_angle, double tolerance_h, bool random_startingpoint, bool adjust_h)
{
  double halfcircle_number_of_divisions = 3.0; // number of divisions of a half circle

  std::vector<part> p;


  double ra;
  double dr;
  double dth;
  double th;
  double curvmax;
  double curv;
  double rat;
  double ratio;
  long number_of_parts = 0;
  double current_radius;


  for(double z = -(r*ratioZ)+h/2;z<=(r*ratioZ);z+=h)
  {


    ratio = ratioY;
    current_radius = r * sqrt(1-((z*z)/(r*ratioZ*r*ratioZ)));

    double ctemp[3] = { 0.0,0.0,z }; 
    std::cout << "[Ellipsoid] Packing at z= "<<z<< " with r=" << current_radius << " and ratio=" << ratio << " ..."<<std::endl;
    EllipsoidalPacker *pack  = new EllipsoidalPacker(ctemp, current_radius, ratio,h, state,tolerance_angle,tolerance_h,random_startingpoint,adjust_h);


    for(int u = 0; u<pack->getNumParticles();u++)
    {
      p.push_back(make_part(pack->getPositions()[3*u+0],pack->getPositions()[3*u+1],pack->getPositions()[3*u+2],pack->getStates()[u]));
    }
    number_of_parts += pack->getNumParticles();

    std::cout << "[Ellipsoid] Packing at z= "<<z<< " finished. "<< number_of_parts << " point(s)" << std::endl;
    delete pack;

  }


  states = new int[number_of_parts];
  positions = new double[number_of_parts*3];

  for(long j = 0; j < number_of_parts; j++)
  {
    positions[3*j + 0] = p[j].x + c[0];
    positions[3*j + 1] = p[j].y + c[1];
    positions[3*j + 2] = p[j].z + c[2];
    states[j] = p[j].state;
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

void EllipsoidalPacker::updateStates(double *c, double r0, double h, double r,double ratio, int state)
{
  double xc,yc,zc,thetac,rc,xth,yth,zth,rth, thetamax,ymax;
  double ra = r0 - h/2;
  
  double kk = 0;
  double xmax = 10000000;
  while(xmax > r)  
  {
    kk = kk + h;

    if(kk >= ((ratio*ratio*ra*ra) / ra)) //critical value for kk obtained by solving y(t) = 0
    {
      thetamax = asin(sqrt((((ra*ra*kk*kk)/(ratio*ratio*ra*ra)) - (ratio*ratio*ra*ra)) / (ra*ra-ratio*ratio*ra*ra))); //
      xmax = ra*cos(thetamax)- (ra*ratio*kk*cos(thetamax)) / sqrt(ra*ra*sin(thetamax)*sin(thetamax)+ra*ratio*ratio*ra*cos(thetamax)*cos(thetamax)); // Talbot's curve (inner) intersection point with the y axis
      ymax = ra*ratio*sin(M_PI/2)- (ra*kk*sin(M_PI/2)) / sqrt(ra*ra*sin(M_PI/2)*sin(M_PI/2)+ra*ratio*ratio*ra*cos(M_PI/2)*cos(M_PI/2));
    }
    else
    {
      xmax = ra-kk;
      ymax = ra*ratio*sin(M_PI/2)- (ra*kk*sin(M_PI/2)) / sqrt(ra*ra*sin(M_PI/2)*sin(M_PI/2)+ra*ratio*ratio*ra*cos(M_PI/2)*cos(M_PI/2));
    }
  }  

  std::cout << "Offset : " << kk << " Local radius : " << xmax<< " Asked radius " << r << " h " << h << " r0 " << r0-h/2 << std::endl;
  for(long j = 0; j < numParticles; j++)
  {
    xc = positions[3*j + 0] - c[0];
    yc = positions[3*j + 1] - c[1];
    zc = positions[3*j + 2] - c[2];
    if(fabs(xc) > xmax || fabs(yc) > ymax)
    {
      std::cout << "coucou 1 " << std::endl;
      states[j] = state;
    }
    else
    {

      // thetac = atan2(ra*yc,ratio*ra*xc);
      thetac = atan2((ra*sqrt(ra*ra*ratio)-ra*ratio*kk)*yc,(ra*ratio*sqrt(ra*ra*ratio)-ra*kk)*xc);
      if(thetac < 0) thetac = thetac + 2.0*M_PI;


      rc = sqrt(xc*xc+yc*yc);


      xth = ra*cos(thetac)- (ra*ratio*kk*cos(thetac)) / sqrt(ra*ra*sin(thetac)*sin(thetac)+ra*ratio*ratio*ra*cos(thetac)*cos(thetac));
      yth = ra*ratio*sin(thetac)- (ra*kk*sin(thetac)) / sqrt(ra*ra*sin(thetac)*sin(thetac)+ra*ratio*ratio*ra*cos(thetac)*cos(thetac));
      zth = 0.0;
      rth = sqrt(xth*xth+yth*yth);

      std::cout << " xc : " << xc << " yc : " << yc << " Theta : " << thetac*180/M_PI<< " rc : " << rc<< "rth : " << rth << std::endl;
      if(rc >=(rth+h/1.5))
      {
        std::cout << "coucou 2 " << std::endl;
        states[j] = state;
      }
    }
  }
}


void EllipsoidalPacker::updateStates(double *c, double r,double ratioY, double ratioZ, int state)
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
