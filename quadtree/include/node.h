#include "body.h"

typedef struct {
  // Bounds
  float centerX, centerY;
  float halfDistance;
} bounds;

typedef struct node {
  // Next Level
  struct node* branches[4];

  // Bounds
  bounds* nodeBounds;

  // Body Data
  body* nodeBody;
} node;

// Allocates memory and initialises node data structure.
node* createNode(bounds* p_nodeBounds);

// Return the required branch/quadrant for current bounds.
int checkBounds(body* p_body, bounds* p_bounds);

// Create new bounds for quadrant based on current bounds.
bounds* newBounds(int quadrant, bounds* p_currentBounds);

// Recursively update the mass and position of node.
void updateNodeMP(node* p_currentNode);

// Check and return valid quadrant for body insertion.
int checkBounds(body* p_body, bounds* p_bounds);

// Check if created branch was the first
int firstNewBranch(node* p_currentNode);

// Inset a body into the tree.
void addBody(body* p_body, node* p_currentNode);

// Delete tree recursively
void delTree(node* rootNode);

void printTree(node* rootNode, int level); 
