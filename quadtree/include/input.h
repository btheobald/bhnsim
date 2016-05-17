#ifndef INPUT_H_GUARD
#define INPUT_H_GUARD

#include <GL/glu.h>
#include <GLFW/glfw3.h>

#include "node.h"

void getCoord(GLFWwindow *window, double *aX, double *aY);
void keyEventCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
void cursorPosCallback(GLFWwindow *window, double xpos, double ypos);
void windowResizeCallback(GLFWwindow *window, int width, int height);

void setCallbacks(GLFWwindow *window);

#endif /* end of include guard: INPUT_H_GUARD */
