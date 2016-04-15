#include <string>

#include "doubleField.h"

DoubleField::DoubleField(std::string name, long n, int dim)
{
  this->name = name;
  this->n = n;
  this->dim = dim;

  data = new double[n*dim];
  for(long i=0;i<n*dim;i++)
  {
    data[i]=0;
  }
}

DoubleField::~DoubleField()
{
  delete [] data;
}
