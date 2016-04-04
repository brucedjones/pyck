#include "domain.h"

Domain::Domain(float *size, float h)
{
  this.size = size;

  if(size[2] < 0.000000001) dim = 2;

  float dx = 2*h*sin(M_PI_4)
  len[0] = (int)(size[0]/dx);
  len[1] = (int)(size[1]/(dx*2));
  len[2] = (int)(size[2]/(dx*2));

  state = new int[len[0]*len[1]*len[2]];
  pos = new float[len[0]*len[1]*len[2]*dim];

  for(long k=0; k<len[2]; k++){
    for(long j=0; j<len[1]; j++){
      for(long i=0; i<len[0]; i++){
        state[ID(i,j,k)] = 0;
      }
    }
  }
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

int* Domain::GetPos()
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
    for(long k=0; k<len[2]; k++){
      for(long j=0; j<len[1]; j++){
        for(long i=0; i<len[0]; i++){
          if(state[ID(i,j,k)] == 1) {
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

void Domain::Pos2IDX(float *posIn, long *idxOut)
{
  long i,j,k;
  if(dim>2){
    float idxCoord = posIn[2]/(dx*2);
    long quotient = (long)idxCoord;

    if(idxCoord-(float)quotient<0.5) {
      k = quotient;
    } else {
      k = quotient+1;
    }
  } else {
    k = 0;
  }


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
