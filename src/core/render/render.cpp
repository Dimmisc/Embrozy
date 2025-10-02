#include "render.hpp"
#include "../area/area.hpp"
#include <iostream>
#include "window.hpp"
#include <DS>

#ifdef RENDER_STRUCTURE_VULLKAN_USE
#else
int Init_Render() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return ERROR_INIT_OPENGL;
    }
    if(!glfwInit()){
        std::cout << "Failed to initialize GLFW" << std::endl;
        return ERROR_INIT_GLFW;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    return SUCCESS;
}


int UpdateScreen() {
    return SUCCESS;
}

int _ClearRender() {
    return SUCCESS;
}
#endif