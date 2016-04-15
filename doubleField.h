#ifndef DOUBLE_FIELD_H
#define DOUBLE_FIELD_H

#include <string>

class DoubleField {
  public:
    DoubleField(std::string name, long n, int dim);
    ~DoubleField();

    std::string name;
    long n;
    int dim;
    double *data;
};

#endif
