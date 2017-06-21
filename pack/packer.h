#ifndef PACKER_H
#define PACKER_H

#include <vector>

class Packer {

  public:
    /**
     * Packer constructor. A new constructor should be implemented by the deriving class which sets the length of the domain in ijk and the spacing between particles.
     * @param len Size of the domain in Cartesian coordinate system
     * @param offset Vector used to shift the particles in this pack
     */
    Packer(double *len, double *offset=nullptr);
    ~Packer();

    /**
     * Converts an ijk index to Cartesian coordinates
     * @param i      i index (along X)
     * @param j      j index (along Y)
     * @param k      k index (along Z)
     * @param posOut Cartesian coordinate output, array of length 3
     */
    virtual void IDX2Pos(long i, long j, long k, double *posOut)=0;

    /**
     * Converts a Cartesian coordinate to an IJK position
     * @param posIn   Cartesian coordinate input, array of length 3
     * @param idxOut  ijk coordinate output, array of length 3
     * @param doFloor Returns the lower-left point in relation to the Cartesian point if true. Returns the upper-right point if false
     */
    virtual void Pos2IDX(double *posIn, long *idxOut, bool doFloor)=0;

    /**
     * Get a domain extent which represents a periodic domain. For a domain boundary to be periodic, particles must be packed all the way to the boundary.
     * @return Periodic domain extent
     */
    virtual std::vector<double> GetPeriodicExtent()=0;

    /**
     * Applies the packers offset to a set of coordinates
     * @param Coordinates to apply the offset to
     */
    void ApplyOffset(double *coord);

    /**
     * Removes the packers offset to a set of coordinates
     * @param Coordinates to remove the offset from
     */
    void RemoveOffset(double *coord);

    /**
     * Get particle volume
     * @return The approximate volume of a single particle, computed as domain volume / number of particles.
     */
     double GetParticleVolume();

    double dx; /**< Spacing between particle */
    long len[3]; /**< Size of the domain in ijk system */
    double lend[3]; /**< Size of the domain in Cartesian coordinate system*/
    double offset[3]; /**< Vector used to shift the particles in this pack */
};

#endif
