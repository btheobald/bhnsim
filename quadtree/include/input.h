#ifndef INPUT_H_GUARD
#define INPUT_H_GUARD

#include <GLFW/glfw3.h>
#include <GL/glu.h>

#include "node.h"

node* cbTreeAccess;

void getCoord(GLFWwindow* window, double* aX, double* aY);
void cursorPosCallback(GLFWwindow* window, double xpos, double ypos);
void windowResizeCallback(GLFWwindow* window, int width, int height);

void setCallbacks(GLFWwindow* window);

#endif /* end of include guard: INPUT_H_GUARD */
