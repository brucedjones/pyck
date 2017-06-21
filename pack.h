#ifndef PACK_H
#define PACK_H

#include <vector>

#include "shape.h"

/**
 * The pack to be packed with particles.
 */
class Pack {
  public:
    // Methods

    /**
     * Pack Constructor
     */
    Pack();
    ~Pack();

    /**
     * Add a shape to the Pack
     * @param shape Shape to be mapped
     */
    void AddShape(Shape *shape);

    /**
     * Pack all added shapes and generate positions and states
     */
    void MapShapes();

    /**
    * Get number of particles
    * @return the number of particles in the model
    */
    long GetNumParticles();

    /**
    * Get number of particles for a given state
    * @param state Integer representing the state of the created particles
    * @return The number of particles with corresponding input state
    */
    long GetNumParticlesByState(int state);

    double * GetPositions();
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
    virtual void MapShape(Shape *shape)=0;

    std::vector<Shape*> shapes; /**< Vector of integer fields */
};

#endif
