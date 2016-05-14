#ifndef RENDER_H_GUARD
#define RENDER_H_GUARD

#include <GLFW/glfw3.h>
#include "node.h"

void drawPoints(bounds* p_nodeBounds, int level);
void drawTree(node* treeRoot, int level);

#endif /* end of include guard: RENDER_H_GUARD */
