#define M_PI 3.14159265358979323846264338327

#include <math.h>

#include "bccPacker.h"

BccPacker::BccPacker(float *floatLenIn, float h)
{
  dx = sqrt((16.0/3.0)*h*h);
  len[0] = (int)(floatLenIn[0]/dx);
  len[1] = (int)(floatLenIn[1]/dx);
  len[2] = (int)(2*floatLenIn[2]/dx);

  if(floatLenIn[2]<0.00000001) len[2] = 1;
}

BccPacker::~BccPacker(){}

void BccPacker::IDX2Pos(long i, long j, long k, float *posOut)
{
    posOut[0] = (float)i*dx+(float)(k%2)*dx/2;
    posOut[1] = (float)j*dx+(float)(k%2)*dx/2;
    posOut[2] = (float)k*dx/2;
}

void BccPacker::Pos2IDX(float *posIn, long *idxOut, bool doFloor)
{
  float i,j,k;
  i = posIn[0]/dx;
  j = posIn[1]/dx;
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
