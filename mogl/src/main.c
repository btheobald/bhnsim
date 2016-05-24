#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>

GLFWwindow *setupWindow(void);
void initDisplay(int lXRes, int lYRes);

int main() {
  // Setup window and give pointer
  GLFWwindow *window = setupWindow();

  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}

GLFWwindow *setupWindow(void) {
  // Try init GLFW
  if (!glfwInit()) {
    fprintf(stderr, "GLFW could not init.\n");
    exit(1);
  }

  // Configure Context
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  // Create window
  GLFWwindow* window = glfwCreateWindow(800, 600, "Modern OpenGL Example", NULL, NULL);

  // Check that window opened
  if (!window) {
    // Terminate if not
    fprintf(stderr, "GLFW could not create window.\n");
    glfwTerminate();
    exit(1);
  }

  glfwMakeContextCurrent(window);

  glewExperimental = GL_TRUE;
  glewInit();

  GLuint vertexBuffer;
  glGenBuffers(1, &vertexBuffer);

  printf("%u\n", vertexBuffer);

  glfwSwapInterval(1);

  return window;
}
