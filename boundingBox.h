#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

/**
 * Stores Lower-left and Upper-right bounding box coordinates in ijk indexes. This bounding box will be iterated over when mapping a shape.
 */
class BoundingBox {
  public:
    /**
     * BoundingBox Constructor
     * @param p1 Lower-left corner in cartesian coordinates
     * @param p2 Upper-right corner in cartesian coordinates
     * @param domain Domain in which this BoundingBox exists
     */
    BoundingBox(double *p1, double *p2);
    ~BoundingBox();

    double *p1; /**< Lower-left corner */
    double *p2; /**< Upper-right corner */
};

#endif
