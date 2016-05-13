#include <stdio.h>
#include <stdlib.h>
#include "node.h"

int main() {
  // Initialise tree variables
  node* treeRoot;
  bounds* initial = malloc(sizeof(bounds));

  // Setup initial bounds
  initial->centerX = 0;
  initial->centerY = 0;
  initial->halfDistance = 10;

  // Create initial bodies
  body* b0 = createBody(1, 5.0, 1.0, 0, 0);
  body* b1 = createBody(1, -5.0, 1.0, 0, 0);
  body* b2 = createBody(1, -8.0, -8.0, 0, 0);

  // Create tree root
  treeRoot = createNode(initial);

  // Add body to tree
  addBody(b0, treeRoot);
  addBody(b1, treeRoot);
  addBody(b2, treeRoot);

  updateNodeMP(treeRoot);

  printf("Root node mass = %f.\n", treeRoot->nodeBody->m);
  printf("Root node position = %f, %f.\n", treeRoot->nodeBody->xP, treeRoot->nodeBody->yP);

  // Print tree
  printTree(treeRoot, 0);

  // Free tree memory
  delTree(treeRoot);
}
