#ifndef _RENDER_HPP_
#define _RENDER_HPP_


#include <glad/glad.h>
// #include "../window/window.hpp"


#include "camera.hpp"
#include "../area/area.hpp"
#include "renderer_obj.hpp"



// uncomit to turn on Vullcan using 
// #define RENDER_STRUCTURE_VULLKAN_USE

struct RP {
    bool VULCAN_USING{false};
    bool DEPTH_TEST{true};
    WP *window_params;
};

class Renderer {
private:
    RP params;

    Camera main_camera;
public:
    Renderer();

    void renderObj(void *pointer);

    void renderArrayObj( **pointer, int count);
};

void RparE(){
    printf("RP:%llu, R:%llu", sizeof(RP), sizeof(Renderer));
}

int Init_Render(int width, int height);

int UpdateScreen();

int _ClearRender();

#endif //_RENDER_HPP_