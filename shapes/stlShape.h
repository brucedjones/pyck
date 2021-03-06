#ifndef STL_SHAPE_H
#define STL_SHAPE_H

#include "../shape.h"

#include <string>
#include <vector>

class FacetBins {
  public:
    FacetBins(float minX, float minY, float maxX, float maxY,  std::vector<double> &v1, std::vector<double> &v2, std::vector<double> &v3, long numFacets);
    ~FacetBins();

    std::vector<long> *GetBin(double *pt);

  private:
    float dx,dy,minX,minY;
    int nx,ny;
    std::vector<long> **bins;
};

class Geom {
  public:
    static bool PointInsideTriangle(double *p, double *p0, double *p1, double *p2);
    static bool PointInsideSquare(double *p, double *p0, double *p1);
    static bool TriSqIntersection(double *v1, double *v2, double *v3, double *p1, double *p2);
    static bool LineLineIntersection(double *a1, double *a2, double *b1, double *b2);
};

class StlShape: public Shape {
  public:
    /**
     * StlShape constructor
     * @param state State to be applied to particles within this shape. state = 0 will remove particle from output
     * @param fname STL filename
     * @param translation (Optional) Vector of length three representing a translation to be applied to the shape
     * @param scale (Optional) Scaling factor to be applied to the STL geometry
     * @param rot_axis (Optional) Vector of length three representing the axis about which to rotate the STL Geometry
     * @param rot_angle (Optional) Angle (in radians) by which the shape will be rotated about the rotation axis
     * @param invert Inverts the shape to tag particles outside the shape instead of inside
     */
    StlShape(int state, std::string fname, std::vector<double> translation = std::vector<double>(), double scale=1.0, std::vector<double> rot_axis = std::vector<double>(), double rot_angle=0.0, bool invert=false);
    ~StlShape();

    /**
     * Check if given coordinate is inside this shape
     * @param  pt Coordinates to check
     * @return    True if coordinate is inside shape, false otherwise
     */
    bool IsInside(double *pt);

  private:
    std::vector<double> c; /**< Center of the stl in cartesian coordinates */
    std::vector<double> translation; /**< Translation to apply to the STL */
    double scale; /**< Scaling factor to be applied to the stl */
    std::vector<double> v1; /**< Vector of vertex coordinates for vertex 1 (x1,y1,z1,x2,y2,z2,...xn,yn,zn) */
    std::vector<double> v2; /**< Vector of vertex coordinates for vertex 2 (x1,y1,z1,x2,y2,z2,...xn,yn,zn) */
    std::vector<double> v3; /**< Vector of vertex coordinates for vertex 3 (x1,y1,z1,x2,y2,z2,...xn,yn,zn) */
    std::vector<double> normal; /**< Vector of face normals*/
    long numFacets; /**< Number of triangles*/
    FacetBins *bins;

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
