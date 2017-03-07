#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <math.h>
#include <cstdlib>

#include "AsciiWriter.h"
#include "../intField.h"
#include "../doubleField.h"
#include "../progressBar.h"

AsciiWriter::AsciiWriter(){}

AsciiWriter::~AsciiWriter(){}

void AsciiWriter::Write(std::string fname,
  std::map<std::string, std::string> parameters,
  double *positions,
  std::vector<IntField*> intFields,
  std::vector<DoubleField*> doubleFields,
  int dim,
  long numParticles
  )
{
  std::map<std::string, std::string>::iterator it;
  int progress = 1;
  int j = 0;

  if(numParticles == 0)
  {
    std::cout << "Error: Number of particles is 0, exiting" << std::endl;
    std::exit(1);
  }

  ProgressBar pb(intFields.size()+doubleFields.size()+parameters.size()+1,"Writing output");

  std::ofstream outfile((char*)fname.c_str(), std::ios::out);
  if(outfile.is_open()) {
    std::cout << "Writing to output file..." << std::flush;

    outfile <<  numParticles << std::endl; // Number of particles

    for ( it = parameters.begin(); it != parameters.end(); it++ ) // All the parameters defined int he python script
    {
      outfile <<  it->first << std::endl;
      outfile <<  it->second << std::endl;
    }

    outfile <<  "Position0" << " " << "Position1" << " " << "Position2";
    for (long intf=0; intf < intFields.size(); intf++)
    {
      IntField *thisField = intFields[intf];
      for( int i=0; i<thisField->dim; i++)
      {
        outfile << " " << thisField->name << i;
      }
    }

    for (long intf=0; intf < doubleFields.size(); intf++)
    {
      DoubleField *thisField = doubleFields[intf];
      for( int i=0; i<thisField->dim; i++)
      {
        outfile << " " << thisField->name << i;
      }
    }
    outfile << std::endl;

   for ( int i = 0; i<numParticles; i++ ) // All positions, duplicate this loop to write extra arrays
   {
    j = 3*i;
    outfile <<  positions[j] << " " << positions[j+1] << " " << positions[j+2];

    for (long intf=0; intf < intFields.size(); intf++)
    {
      IntField *thisField = intFields[intf];
      outfile << " " << thisField->data[i];
    }

    for (long intf=0; intf < doubleFields.size(); intf++)
    {
      DoubleField *thisField = doubleFields[intf];
      outfile << " " << thisField->data[i];
    }

    outfile << std::endl;
  }

  outfile.close();
  pb.Finish();
}
}
