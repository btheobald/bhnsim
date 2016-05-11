#include "body.h"

typedef struct bounds {
  // Bounds
  float centerX, centerY;
  float halfDistance;
} bounds;

typedef struct node {
  // Next Level
  node* branches[4];

  // Bounds
  bounds* nodeBounds;

  // Body Data
  body* nodeBody;
} node;

// Allocates memory and initialises node data structure.
node* createNode(float p_centerX, float p_centerY, float p_halfDistance);

// Check and return valid quadrant for body insertion.
int checkBounds(body* p_body, bounds* p_bounds);

// Inset a body into the tree.
int addBody(body* p_body);
