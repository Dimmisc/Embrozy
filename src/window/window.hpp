#ifndef _WINDOW_HPP_
#define _WINDOW_HPP_

#include <GLFW/glfw3.h>
// #include "camera.hpp"
#include <string>
#include <iostream>

class WP {
    bool cursor_tracking{false};
    int HEIGHT{500}, WIDTH{1000};
    std::string name{"Embrozy"};

};


class Window {
    WP params;
    GLFWwindow *window;

public:
    Window(WP win_params = WP());
    
    void switch_cursor_tracking();

    void set_cursor_tracking(bool Flag);
    
    void SwapBuffers() {
        glfwSwapBuffers(this->window);
        glfwPollEvents();
    }
    
    int WindowShouldClose() {
        return glfwWindowShouldClose(this->window);
    }
};


GLFWwindow *Init_Window(std::string Title, Camera *CAMERA);

#endif //_WINDOW_HPP_