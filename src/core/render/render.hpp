#ifndef _RENDER_HPP_
#define _RENDER_HPP_


#include <glad/glad.h>
#include "window.hpp"


#include "camera.hpp"
#include "../area/area.hpp"



// uncomit to turn on Vullcan using 
// #define RENDER_STRUCTURE_VULLKAN_USE

int Init_Render(int width, int height);

int UpdateScreen();

int _ClearRender();

#endif //_RENDER_HPP_