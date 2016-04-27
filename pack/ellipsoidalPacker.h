
#ifndef ELLIPSOIDALPACKER_H
#define ELLIPSOIDALPACKER_H

#include "../pack.h"
#include "../shape.h"

class EllipsoidalPacker : public Pack
{
public:

    /**
     * 2D Ellipsoidal constructor.
     * @param c Array of 3 doubles (x y z) representing the center of the ellipsoidal packing
     * @param r Double representing the radius of the ellipse along X
     * @param ratio Double representing the ratio of the ellipse so that the radius along Y is equal to r*ratio
     * @param h Double representing the spacing between created particles
     * @param state Integer representing the state of the created particles
     * @param tolerance_angle Double representing the tolerance for the angle update (default 0.001)
     * @param tolerance_h Double representing the tolerance for the spacing (default 0.55)
     * @param random_startingpoint Boolean to enable/disable the random starting point when packing the inner ellipses (default true)
     * @param adjust_h Boolean to enable/disable the adjustement of h so that the  particles are better (equally) spaced along the ellipse 9default true)
     */
  EllipsoidalPacker(double *c, double r, double ratio,double h, int state, double tolerance_angle = 0.001, double tolerance_h = 0.55, bool random_startingpoint = true, bool adjust_h = true);
    /**
     * 3D 'Cylindrical' Ellipsoidal constructor.
     * @param c Array of 3 doubles (x y z) representing the center of the ellipsoidal packing
     * @param r Double representing the radius of the ellipse along X
     * @param ratio Double representing the ratio of the ellipse so that the radius along Y is equal to r*ratio
     * @param l  Array of 3 doubles (lx ly lz). Only one component should be non-zero indicating the length of the and the direction of the 'cylinder'
     * @param h Double representing the spacing between created particles
     * @param state Integer representing the state of the created particles
     * @param tolerance_angle Double representing the tolerance for the angle update (default 0.001)
     * @param tolerance_h Double representing the tolerance for the spacing (default 0.55)
     * @param random_startingpoint Boolean to enable/disable the random starting point when packing the inner ellipses (default true)
     * @param adjust_h Boolean to enable/disable the adjustement of h so that the  particles are better (equally) spaced along the ellipse 9default true)
     */
  EllipsoidalPacker(double *c, double r, double ratio, double *l, double h, int state, double tolerance_angle = 0.001, double tolerance_h = 0.55, bool random_startingpoint = true, bool adjust_h = true);
      /**
     * 3D Ellipsoidal constructor.
     * @param c Array of 3 doubles (x y z) representing the center of the ellipsoidal packing
     * @param r Double representing the radius of the ellipse along X
     * @param ratioY Double representing the ratio of the ellipse so that the radius along Y is equal to r*ratioY
     * @param ratioZ Double representing the ratio of the ellipse so that the radius along Z is equal to r*ratioZ
     * @param h Double representing the spacing between created particles
     * @param state Integer representing the state of the created particles
     * @param tolerance_angle Double representing the tolerance for the angle update (default 0.001)
     * @param tolerance_h Double representing the tolerance for the spacing (default 0.55)
     * @param random_startingpoint Boolean to enable/disable the random starting point when packing the inner ellipses (default true)
     * @param adjust_h Boolean to enable/disable the adjustement of h so that the  particles are better (equally) spaced along the ellipse 9default true)
     */
  EllipsoidalPacker(double *c, double r, double ratioY, double ratioZ, double h, int state, double tolerance_angle = 0.001, double tolerance_h = 0.55, bool random_startingpoint = true, bool adjust_h = true);
     /**
     * Ellipsoidal destructor.
     */
  ~EllipsoidalPacker();
    /**
     * 2D Method to update the state of the particles outside a certain radius.
     * @param c Array of 3 doubles (x y z) representing the center of the ellipsoidal packing
     * @param r0 Double representing the radius of the ellipse along X
     * @param h Double representing the spacing between created particles
     * @param r Double representing the radius from which particles have their state updated
     * @param ratio Double representing the ratio of the ellipse so that the radius along Y is equal to r*ratio
     * @param state Integer representing the state of the created particles
     */
  void updateStates(double *c, double r0, double h, double r,double ratio, int state);
      /**
     * 3D Method to update the state of the particles outside a certain radius.
     * @param c Array of 3 doubles (x y z) representing the center of the ellipsoidal packing
     * @param r0 Double representing the radius of the ellipse along X
     * @param h Double representing the spacing between created particles
     * @param r Double representing the radius from which particles have their state updated
     * @param ratioY Double representing the ratio of the ellipse so that the radius along Y is equal to r*ratioY
     * @param ratioZ Double representing the ratio of the ellipse so that the radius along Z is equal to r*ratioZ
     * @param state Integer representing the state of the created particles
     */
  void updateStates(double *c, double r0, double h, double r,double ratioY, double ratioZ, int state);

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
     * Get number of particles
     */
  long getNumParticles();
            /**
     * Get number of particles for a given state
     * @param state Integer representing the state of the created particles
     */
  long getNumParticlesByState(int state);
      /**
     * Get dimension value
     */
  int getDim();

private:
};

#endif
