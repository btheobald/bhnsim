#include "node.h"

// Allocates memory and initialises node data structure.
node* createNode(bounds* p_nodeBounds) {
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

void updateNodeMP(node* p_currentNode) {
  float nodeMass = 0;
  float nodePosX = 0,
  float nodePosY = 0;

  // Check for branches
  for(int q = 0; q < 4; q++) {
    if(p_currentNode->branches[q]) {
      // Recurse down into branch
      updateNodeMP(p_currentNode->branches[q]);

      // Create tempoary quick body pointer.
      body* qbp = p_currentNode->branches[q]->nodeBody;

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
    p_currentNode->nodeBody->m = nodeMass;
    p_currentNode->nodeBody->xP = nodePosX;
    p_currentNode->nodeBody->yP = nodePosY;
  }
}

int firstNewBranch(node* p_currentNode) {
  // Check if first new quadrant
  int check = 0;
  for(int n = 0; n < 4; n++) {
    if(p_currentNode->branches[n])
      check++;
  }

  if(check == 1) return 1; // If first new quadrant

  return 0; // If not first
}

// Inset a body into the tree.
int addBody(body* p_body, node* p_currentNode) {
  if(!p_currentNode->nodeBody) { // Populate node if empty
    p_currentNode->nodeBody = p_body;
  } else { // If not empty
    int reqBranch = checkBounds(p_body, p_currentNode->nodeBounds);

    if(p_currentNode->branches[reqBranch]) { // Check if required branch exists
      addBody(p_body, p_currentNode->branches[reqBranch]); // Recursively add to branch
    } else { // If branch does not exist
      p_currentNode->branches[reqBranch] = createNode(newBounds(reqBranch, p_currentNode->branches)); // Create new node on branch
      addBody(p_body, p_currentNode->branches[reqBranch]); // Recursively add to branch

      if(firstNewBranch(p_currentNode)) {
        addBody(p_currentNode->nodeBody, p_currentNode);
      }
    }

    // Update total mass and mean position for node
    updateNodeMP(p_currentNode);
  }
}
