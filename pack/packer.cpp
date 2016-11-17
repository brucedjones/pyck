#include "packer.h"

Packer::Packer(double *len)
{
    for(int i=0;i<3;i++) lend[i] = len[i];
}

Packer::~Packer(){}

double Packer::GetParticleVolume()
{
    double volume = 1.0;
    for(int i=0;i<3;i++) volume*=lend[i];
    
    long numParticles = 1;
    for(int i=0;i<3;i++) numParticles*=len[i];

    return volume/(double)numParticles;
}