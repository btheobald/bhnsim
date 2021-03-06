#include "input.h"
#include "node.h"
#include "render.h"
#include <GLFW/glfw3.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const float squareSize = 4000;
const int displayRes = 700;

void addStructure(node *treeRoot, int p_soBodies, float p_xP, float p_yP, float p_coS, float p_sR);
void initDisplay(int lXRes, int lYRes);
GLFWwindow *setupWindow(void);

int main() {
  srand(time(NULL));

  // Setup window and give pointer
  GLFWwindow *window = setupWindow();

  // Initialise tree variables
  node *treeRoot;
  bounds *initial = malloc(sizeof(bounds));

  // Setup initial bounds
  initial->centerX = 0;
  initial->centerY = 0;
  initial->halfDistance = squareSize / 2;

  // Create tree root
  treeRoot = createNode(initial);
  glfwSetWindowUserPointer(window, treeRoot);

  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);

    drawTree(treeRoot, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // Free tree memory
  delTree(treeRoot);

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}

void addStructure(node *treeRoot, int p_soBodies, float p_xP, float p_yP,
                  float p_coS, float p_sR) {
  // Create a Pseudo-random circular distribution of bodies around a central
  // body.
  float max = p_sR * 2;

  // Temporary Variables
  double tempRand, tempCirX, tempCirY;
  // Add Central Body
  addBody(createBody(1, p_xP, p_yP, 0, 0), treeRoot);

  for (int bIDC = 0; bIDC < p_soBodies; bIDC++) {
    // Ensure that bodies are not too close to center.
    do {
      tempRand = (((float)rand() / (float)(RAND_MAX)) * max) - p_sR;
    } while ((tempRand < p_coS) & (tempRand > -p_coS));
    // Map to Circle
    tempCirX = p_xP + (tempRand * cos(2 * 3.14592 * tempRand));
    tempCirY = p_yP + (tempRand * sin(2 * 3.14592 * tempRand));

    addBody(createBody(1, tempCirX, tempCirY, 0, 0), treeRoot);
  }
}

void initDisplay(int lXRes, int lYRes) {
  // Init Projection
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-lXRes * 3, lXRes * 3, -lYRes * 3, lYRes * 3, 1.0f, -1.0f);

  // Init Modelview
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // Set Viewport Extents
  glViewport(0, 0, lXRes, lYRes);
  glClearColor(0.0f, 0.0f, 0.0f, 1);
}

GLFWwindow *setupWindow(void) {
  // Try init GLFW
  if (!glfwInit()) {
    fprintf(stderr, "GLFW could not init.\n");
    exit(1);
  }

  // Create window
  GLFWwindow *window =
      glfwCreateWindow(displayRes, displayRes, "QuadTree Example", NULL, NULL);

  // Check that window opened
  if (!window) {
    // Terminate if not
    fprintf(stderr, "GLFW could not create window.\n");
    glfwTerminate();
    exit(1);
  }

  glfwMakeContextCurrent(window);
  initDisplay(displayRes, displayRes);
  glfwSwapInterval(1);
  setCallbacks(window);

  return window;
}
