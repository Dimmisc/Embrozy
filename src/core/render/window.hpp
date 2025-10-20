#ifndef _WINDOW_HPP_
#define _WINDOW_HPP_

#include <GLFW/glfw3.h>
#include "camera.hpp"
#include <string>
#include <iostream>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

GLFWwindow *Init_Window(std::string Title, Camera *CAMERA);

#endif //_WINDOW_HPP_