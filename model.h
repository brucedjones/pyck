#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>
#include <map>
#include <vector>
#include <Python.h>

#include "pack.h"
#include "writer.h"

class Model {
  public:

    /**
     * Model Constructor, creates an empty model with no particles
     */
    Model();

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
     * @param dim Specifies the dimensionality of the pack
     */
    Model(double *positions, int *states, long numParticles, int dim);

    /**
     * Model Constructor
     * @param positions N x 3 array of positions, third dimension should be 0.0 for 2d
     * @param states N x 1 array of pack states
     * @param numParticles Specifies N particles
     * @param dim Specifies the dimensionality of the pack
     */
    Model(std::vector<double> positions, std::vector<int> states, long numParticles, int dim);

    ~Model();

    /**
     * Append particles from another pack to this model
     * @param pack A fully processed pack object
     */
    void AddPack(Pack *pack);

    /**
     * Append particles to this model
     * @param positions    Nx3 array of positions (x1,y1,z1,x2,y2,z2,...,xn,yn,zn)
     * @param states       Length N integer array of states
     * @param numParticles Number of particles to add
     * @param dim          Dimensionality of the pack
     */
    void AddPack(double *positions, int *states, long numParticles, int dim);

    /**
     * Append particles to this model
     * @param positions    Nx3 array of positions (x1,y1,z1,x2,y2,z2,...,xn,yn,zn)
     * @param states       Length N integer array of states
     * @param numParticles Number of particles to add
     * @param dim          Dimensionality of the pack
     */
    void Model::AddPack(std::vector<double> positions, std::vector<int> states, long numParticles, int dim);
    
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
     * @param state  particle state for which these values will be applied
     * @param val    Array of length equal to the dimensionality of the field
     */
    void SetIntField(int handle, int state, std::vector<int> val);
    
    /**
     * Set the values of an integer field
     * @param handle Handle of the field to be set
     * @param state  particle state for which these values will be applied
     * @param val    Value to set
     */
    void SetIntField(int handle, int state, int val);
    
    /**
     * Set the values of an integer field
     * @param handle Handle of the field to be set
     * @param state  particle state for which these values will be applied
     * @param PyFunc Python callback used to determine the value of the field for any given particle. Callback takes an array indicating xyz position, and returns the value of the field at this position.
     */
    void SetIntField(int handle, int state, PyObject *PyFunc);

    /**
     * Get a pointer to a DoubleField
     * @param handle Handle of the field
     */
    IntField *GetIntField(int handle);

    /**
    * Get the xyz position of a particle
    */
    double *GetPositions();

    /**

    */
    int GetNumberParticles();

    /**
     * Set the values of an float field
     * @param handle Handle of the field to be set
     * @param state  particle state for which these values will be applied
     * @param val    Value to set
     */
    void SetDoubleField(int handle, int state, double val);
    
    /**
     * Set the values of an float field
     * @param handle Handle of the field to be set
     * @param state  particle state for which these values will be applied
     * @param val    Array of length equal to the dimensionality of the field
     */
    void SetDoubleField(int handle, int state, std::vector<double> val);
    
    /**
     * Set the values of a float field
     * @param handle Handle of the field to be set
     * @param state  particle state for which these values will be applied
     * @param PyFunc Python callback used to determine the value of the field for any given particle. Callback takes an array indicating xyz position, and returns the value of the field at this position.
     */
    void SetDoubleField(int handle, int state, PyObject *PyFunc);

    /**
     * Get a pointer to a DoubleField
     * @param handle Handle of the field
     */
    DoubleField *GetDoubleField(int handle);

    /**
     * Add a parameter to the domain
     * @param key   The label for this parameter
     * @param value The value of this parameter
     */
    void SetParameter(std::string key, std::string value);

    /**
     * Add a parameter to the domain
     * @param parameters   Map of parameters to add
     */
    void SetParameters(std::map<std::string, std::string> &parameters);

    /**
     * Read a parameter of integer type
     * @param key   Parameter name
     */
    int ReadSingleIntegerParameter(std::string key);

   /**
     * Read a parameter of double type or a double array
     * Note: n can be as large as 3, but cannot be larger than 3 due to vector interface in swig.
     * @param key: parameter name
     * @param n: number of elements
     */
    std::vector<double> ReadMultipleDoubleParameter(std::string key, int n);

    /**
     * Write domain to CSV file
     * @param fname Output filename
     */
    void Serialize(std::string fname, Writer *writer);

  private:
    double *positions;
    int *states;
    long numParticles;
    int dim;
    std::vector<IntField*> intFields; /**< Vector of integer fields */
    std::vector<DoubleField*> doubleFields; /**< Vector of double fields */
    std::map<std::string, std::string> parameters; /**< Map of parameters */

    template<typename T>
    int Process_Python_Result(PyObject* incoming, std::vector<T> *data);
};

#endif
