#ifndef _UI_HPP__
#define _UI_HPP__
#include "gui/gui.hpp"

#include <vector>
#include <functional>

struct UIP {

};


class UI {
    using Callback = std::function<void(int, int)>;
private:
    UIP params;
    GUI gui;
    


public: // Event listeners 
    // Event listener 
    void addELMouseMotion(void (*_func)(int x_offset, int y_offset));
    // Event listener
    void addELMouseScroll(void (*_func)(int x_offset, int y_offset));
    // Event listener
    void addELMouseClick(void (*_func)(int Wx, int Wy));
    // Event listener
    void addELKey(void (*_func)(int Wx, int Wy));

        
};  

#endif