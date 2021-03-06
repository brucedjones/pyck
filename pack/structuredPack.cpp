#include <iostream>
#include <vector>
#include <omp.h>

#include "structuredPack.h"
#include "packer.h"
#include "../boundingBox.h"
#include "../shape.h"
#include "../progressBar.h"


StructuredPack::StructuredPack(Packer *packer){
  this->packer = packer;
  this->len = packer->len;

  int progress = 0;
  ProgressBar pb(3,"Initializing StructuredPack");

  dim = 3;
  if(len[2] < 2) dim = 2;

  progress++;
  pb.UpdateProgress(progress);
  state = new int[len[0]*len[1]*len[2]];

  progress++;
  pb.UpdateProgress(progress);
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

  progress++;
  pb.UpdateProgress(progress);

  numParticles = 0;

  positions = NULL;
  states = NULL;

  pb.Finish();
}

StructuredPack::~StructuredPack()
{
  delete [] state;
  delete [] pos;
  if(positions) delete [] positions;
  if(states) delete [] states;
}

long* StructuredPack::GetIntLength()
{
  return len;
}

int* StructuredPack::GetState()
{
  return state;
}

double* StructuredPack::GetPos()
{
  return pos;
}

long StructuredPack::ID(long i, long j, long k)
{
  return i+j*len[0]+k*len[0]*len[1];
}

long StructuredPack::DimID(long thisDim,long i, long j, long k)
{
  return thisDim+i*dim+j*dim*len[0]+k*dim*len[0]*len[1];
}

void StructuredPack::Process()
{
  MapShapes();

  int progress;
  ProgressBar pb(3,"Processing particles");

  progress++;
  pb.UpdateProgress(progress);
  numParticles = ComputeNumParticles();

  progress++;
  pb.UpdateProgress(progress);
  positions = CreatePositions();

  progress++;
  pb.UpdateProgress(progress);
  states = CreateStates();

  pb.Finish();
}

void StructuredPack::MapShape(Shape *shape)
{
  if(!shape->inverted) MapNormalShape(shape);
  else MapInvertedShape(shape);
}

void StructuredPack::MapNormalShape(Shape *shape)
{
  BoundingBox *bb = shape->boundingBox;

  // Convert to StructuredPack indexes
  long *p1 = new long[3];
  long *p2 = new long[3];

  // Get the ijk extent
  // Third argument "floors" the ijk indexes (lower left corner) if true
  // "ceils" the ijk indexes (upper right corner) if false
  packer->Pos2IDX(bb->p1, p1, true);
  packer->Pos2IDX(bb->p2, p2, false);

  int numThreads = omp_get_max_threads();
  if(!shape->parallel) numThreads = 1;

  //std::cout << "Mapping a shape..." << std::flush;
  long plx = p2[0]-p1[0];
  long ply = p2[1]-p1[1];
  long plz = p2[2]-p1[2];
  long progress = 0;
  ProgressBar pb(plx*ply*plz, "Mapping shape");

  if(dim>2)
  {
    #pragma omp parallel for num_threads(numThreads) schedule(static)
    for(long k=p1[2]; k<p2[2]; k++){
      double thisPos[3];
      for(long j=p1[1]; j<p2[1]; j++){
        for(long i=p1[0]; i<p2[0]; i++){
          // Mapping
          packer->IDX2Pos(i,j,k,thisPos);
          if(shape->IsInside(thisPos)){
            state[ID(i,j,k)] = shape->state;
            pos[DimID(0,i,j,k)] = thisPos[0];
            pos[DimID(1,i,j,k)] = thisPos[1];
            if(dim>2) pos[DimID(2,i,j,k)] = thisPos[2];
          }
          // Progress Reporting
          #pragma omp atomic
            progress++;
          if(omp_get_thread_num()==0) pb.UpdateProgress(progress);
        }
      }
    }
  } else {
    long k = 0;
    #pragma omp parallel for num_threads(numThreads) schedule(static)
    for(long j=p1[1]; j<p2[1]; j++){
      double thisPos[3];
      for(long i=p1[0]; i<p2[0]; i++){
        // Mapping
        packer->IDX2Pos(i,j,k,thisPos);
        if(shape->IsInside(thisPos)){
          state[ID(i,j,k)] = shape->state;
          pos[DimID(0,i,j,k)] = thisPos[0];
          pos[DimID(1,i,j,k)] = thisPos[1];
          if(dim>2) pos[DimID(2,i,j,k)] = thisPos[2];
        }
        // Progress Reporting
        #pragma omp atomic
          progress++;
        if(omp_get_thread_num()==0) pb.UpdateProgress(progress);
      }
    }
  }

  pb.Finish();
}

void StructuredPack::MapInvertedShape(Shape *shape)
{
  BoundingBox *bb = shape->boundingBox;

  // Convert to StructuredPack indexes
  long *p1 = new long[3];
  long *p2 = new long[3];

  // Get the ijk extent
  // Third argument "floors" the ijk indexes (lower left corner) if true
  // "ceils" the ijk indexes (upper right corner) if false
  packer->Pos2IDX(bb->p1, p1, true);
  packer->Pos2IDX(bb->p2, p2, false);

  int numThreads = omp_get_max_threads();
  if(!shape->parallel) numThreads = 1;

  //std::cout << "Mapping a shape..." << std::flush;
  long plx = p2[0]-p1[0];
  long ply = p2[1]-p1[1];
  long plz = p2[2]-p1[2];
  long progress = 0;
  ProgressBar pb(len[0]*len[1]*len[3], "Mapping shape");

  if(dim>2)
  {
    #pragma omp parallel for num_threads(numThreads) schedule(static)
    for(long k=0; k<len[2]; k++){
      double thisPos[3];
      for(long j=0; j<len[1]; j++){
        for(long i=0; i<len[0]; i++){
          // Mapping
          packer->IDX2Pos(i,j,k,thisPos);
          if( (k<p1[2] || k>=p2[2])
           || (j<p1[1] || j>=p2[1])
           || (i<p1[0] || i>=p2[0])
           || !shape->IsInside(thisPos)){
            state[ID(i,j,k)] = shape->state;
            pos[DimID(0,i,j,k)] = thisPos[0];
            pos[DimID(1,i,j,k)] = thisPos[1];
            if(dim>2) pos[DimID(2,i,j,k)] = thisPos[2];
          }
          // Progress Reporting
          #pragma omp atomic
            progress++;
          if(omp_get_thread_num()==0) pb.UpdateProgress(progress);
        }
      }
    }
  } else {
    long k = 0;
    #pragma omp parallel for num_threads(numThreads) schedule(static)
    for(long j=0; j<len[1]; j++){
      double thisPos[3];
      for(long i=0; i<len[0]; i++){
        // Mapping
        packer->IDX2Pos(i,j,k,thisPos);
        if( (j<p1[1] || j>=p2[1])
         || (i<p1[0] || i>=p2[0])
         || !shape->IsInside(thisPos)){
          state[ID(i,j,k)] = shape->state;
          pos[DimID(0,i,j,k)] = thisPos[0];
          pos[DimID(1,i,j,k)] = thisPos[1];
          if(dim>2) pos[DimID(2,i,j,k)] = thisPos[2];
        }
        // Progress Reporting
        #pragma omp atomic
          progress++;
        if(omp_get_thread_num()==0) pb.UpdateProgress(progress);
      }
    }
  }

  pb.Finish();
}

long StructuredPack::ComputeNumParticles(){
  long n = 0;
  long totalIJK = len[0]*len[1]*len[2];
  for(long i=0;i<totalIJK;i++){
    if(state[i]!=0) n++;
  }

  return n;
}

double* StructuredPack::CreatePositions(){
  double *positions = new double[numParticles*3];

  long totalIJK = len[0]*len[1]*len[2];
  long particle = 0;

  for(long i=0;i<totalIJK;i++){
    if(state[i]!=0){
      long thisIDX = i*dim;
      positions[particle] = pos[thisIDX];
      positions[particle+1] = pos[thisIDX+1];
      if(dim>2)
      {
        positions[particle+2] = pos[thisIDX+2];
      } else {
        positions[particle+2] = 0.0;
      }
      particle+=3;
    }
  }

  return positions;
}

int* StructuredPack::CreateStates()
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

int StructuredPack::GetDim()
{
  return dim;
}

std::vector<double> StructuredPack::GetClosestParticlePosition(std::vector<double> pos)
{
  long *p1 = new long[3];
  long *p2 = new long[3];

  // Get the ijk range to check against the input pos
  packer->Pos2IDX(pos.data(), p1, true);
  packer->Pos2IDX(pos.data(), p2, false);

  std::vector<double> output(3,0.);

  double minDist = 10000000000000;

  if(dim>2)
  {
    double thisPos[3];
    for(long k=p1[2]; k<p2[2]; k++){
      for(long j=p1[1]; j<p2[1]; j++){
        for(long i=p1[0]; i<p2[0]; i++){
          packer->IDX2Pos(i,j,k,thisPos);
          double dist = 0;
          for(int d=0;d<3;d++)
          {
            dist += (thisPos[d]-output[d])*(thisPos[d]-output[d]);
          }

          if (dist<minDist)
          {
            output[0] = thisPos[0]; output[1] = thisPos[1]; output[2] = thisPos[2];
          }
        }
      }
    }
  } else {
    long k = 0;
    double thisPos[3];
    for(long j=p1[1]; j<p2[1]; j++){
      for(long i=p1[0]; i<p2[0]; i++){
        packer->IDX2Pos(i,j,k,thisPos);
        double dist = 0;
        for(int d=0;d<3;d++)
        {
          dist += (thisPos[d]-output[d])*(thisPos[d]-output[d]);
        }

        if (dist<minDist)
        {
          output[0] = thisPos[0]; output[1] = thisPos[1]; output[2] = thisPos[2];
        }
      }
    }
  }

  return output;
}
