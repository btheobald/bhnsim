#include "render.h"

void drawPoints(bounds* p_nodeBounds) {
  glBegin(GL_LINE_LOOP);
    //glVertex2f(p_nodeBounds->centerX - p_nodeBounds->halfDistance*2, p_nodeBounds->centerY + p_nodeBounds->halfDistance*2);
    //glVertex2f(p_nodeBounds->centerX + p_nodeBounds->halfDistance*2, p_nodeBounds->centerY + p_nodeBounds->halfDistance*2);
    //glVertex2f(p_nodeBounds->centerX + p_nodeBounds->halfDistance*2, p_nodeBounds->centerY - p_nodeBounds->halfDistance*2);
    //glVertex2f(p_nodeBounds->centerX - p_nodeBounds->halfDistance*2, p_nodeBounds->centerY - p_nodeBounds->halfDistance*2);
    glVertex2f(p_nodeBounds->centerX - p_nodeBounds->halfDistance, p_nodeBounds->centerY + p_nodeBounds->halfDistance);
    glVertex2f(p_nodeBounds->centerX + p_nodeBounds->halfDistance, p_nodeBounds->centerY + p_nodeBounds->halfDistance);
    glVertex2f(p_nodeBounds->centerX + p_nodeBounds->halfDistance, p_nodeBounds->centerY - p_nodeBounds->halfDistance);
    glVertex2f(p_nodeBounds->centerX - p_nodeBounds->halfDistance, p_nodeBounds->centerY - p_nodeBounds->halfDistance);
  glEnd();

  /*
  // Render center point
  glPointSize(5.0f);
  glColor3b(0, 0, 127);
  glBegin(GL_POINTS);
    //glVertex2f(p_nodeBounds->centerX, p_nodeBounds->centerY);
  glEnd();
  glColor3b(127, 127, 127);
  */
}

void drawTree(node* treeRoot) {
  int hasBranches = 0;

  drawPoints(treeRoot->nodeBounds);
  for(int i = 0; i < 4; i++) {
    if(treeRoot->branches[i]) {
      drawTree(treeRoot->branches[i]);
      hasBranches = 1;
    }
  }

  glPointSize(3.0f);

  if(hasBranches == 0)
    glColor3b(127, 0, 0);
  else
    glColor3b(0, 127, 0);

  if(treeRoot->nodeBody) {
    glBegin(GL_POINTS);
      glVertex2d(treeRoot->nodeBody->xP, treeRoot->nodeBody->yP);
    glEnd();
  }

  glColor3b(127, 127, 127);
}
