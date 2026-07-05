#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>



constexpr int WINDOW_X = 800;
constexpr int WINDOW_Y = 600;


// Resizing window
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

// Processing input
void processInput(GLFWwindow *window)
{
  // Exit on key ESCAPE
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwWindowShouldClose(window);
  }
}


int main(void)
{
  // GLFW Init
  glfwInit();

  // OpenGL 3.3 (Core)
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  // Window creation
  GLFWwindow* window = glfwCreateWindow(WINDOW_X, WINDOW_Y, "Triangle", NULL, NULL);
 if (window == NULL) {
    std::cout << "Failed to create window (GLFW)" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  // Glad init
  if (!gladLoadGL(glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -2;
  }

  // OpenGL init
  glViewport(0, 0, WINDOW_X, WINDOW_Y);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); 
  
  // Mainloop
  while(!glfwWindowShouldClose(window))
  {
    // Reset and process
    processInput(window);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Do other stuff

    // Render and poll
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // Cleanup
  glfwTerminate();
  return 0;
}

