#include "input.h"

void getCoord(GLFWwindow* window, double* aX, double* aY) {
  double mX, mY; // Window system mouse
  glfwGetCursorPos(window, &mX, &mY);

  // Initialise local display matrix storage
  GLint viewport[4];
  GLdouble modelview[16];
  GLdouble projection[16];
  // Get current display matricies
  glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
  glGetDoublev(GL_PROJECTION_MATRIX, projection);
  glGetIntegerv(GL_VIEWPORT, viewport);

  // Flip window y
  mY = viewport[3] - mY;

  // Z is not important here, variable is required
  GLdouble ignoreZ;

  // Project mouse to world
  gluUnProject(mX, mY, 0, modelview, projection, viewport, aX, aY, &ignoreZ);
}

void cursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
  int action = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
  if(action == GLFW_PRESS) {
    getCoord(window, &xpos, &ypos);
    if(((xpos > -2000) & (xpos < 2000)) & ((ypos > -2000) & (ypos < 2000))) {
      addBody(createBody(1, xpos, ypos, 0, 0), cbTreeAccess);
    }
  }
}

void windowResizeCallback(GLFWwindow* window, int width, int height) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-width*3, width*3, -height*3, height*3, 1.0f, -1.0f);

  glViewport(0, 0, width, height);

  glPushMatrix();
}

void setCallbacks(GLFWwindow* window) {
  glfwSetCursorPosCallback(window, cursorPosCallback);
  glfwSetWindowSizeCallback(window, windowResizeCallback);
}
