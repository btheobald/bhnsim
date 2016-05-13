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

  glPointSize(5.0f);
  glColor3b(0, 0, 127);
  glBegin(GL_POINTS);
    //glVertex2f(p_nodeBounds->centerX, p_nodeBounds->centerY);
  glEnd();
  glColor3b(127, 127, 127);
}

void drawTree(node* treeRoot) {
  glPointSize(2.0f);
  glColor3b(127, 0, 0);
  glBegin(GL_POINTS);
    glVertex2d(treeRoot->nodeBody->xP, treeRoot->nodeBody->yP);
    //glVertex2d(treeRoot->nodeBody->yP, treeRoot->nodeBody->xP);
  glEnd();


  glColor3b(127, 127, 127);
  drawPoints(treeRoot->nodeBounds);
  for(int i = 0; i < 4; i++) {
    if(treeRoot->branches[i]) {
      drawTree(treeRoot->branches[i]);
    }
  }
}
