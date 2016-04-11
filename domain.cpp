#define M_PI 3.14159265358979323846264338327

#include <math.h>
#include <iostream>
#include <fstream>

#include "domain.h"
#include "boundingBox.h"
#include "shape.h"


Domain::Domain(float *size, float h)
{
  this->size[0] = size[0];
  this->size[1] = size[1];
  this->size[2] = size[2];

  dim = 3;
  if(size[2] < 0.000000001) dim = 2;

  dx = 2*h*sin(M_PI/4.0);
  len[0] = (int)(size[0]/dx);
  len[1] = (int)(2*size[1]/dx);
  len[2] = (int)(2*size[2]/dx);

  state = new int[len[0]*len[1]*len[2]];
  pos = new float[len[0]*len[1]*len[2]*dim];

  for(long k=0; k<len[2]; k++){
    for(long j=0; j<len[1]; j++){
      for(long i=0; i<len[0]; i++){
        state[ID(i,j,k)] = 0;
      }
    }
  }

  numParticles = 0;
}

Domain::~Domain()
{
  delete [] state;
  delete [] pos;
}

long* Domain::GetIntLength()
{
  return len;
}

float* Domain::GetSize()
{
  return size;
}

int* Domain::GetState()
{
  return state;
}

float* Domain::GetPos()
{
  return pos;
}

long Domain::ID(long i, long j, long k)
{
  return i+j*len[0]+k*len[0]*len[1];
}

long Domain::DimID(long thisDim,long i, long j, long k)
{
  return thisDim+i*dim+j*dim*len[0]+k*dim*len[0]*len[1];
}

void Domain::IDX2Pos(long i, long j, long k, float *posOut)
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

void Domain::Serialize(char *fname)
{
  std::ofstream outfile (fname, std::ios::out);
  if(outfile.is_open()) {

    float *positions = GetPositions();
    int *states = GetStates();
    long numParticles = GetNumParticles();

    for(long i=0; i<numParticles; i++){
      outfile << positions[i*dim] << "," << positions[i*dim+1];
      if(dim>2) outfile << "," << positions[i*dim+2];
      outfile << "," << states[i];
      outfile << std::endl;
    }
    outfile.close();
  }
}

void Domain::Pos2IDX(float *posIn, long *idxOut, bool doFloor)
{
  float i,j,k;
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

void Domain::MapShape(Shape *shape)
{
  BoundingBox *bb = shape->boundingBox;

  // Convert to domain indexes
  long *p1 = new long[3];
  long *p2 = new long[3];

  // Get the ijk extent
  // Third argument "floors" the ijk indexes (lower left corner) if true
  // "ceils" the ijk indexes (upper right corner) if false
  Pos2IDX(bb->p1, p1, true);
  Pos2IDX(bb->p2, p2, false);

  float thisPos[3];

  for(long k=p1[2]; k<p2[2]; k++){
    for(long j=p1[1]; j<p2[1]; j++){
      for(long i=p1[0]; i<p2[0]; i++){
        IDX2Pos(i,j,k,thisPos);
        if(shape->IsInside(thisPos)){
          state[ID(i,j,k)] = shape->state;
          pos[DimID(0,i,j,k)] = thisPos[0];
          pos[DimID(1,i,j,k)] = thisPos[1];
          if(dim>2) pos[DimID(2,i,j,k)] = thisPos[2];
        }
      }
    }
  }
}

long Domain::GetNumParticles(){
  //if(numParticles != 0) return numParticles;

  numParticles = 0;
  long totalIJK = len[0]*len[1]*len[2];
  for(long i=0;i<totalIJK;i++){
    if(state[i]!=0) numParticles++;
  }

  return numParticles;
}

float* Domain::GetPositions(){
  long numParticles = GetNumParticles();

  float *positions = new float[numParticles*dim];

  long totalIJK = len[0]*len[1]*len[2];
  long particle = 0;
  for(long i=0;i<totalIJK;i++){
    if(state[i]!=0){
      long thisIDX = i*dim;
      positions[particle] = pos[thisIDX];
      positions[particle+1] = pos[thisIDX+1];
      if(dim>2) positions[particle+2] = pos[thisIDX+2];
      particle+=dim;
    }
  }

  return positions;
}

int* Domain::GetStates(){
  long numParticles = GetNumParticles();

  int *states = new int[numParticles];

  long totalIJK = len[0]*len[1]*len[2];
  long particle = 0;
  for(long i=0;i<totalIJK;i++){
    if(state[i]!=0){
      states[particle] = state[i];
      particle++;
    }
  }

  return states;
}
