#define M_PI 3.14159265358979323846264338327

#include <math.h>
#include <iostream>

#include "hcp2dPacker.h"

Hcp2dPacker::Hcp2dPacker(double *doubleLenIn, double h)
{
  dx = h;
  len[0] = (long)(doubleLenIn[0]/dx);
  len[1] = (long)(doubleLenIn[1]/((dx/2.0)*sqrt(3.0)));
  len[2] = (long)(doubleLenIn[2]/dx);

  if(doubleLenIn[2]<0.00000001) len[2] = 1;
}

Hcp2dPacker::~Hcp2dPacker(){}

void Hcp2dPacker::IDX2Pos(long i, long j, long k, double *posOut)
{
  posOut[0] = (double)i*dx+(double)(j%2)*dx/2.0;
  posOut[1] = (double)j*dx*sqrt(3)/2.0;
  posOut[2] = (double)k*dx;
}

void Hcp2dPacker::Pos2IDX(double *posIn, long *idxOut, bool doFloor)
{
  double i,j,k;
  i = posIn[0]/dx;
  j = posIn[1]/(dx*sqrt(3)/2.0);
  k = posIn[2]/dx;

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
