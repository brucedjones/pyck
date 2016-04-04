#include <iostream>
#include <fstream>
#include "pyck.h"

int main()
{
  float size[3];
  size[0] = 1; size[1] = 1; size[2] = 1;

  float h = 0.1;

  float p1[3], p2[3];
  p1[0] = 0; p1[1] = 0; p1[2] = 0;
  p2[0] = 1; p2[1] = 1; p2[2] = 1;

  Domain domain = new Domain(size, h);

  PackCube(p1,p2);
  WriteCSV();

  std::cout << "Packing Complete\n";
  delete domain;
}

void PackCube(int p1[3], int p2[3])
{
  float thisPos[3];
  int *state = domain.GetState();
  int *pos = domain.GetPos();

  for(long k=p1[2]; k<p2[2]; k++){
    for(long j=p1[1]; j<p2[1]; j++){
      for(long i=p1[0]; i<p2[0]; i++){
        state[domain.ID(i,j,k)] = 1;
        domain.IDX2Pos(i,j,k,thisPos);
        pos[domain.DimID(0,i,j,k)] = thisPos[0];
        pos[domain.DimID(1,i,j,k)] = thisPos[1];
        if(dim>2) pos[domain.DimID(2,i,j,k)] = thisPos[2];
      }
    }
  }
}
