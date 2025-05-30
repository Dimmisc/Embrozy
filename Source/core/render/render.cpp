#include "render.hpp"
#include "window.hpp"
#include "../../../glad/include/glad/glad.h"

#include <GLFW/glfw3.h>
#include <iostream>


#ifdef RENDER_STRUCTURE_VULLKAN_USE

#else
int _RenderInit() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGwwqqL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
}




#endif