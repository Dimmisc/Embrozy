#include "window.hpp"

#include "../../../glad/include/glad/glad.h"

#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdint>


int Window_Init (uint16_t SCREEN_WIDTH, uint16_t SCREEN_HEIGHT) {

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "3D Cube - OpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
}