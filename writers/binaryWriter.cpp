#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <math.h>
#include <cstdlib>
#include <limits>
// #include <iomanip>

#include "binaryWriter.h"
#include "../intField.h"
#include "../doubleField.h"
#include "../progressBar.h"

BinaryWriter::BinaryWriter(){}

BinaryWriter::~BinaryWriter(){}

std::string space2comma2(std::string text) {
    for(std::string::iterator it = text.begin(); it != text.end(); ++it) {
        if(*it == ' ') {
            *it = ',';
        }
    }
    return text;
}

template <typename T>
void SwapEnd(T& var)
{
  char* varArray = reinterpret_cast<char*>(&var);
  for(long i = 0; i < static_cast<long>(sizeof(var)/2); i++)
    std::swap(varArray[sizeof(var) - 1 - i],varArray[i]);
}

void BinaryWriter::Write(std::string fname,
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
  double temp;

  if(numParticles == 0)
  {
    std::cout << "Error: Number of particles is 0, exiting" << std::endl;
    std::exit(1);
  }

  ProgressBar pb(intFields.size()+doubleFields.size()+parameters.size()+1,"Writing output");

  std::ofstream outfile((char*)fname.c_str(), std::ios::binary);
  if(outfile.is_open()) 
  {
    std::cout << "Writing to output file..." << std::flush;

    outfile <<  "# vtk DataFile Version 1.0" << std::endl;
    outfile <<  "vtk output" << std::endl;
    outfile <<  "BINARY" << std::endl;
    outfile <<  "DATASET POLYDATA" << std::endl;
    outfile <<  "POINTS " << numParticles << " double" << std::endl;
   for ( int i = 0; i<numParticles; i++ ) // All positions, duplicate this loop to write extra arrays
   {
    j = 3*i;

    // SwapEnd(positions[j]);
    // outfile.write((char*)&positions[j], sizeof(double));
    // SwapEnd(positions[j+1]);
    // outfile.write((char*)&positions[j+1], sizeof(double));
    // SwapEnd(positions[j+2]);
    // outfile.write((char*)&positions[j+2], sizeof(double));

    temp = std::stod(std::to_string(positions[j]));
    SwapEnd(temp);
    outfile.write((char*)&temp, sizeof(double));
    temp = std::stod(std::to_string(positions[j+1]));
    SwapEnd(temp);
    outfile.write((char*)&temp, sizeof(double));
    temp = std::stod(std::to_string(positions[j+2]));
    SwapEnd(temp);
    outfile.write((char*)&temp, sizeof(double));

   }	

    outfile <<  std::endl; // NEW LINE

    outfile <<  "POINT_DATA " << numParticles << std::endl;

    outfile <<  "FIELD FieldData " << doubleFields.size()+intFields.size() << std::endl;

    for (long intf=0; intf < intFields.size(); intf++)
    {
      IntField *thisField = intFields[intf];

      outfile <<  thisField->name << " " << thisField->dim << " " << numParticles << " integer" << std::endl;

      for ( int i = 0; i<numParticles; i++ )
      {

        k= thisField->dim * i;

        for( int l=0; l<thisField->dim; l++)
        {

          SwapEnd(thisField->data[k+l]);
          outfile.write((char*)&thisField->data[k+l], sizeof(int));


        }
      }

      outfile <<  std::endl;
    }

    for (long intf=0; intf < doubleFields.size(); intf++)
    {
      DoubleField *thisField = doubleFields[intf];

      outfile <<  thisField->name << " " << thisField->dim << " " << numParticles << " double" << std::endl;

      for ( int i = 0; i<numParticles; i++ )
      {
        k= thisField->dim * i;
        for( int l=0; l<thisField->dim; l++)
        {

          SwapEnd(thisField->data[k+l]);
          outfile.write((char*)&thisField->data[k+l], sizeof(double));
        }
      }

      outfile <<  std::endl;
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
      outfile2 <<  it->first << "=" << space2comma2(it->second) << std::endl;
    }

    outfile2.close();
  }

  pb.Finish();
}
