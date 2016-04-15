#include <string>
#include <iostream>

#include "intField.h"

IntField::IntField(std::string name, long n, int dim)
{
  this->name = name;
  this->n = n;
  this->dim = dim;

  data = new int[n*dim];

  for(long i=0;i<n*dim;i++)
  {
    data[i]=0;
  }
}

IntField::~IntField()
{
  delete [] data;
}
