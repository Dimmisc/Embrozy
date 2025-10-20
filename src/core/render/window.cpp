#include "window.hpp"
#include "camera.hpp"

#include <GLFW/glfw3.h>
#include <cstdint>
float deltaTime = 20.0f;


void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

void processWindowInput(GLFWwindow *window) {
    Camera* camera = static_cast<Camera*>(glfwGetWindowUserPointer(window));

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera->ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera->ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera->ProcessKeyboard(RIGHT, deltaTime);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    Camera* camera = static_cast<Camera*>(glfwGetWindowUserPointer(window));

    camera->ProcessMouseScroll(static_cast<float>(yoffset));
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{   
    Camera* camera = static_cast<Camera*>(glfwGetWindowUserPointer(window));
    
    static struct MouseState {
        double lastX = 0.0;
        double lastY = 0.0;
        bool firstMouse = true;
    } mouseState;
    
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (mouseState.firstMouse)
    {
        mouseState.lastX = xpos;
        mouseState.lastY = ypos;
        mouseState.firstMouse = false;
        return; 
    }

    float xoffset = xpos - mouseState.lastX;
    float yoffset = mouseState.lastY - ypos; 

    mouseState.lastX = xpos;
    mouseState.lastY = ypos;
    
    // If you uncommit it will be very luggy!!!!!
    // printf("Mouse: offset_x:%.2f, offset_y:%.2f | pos_x:%.1f, pos_y:%.1f\n", 
    //        xoffset, yoffset, xpos, ypos);
    
    camera->ProcessMouseMovement(xoffset, yoffset);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    Camera* camera = static_cast<Camera*>(glfwGetWindowUserPointer(window));
    glViewport(0, 0, width, height);
    camera->ProcessScreen(height, width);
    
}  

GLFWwindow *Init_Window(std::string Name, Camera * P){
        
    if(!glfwInit()){
        std::cout << "Failed to initialize GLFW" << std::endl;
        return nullptr;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_DEPTH_BITS, 32);
    GLFWwindow * window = glfwCreateWindow(2560, 1600, Name.data(), NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return NULL;
    }
    if (P == nullptr) {
        perror("nullptr given in Window\n");
    }

    glfwSetWindowUserPointer(window, P);

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

    return window;
}