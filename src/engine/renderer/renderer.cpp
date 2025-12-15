#include "renderer.hpp"
#include "../area/area.hpp"
#include <iostream>
#include "window.hpp"
#include <DS>


int Init_Render(int width, int height) {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cout << "Failed to initialize GLAD" << std::endl;
    }

    // GLuint fbo;
    // glGenFramebuffers(1, &fbo);
    // glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    // GLuint rboDepthStencil;
    // glGenRenderbuffers(1, &rboDepthStencil);
    // glBindRenderbuffer(GL_RENDERBUFFER, rboDepthStencil);
    // glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH32F_STENCIL8, width, height);
    // glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rboDepthStencil);
    // if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
    //     std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    // }
    // GLint depthBits;
    // glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, 
    //                                  GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE, &depthBits);
    // printf("Depth bits: %d\n", depthBits);
    glEnable(GL_DEPTH_TEST);
    // glBindFramebuffer(GL_FRAMEBUFFER, 0);

    
    return SUCCESS;
}




int UpdateScreen() {
    return SUCCESS;
}

int _ClearRender() {
    return SUCCESS;
}