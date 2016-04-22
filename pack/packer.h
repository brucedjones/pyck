#ifndef PACKER_H
#define PACKER_H

class Packer {

  public:
    /**
     * Packer constructor. A new constructor should be implemented by the deriving class which sets the length of the domain in ijk and the spacing between particles.
     */
    Packer();
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

    double dx; /**< Offset between particle */
    long len[3]; /**< Size of the domain in ijk system */
};

#endif
