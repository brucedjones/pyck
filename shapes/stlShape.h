#ifndef STL_SHAPE_H
#define STL_SHAPE_H

#include "../shape.h"

#include <string>

class StlShape: public Shape {
  public:
    /**
     * StlShape constructor
     * @param state State to be applied to particles within this shape. state = 0 will remove particle from output
     * @param c Center of the sphere in cartesian coordinates
     * @param r Radius of the sphere
     * @param domain Domain in which this shape will be mapped
     */
    StlShape(int state, std::string fname, double *c, double scale);
    ~StlShape();

    /**
     * Check if given coordinate is inside this shape
     * @param  pt Coordinates to check
     * @return    True if coordinate is inside shape, false otherwise
     */
    bool IsInside(double *pt);

  private:
    double *c; /**< Center of the stl in cartesian coordinates */
    double scale; /**< Scaling factor to be applied to the stl */
    double *v1;
    double *v2;
    double *v3;
    double *normal;
    long numFacets;

    /**
     * Check if ray cast from point along Z direction intersects with a facet
     * @param  pt           input point
     * @param  v1           Vertex 1
     * @param  v2           Vertex 2
     * @param  v3           Vertex 3
     * @return              True if intersection occurs
     */
    bool FacetIntersection(double *pt, double *v1, double *v2, double *v3, double *n);
};

#endif