#ifndef STUCTURED_PACK_H
#define STUCTURED_PACK_H

#include "../shape.h"
#include "packer.h"
#include "../pack.h"

#include <vector>

/**
 * The StructuredPack to be StructuredPacked with particles.
 */
class StructuredPack : public Pack {
  public:
    // Methods

    /**
     * StructuredPack Constructor
     * @param StructuredPacker Determines the relationship between IJK and Cartesian coordinates.
     */
    StructuredPack(Packer *packer);
    ~StructuredPack();

    /**
     * StructuredPack all added shapes and generate positions and states
     */
    void Process();

    /**
     * Get the position of the closest valid particle to the input coordinate
     * @param pos Input coordinate
     * @return The coordinates of the closest valid particle
     */
    std::vector<double> GetClosestParticlePosition(std::vector<double> pos);

  private:
    // Methods
    /**
     * Map a shape to the StructuredPack
     * @param shape Shape to be mapped
     */
    void MapShape(Shape *shape);

    /**
     * Map a shape to the StructuredPack
     * @param shape Shape to be mapped
     */
    void MapNormalShape(Shape *shape);

    /**
     * Map an inverted shape to the StructuredPack
     * @param shape Shape to be mapped
     */
    void MapInvertedShape(Shape *shape);

    /**
     * Create 1D array of particle positions
     * @return 1D array of particle positions, format is [x1,y1,x2,y2,...xn,yn]
     */
    double *CreatePositions();

    /**
     * Create 1D array of particle positions
     * @return 1D array of particle States, format is [x1,y1,x2,y2,...xn,yn]
     */
    int *CreateStates();

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
     * Get the size of the StructuredPack in integer index format
     * @return Pointer to an array of length 3 containing length in ijk
     */
    long *GetIntLength();

    /**
     * Get the size of the StructuredPack in cartesian format
     * @return Pointer to an array of length 3 containing length in xyz
     */
    double *GetSize();

    /**
     * Get the ijk ordered array of particle states
     * @return Pointer to array of particle states
     */
    int *GetState();

    /**
     * Get the ijk ordered array of particle positions
     * @return Pointer to array of particle positions
     */
    double *GetPos();

    /**
     * Get the number of particles in this StructuredPack
     */
    long ComputeNumParticles();

    /**
     * Get the dimensionality of the StructuredPack
     * @return Number of dimensions
     */
    int GetDim();
    //Properties
    Packer *packer; /**< Determines the packing configuration (The relationship between ijk and coordinates)*/
    long *len; /**< Size of the StructuredPack in ijk system */
    int *state; /**< ijk Array of particle states */
    double *pos; /**< ijk Array of particle coordinates (cartesian) */
};

#endif
