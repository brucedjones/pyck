#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <math.h>
#include <cstdlib>
#include <iomanip>

#include "verditeWriter.h"
#include "../intField.h"
#include "../doubleField.h"
#include "../progressBar.h"

VerditeWriter::VerditeWriter(){}

VerditeWriter::~VerditeWriter(){}

std::string space2comma(std::string text) {
    for(std::string::iterator it = text.begin(); it != text.end(); ++it) {
        if(*it == ' ') {
            *it = ',';
        }
    }
    return text;
}

void VerditeWriter::Write(std::string fname,
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
  int k = 0;

  if(numParticles == 0)
  {
    std::cout << "Error: Number of particles is 0, exiting" << std::endl;
    std::exit(1);
  }

  ProgressBar pb(intFields.size()+doubleFields.size()+parameters.size()+1,"Writing output");

  std::ofstream outfile((char*)fname.c_str(), std::ios::out);
  if(outfile.is_open()) 
  {
    std::cout << "Writing to output file..." << std::flush;

    outfile <<  "# vtk DataFile Version 1.0" << std::endl;
    outfile <<  "vtk output" << std::endl;
    outfile <<  "ASCII" << std::endl;
    outfile <<  "DATASET POLYDATA" << std::endl;
    outfile <<  "POINTS " << numParticles << " float" << std::endl;
   for ( int i = 0; i<numParticles; i++ ) // All positions, duplicate this loop to write extra arrays
   {
    j = 3*i;
    outfile <<  positions[j] << " " << positions[j+1] << " " << positions[j+2] << std::endl;
   }	

    outfile <<  "POINT_DATA " << numParticles << std::endl;

    outfile <<  "FIELD FieldData " << doubleFields.size()+intFields.size() << std::endl;

    for (long intf=0; intf < intFields.size(); intf++)
    {
      IntField *thisField = intFields[intf];

      outfile <<  thisField->name << " " << thisField->dim << " " << numParticles << " float" << std::endl;

      for ( int i = 0; i<numParticles; i++ )
      {

        k= thisField->dim * i;

        for( int l=0; l<thisField->dim; l++)
        {
          outfile << " " << thisField->data[k+l];
        }
        outfile << std::endl;
      }
    }

    for (long intf=0; intf < doubleFields.size(); intf++)
    {
      DoubleField *thisField = doubleFields[intf];

      outfile <<  thisField->name << " " << thisField->dim << " " << numParticles << " float" << std::endl;

      for ( int i = 0; i<numParticles; i++ )
      {
        k= thisField->dim * i;
        for( int l=0; l<thisField->dim; l++)
        {
          outfile << " " << thisField->data[k+l];
        }
        outfile << std::endl;
      }
    }

    outfile.close();
  }


  std::string fname_par = fname.substr(0, fname.find(".", 0));
  fname_par = fname_par + ".par";

  std::ofstream outfile2((char*)fname_par.c_str(), std::ios::out);
  if(outfile2.is_open()) 
  {

    outfile2 <<  "numParticles=" << numParticles << std::endl; // Number of particles

    for ( it = parameters.begin(); it != parameters.end(); it++ ) // All the parameters defined int he python script
    {
      outfile2 <<  it->first << "=" << space2comma(it->second) << std::endl;
    }

    outfile2.close();
  }

  pb.Finish();
}
