#include "packer.h"

#include <iostream>

Packer::Packer(double *len, double *offset)
{
    for(int i=0;i<3;i++) lend[i] = len[i];
    if(offset != nullptr) {
        for(int i=0;i<3;i++) {
            this->offset[i] = offset[i];
            std::cout << this->offset[i] << std::endl;
        }
    }
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