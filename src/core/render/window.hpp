#ifndef _WINDOW_HPP_
#define _WINDOW_HPP_

#include <GLFW/glfw3.h>
#include "camera.hpp"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn, Camera &camera);

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset, Camera &camera);

#endif //_WINDOW_HPP_