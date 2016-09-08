#include "shape.h"

Shape::Shape(int state, bool invert)
{
  this->state = state;
  this->parallel = true;
  this->inverted = invert;
}

Shape::~Shape(){}
