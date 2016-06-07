#include "stlShape.h"
#include "../quarternionRotation.h"

#include <string>
#include <iostream>
#include <fstream>
#include <math.h>

StlShape::StlShape(int state, std::string fname, double *translation, double scale, double *rot_axis, double rot_angle) : Shape(state)
{
  bool translate=false;
  if(translation!=NULL) translate=true;

  bool rescale=false;
  if(scale!=1.0) rescale=true;

  bool rotation=false;
  if(rot_axis!=NULL) rotation=true;

  this->translation = new double[3];
  if(translate){
    this->translation[0] = translation[0];
    this->translation[1] = translation[1];
    this->translation[2] = translation[2];
  }

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

  double center[3];
  center[0] = 0.0; center[1] = 0.0; center[2] = 0.0;

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
    normal = new double[numFacets*3];
    v1 = new double[numFacets*3];
    v2 = new double[numFacets*3];
    v3 = new double[numFacets*3];

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
  this->c = new double[3];
  for (size_t i = 0; i < 3; i++) {
    center[i] = center[i]/(numFacets*3);
    this->c[i] = center[i];
  }

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

  delete [] p1;
  delete [] p2;
  delete [] quart;
}

StlShape::~StlShape(){
  delete [] c;
  delete [] translation;
  delete [] normal;
  delete [] v1;
  delete [] v2;
  delete [] v3;
}

bool StlShape::IsInside(double *pt)
{
  bool isInside = false;

  int numIntersections = 0;
  for (size_t i = 0; i < numFacets; i++) {
    bool intersects = FacetIntersection(pt,&v1[i*3],&v2[i*3],&v3[i*3],&normal[i*3]);
    if(intersects) numIntersections++;
  }

  if(numIntersections%2 == 1) isInside = true;

  return isInside;
}

bool StlShape::FacetIntersection(double *p, double *p0, double *p1, double *p2, double *n)
{
  // First check if infinite ray intersects facet
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

  bool inside = (u >= 0) && (v >= 0) && (u + v < 1);

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
