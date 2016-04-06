#ifndef DOMAIN_H
#define DOMAIN_H

#include "shape.h"

/**
 * The domain to be packed with particles.
 */
class Domain {
  public:
    // Methods
    /**
     * Domain Constructor
     * @param Size of the domain in cartesian cooridnate system
     * @param Spacing between particles
     */
    Domain(float *size, float h);
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
     * Get the array of particle states
     * @return Pointer to array of particle states
     */
    int *GetState();

    /**
     * Get the array of particle positions
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
     * Converts an ijk index to cartesian coordinates
     * @param i      Index along X
     * @param j      Index along Y
     * @param k      Index along Z
     * @param posOut Pointer to array of length 3 where cartesian coordinates will be written
     */
    void IDX2Pos(long i, long j, long k, float *posOut);

    /**
     * Converts cartesian coordinates to ijk indexes
     * @param posIn   Vector of length 3 containing input cartesian coordinates
     * @param idxOut  Vector of length 3 which will contain output ijk indexes
     * @param doFloor Round down to nearest ijk if true, round up if false
     */
    void Pos2IDX(float *posIn, long *idxOut, bool doFloor);

    /**
     * Map a shape to the domain
     * @param shape Shape to be mapped
     */
    void MapShape(Shape *shape);

  private:
    // Methods

    //Properties
    long len[3]; /** Size of the domain in ijk system */
    float size[3]; /** size of the domain in cartesian system */
    int dim; /** Dimensionality of domain (2D or 3D) */
    float dx; /** Particle spacing */
    int *state; /** Array of particle states */
    float *pos; /** Array of particle coordinates (cartesian) */
};

#endif
