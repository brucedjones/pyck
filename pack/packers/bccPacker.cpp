#define M_PI 3.14159265358979323846264338327

#include <math.h>
#include <vector>

#include "bccPacker.h"

BccPacker::BccPacker(double *doubleLenIn, double h) : Packer(doubleLenIn)
{
  h = h/2.0;
  dx = sqrt((16.0/3.0)*h*h);
  len[0] = (int)(doubleLenIn[0]/dx);
  len[1] = (int)(doubleLenIn[1]/dx);
  len[2] = (int)(2*doubleLenIn[2]/dx);

  if(len[2]%2!=0) len[2]++; // ensure pack is periodic in Z direction
  if(doubleLenIn[2]<0.00000001) len[2] = 1; // Check for 2D
}

BccPacker::~BccPacker(){}

void BccPacker::IDX2Pos(long i, long j, long k, double *posOut)
{
    posOut[0] = (double)i*dx+(double)(k%2)*dx/2;
    posOut[1] = (double)j*dx+(double)(k%2)*dx/2;
    posOut[2] = (double)k*dx/2;
}

void BccPacker::Pos2IDX(double *posIn, long *idxOut, bool doFloor)
{
  double i,j,k;
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

std::vector<double> BccPacker::GetPeriodicExtent()
{
  std::vector<double> output(3,0.);

  output[0] = (len[0]-1)*(dx)+(dx/2);
  output[1] = (len[1]-1)*(dx)+(dx/2);
  output[2] = (len[2]-1)*(dx/2);

  // Add periodic offset
  output[0] += dx/2;
  output[1] += dx/2;
  output[2] += dx/2;

  return output;
}
