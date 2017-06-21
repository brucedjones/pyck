#define M_PI 3.14159265358979323846264338327

#include <math.h>
#include <iostream>
#include <vector>

#include "hcp2dPacker.h"

Hcp2dPacker::Hcp2dPacker(double *doubleLenIn, double h, bool rotate90, double *offset) : Packer(doubleLenIn, offset)
{
  this->rotate90 = rotate90;

  dx = h;

  if(!rotate90){
    len[0] = (long)(doubleLenIn[0]/dx);
    len[1] = (long)(doubleLenIn[1]/((dx/2.0)*sqrt(3.0)));
    len[2] = (long)(doubleLenIn[2]/dx);

    if(len[1]%2!=0) len[1]++; // ensure pack is periodic in Y direction

  } else {
    len[0] = (long)(doubleLenIn[0]/((dx/2.0)*sqrt(3.0)));
    len[1] = (long)(doubleLenIn[1]/dx);;
    len[2] = (long)(doubleLenIn[2]/dx);

    if(len[0]%2!=0) len[0]++; // ensure pack is periodic in X direction
  }

  if(doubleLenIn[2]<0.00000001) len[2] = 1;
}

Hcp2dPacker::~Hcp2dPacker(){}

void Hcp2dPacker::IDX2Pos(long i, long j, long k, double *posOut)
{
  if(!rotate90){
    posOut[0] = (double)i*dx+(double)(j%2)*dx/2.0;
    posOut[1] = (double)j*dx*sqrt(3)/2.0;
    posOut[2] = (double)k*dx;
  } else {
    posOut[0] = (double)i*dx*sqrt(3)/2.0;
    posOut[1] = (double)j*dx+(double)(i%2)*dx/2.0;
    posOut[2] = (double)k*dx;
  }

  ApplyOffset(posOut);
}

void Hcp2dPacker::Pos2IDX(double *posIn, long *idxOut, bool doFloor)
{
  RemoveOffset(posIn);
  double i,j,k;

  if(!rotate90){
    i = posIn[0]/dx;
    j = posIn[1]/(dx*sqrt(3)/2.0);
    k = posIn[2]/dx;
  } else {
      i = posIn[0]/(dx*sqrt(3)/2.0);
      j = posIn[1]/dx;
      k = posIn[2]/dx;
  }

  if(doFloor) {
    idxOut[0] = floor(i)-1;
    idxOut[1] = floor(j)-1;
    idxOut[2] = floor(k)-1;
  } else {
    idxOut[0] = ceil(i)+1;
    idxOut[1] = ceil(j)+1;
    idxOut[2] = floor(k)-1;
  }

  for(int i=0; i<3; i++){
    if(idxOut[i] < 0) idxOut[i] = 0;
    if(idxOut[i] >= len[i]) idxOut[i] = len[i];
  }
}

std::vector<double> Hcp2dPacker::GetPeriodicExtent()
{
  std::vector<double> output(3,0.);

  if(!rotate90)
  {
    output[0] = (double)(len[0]-1)*dx + dx/2.0;
    output[1] = (double)(len[1]-1)*dx*sqrt(3.0)/2.0;
    output[2] = 0.0;

    // Add periodic offset
    output[0] += dx/2.0;
    output[1] += dx*sqrt(3.0)/2.0;
  } else {
    output[0] = (double)(len[0]-1)*dx*sqrt(3.0)/2.0;
    output[1] = (double)(len[1]-1)*dx + dx/2.0;
    output[2] = 0.0;

    // Add periodic offset
    output[0] += dx*sqrt(3.0)/2.0;
    output[1] += dx/2.0;

  }

  return output;
}
