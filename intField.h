#ifndef INT_FIELD_H
#define INT_FIELD_H

#include <string>

class IntField {
  public:
    IntField(std::string name, long n, int dim);
    ~IntField();

    std::string name;
    long n;
    int dim;
    int *data;
};

#endif
