#ifndef _RENDER_HPP_
#define _RENDER_HPP_

#include "window.hpp"
#include "camera.hpp"

// uncomit to turn on Vullcan using 
// #define RENDER_STRUCTURE_VULLKAN_USE


int Init_Render();

int _PrepareRender();

int UpdateScreen();

int _ClearRender();

#endif //_RENDER_HPP_