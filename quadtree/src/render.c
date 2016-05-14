#include "render.h"
#include <stdlib.h>

const GLbyte colours[10][3] = {
  {0,0,0},
  {100,0,0},
  {0,100,0},
  {0,0,100},
  {100,0,100},
  {100,100,0},
  {0,100,100},
};

void drawPoints(bounds* p_nodeBounds, int level) {
  //glColor3b(colours[level][0], colours[level][1], colours[level][2]);
  //glBegin(GL_QUADS);
  //  glVertex2f(p_nodeBounds->centerX - p_nodeBounds->halfDistance, p_nodeBounds->centerY + p_nodeBounds->halfDistance);
  //  glVertex2f(p_nodeBounds->centerX + p_nodeBounds->halfDistance, p_nodeBounds->centerY + p_nodeBounds->halfDistance);
  //  glVertex2f(p_nodeBounds->centerX + p_nodeBounds->halfDistance, p_nodeBounds->centerY - p_nodeBounds->halfDistance);
  //  glVertex2f(p_nodeBounds->centerX - p_nodeBounds->halfDistance, p_nodeBounds->centerY - p_nodeBounds->halfDistance);
  //glEnd();
  glColor3b(32, 32, 32);
  glBegin(GL_LINE_LOOP);
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

void drawTree(node* treeRoot, int level) {
  int hasBranches = 0;

  drawPoints(treeRoot->nodeBounds, level);
  for(int i = 0; i < 4; i++) {
    if(treeRoot->branches[i]) {
      drawTree(treeRoot->branches[i], level+1);
      hasBranches = 1;
    }
  }

  glPointSize(2.0f);

  if(hasBranches == 0)
    glColor3b(127, 0, 0);
  else
    glColor3b(0, 64, 0);

  if(treeRoot->nodeBody) {
    glBegin(GL_POINTS);
      glVertex2d(treeRoot->nodeBody->xP, treeRoot->nodeBody->yP);
    glEnd();
  }

  glColor3b(127, 127, 127);
}
