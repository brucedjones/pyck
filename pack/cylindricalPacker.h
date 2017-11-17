
#ifndef CYLINDRICALPACKER_H
#define CYLINDRICALPACKER_H

#include "../pack.h"
#include "../shape.h"

class CylindricalPacker : public Pack
{
public:
    /**
     * 2D Circular constructor.
     * @param c Array of 3 doubles (x y z) representing the center of the circular packing
     * @param r Double representing the radius of the ellipse along X
     * @param ratio Double representing the ratio of the ellipse so that the radius along Y is equal to r*ratio
     * @param h Double representing the spacing between created particles
     * @param state Integer representing the state of the created particles
     * @param num_div Double indicating in how many parts the half-circle is divided  (default 3)
     */
  CylindricalPacker(std::vector<double> c, double r, double ratio, double h, int state, double num_div = 3.0);
      /**
     * 3D 'Cylindrical' Circular constructor.
     * @param c Array of 3 doubles (x y z) representing the center of the ellipsoidal packing
     * @param r Double representing the radius of the ellipse along X
     * @param ratio Double representing the ratio of the ellipse so that the radius along Y is equal to r*ratio
     * @param l  Array of 3 doubles (lx ly lz). Only one component should be non-zero indicating the length of the and the direction of the 'cylinder'
     * @param h Double representing the spacing between created particles
     * @param state Integer representing the state of the created particles
     * @param num_div Double indicating in how many parts the half-circle is divided  (default 3)
     */
  CylindricalPacker(std::vector<double> c, double r, double ratio, std::vector<double> l, double h, int state, double num_div = 3.0);
        /**
     * 3D Circular constructor.
     * @param c Array of 3 doubles (x y z) representing the center of the ellipsoidal packing
     * @param r Double representing the radius of the ellipse along X
     * @param ratioY Double representing the ratio of the ellipse so that the radius along Y is equal to r*ratioY
     * @param ratioZ Double representing the ratio of the ellipse so that the radius along Z is equal to r*ratioZ
     * @param h Double representing the spacing between created particles
     * @param state Integer representing the state of the created particles
     * @param num_div Double indicating in how many parts the half-circle is divided  (default 3)
     */
  CylindricalPacker(std::vector<double> c, double r, double ratioY, double ratioZ, double h, int state, double num_div = 3.0);
       /**
     * Circular destructor.
     */
  ~CylindricalPacker();

    /**
     * 2D Method to update the state of the particles outside a certain radius.
     * @param c Array of 3 doubles (x y z) representing the center of the circular packing
     * @param r0 Double representing the radius of the ellipse along X
     * @param h Double representing the spacing between created particles
     * @param r Double representing the radius from which particles have their state updated
     * @param ratio Double representing the ratio of the ellipse so that the radius along Y is equal to r*ratio
     * @param state Integer representing the state of the created particles
     */
  void updateStates(std::vector<double> c, double r,double ratio, int state);
        /**
     * 3D Method to update the state of the particles outside a certain radius.
     * @param c Array of 3 doubles (x y z) representing the center of the circular packing
     * @param r0 Double representing the radius of the ellipse along X
     * @param h Double representing the spacing between created particles
     * @param r Double representing the radius from which particles have their state updated
     * @param ratioY Double representing the ratio of the ellipse so that the radius along Y is equal to r*ratioY
     * @param ratioZ Double representing the ratio of the ellipse so that the radius along Z is equal to r*ratioZ
     * @param state Integer representing the state of the created particles
     */
  void updateStates(std::vector<double> c, double r,double ratioY, double ratioZ, int state);
    /**
     * Method that return the particles within a shape
     * @param shape Shape object
     */
  void MapShape(Shape *shape);
          /**
     * Pack all added shapes and generate positions and states
     */
    void Process();
    /**
     * Get the number of particles in this Pack
     */
    long ComputeNumParticles();
        /**
     * Create 1D array of particle positions
     * @param numParticles_temp Long representing the number of particles with a non-zero value state
     * @return 1D array of particle positions, format is [x1,y1,x2,y2,...xn,yn]
     */
    double *CreatePositions(long numParticles_temp);

    /**
     * Create 1D array of particle positions
     * @param numParticles_temp Long representing the number of particles with a non-zero value state
     * @return 1D array of particle States, format is [x1,y1,x2,y2,...xn,yn]
     */
    int *CreateStates(long numParticles_temp);
    /**
     * Get positions array
     */
  double *getPositions();
  /**
  * Get states array
  */
  int *getStates();

  /**
  * Get dimension value
  */
  int getDim();
};

#endif
