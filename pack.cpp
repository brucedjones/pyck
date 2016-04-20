#include <iostream>
#include <fstream>
#include <omp.h>

#include "pack.h"
#include "packer.h"
#include "boundingBox.h"
#include "shape.h"


Pack::Pack(Packer *packer)
{
  std::cout << "Initializing pack..." << std::flush;
  this->packer = packer;
  this->len = packer->len;

  dim = 3;
  if(len[2] < 2) dim = 2;

  state = new int[len[0]*len[1]*len[2]];
  pos = new double[len[0]*len[1]*len[2]*dim];

  if(dim>2)
  {
    #pragma omp parallel for schedule(static)
    for(long k=0; k<len[2]; k++){
      for(long j=0; j<len[1]; j++){
        for(long i=0; i<len[0]; i++){
          state[ID(i,j,k)] = 0;
        }
      }
    }
  } else {
    for(long k=0; k<len[2]; k++){
      #pragma omp parallel for schedule(static)
      for(long j=0; j<len[1]; j++){
        for(long i=0; i<len[0]; i++){
          state[ID(i,j,k)] = 0;
        }
      }
    }
  }

  numParticles = 0;

  positions = NULL;
  states = NULL;

  std::cout << " complete" << std::endl;
}

Pack::~Pack()
{
  delete [] state;
  delete [] pos;
  if(!positions) delete [] positions;
  if(!states) delete [] states;
}

long* Pack::GetIntLength()
{
  return len;
}

int* Pack::GetState()
{
  return state;
}

double* Pack::GetPos()
{
  return pos;
}

long Pack::ID(long i, long j, long k)
{
  return i+j*len[0]+k*len[0]*len[1];
}

long Pack::DimID(long thisDim,long i, long j, long k)
{
  return thisDim+i*dim+j*dim*len[0]+k*dim*len[0]*len[1];
}

void Pack::AddShape(Shape *shape)
{
  shapes.push_back(shape);
}

void Pack::Process()
{
  for (int i=0; i<shapes.size(); i++)
  {
    MapShape(shapes[i]);
  }

  numParticles = ComputeNumParticles();
  positions = CreatePositions();
  states = CreateStates();

  std::cout << "Processing pack...complete (" << numParticles << " particles)" << std::endl;;
}

void Pack::MapShape(Shape *shape)
{
  BoundingBox *bb = shape->boundingBox;

  // Convert to pack indexes
  long *p1 = new long[3];
  long *p2 = new long[3];

  // Get the ijk extent
  // Third argument "floors" the ijk indexes (lower left corner) if true
  // "ceils" the ijk indexes (upper right corner) if false
  packer->Pos2IDX(bb->p1, p1, true);
  packer->Pos2IDX(bb->p2, p2, false);

  std::cout << "Mapping a shape..." << std::flush;

  if(dim>2)
  {
    #pragma omp parallel for schedule(static)
    for(long k=p1[2]; k<p2[2]; k++){
      double thisPos[3];
      for(long j=p1[1]; j<p2[1]; j++){
        for(long i=p1[0]; i<p2[0]; i++){
          packer->IDX2Pos(i,j,k,thisPos);
          if(shape->IsInside(thisPos)){
            state[ID(i,j,k)] = shape->state;
            pos[DimID(0,i,j,k)] = thisPos[0];
            pos[DimID(1,i,j,k)] = thisPos[1];
            if(dim>2) pos[DimID(2,i,j,k)] = thisPos[2];
          }
        }
      }
    }
  } else {
    for(long k=p1[2]; k<p2[2]; k++){
      #pragma omp parallel for schedule(static)
      for(long j=p1[1]; j<p2[1]; j++){
        double thisPos[3];
        for(long i=p1[0]; i<p2[0]; i++){
          packer->IDX2Pos(i,j,k,thisPos);
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
    std::cout << " complete" << std::endl;
}

long Pack::ComputeNumParticles(){
  if(numParticles != 0) return numParticles;

  long n = 0;
  long totalIJK = len[0]*len[1]*len[2];
  for(long i=0;i<totalIJK;i++){
    if(state[i]!=0) n++;
  }

  return n;
}

double* Pack::CreatePositions(){
  double *positions = new double[numParticles*3];

  long totalIJK = len[0]*len[1]*len[2];
  long particle = 0;
  
  for(long i=0;i<totalIJK;i++){
    if(state[i]!=0){
      long thisIDX = i*3;
      positions[particle] = pos[thisIDX];
      positions[particle+1] = pos[thisIDX+1];
      if(dim>2)
      {
        positions[particle+2] = pos[thisIDX+2];
      } else {
        positions[particle+2] = 0.0;
      }
      particle+=dim;
    }
  }

  return positions;
}

int* Pack::CreateStates()
{
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


int Pack::GetDim()
{
  return dim;
}
