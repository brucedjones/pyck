#define M_PI 3.14159265358979323846264338327

#include <math.h>
#include <vector>

#include "cubicPacker.h"
#include "../packer.h"

CubicPacker::CubicPacker(std::vector<double> doubleLenIn, double h, std::vector<double> offset) : Packer(doubleLenIn, offset)
{
  dx = h;
  len[0] = (int)(doubleLenIn[0]/dx);
  len[1] = (int)(doubleLenIn[1]/dx);
  len[2] = (int)(doubleLenIn[2]/dx);

  if(doubleLenIn[2]<0.00000001) len[2] = 1;
}

CubicPacker::~CubicPacker(){}

void CubicPacker::IDX2Pos(long i, long j, long k, double *posOut)
{
  posOut[0] = (double)i*dx;
  posOut[1] = (double)j*dx;
  posOut[2] = (double)k*dx;
  ApplyOffset(posOut);
}

void CubicPacker::Pos2IDX(double *posIn, long *idxOut, bool doFloor)
{
  RemoveOffset(posIn);
  double i,j,k;
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

std::vector<double> CubicPacker::GetPeriodicExtent()
{
  std::vector<double> output(3,0.);
  IDX2Pos(len[0],len[1],len[2],&output[0]);

  return output;
}
