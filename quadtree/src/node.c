#include "node.h"

// Allocates memory and initialises node data structure.
node* createNode(bounds* p_odeBounds) {
  // Allocate memory for nodes
  node* tempNode = malloc(sizeof(node));
  tempNode->nodeBounds = p_nodeBounds;

  // Null data and node pointers
  body* nodeBody = NULL;
  for(int i = 0; i < 4; i++) {
    branches[i] = NULL;
  }

  // Return node pointer
  return tempNode;
}

// Check and return valid quadrant for body insertion.
int checkBounds(body* p_body, bounds* p_bounds) {
  if(body->xP <= p_bounds->centerX & body->yP > p_bounds->centerY)
    return 0;
  if(body->xP > p_bounds->centerX & body->yP > p_bounds->centerY)
    return 1;
  if(body->xP <= p_bounds->centerX & body->yP <= p_bounds->centerY)
    return 2;
  if(body->xP > p_bounds->centerX & body->yP <= p_bounds->centerY)
    return 3;
}

bounds* newBounds(int quadrant, bounds* p_currentBounds) {
  // Allocate memory for bounds storage
  bounds* tempBounds = malloc(sizeof(bounds));

  // Set new half distance
  tempBounds->halfDistance = p_currentBounds/2;

  // Set new center point
  if(quadrant = 0) {
    tempBounds->centerX = p_currentBounds->centerX-p_currentBounds->halfDistance;
    tempBounds->centerY = p_currentBounds->centerY+p_currentBounds->halfDistance;
  }
  if(quadrant = 1) {
    tempBounds->centerX = p_currentBounds->centerX+p_currentBounds->halfDistance;
    tempBounds->centerY = p_currentBounds->centerY+p_currentBounds->halfDistance;
  }
  if(quadrant = 2) {
    tempBounds->centerX = p_currentBounds->centerX-p_currentBounds->halfDistance;
    tempBounds->centerY = p_currentBounds->centerY-p_currentBounds->halfDistance;
  }
  if(quadrant = 3) {
    tempBounds->centerX = p_currentBounds->centerX+p_currentBounds->halfDistance;
    tempBounds->centerY = p_currentBounds->centerY-p_currentBounds->halfDistance;
  }

  // Return new calculated bounds
  return tempBounds;
}

// Inset a body into the tree.
int addBody(body* p_body, node* currentNode) {
  if(!nodeBody) { // Check if node has branches.
    currentNode->nodeBody = p_body;
  } else if(currentNode->nodeBody == -1) { // Check required branch.
    requiredBranch = checkBounds(p_body, currentNode->nodeBounds)];
    if(!currentNode->branches[requiredBranch]) {
      // If empty insert body
      currentNode->nodeBody = p_body;
    } else {
      // If node does not exist
      bounds* tempBounds = newBounds(requiredBranch, currentNode->nodeBounds);
      currentNode->branches[requiredBranch] = createNode(tempBounds);
    }
  }
}
