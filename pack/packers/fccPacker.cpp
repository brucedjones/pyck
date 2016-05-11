#include <math.h>

#include "fccPacker.h"

FccPacker::FccPacker(double *doubleLenIn, double h)
{
  h = h/2.0;
  dx = sqrt(8*h*h);
  len[0] = (int)(doubleLenIn[0]/dx);
  len[1] = (int)(2*doubleLenIn[1]/dx);
  len[2] = (int)(2*doubleLenIn[2]/dx);

  if(doubleLenIn[2]<0.00000001) len[2] = 1;
}

FccPacker::~FccPacker(){}

void FccPacker::IDX2Pos(long i, long j, long k, double *posOut)
{
  if(k%2==0){
    double offset_i = (double)((j+1)%2)*dx/2;
    posOut[0] = (double)i*dx+offset_i;
    posOut[1] = (double)j*dx/2;
    posOut[2] = (double)k*dx/2;
  } else {
    double offset_i = (double)(j%2)*dx/2;
    posOut[0] = (double)i*dx+offset_i;
    posOut[1] = (double)j*dx/2;
    posOut[2] = (double)k*dx/2;
  }
}

void FccPacker::Pos2IDX(double *posIn, long *idxOut, bool doFloor)
{
  double i,j,k;
  i = posIn[0]/dx;
  j = 2*posIn[1]/dx;
  k = 2*posIn[2]/dx;

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
