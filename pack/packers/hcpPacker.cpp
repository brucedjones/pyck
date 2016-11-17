#define M_PI 3.14159265358979323846264338327

#include <math.h>
#include <iostream>
#include <vector>

#include "hcpPacker.h"

HcpPacker::HcpPacker(double *doubleLenIn, double h, bool rotate90) : Packer(doubleLenIn)
{
  this->rotate90 = rotate90;

  dx = h;

  if(!rotate90){
    len[0] = (int)(doubleLenIn[0]/((dx/2.0)*(2.0*sqrt(6.0)/3.0)));
    len[1] = (int)(doubleLenIn[1]/((dx/2.0)*sqrt(3.0)));
    len[2] = (int)(doubleLenIn[2]/dx);

    if(len[0]%2!=0) len[0]++; // ensure pack is periodic in X direction
    if(len[1]%2!=0) len[1]++; // ensure pack is periodic in X direction
  } else {
    len[0] = (int)(doubleLenIn[0]/((dx/2.0)*sqrt(3.0)));
    len[1] = (int)(doubleLenIn[1]/((dx/2.0)*(2.0*sqrt(6.0)/3.0)));
    len[2] = (int)(doubleLenIn[2]/dx);

    if(len[1]%2!=0) len[1]++; // ensure pack is periodic in Y direction
  }

  if(doubleLenIn[2]<0.00000001) len[2] = 1;
}

HcpPacker::~HcpPacker(){}

void HcpPacker::IDX2Pos(long i, long j, long k, double *posOut)
{
  if(!rotate90){
    posOut[0] = (dx/2.0)*2.0*sqrt(6.0)*(double)(i)/3.0;
    posOut[1] = (dx/2.0)*sqrt(3.0)*((double)j+(double)(i%2)/3.0);
    posOut[2] = (dx/2.0)*2.0*(double)(k+(j+i)%2);
  } else {
    posOut[0] = (dx/2.0)*sqrt(3.0)*((double)i+(double)(j%2)/3.0);
    posOut[1] = (dx/2.0)*2.0*sqrt(6.0)*(double)(j)/3.0;
    posOut[2] = (dx/2.0)*2.0*(double)(k+(j+i)%2);
  }
}

void HcpPacker::Pos2IDX(double *posIn, long *idxOut, bool doFloor)
{
  double i,j,k;

  if(!rotate90){
    i = posIn[0]/((dx/2.0)*(2.0*sqrt(6)/3.0));
    j = posIn[1]/((dx/2.0)*sqrt(3));
    k = posIn[2]/dx;
  } else {
    i = posIn[0]/((dx/2.0)*sqrt(3));
    j = posIn[1]/((dx/2.0)*(2.0*sqrt(6)/3.0));
    k = posIn[2]/dx;
  }

  if(doFloor) {
    idxOut[0] = floor(i)-1;
    idxOut[1] = floor(j)-1;
    idxOut[2] = floor(k)-1;
  } else {
    idxOut[0] = ceil(i)+1;
    idxOut[1] = ceil(j)+1;
    idxOut[2] = ceil(k)+1;
  }

  for(int i=0; i<3; i++){
    if(idxOut[i] < 0) idxOut[i] = 0;
    if(idxOut[i] >= len[i]) idxOut[i] = len[i];
  }
}

std::vector<double> HcpPacker::GetPeriodicExtent()
{
  std::vector<double> output(3,0.);

  if(!rotate90)
  {
    output[0] = (dx/2.0)*2.0*sqrt(6.0)*(double)(len[0]-1)/3.0;
    output[1] = (dx/2.0)*sqrt(3.0)*((double)(len[1]-1)+(1.0/3.0));
    output[2] = (dx/2.0)*2.0*(double)(len[2]-1+1);

    // Add periodic offset
    output[0] += (dx/2.0)*2.0*sqrt(6.0)/3.0;
    output[1] += (dx/2.0)*sqrt(3.0)*(1+(1.0/3.0))/2.0;
    output[2] += 0.0;
  } else {
    output[0] = (dx/2.0)*sqrt(3.0)*((double)(len[0]-1)+(1.0/3.0));
    output[1] = (dx/2.0)*2.0*sqrt(6.0)*(double)(len[1]-1)/3.0;
    output[2] = (dx/2.0)*2.0*(double)(len[2]-1+1);

    // Add periodic offset
    output[0] += (dx/2.0)*sqrt(3.0)*(1+(1.0/3.0))/2.0;
    output[1] += (dx/2.0)*2.0*sqrt(6.0)/3.0;
    output[2] += 0.0;

  }

  return output;
}
