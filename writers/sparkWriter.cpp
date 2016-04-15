#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

#include "sparkWriter.h"
#include "../intField.h"
#include "../doubleField.h"

SparkWriter::SparkWriter(){}

SparkWriter::~SparkWriter(){}

void SparkWriter::Write(std::string fname,
  std::map<std::string, std::string> parameters,
  double *positions,
  std::vector<IntField*> intFields,
  std::vector<DoubleField*> doubleFields,
  int dim,
  int numParticles
)
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
      outfile << positions[i*dim] << "," << positions[i*dim+1];
      if(dim==2)
      {
        outfile << "," << 0.0;
      }
      else
      {
        outfile << "," << positions[i*dim+2];
      }

      for (long intf=0; intf < intFields.size(); intf++)
      {
        IntField *thisField;
        thisField = intFields[intf];
        int thisDim = thisField->dim;
        for(int d=0; d<thisDim; d++)
        {
          long idx = d+i*thisDim;

          outfile << "," << thisField->data[idx];
        }
      }

      for (long doublef=0; doublef < doubleFields.size(); doublef++)
      {
        DoubleField *thisField;
        thisField = doubleFields[doublef];
        int thisDim = thisField->dim;
        for(int d=0; d<thisDim; d++)
        {
          long idx = d+i*thisDim;

          outfile << "," << thisField->data[idx];
        }
      }

      outfile << std::endl;
    }
    outfile.close();
    std::cout << " complete" << std::endl;
  }
}
