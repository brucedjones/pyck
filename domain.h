#ifndef DOMAIN_H
#define DOMAIN_H

#include "shape.h"
#include "packer.h"

/**
 * The domain to be packed with particles.
 */
class Domain {
  public:
    // Methods

    /**
     * Domain Constructor
     * @param packer Determines the relationship between IJK and Cartesian coordinates.
     */
    Domain(Packer *packer);
    ~Domain();

    /**
     * Get the size of the domain in integer index format
     * @return Pointer to an array of length 3 containing length in ijk
     */
    long *GetIntLength();

    /**
     * Get the size of the domain in cartesian format
     * @return Pointer to an array of length 3 containing length in xyz
     */
    float *GetSize();

    /**
     * Get the ijk ordered array of particle states
     * @return Pointer to array of particle states
     */
    int *GetState();

    /**
     * Get the ijk ordered array of particle positions
     * @return Pointer to array of particle positions
     */
    float *GetPos();

    /**
     * Write domain to CSV file
     * @param fname Output filename
     */
    void Serialize(char *fname);

    /**
     * Computes the 1D index from ijk values for scalar properties
     * @param  i Index along X
     * @param  j Index along Y
     * @param  k Index along Z
     * @return   1D equivalent index
     */
    long ID(long i, long j, long k);

    /**
     * Computes the 1D index from ijk values for vector properties
     * @param  thisDim Dimension index X = 0, Y = 1, Z = 2
     * @param  i Index along X
     * @param  j Index along Y
     * @param  k Index along Z
     * @return 1D equivalent index
     */
    long DimID(long thisDim,long i, long j, long k);

    /**
     * Map a shape to the domain
     * @param shape Shape to be mapped
     */
    void MapShape(Shape *shape);

    /**
     * Get the number of particles in this domain
     */
    long GetNumParticles();

    /**
     * Get 1D array of particle positions
     * @return 1D array of particle positions, format is [x1,y1,x2,y2,...xn,yn]
     */
    float *GetPositions();

    /**
     * Get 1D array of particle positions
     * @return 1D array of particle States, format is [x1,y1,x2,y2,...xn,yn]
     */
    int *GetStates();

  private:
    // Methods

    //Properties
    Packer *packer;
    long *len; /**< Size of the domain in ijk system */
    int dim; /**< Dimensionality of domain (2D or 3D) */
    int *state; /**< Array of particle states */
    float *pos; /**< Array of particle coordinates (cartesian) */
    long numParticles; /**< The number of particles packed in this domain */
};

#endif
