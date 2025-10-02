#ifndef _CORE_HPP_
#define _CORE_HPP_

#include <filesystem>
#include "area/area.hpp"
#include "render/render.hpp"
#include <DS>


struct CoreParams {
    uint16_t target_fps{(uint16_t)60};
};

class Core {
    Area *area;
    GLFWwindow *window;
    CoreParams params;

    public:
    Core() {}
    ~Core() {}
};

int MainLoop(int target_fps, Area *AREA);

#endif