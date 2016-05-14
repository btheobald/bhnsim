#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "node.h"

void addRandomBodies(node* p_root, int p_bodies);

int main() {
  // Initialise tree variables
  node* treeRoot;
  bounds* initial = malloc(sizeof(bounds));

  // Setup initial bounds
  initial->centerX = 0;
  initial->centerY = 0;
  initial->halfDistance = 1000;

  // Create tree root
  treeRoot = createNode(initial);

  // Add Random initial bodies
  addRandomBodies(treeRoot, 20);

  updateNodeMP(treeRoot);

  printf("Root node mass = %f.\n", treeRoot->nodeBody->m);
  printf("Root node position = %f, %f.\n", treeRoot->nodeBody->xP, treeRoot->nodeBody->yP);

  // Print tree
  printTree(treeRoot, 0);

  // Free tree memory
  delTree(treeRoot);
}

void addRandomBodies(node* p_root, int p_bodies) {
  srand(time(NULL));

  float max = 2000.0;
  float rX, rY;

  for(int n = 0; n < p_bodies; n++) {
    rX = (((float)rand()/(float)(RAND_MAX)) * max) - 10;
    rY = (((float)rand()/(float)(RAND_MAX)) * max) - 10;
    addBody(createBody(1, rX, rY, 0, 0), p_root);
  }
}
