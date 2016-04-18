#ifndef DOMAIN_H
#define DOMAIN_H

#include <vector>

#include "shape.h"
#include "packer.h"
#include "intField.h"
#include "doubleField.h"
#include "writer.h"

/**
 * The pack to be packed with particles.
 */
class Pack {
  public:
    // Methods

    /**
     * Pack Constructor
     * @param packer Determines the relationship between IJK and Cartesian coordinates.
     */
    Pack(Packer *packer);
    ~Pack();

    /**
     * Add a shape to the Pack
     * @param shape Shape to be mapped
     */
    void AddShape(Shape *shape);

    /**
     * Pack all added shapes and generate positions and states
     */
    void Process();

    double *positions; /**< Array containing all packed particle positions */
    int *states; /**< Array containing all packed particle states */
    long numParticles; /**< The number of particles packed in this pack */
    int dim; /**< Dimensionality of pack (2D or 3D) */

  private:
    // Methods
    /**
     * Map a shape to the pack
     * @param shape Shape to be mapped
     */
    void MapShape(Shape *shape);

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
     * Get the size of the pack in integer index format
     * @return Pointer to an array of length 3 containing length in ijk
     */
    long *GetIntLength();

    /**
     * Get the size of the pack in cartesian format
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
     * Get the number of particles in this pack
     */
    long ComputeNumParticles();

    /**
     * Get the dimensionality of the pack
     * @return Number of dimensions
     */
    int GetDim();

    //Properties
    Packer *packer;
    long *len; /**< Size of the pack in ijk system */
    int *state; /**< ijk Array of particle states */
    double *pos; /**< ijk Array of particle coordinates (cartesian) */
    std::vector<Shape*> shapes; /**< Vector of integer fields */
};

#endif
