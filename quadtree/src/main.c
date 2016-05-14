#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "node.h"
#include "render.h"

void addStructure(node* treeRoot, int p_soBodies, float p_xP, float p_yP, float p_coS, float p_sR);
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
  initial->halfDistance = 4000;

  // Create tree root
  treeRoot = createNode(initial);

  // Add Random initial bodies
  //addRandomBodies(treeRoot, 1000);
  //addStructure(treeRoot, 500, 0, 0, 20, 2000);
  //addStructure(treeRoot, 250, 2500, 3000, 20, 1000);

  updateNodeMP(treeRoot);

  //printf("Root node mass = %f.\n", treeRoot->nodeBody->m);
  //printf("Root node position = %f, %f.\n", treeRoot->nodeBody->xP, treeRoot->nodeBody->yP);

  // Print tree
  //printTree(treeRoot, 0);

  while(!glfwWindowShouldClose(window)) {
  int i = 0;
  //while(i < 1000) {
    glClear(GL_COLOR_BUFFER_BIT);

    addRandomBodies(treeRoot, 1);

    drawTree(treeRoot);

    glfwSwapBuffers(window);
    glfwPollEvents();

    i++;
  }

  // Free tree memory
  delTree(treeRoot);

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}

void addRandomBodies(node* p_root, int p_bodies) {
  srand(time(NULL));

  float max = 8000.0;
  float rX, rY;

  for(int n = 0; n < p_bodies; n++) {
    rX = (((float)rand()/(float)(RAND_MAX)) * max) - 4000;
    rY = (((float)rand()/(float)(RAND_MAX)) * max) - 4000;
    addBody(createBody(1, rX, rY, 0, 0), p_root);
  }
}

void addStructure(node* treeRoot, int p_soBodies, float p_xP, float p_yP, float p_coS, float p_sR) {
  // Create a Pseudo-random circular distribution of bodies around a central body.
  float max = p_sR * 2;

  // Temporary Variables
  double tempRand, tempCirX, tempCirY;
  // Add Central Body
  addBody(createBody(1, p_xP, p_yP, 0, 0), treeRoot);

  for(int bIDC = 0; bIDC < p_soBodies; bIDC++) {
    // Ensure that bodies are not too close to center.
    do {
      tempRand = (((float)rand()/(float)(RAND_MAX)) * max) - p_sR;
    } while((tempRand < p_coS) & (tempRand > -p_coS));
    // Map to Circle
    tempCirX = p_xP+(tempRand * cos(2 * 3.14 * tempRand));
    tempCirY = p_yP+(tempRand * sin(2 * 3.14 * tempRand));

    addBody(createBody(1, tempCirX, tempCirY, 0, 0), treeRoot);
  }
}

void initDisplay(int lXRes, int lYRes) {
  // Init Projection
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-lXRes*4, lXRes*4, -lYRes*4, lYRes*4, 1.0f, -1.0f);

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
  GLFWwindow* window = glfwCreateWindow(1000, 1000, "QuadTree Example", NULL, NULL);

  // Check that window opened
  if(!window) {
    // Terminate if not
    fprintf(stderr, "GLFW could not create window.\n");
    glfwTerminate();
    exit(1);
  }

  glfwMakeContextCurrent(window);
  initDisplay(1000, 1000);
  //setCallbacks();

  return window;
}
