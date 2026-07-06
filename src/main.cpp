#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "get_shader.hpp"



// Window dims
constexpr int WINDOW_X = 800;
constexpr int WINDOW_Y = 600;


// Resizing window
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

// Processing input
void processInput(GLFWwindow *window) {
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
    std::cerr << "ERROR: Failed to create window (GLFW)" << std::endl;
    glfwTerminate();
    return 1;
  }
  glfwMakeContextCurrent(window);

  // Glad init check
  if (!gladLoadGL(glfwGetProcAddress)) {
    std::cerr << "ERROR: Failed to initialize GLAD" << std::endl;
    return 1;
  }

  // OpenGL init
  glViewport(0, 0, WINDOW_X, WINDOW_Y);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  /*
   * Shader loading and initializing
   */

  const std::string vertexShaderString = get_shader("shaders/basic.vert");
  const std::string fragmentShaderString = get_shader("shaders/basic.frag");

  // Shader source char pointers (C string)
  const char *vertexShaderSource = vertexShaderString.data();
  const char *fragmentShaderSource = fragmentShaderString.data();

  // Initializing pointers
  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

  // Assigning pointers to sources
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);

  // Compiling shaders
  glCompileShader(vertexShader);
  glCompileShader(fragmentShader);

  // Vertex shader status
  int vertexSuccess;
  char vertexInfoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexSuccess);
  if(!vertexSuccess) {
    glGetShaderInfoLog(vertexShader, 512, NULL, vertexInfoLog);
    std::cerr << "ERROR: Vertex shader failed to compile\n" 
      << vertexInfoLog << std::endl;
  }

  // Fragement shader status
  int fragementSuccess;
  char fragmentInfoLog[512];
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragementSuccess);
  if(!fragementSuccess) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, fragmentInfoLog);
    std::cerr << "ERROR: Fragment shader failed to compile\n" 
      << fragmentInfoLog << std::endl;
  }

  // Init combined shader program
  unsigned int shaderProgram;
  shaderProgram = glCreateProgram();
  
  // Attach shaders and link
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  // Shader program status
  int shaderProgramSuccess;
  char shaderProgramInfoLog[512];
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &shaderProgramSuccess);
  if(!shaderProgramSuccess) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, shaderProgramInfoLog);
    std::cerr << "ERROR: Full shader program failed to link/compile\n" 
      << shaderProgramInfoLog << std::endl;
  }
  glUseProgram(shaderProgram);

  // Deleting unused shader objects
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

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

