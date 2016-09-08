#ifndef TRIPRISM_H
#define TRIPRISM_H
#include "../shape.h"

class TriPrism: public Shape {
  public:
    /**
     * Triangular Prism constructor
     * @param state State to be applied to particles within this shape. state = 0 will remove particle from output
     * @param pt1 first point to define tripism in cartesian coordinates
     * @param pt2 second point to define tripism in cartesian coordinates
     * @param pt3 third point to define tripism in cartesian coordinates
     * @param pt4 fourth point to define tripism in cartesian coordinates
     * @param l Length of the cylinder in cartesian coordinates, (0,0,l) or (0,l,0) or (l,0,0) indicates the direction
     * @param invert Inverts the shape to tag particles outside the shape instead of inside
        //        pt1  ______length_______
        //        ||||                    ||||
        //       ||  ||                  ||  ||
        //      ||    ||                ||    ||
        //     ||      ||              ||      ||
        // pt3||||||||||||pt2_________||||||||||||
     */
    TriPrism(int state, double *pt1, double *pt2, double *pt3, double l, bool invert=false);
    ~TriPrism();

    /**
     * Check if given coordinate is inside this shape
     * @param  pt Coordinates to check
     * @return    True if coordinate is inside shape, false otherwise
     */
    bool IsInside(double *pt);

  private:
    double *pt1; /**< Point 1 of the triprism in cartesian coordinates */
    double *pt2; /**< Point 2 of the triprism in cartesian coordinates */
    double *pt3; /**< Point 3 of the triprism in cartesian coordinates */
    double l; /**< Length of the triprism */
};

#endif
