#include "node.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Allocates memory and initialises node data structure.
node* createNode(bounds* p_nodeBounds) {
  // Allocate memory for nodes
  node* tempNode = malloc(sizeof(node));
  tempNode->nodeBounds = p_nodeBounds;

  // Null data and node pointers
  tempNode->nodeBody = NULL;
  for(int i = 0; i < 4; i++) {
    tempNode->branches[i] = NULL;
  }

  // Return node pointer
  return tempNode;
}

// Check and return valid quadrant for body insertion.
int checkBounds(body* p_body, bounds* p_bounds) {
  if((p_body->xP <= p_bounds->centerX) & (p_body->yP >  p_bounds->centerY))
    return 0;
  if((p_body->xP >  p_bounds->centerX) & (p_body->yP >  p_bounds->centerY))
    return 1;
  if((p_body->xP <= p_bounds->centerX) & (p_body->yP <= p_bounds->centerY))
    return 2;
  if((p_body->xP >  p_bounds->centerX) & (p_body->yP <= p_bounds->centerY))
    return 3;
  return -1;
}

bounds* newBounds(int quadrant, bounds* p_currentBounds) {
  // Allocate memory for bounds storage
  bounds* tempBounds = malloc(sizeof(bounds));

  // Set new half distance
  tempBounds->halfDistance = p_currentBounds->halfDistance/2;

  // Set new center point
  if(quadrant == 0) {
    tempBounds->centerX = p_currentBounds->centerX-p_currentBounds->halfDistance;
    tempBounds->centerY = p_currentBounds->centerY+p_currentBounds->halfDistance;
  }
  if(quadrant == 1) {
    tempBounds->centerX = p_currentBounds->centerX+p_currentBounds->halfDistance;
    tempBounds->centerY = p_currentBounds->centerY+p_currentBounds->halfDistance;
  }
  if(quadrant == 2) {
    tempBounds->centerX = p_currentBounds->centerX-p_currentBounds->halfDistance;
    tempBounds->centerY = p_currentBounds->centerY-p_currentBounds->halfDistance;
  }
  if(quadrant == 3) {
    tempBounds->centerX = p_currentBounds->centerX+p_currentBounds->halfDistance;
    tempBounds->centerY = p_currentBounds->centerY-p_currentBounds->halfDistance;
  }

  // Return new calculated bounds
  return tempBounds;
}

void updateNodeMP(node* p_currentNode) {
  int hasBranches = 0;
  for(int c = 0; c < 4; c++) {
    if(p_currentNode->branches[c]) {
      hasBranches = 1;
    }
  }
  if(hasBranches) {
    p_currentNode->nodeBody->m = 0;
    p_currentNode->nodeBody->xP = 0;
    p_currentNode->nodeBody->yP = 0;
  }

  // Check for branches
  for(int q = 0; q < 4; q++) {
    if(p_currentNode->branches[q]) {
      // Recurse down into branch
      updateNodeMP(p_currentNode->branches[q]);
      if(p_currentNode->branches[q]->nodeBody) {
        sumBody(p_currentNode->nodeBody, p_currentNode->branches[q]->nodeBody);
      }
    }
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
    // Check that bodies are not in same position
    if(((p_currentNode->nodeBody->xP == p_body->xP) & (p_currentNode->nodeBody->yP == p_body->yP)) & !(p_currentNode->nodeBody->m == -1)) {
      // If bodies are in the same position abort.
      return 0;
    }

    int reqBranch = checkBounds(p_body, p_currentNode->nodeBounds);

    if(p_currentNode->branches[reqBranch]) { // Check if required branch exists
      addBody(p_body, p_currentNode->branches[reqBranch]); // Recursively add to branch
    } else { // If branch does not exist
      p_currentNode->branches[reqBranch] = createNode(newBounds(reqBranch, p_currentNode->nodeBounds)); // Create new node on branch
      addBody(p_body, p_currentNode->branches[reqBranch]); // Recursively add to branch

      if(firstNewBranch(p_currentNode)) {
        body* temp = p_currentNode->nodeBody;
        // Create filler body for later average
        p_currentNode->nodeBody = createBody(-1, 0, 0, 0, 0);
        addBody(temp, p_currentNode);
      }
      // Create temp pointer to preset node body
    }

    // Update total mass and mean position for node
    updateNodeMP(p_currentNode);
  }

  return 1;
}

// Delete Entire Tree, Frees all memory for bodies and tree. Starts recursively from root.
void delTree(node* rootNode) {
  for(int i = 0; i < 4; i++) {
    if(rootNode->branches[i]) {
      // Recurse into tree.
      delTree(rootNode->branches[i]);
    }
  }
  // Free node memory
  if(rootNode->nodeBody) {
    free(rootNode->nodeBody);
  }
  free(rootNode->nodeBounds);
  free(rootNode);
}

void insertTabs(int n) {
  for(int l = 0; l < n; l++) {
    printf("  ");
  }
}

void printTree(node* rootNode, int level) {
  insertTabs(level);
  printf("\\-%d\n", level);
  for(int i = 0; i < 4; i++) {
    if(rootNode->branches[i]) {
      insertTabs(level+1);
      printf("|->B%d\n", i);
      printTree(rootNode->branches[i], level+1);
    }
  }
}
