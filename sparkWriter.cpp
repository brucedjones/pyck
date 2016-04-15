#include <iostream>
#include <fstream>
#include <map>

#include "sparkWriter.h"
#include "domain.h"
#include "intField.h"
#include "doubleField.h"

SparkWriter::SparkWriter(Domain *domain)
{
  this->domain = domain;
  domDim = domain->GetDim();
  pos = domain->GetPositions();
  domState = domain->GetStates();
  numParticles = domain->GetNumParticles();
}

SparkWriter::~SparkWriter(){};

int SparkWriter::CreateIntField(std::string name, int dim)
{
  intFields.push_back(new IntField(name, numParticles,dim));
  return intFields.size()-1;
}

int SparkWriter::CreateDoubleField(std::string name, int dim)
{
  doubleFields.push_back(new DoubleField(name, numParticles,dim));
  return doubleFields.size()-1;
}

void SparkWriter::SetIntField(int handle, int state, int *val)
{
  IntField *thisField = intFields[handle];
  int dim = thisField->dim;

  for(long i=0; i<numParticles; i++)
  {

    if(domState[i] == state)
    {
      for(int d=0; d<dim; d++)
      {
        long idx = d+i*dim;
        thisField->data[idx] = val[d];
      }
    }
  }
}

void SparkWriter::SetDoubleField(int handle, int state, double *val)
{
  DoubleField *thisField = doubleFields[handle];
  int dim = thisField->dim;

  for(long i=0; i<numParticles; i++)
  {
    if(domState[i] == state)
    {
      for(int d=0; d<dim; d++)
      {
        long idx = d+i*dim;
        thisField->data[idx] = val[d];
      }
    }
  }
}

void SparkWriter::Serialize(std::string fname)
{
  std::ofstream outfile((char*)fname.c_str(), std::ios::out);
  if(outfile.is_open()) {
    std::cout << "Writing to output file..." << std::flush;

    std::map<std::string, std::string>::iterator it;

    for ( it = parameters.begin(); it != parameters.end(); it++ )
    {
      outfile << it->first << " = " << it->second << std::endl;
    }

    for(long i=0; i<numParticles; i++){
      outfile << pos[i*domDim] << "," << pos[i*domDim+1];
      if(domDim==2)
      {
        outfile << "," << 0.0;
      }
      else
      {
        outfile << "," << pos[i*domDim+2];
      }
      outfile << "," << domState[i];

      for (long intf=0; intf < intFields.size(); intf++)
      {
        IntField *thisField;
        thisField = intFields[intf];
        int dim = thisField->dim;
        for(int d=0; d<dim; d++)
        {
          long idx = d+i*dim;

          outfile << "," << thisField->data[idx];
        }
      }

      for (long doublef=0; doublef < doubleFields.size(); doublef++)
      {
        DoubleField *thisField;
        thisField = doubleFields[doublef];
        int dim = thisField->dim;
        for(int d=0; d<dim; d++)
        {
          long idx = d+i*dim;

          outfile << "," << thisField->data[idx];
        }
      }

      outfile << std::endl;
    }
    outfile.close();
    std::cout << " complete" << std::endl;
  }
}

void SparkWriter::AddParameter(std::string key, std::string value)
{
  parameters[key] = value;
}
