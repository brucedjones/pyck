#include "stlShape.h"
#include "../quarternionRotation.h"

#include <string>
#include <iostream>
#include <fstream>
#include <math.h>
#include <omp.h>
#include <algorithm>

StlShape::StlShape(int state, std::string fname, std::vector<double> translation, double scale, std::vector<double> rot_axis, double rot_angle, bool invert) : Shape(state,invert)
{
  bool translate=false;
  if(translation.size()>0) translate=true;

  bool rescale=false;
  if(scale!=1.0) rescale=true;

  bool rotation=false;
  if(rot_axis.size()>0) rotation=true;

  if(translate) this->translation = translation;

  if(rescale) this->scale = scale;

  // Normalize the rotation axis
  if(rotation){
    double rot_mag;
    for (size_t i = 0; i < 3; i++) {
      rot_mag += rot_axis[i]*rot_axis[i];
    }
    rot_mag = sqrt(rot_mag);
    if(rot_mag<0.00000001) rot_mag = 1;
    for (size_t i = 0; i < 3; i++) {
      rot_axis[i]/=rot_mag;
    }
  }

  std::vector<double> center(3,0.0);

  // Load the STL file
  std::ifstream stlFile(fname.c_str(), std::ios::in | std::ios::binary);

  char header_info[80] = "";
  char buff[4];

  if (stlFile) {

    // Skip the header
    stlFile.read (header_info, 80);

    // Read number of triangles
    stlFile.read (buff, 4);
    numFacets = (long)*((unsigned int*)buff);

    // Allocate arrays
    normal.resize(numFacets*3);
    v1.resize(numFacets*3);
    v2.resize(numFacets*3);
    v3.resize(numFacets*3);

    // Read normal and vertices
    for (size_t t = 0; t < numFacets; t++) {
      stlFile.read (buff, 4);
      normal[t*3] = *(float*)buff;
      stlFile.read (buff, 4);
      normal[t*3+1] = *(float*)buff;
      stlFile.read (buff, 4);
      normal[t*3+2] = *(float*)buff;

      stlFile.read (buff, 4);
      v1[t*3] = *(float*)buff;
      stlFile.read (buff, 4);
      v1[t*3+1] = *(float*)buff;
      stlFile.read (buff, 4);
      v1[t*3+2] = *(float*)buff;

      stlFile.read (buff, 4);
      v2[t*3] = *(float*)buff;
      stlFile.read (buff, 4);
      v2[t*3+1] = *(float*)buff;
      stlFile.read (buff, 4);
      v2[t*3+2] = *(float*)buff;

      stlFile.read (buff, 4);
      v3[t*3] = *(float*)buff;
      stlFile.read (buff, 4);
      v3[t*3+1] = *(float*)buff;
      stlFile.read (buff, 4);
      v3[t*3+2] = *(float*)buff;

      // Find centroid
      for (size_t i = 0; i < 3; i++) {
        center[i] += v1[t*3+i];
        center[i] += v2[t*3+i];
        center[i] += v3[t*3+i];
      }
      // Discard Attribute byte count
      stlFile.read (buff, 2);
    }
  } else {
    std::cout << "Failed to read STL file!" << std::endl;
  }

  stlFile.close();

  // Finalize centroid calculation
  for (size_t i = 0; i < 3; i++) center[i] = center[i]/(numFacets*3);
  this->c = center;

  // Rotate, Scale, Translate points
  double *quart = new double[4];
  if(rotation)
  {
    quart[0] = cos(rot_angle/2);
    quart[1] = rot_axis[0]*sin(rot_angle/2);
    quart[2] = rot_axis[1]*sin(rot_angle/2);
    quart[3] = rot_axis[2]*sin(rot_angle/2);
  }

  if(translate || rescale || rotation)
  {
    for (size_t t = 0; t < numFacets; t++) {

      for (size_t i = 0; i < 3; i++) {
        v1[t*3+i] -= this->c[i];
        v2[t*3+i] -= this->c[i];
        v3[t*3+i] -= this->c[i];
      }

      if(rotation)
      {
        rotate(&v1[t*3],quart);
        rotate(&v2[t*3],quart);
        rotate(&v3[t*3],quart);
        rotate(&normal[t*3],quart);
      }

      if(rescale)
      {
        for (size_t i = 0; i < 3; i++) {
          v1[t*3+i] *= scale;
          v2[t*3+i] *= scale;
          v3[t*3+i] *= scale;
        }
      }

      for (size_t i = 0; i < 3; i++) {
        v1[t*3+i] += this->c[i];
        v2[t*3+i] += this->c[i];
        v3[t*3+i] += this->c[i];
      }

      if(translate)
      {
        for (size_t i = 0; i < 3; i++) {
            v1[t*3+i] += this->translation[i];
            v2[t*3+i] += this->translation[i];
            v3[t*3+i] += this->translation[i];
        }
      }
    }
  }

  // Find the bounding box
  double *p1 = new double[3];
  double *p2 = new double[3];
  p1[0] = 100000000000000; p1[1] = 100000000000000; p1[2] = 100000000000000;
  p2[0] = 0; p2[1] = 0; p2[2] = 0;

  for (size_t t = 0; t < numFacets; t++) {
    for (size_t i = 0; i < 3; i++) {
      if(v1[t*3+i]<p1[i]) p1[i] = v1[t*3+i];
      if(v2[t*3+i]<p1[i]) p1[i] = v2[t*3+i];
      if(v3[t*3+i]<p1[i]) p1[i] = v3[t*3+i];

      if(v1[t*3+i]>p2[i]) p2[i] = v1[t*3+i];
      if(v2[t*3+i]>p2[i]) p2[i] = v2[t*3+i];
      if(v3[t*3+i]>p2[i]) p2[i] = v3[t*3+i];
    }
  }

  this->boundingBox = new BoundingBox(p1,p2);

  this->bins = new FacetBins(p1[0],p1[1],p2[0],p2[1],v1,v2,v3,numFacets);

  delete [] p1;
  delete [] p2;
  delete [] quart;
}

StlShape::~StlShape(){
  delete bins;
}

bool StlShape::IsInside(double *pt)
{
  bool isInside = false;

  std::vector<long> *bin = bins->GetBin(pt);
  long *facets = bin->data();

  int numIntersections = 0;
  for (size_t i = 0; i < bin->size(); i++) {
    long id = facets[i];
    bool intersects = FacetIntersection(pt,&v1[id*3],&v2[id*3],&v3[id*3],&normal[id*3]);
    if(intersects) numIntersections++;
  }

  if(numIntersections%2 == 1) isInside = true;

  return isInside;
}

bool StlShape::FacetIntersection(double *p, double *p0, double *p1, double *p2, double *n)
{
  // First check if infinite ray intersects facet
  bool inside = Geom::PointInsideTriangle(p,p0,p1,p2);

  if(inside)
  {
    // Now find the z coordinate of the intersection and
    // check it is greater than the particles z coordinate
    double z = (n[0]*p0[0]+n[1]*p0[1]+n[2]*p0[2]-n[0]*p[0]-n[1]*p[1])/n[2];
    if(z>p[2]){
      inside = true;
    } else {
      inside = false;
    }
  }

  return inside;
}

FacetBins::FacetBins(float minX, float minY, float maxX, float maxY,  std::vector<double> &v1, std::vector<double> &v2, std::vector<double> &v3, long numFacets)
{
  this->nx = 10;
  this->ny = 10;
  this->dx = (maxX-minX)/nx;
  this->dy = (maxY-minY)/ny;
  this->minX = minX;
  this->minY = minY;

  bins = new std::vector<long>*[nx*ny];

  #pragma omp parallel for
  for (size_t idx = 0; idx < nx*ny; idx++) {

    bins[idx] = new std::vector<long>();

    int j = idx/nx;
    int i = idx-j*nx;

    double p1[2],p2[2];
    p1[0] = i*dx+minX;
    p2[0] = (i+1)*dx+minX;
    p1[1] = j*dy+minY;
    p2[1] = (j+1)*dy+minY;

    for (size_t facet = 0; facet < numFacets; facet++) {
      if(Geom::TriSqIntersection(&v1[facet*3],&v2[facet*3],&v3[facet*3],&p1[0],&p2[0])){
        bins[idx]->push_back(facet);
      }
    }
  }
  for (size_t idx = 0; idx < nx*ny; idx++) {
    std::sort(bins[idx]->begin(), bins[idx]->end());
  }
}

FacetBins::~FacetBins()
{
  for (size_t i = 0; i < nx*ny; i++) {
    delete bins[i];
  }
  delete [] bins;
}

std::vector<long> *FacetBins::GetBin(double *pt)
{
  int i = (int)((pt[0]-minX)/dx);
  int j = (int)((pt[1]-minY)/dy);

  if(i<0) i=0;
  if(i>=nx) i=nx-1;
  if(j<0) j=0;
  if(j>=ny) j=ny-1;

  int idx = i + j*nx;

  return bins[idx];
}

bool Geom::TriSqIntersection(double *v1, double *v2, double *v3, double *p1, double *p2)
{
  // Check if triangle vertices are inside square
  if(Geom::PointInsideSquare(v1,p1,p2)) return true;
  if(Geom::PointInsideSquare(v2,p1,p2)) return true;
  if(Geom::PointInsideSquare(v3,p1,p2)) return true;

  // Check if square vertices are inside triangle
  double sp[2];
  // Lower-left
  sp[0] = p1[0]; sp[1] = p1[1];
  if(Geom::PointInsideTriangle(&sp[0],v1,v2,v3)) return true;
  // Upper-left
  sp[0] = p1[0]; sp[1] = p2[1];
  if(Geom::PointInsideTriangle(&sp[0],v1,v2,v3)) return true;
  // Lower-right
  sp[0] = p2[0]; sp[1] = p1[1];
  if(Geom::PointInsideTriangle(&sp[0],v1,v2,v3)) return true;
  // Upper-right
  sp[0] = p2[0]; sp[1] = p2[1];
  if(Geom::PointInsideTriangle(&sp[0],v1,v2,v3)) return true;

  // Check if triangle edges intersect square edges
  double *v[4];
  v[0] = v1; v[1] = v2; v[2] = v3; v[3]=v1;

  double sp1[2], sp2[2];

  for (size_t i = 0; i < 3; i++) {
    // Left-edge
    sp1[0] = p1[0]; sp1[1] = p1[1];
    sp2[0] = p1[0]; sp2[1] = p2[1];
    if(Geom::LineLineIntersection(v[i],v[i+1],sp1,sp2)) return true;
    // Upper-edge
    sp1[0] = p1[0]; sp1[1] = p2[1];
    sp2[0] = p2[0]; sp2[1] = p2[1];
    if(Geom::LineLineIntersection(v[i],v[i+1],sp1,sp2)) return true;
    // Right-edge
    sp1[0] = p2[0]; sp1[1] = p2[1];
    sp2[0] = p2[0]; sp2[1] = p1[1];
    if(Geom::LineLineIntersection(v[i],v[i+1],sp1,sp2)) return true;
    // Lower-edge
    sp1[0] = p1[0]; sp1[1] = p1[1];
    sp2[0] = p2[0]; sp2[1] = p1[1];
    if(Geom::LineLineIntersection(v[i],v[i+1],sp1,sp2)) return true;
  }

  return false;
}

bool Geom::PointInsideTriangle(double *p, double *p0, double *p1, double *p2)
{
  // barycentric method http://www.blackpawn.com/texts/pointinpoly/
  double v0[2], v1[2], v2[2];

  for (size_t i = 0; i < 2; i++) {
    v0[i] = p1[i]-p0[i];
    v1[i] = p2[i]-p0[i];
    v2[i] = p[i]-p0[i];
  }

  double dot00=0, dot01=0, dot02=0, dot11=0, dot12=0;

  for (size_t i = 0; i < 2; i++) {
    dot00 += v0[i]*v0[i];
    dot01 += v0[i]*v1[i];
    dot02 += v0[i]*v2[i];
    dot11 += v1[i]*v1[i];
    dot12 += v1[i]*v2[i];
  }

  double invDenom = 1.0 / (dot00 * dot11 - dot01 * dot01);
  double u = (dot11 * dot02 - dot01 * dot12) * invDenom;
  double v = (dot00 * dot12 - dot01 * dot02) * invDenom;

  return (u > 0) && (v > 0) && (u + v <= 1);
}

bool Geom::PointInsideSquare(double *p, double *p0, double *p1)
{
  if(p[0]<=p0[0] || p[0]>p1[0] || p[1] <= p0[1] || p[1]>p1[1]) return false;
  return true;
}

bool Geom::LineLineIntersection(double *a1, double *a2, double *b1, double *b2)
{
  float s1_x, s1_y, s2_x, s2_y;
  s1_x = a2[0] - a1[0];     s1_y = a2[1] - a1[1];
  s2_x = b2[0] - b1[0];     s2_y = b2[1] - b1[1];

  float determinant = s1_x*s2_y-s1_y*s2_x;
  if(determinant<0.0000001) return false; // lines are parallel

  float s, t;
  s = (-s1_y * (a1[0] - b1[0]) + s1_x * (a1[1] - b1[1])) / (-s2_x * s1_y + s1_x * s2_y);
  t = ( s2_x * (a1[1] - b1[1]) - s2_y * (a1[0] - b1[0])) / (-s2_x * s1_y + s1_x * s2_y);

  if (s >= 0 && s <= 1 && t >= 0 && t <= 1) return true;

  return false; // No intersection
}
