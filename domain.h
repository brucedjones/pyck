#ifndef DOMAIN_H
#define DOMAIN_H
#include <vector>
#include <string>
#include <map>

#include "shape.h"
#include "packer.h"
#include "intField.h"
#include "doubleField.h"
#include "writer.h"

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
    Domain(Packer *packer, Writer *writer);
    ~Domain();

    /**
     * Write domain to CSV file
     * @param fname Output filename
     */
    void Serialize(std::string fname);

    /**
     * Add a shape to the Domain
     * @param shape Shape to be mapped
     */
    void AddShape(Shape *shape);

    /**
     * Pack all added shapes and generate positions and states
     */
    void Pack();

    /**
     * Create a dim dimensional field of integers
     * @param  name Name of the field
     * @param  dim  dimensionality of the field
     * @return      A Handle to the field so that values may be set
     */
    int CreateIntField(std::string name, int dim);

    /**
     * Create a dim dimensional field of floats
     * @param  name Name of the field
     * @param  dim  dimensionality of the field
     * @return      A Handle to the field so that values may be set
     */
    int CreateDoubleField(std::string name, int dim);

    /**
     * Set the values of an integer field
     * @param handle Handle of the field to be set
     * @param state  particle state for which these values will be applioed
     * @param val    Array of length equal to the dimensionality of the field
     */
    void SetIntField(int handle, int state, int *val);

    /**
     * Set the values of an float field
     * @param handle Handle of the field to be set
     * @param state  particle state for which these values will be applioed
     * @param val    Array of length equal to the dimensionality of the field
     */
    void SetDoubleField(int handle, int state, double *val);

    /**
     * Add a parameter to the domain
     * @param key   The label for this parameter
     * @param value The value of this parameter
     */
    void AddParameter(std::string key, std::string value);

  private:
    // Methods
    /**
     * Map a shape to the domain
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
     * Get the size of the domain in integer index format
     * @return Pointer to an array of length 3 containing length in ijk
     */
    long *GetIntLength();

    /**
     * Get the size of the domain in cartesian format
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
     * Get the number of particles in this domain
     */
    long ComputeNumParticles();

    /**
     * Get the dimensionality of the domain
     * @return Number of dimensions
     */
    int GetDim();

    //Properties
    Packer *packer;
    Writer *writer;
    long *len; /**< Size of the domain in ijk system */
    int dim; /**< Dimensionality of domain (2D or 3D) */
    int *state; /**< ijk Array of particle states */
    double *pos; /**< ijk Array of particle coordinates (cartesian) */
    double *positions; /**< Array containing all packed particle positions */
    int *states; /**< Array containing all packed particle states */
    long numParticles; /**< The number of particles packed in this domain */
    std::vector<Shape*> shapes; /**< Vector of integer fields */
    std::vector<IntField*> intFields; /**< Vector of integer fields */
    std::vector<DoubleField*> doubleFields; /**< Vector of double fields */
    std::map<std::string, std::string> parameters; /**< Map of parameters */
};

#endif
