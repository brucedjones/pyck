#ifndef QUARTERNION_ROTATION_H
#define QUARTERNION_ROTATION_H

inline void hamilton_product(double *result,double a1, double b1, double c1, double d1, double a2, double b2, double c2, double d2)
{
  result[0] = a1*a2-b1*b2-c1*c2-d1*d2;
  result[1] = a1*b2+b1*a2+c1*d2-d1*c2;
  result[2] = a1*c2-b1*d2+c1*a2+d1*b2;
  result[3] = a1*d2+b1*c2-c1*b2+d1*a2;
}

inline void rotate(double *pt, double *quart)
{
  double step1[4],step2[4];
  hamilton_product(step1,quart[0],quart[1],quart[2],quart[3],0,pt[0],pt[1],pt[2]);
  hamilton_product(step2,step1[0],step1[1],step1[2],step1[3],quart[0],-quart[1],-quart[2],-quart[3]);
  pt[0] = step2[1];
  pt[1] = step2[2];
  pt[2] = step2[3];
}

#endif
