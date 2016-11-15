#ifndef COMPOSITE_SHAPE_H
#define COMPOSITE_SHAPE_H
#include <vector>

#include "../shape.h"

class CompositeShape: public Shape {
  public:
    /**
     * CompositeShape constructor
     * @param shapes List of shapes, a point must be inside all shapes in this list for it to be inside this composite shape
     * @param state State to be applied to particles within this shape. state = 0 will remove particle from output. This state overides the state of component shapes
     * @param invert Inverts the shape to tag particles outside the shape instead of inside
     */
    CompositeShape(int state, std::vector<Shape*> shapes, bool invert=false);
    ~CompositeShape();

    /**
     * Check if given coordinate is inside this shape
     * @param  pt Coordinates to check
     * @return    True if coordinate is inside shape, false otherwise
     */
    bool IsInside(double *pt);

  private:
    std::vector<Shape*> shapes;
};

#endif
