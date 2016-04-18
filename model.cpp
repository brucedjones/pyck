#include <string>
#include <vector>
#include <map>

#include "model.h"
#include "writer.h"
#include "intField.h"
#include "doubleField.h"

Model::Model(Pack *pack)
{
  this->positions = pack->positions;
  this->states = pack->states;
  this->numParticles = pack->numParticles;
  this->numParticles = pack->dim;
}

Model::Model(double *positions, int *states, long numParticles, int dim)
{
  this->positions = positions;
  this->states = states;
  this->numParticles = numParticles;
}

Model::~Model()
{
  for (long i=0; i < intFields.size(); i++)
  {
    IntField *thisField = intFields[i];
    delete [] thisField;
  }

  for (long i=0; i < doubleFields.size(); i++)
  {
    DoubleField *thisField = doubleFields[i];
    delete [] thisField;
  }
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

void Model::AddParameter(std::string key, std::string value)
{
  parameters[key] = value;
}
