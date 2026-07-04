cmake_minimum_required(VERSION 3.25)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

project(FirstLinuxOpenGL LANGUAGES C CXX)

add_library(glad
    external/glad/src/gl.c
)

target_include_directories(glad PUBLIC
    external/glad/include
)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(FirstLinuxOpenGL
    src/main.cpp
)

target_link_libraries(FirstLinuxOpenGL
    PRIVATE glad
    PRIVATE glfw
    PRIVATE OpenGL::GL
)

