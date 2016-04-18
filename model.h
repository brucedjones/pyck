#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>
#include <map>

#include "domain.h"
#include "writer.h"

class Model {
  public:

    /**
     * Model Constructor
     * @param pack Packed pack object
     */
    Model(Pack *pack);

    /**
     * Model Constructor
     * @param positions N x 3 array of positions, third dimension should be 0.0 for 2d
     * @param states N x 1 array of pack states
     * @param numParticles Specifies N particles
     */
    Model(double *positions, int *states, long numParticles);
    ~Model();

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

    /**
     * Write domain to CSV file
     * @param fname Output filename
     */
    void Serialize(std::string fname, Writer *writer);

  private:
    double *positions;
    int *states;
    long numParticles;
    std::vector<IntField*> intFields; /**< Vector of integer fields */
    std::vector<DoubleField*> doubleFields; /**< Vector of double fields */
    std::map<std::string, std::string> parameters; /**< Map of parameters */


};

#endif
