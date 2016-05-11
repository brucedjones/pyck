#ifndef CUBIC_PACKER_H
#define CUBIC_PACKER_H

#include "../packer.h"

class CubicPacker: public Packer {

  public:

    /**
     * CubicPacker constructor.
     * @param doubleLenIn Size of the domain in Cartesian coordinate system
     * @param h Minimum particle separation
     */
    CubicPacker(double *doubleLenIn, double h);
    ~CubicPacker();

    /**
     * Converts an ijk index to Cartesian coordinates
     * @param i      i index (along X)
     * @param j      j index (along Y)
     * @param k      k index (along Z)
     * @param posOut Cartesian coordinate output, array of length 3
     */
    void IDX2Pos(long i, long j, long k, double *posOut);

    /**
     * Converts a Cartesian coordinate to an IJK position
     * @param posIn   Cartesian coordinate input, array of length 3
     * @param idxOut  ijk coordinate output, array of length 3
     * @param doFloor Returns the lower-left point in relation to the Cartesian point if true. Returns the upper-right point if false
     */
    void Pos2IDX(double *posIn, long *idxOut, bool doFloor);
};

#endif
