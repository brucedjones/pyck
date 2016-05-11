#define M_PI 3.14159265358979323846264338327

#include <math.h>
#include <iostream>

#include "hcpPacker.h"

HcpPacker::HcpPacker(double *doubleLenIn, double h)
{
  dx = h;
  len[0] = (int)(doubleLenIn[0]/((dx/2.0)*(2.0*sqrt(6.0)/3.0)));
  len[1] = (int)(doubleLenIn[1]/((dx/2.0)*sqrt(3.0)));
  len[2] = (int)(doubleLenIn[2]/dx);

  if(doubleLenIn[2]<0.00000001) len[2] = 1;
}

HcpPacker::~HcpPacker(){}

void HcpPacker::IDX2Pos(long i, long j, long k, double *posOut)
{
  posOut[0] = (dx/2.0)*2.0*sqrt(6.0)*(double)(i)/3.0;
  posOut[1] = (dx/2.0)*sqrt(3.0)*((double)j+(double)(i%2)/3.0);
  posOut[2] = (dx/2.0)*2.0*(double)(k+(j+i)%2);
}

void HcpPacker::Pos2IDX(double *posIn, long *idxOut, bool doFloor)
{
  double i,j,k;
  i = posIn[0]/((dx/2.0)*(2.0*sqrt(6)/3.0));
  j = posIn[1]/((dx/2.0)*sqrt(3));
  k = posIn[2]/dx;

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
