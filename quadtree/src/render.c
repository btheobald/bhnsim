#include "render.h"

void drawPoints(bounds* p_nodeBounds) {
  glBegin(GL_LINE_LOOP);
    glVertex2f(p_nodeBounds->centerX + p_nodeBounds->halfDistance, p_nodeBounds->centerY - p_nodeBounds->halfDistance);
    glVertex2f(p_nodeBounds->centerX - p_nodeBounds->halfDistance, p_nodeBounds->centerY - p_nodeBounds->halfDistance);
    glVertex2f(p_nodeBounds->centerX - p_nodeBounds->halfDistance, p_nodeBounds->centerY + p_nodeBounds->halfDistance);
    glVertex2f(p_nodeBounds->centerX + p_nodeBounds->halfDistance, p_nodeBounds->centerY + p_nodeBounds->halfDistance);
  glEnd();
}

void drawTree(node* treeRoot) {
  glBegin(GL_POINTS);
    glVertex2d(treeRoot->nodeBody->xP, treeRoot->nodeBody->yP);
    //glVertex2d(treeRoot->nodeBody->yP, treeRoot->nodeBody->xP);
  glEnd();

  drawPoints(treeRoot->nodeBounds);
  for(int i = 0; i < 4; i++) {
    if(treeRoot->branches[i]) {
      drawTree(treeRoot->branches[i]);
    }
  }
}
