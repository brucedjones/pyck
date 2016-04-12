#define M_PI 3.14159265358979323846264338327

#include <math.h>

#include "cubicPacker.h"

CubicPacker::CubicPacker(float *floatLenIn, float h)
{
  dx = 2.0*h;
  len[0] = (int)(floatLenIn[0]/dx);
  len[1] = (int)(floatLenIn[1]/dx);
  len[2] = (int)(floatLenIn[2]/dx);

  if(floatLenIn[2]<0.00000001) len[2] = 1;
}

CubicPacker::~CubicPacker(){}

void CubicPacker::IDX2Pos(long i, long j, long k, float *posOut)
{
  posOut[0] = (float)i*dx;
  posOut[1] = (float)j*dx;
  posOut[2] = (float)k*dx;
}

void CubicPacker::Pos2IDX(float *posIn, long *idxOut, bool doFloor)
{
  float i,j,k;
  i = posIn[0]/dx;
  j = posIn[1]/dx;
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
