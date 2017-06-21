#include "packer.h"

Packer::Packer(double *len, double *offset)
{
    for(int i=0;i<3;i++) lend[i] = len[i];
    if(offset != nullptr) for(int i=0;i<3;i++) this->offset[i] = offset[i];
    else for(int i=0;i<3;i++) this->offset[i] = 0.0;
}

Packer::~Packer(){}

void Packer::ApplyOffset(double *coord)
{
    for(int i=0;i<3;i++) coord[i] += offset[i];
}

void Packer::RemoveOffset(double *coord)
{
    for(int i=0;i<3;i++) coord[i] -= offset[i];
}

double Packer::GetParticleVolume()
{
    double volume = 1.0;
    for(int i=0;i<3;i++) volume*=lend[i];
    
    long numParticles = 1;
    for(int i=0;i<3;i++) numParticles*=len[i];

    return volume/(double)numParticles;
}