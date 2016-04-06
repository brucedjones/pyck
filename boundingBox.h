#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

class Domain;

class BoundingBox {
  public:
    BoundingBox(float *p1, float *p2, Domain *domain);
    ~BoundingBox();

    long *p1, *p2;
};

#endif
