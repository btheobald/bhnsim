#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "node.h"
#include "render.h"

void addRandomBodies(node* p_root, int p_bodies);
void initDisplay(int lXRes, int lYRes);
GLFWwindow* setupWindow(void);

int main() {
  // Setup window and give pointer
  GLFWwindow* window = setupWindow();

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
  addRandomBodies(treeRoot, 2);

  updateNodeMP(treeRoot);

  printf("Root node mass = %f.\n", treeRoot->nodeBody->m);
  printf("Root node position = %f, %f.\n", treeRoot->nodeBody->xP, treeRoot->nodeBody->yP);

  // Print tree
  //printTree(treeRoot, 0);

  glClear(GL_COLOR_BUFFER_BIT);
  drawTree(treeRoot);
  glfwSwapBuffers(window);

  while(1) { }

  // Free tree memory
  delTree(treeRoot);
}

void addRandomBodies(node* p_root, int p_bodies) {
  srand(time(NULL));

  float max = 2000.0;
  float rX, rY;

  for(int n = 0; n < p_bodies; n++) {
    rX = (((float)rand()/(float)(RAND_MAX)) * max) - 1000;
    rY = (((float)rand()/(float)(RAND_MAX)) * max) - 1000;
    addBody(createBody(1, rX, rY, 0, 0), p_root);
  }
}

void initDisplay(int lXRes, int lYRes) {
  // Init Projection
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-lXRes*5, lXRes*5, -lYRes*5, lYRes*5, 1.0f, -1.0f);

  // Init Modelview
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // Set Viewport Extents
  glViewport(0, 0, lXRes, lYRes);
  glClearColor(0.0f, 0.0f, 0.0f, 1);
}

GLFWwindow* setupWindow(void) {
  // Try init GLFW
  if(!glfwInit()) {
    fprintf(stderr, "GLFW could not init.\n");
    exit(1);
  }

  // Create window
  GLFWwindow* window = glfwCreateWindow(500, 500, "QuadTree Example", NULL, NULL);

  // Check that window opened
  if(!window) {
    // Terminate if not
    fprintf(stderr, "GLFW could not create window.\n");
    glfwTerminate();
    exit(1);
  }

  glfwMakeContextCurrent(window);
  initDisplay(500, 500);
  //setCallbacks();

  return window;
}
