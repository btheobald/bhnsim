#ifndef RENDER_H_GUARD
#define RENDER_H_GUARD

#include <GLFW/glfw3.h>
#include "node.h"

typedef struct squarePoints {
  float points[2][4]; // X/Y, 0..3
} squarePoints;

void renderTree(node* treeRoot);
squarePoints getPoints(bounds* p_nodeBounds);

#endif /* end of include guard: RENDER_H_GUARD */
