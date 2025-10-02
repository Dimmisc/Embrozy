#ifndef _RENDER_HPP_
#define _RENDER_HPP_

#include "window.hpp"
#include "camera.hpp"
#include "../area/area.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// uncomit to turn on Vullcan using 
// #define RENDER_STRUCTURE_VULLKAN_USE


int Init_Render();

int UpdateScreen();

int _ClearRender();

#endif //_RENDER_HPP_