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

void updateNodeMV(node* currentNode) {
  float nodeMass = 0;
  float nodePosX = 0,
  float nodePosY = 0;

  // Check for branches
  for(int q = 0; q < 4; q++) {
    if(currentNode->branches[q]) {
      // Recurse down into branch
      updateNodeMV(currentNode->branches[q]);

      // Create tempoary quick body pointer.
      body* qbp = currentNode->branches[q]->nodeBody;

      // Sum total mass of branches
      nodeMass += qbp->m;

      // Sum weighted mean position
      nodePosX += qbp->xP * qbp->m;
      nodePosY += qbp->yP * qbp->m;
    }

    // Get final weigted mean
    nodePosX /= nodeMass;
    nodePosY /= nodeMass;

    // Update current node (Branched nodes only, leaves are not modified)
    currentNode->nodeBody->m = nodeMass;
    currentNode->nodeBody->xP = nodePosX;
    currentNode->nodeBody->yP = nodePosY;
  }
}

// Inset a body into the tree.
int addBody(body* p_body, node* currentNode) {
  if(!currentNode->nodeBody) { // Check if node is populated
    currentNode->nodeBody = p_body;
  }
  // Check if node is populated
    // If empty populate
  // If populated
    // Get required quadrant
    // Check if required quadrant already exists
      // If exists recursively add into quadrant
    // If quadrant does not exist create, calculate bounds
      // Recursively add into quadrant
      // If first new quadrant for node
        // Recursively add node body
        // Update total mass and mean position for node
}
