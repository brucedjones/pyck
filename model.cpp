#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <Python.h>

#include "model.h"
#include "writer.h"
#include "intField.h"
#include "doubleField.h"

using namespace std;

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

Model::Model(std::vector<double> positions, std::vector<int> states, long numParticles, int dim)
{
  this->numParticles = numParticles;

  this->positions = new double[numParticles*3];
  std::copy(positions.data(), positions.data()+numParticles*3, this->positions);

  this->states = new int[numParticles];
  std::copy(states.data(), states.data()+numParticles, this->states);

  this->dim = dim;
}

Model::~Model()
{
  if(positions) delete [] positions;
  if(states) delete [] states;

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


void Model::AddPack(std::vector<double> positions, std::vector<int> states, long numParticles, int dim)
{
  AddPack(positions.data(), states.data(), numParticles, dim);
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

void Model::SetIntField(int handle, int state, int val)
{
  IntField *thisField = intFields[handle];
  int fieldDim = thisField->dim;

  if(fieldDim>1)
  {
    std::cout << "Error: Input value does not have the same dimensionality as IntField" << std::endl;
    return;
  }

  for(long i=0; i<numParticles; i++)
  {
    if(states[i] == state) thisField->data[i] = val;
  }
}

void Model::SetIntField(int handle, int state, std::vector<int> val)
{
  IntField *thisField = intFields[handle];
  int fieldDim = thisField->dim;

  if(val.size()!=thisField->dim)
  {
    std::cout << "Error: Input value does not have the same dimensionality as IntField" << std::endl;
    return;
  }

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

void Model::SetIntField(int handle, int state, PyObject *PyFunc)
{
  IntField *thisField = intFields[handle];
  int fieldDim = thisField->dim;

  Py_XINCREF(PyFunc);
  PyObject *func, *arglist;
  PyObject *result;
  std::vector<int> cResult;
  double pt[3];
  for(long i=0; i<numParticles; i++)
  {
    if(states[i] == state)
    {
      pt[0] = positions[0+i*3];
      pt[1] = positions[1+i*3];
      pt[2] = positions[2+i*3];

      arglist = Py_BuildValue("(ddd)",pt[0],pt[1],pt[2]);
      result =  PyEval_CallObject(PyFunc, arglist);

      if(result == NULL) { std::cout << "Error in field callback" << std::endl; break; }

      int success = Process_Python_Result<int>(result, &cResult);
      if(!success) { std::cout << "Error: Non-numeric data returned from field callback" << std::endl; break; }
      if(cResult.size() != fieldDim) { std::cout << "Error: Data returned from field callback has different dimensions to field" << std::endl; break; }
      
      for(int d=0; d<fieldDim; d++)
      {
        long idx = d+i*fieldDim;
        thisField->data[idx] = cResult[d];
      }

      cResult.clear();
      
      Py_DECREF(arglist);
      Py_XDECREF(result);
    }
  }
  Py_XDECREF(PyFunc);
}

IntField *Model::GetIntField(int handle)
{
  return intFields[handle];
}

void Model::SetDoubleField(int handle, int state, double val)
{
  DoubleField *thisField = doubleFields[handle];
  int fieldDim = thisField->dim;

  if(fieldDim>1)
  {
    std::cout << "Error: Input value does not have the same dimensionality as DoubleField" << std::endl;
    return;
  }

  for(long i=0; i<numParticles; i++)
  {
    if(states[i] == state) thisField->data[i] = val;
  }
}

void Model::SetDoubleField(int handle, int state, std::vector<double> val)
{
  DoubleField *thisField = doubleFields[handle];
  int fieldDim = thisField->dim;

  if(val.size()!=thisField->dim)
  {
    std::cout << "Error: Input value does not have the same dimensionality as DoubleField" << std::endl;
    return;
  }

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

void Model::SetDoubleField(int handle, int state, PyObject *PyFunc)
{
  DoubleField *thisField = doubleFields[handle];
  int fieldDim = thisField->dim;

  Py_XINCREF(PyFunc);
  PyObject *func, *arglist;
  PyObject *result;
  std::vector<double> cResult;
  double pt[3];

  for(long i=0; i<numParticles; i++)
  {
    if(states[i] == state)
    {
      pt[0] = positions[0+i*3];
      pt[1] = positions[1+i*3];
      pt[2] = positions[2+i*3];

      arglist = Py_BuildValue("(ddd)",pt[0],pt[1],pt[2]);
      result =  PyEval_CallObject(PyFunc, arglist);

      if(result == NULL) { std::cout << "Error in field callback" << std::endl; break; }

      int success = Process_Python_Result<double>(result, &cResult);
      if(!success) { std::cout << "Error: Non-numeric data returned from field callback" << std::endl; break; }
      if(cResult.size() != fieldDim) { std::cout << "Error: Data returned from field callback has different dimensions to field" << std::endl; break; }
      
      for(int d=0; d<fieldDim; d++)
      {
        long idx = d+i*fieldDim;
        thisField->data[idx] = cResult[d];
      }

      cResult.clear();

      Py_DECREF(arglist);
      Py_XDECREF(result);
    }
  }

  Py_XDECREF(PyFunc);
}

DoubleField *Model::GetDoubleField(int handle)
{
  return doubleFields[handle];
}

int Model::GetNumberParticles(){
  return (int)this->numParticles;
  }

double* Model::GetPositions(){
  return positions;
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

int Model::ReadSingleIntegerParameter(std::string key)
{
  return atoi(parameters[key].c_str());
}

std::vector<double> Model::ReadMultipleDoubleParameter(std::string key, int n)
{
    std::vector<double> values(n,0.0);
    double a;
    stringstream stream(parameters[key]);
    for (int i=0; i<n; i++) {stream>>values[i];}

    return values;
}

template<typename T>
int  Model::Process_Python_Result(PyObject* incoming, std::vector<T> *data) {
  bool failure = false;
	if (PyTuple_Check(incoming)) {
		for(Py_ssize_t i = 0; i < PyTuple_Size(incoming); i++) {
			PyObject *value = PyTuple_GetItem(incoming, i);
			if(PyFloat_Check(value)) data->push_back((T)PyFloat_AsDouble(value));
      else failure = true;
		}
	} else if (PyList_Check(incoming)) {
			for(Py_ssize_t i = 0; i < PyList_Size(incoming); i++) {
				PyObject *value = PyList_GetItem(incoming, i);
			  if(PyFloat_Check(value)) data->push_back((T)PyFloat_AsDouble(value));
        else failure = true;
			}
	} else if(PyFloat_Check(incoming))
  {
    data->push_back( (T)PyFloat_AsDouble(incoming) );
  } else failure = true;

  if(failure) return 0;
  return 1;
}