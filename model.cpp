#include <string>
#include <vector>
#include <map>
#include <iostream>

#include "model.h"
#include "writer.h"
#include "intField.h"
#include "doubleField.h"

Model::Model()
{
  this->numParticles = 0;
}

Model::Model(Pack *pack)
{
  numParticles = pack->numParticles;

  positions = new double[numParticles*3];
  std::copy(pack->positions, pack->positions+numParticles*3, positions);

  states = new int[numParticles];
  std::copy(pack->states, pack->states+numParticles, states);

  this->dim = pack->dim;
}

Model::Model(double *positions, int *states, long numParticles, int dim)
{
  this->numParticles = numParticles;

  this->positions = new double[numParticles*3];
  std::copy(positions, positions+numParticles*3, this->positions);

  this->states = new int[numParticles];
  std::copy(states, states+numParticles, this->states);

  this->dim = dim;
}

Model::~Model()
{
  for (long i=0; i < intFields.size(); i++)
  {
    IntField *thisField = intFields[i];
    delete thisField;
  }

  for (long i=0; i < doubleFields.size(); i++)
  {
    DoubleField *thisField = doubleFields[i];
    delete thisField;
  }
}

void Model::AddPack(Pack *pack)
{
  if(this->numParticles!=0){
    long numParticlesNew = numParticles + pack->numParticles;

    double *positionsTmp = new double[numParticlesNew*3];
    int *statesTmp = new int[numParticlesNew];

    std::copy(positions, positions+numParticles*3, positionsTmp);
    std::copy(pack->positions, pack->positions+pack->numParticles*3, positionsTmp+numParticles*3);

    std::copy(states, states+numParticles, statesTmp);
    std::copy(pack->states, pack->states+pack->numParticles, statesTmp+numParticles);

    delete [] positions;
    delete [] states;

    positions = positionsTmp;
    states = statesTmp;
    numParticles = numParticlesNew;
  } else {

    numParticles = pack->numParticles;

    positions = new double[numParticles*3];
    std::copy(pack->positions, pack->positions+numParticles*3, positions);

    states = new int[numParticles];
    std::copy(pack->states, pack->states+numParticles, states);
  }

  dim = pack->dim;
}

void Model::AddPack(double *positions, int *states, long numParticles, int dim)
{
  if(this->numParticles!=0){
    long numParticlesNew = this->numParticles + numParticles;

    double *positionsTmp = new double[numParticlesNew*3];
    int *statesTmp = new int[numParticlesNew];

    std::copy(this->positions, this->positions+this->numParticles*3, positionsTmp);
    std::copy(positions, positions+numParticles*3, positionsTmp+this->numParticles*3);

    std::copy(this->states, this->states+this->numParticles, statesTmp);
    std::copy(states, states+numParticles, statesTmp+this->numParticles);

    delete [] this->positions;
    delete [] this->states;

    this->positions = positionsTmp;
    this->states = statesTmp;
    this->numParticles = numParticlesNew;
  } else {
    this->numParticles = numParticles;

    this->positions = new double[numParticles*3];
    std::copy(positions, positions+numParticles*3, this->positions);

    this->states = new int[numParticles];
    std::copy(states, states+numParticles, this->states);
  }

  this->dim = dim;
}

void Model::Serialize(std::string fname, Writer *writer)
{
  writer->Write(fname, parameters, positions, intFields, doubleFields, dim, numParticles);
}

int Model::CreateIntField(std::string name, int dim)
{
  intFields.push_back(new IntField(name, numParticles,dim));
  return intFields.size()-1;
}

int Model::CreateDoubleField(std::string name, int dim)
{
  doubleFields.push_back(new DoubleField(name, numParticles,dim));
  return doubleFields.size()-1;
}

void Model::SetIntField(int handle, int state, int *val)
{
  IntField *thisField = intFields[handle];
  int fieldDim = thisField->dim;

  for(long i=0; i<numParticles; i++)
  {

    if(states[i] == state)
    {
      for(int d=0; d<fieldDim; d++)
      {
        long idx = d+i*fieldDim;
        thisField->data[idx] = val[d];
      }
    }
  }
}

void Model::SetDoubleField(int handle, int state, double *val)
{
  DoubleField *thisField = doubleFields[handle];
  int fieldDim = thisField->dim;

  for(long i=0; i<numParticles; i++)
  {
    if(states[i] == state)
    {
      for(int d=0; d<fieldDim; d++)
      {
        long idx = d+i*fieldDim;
        thisField->data[idx] = val[d];
      }
    }
  }
}

void Model::SetParameter(std::string key, std::string value)
{
  parameters[key] = value;
}

void Model::SetParameters(std::map<std::string, std::string> &parameters)
{
  std::map<std::string, std::string>::iterator it;
  for ( it = parameters.begin(); it != parameters.end(); it++ )
  {
    this->parameters[it->first] = it->second;
  }
}
