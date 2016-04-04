#include <iostream>
#include <fstream>
#include "pyck.h"

int *domain;
float *pos;
long len[3];
int dim = 3;
float dx;

int main()
{
  len[0] = 10; len[1] = 20; len[2] = 20;
  dx = 0.1;

  int p1[3], p2[3];
  p1[0] = 0; p1[1] = 0; p1[2] = 0;
  p2[0] = 10; p2[1] = 10; p2[2] = 10;

  Init();
  PackCube(p1,p2);
  WriteCSV();

  std::cout << "Packing Complete\n";
  TearDown();
}

void Init()
{
  if(len[2] == 1) dim = 2;

  domain = new int[len[0]*len[1]*len[2]];
  pos = new float[len[0]*len[1]*len[2]*dim];

  for(long k=0; k<len[2]; k++){
    for(long j=0; j<len[1]; j++){
      for(long i=0; i<len[0]; i++){
        domain[ID(i,j,k)] = 0;
      }
    }
  }
}

void TearDown()
{
  delete [] domain;
  delete [] pos;
}

long ID(long i, long j, long k)
{
  return i+j*len[0]+k*len[0]*len[1];
}

long DimID(long thisDim,long i, long j, long k)
{
  return thisDim+i*dim+j*dim*len[0]+k*dim*len[0]*len[1];
}

void IDX2Pos(long i, long j, long k, float *posOut)
{
  if(k%2==0){
    float offset_i = (float)((j+1)%2)*dx/2;
    posOut[0] = (float)i*dx+offset_i;
    posOut[1] = (float)j*dx/2;
    posOut[2] = (float)k*dx/2;
  } else {
    float offset_i = (float)(j%2)*dx/2;
    posOut[0] = (float)i*dx+offset_i;
    posOut[1] = (float)j*dx/2;
    posOut[2] = (float)k*dx/2;
  }
}

void PackCube(int p1[3], int p2[3])
{
  float thisPos[3];
  for(long k=p1[2]; k<p2[2]; k++){
    for(long j=p1[1]; j<p2[1]; j++){
      for(long i=p1[0]; i<p2[0]; i++){
        domain[ID(i,j,k)] = 1;
        IDX2Pos(i,j,k,thisPos);
        pos[DimID(0,i,j,k)] = thisPos[0];
        pos[DimID(1,i,j,k)] = thisPos[1];
        if(dim>2) pos[DimID(2,i,j,k)] = thisPos[2];
      }
    }
  }
}

void WriteCSV()
{
  std::ofstream outfile ("particles.csv", std::ios::out);
  if(outfile.is_open()) {
    for(long k=0; k<len[2]; k++){
      for(long j=0; j<len[1]; j++){
        for(long i=0; i<len[0]; i++){
          if(domain[ID(i,j,k)] == 1) {
            outfile << pos[DimID(0,i,j,k)] << "," << pos[DimID(1,i,j,k)];
            if(dim>2) outfile << "," << pos[DimID(2,i,j,k)];
            outfile << "\n";
          }
        }
      }
    }
    outfile.close();
  }
}
