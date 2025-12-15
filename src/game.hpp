#ifndef _GAME_HPP_
#define _GAME_HPP_

#include <string>
#include <cstdint>
#include <windows.h>

#include "window/window.hpp"
#include "engine/engine.hpp"
#include "settings_control/settings_controller.hpp"
#include "ui/ui.hpp"

struct GP {
    std::string name{"Embrozy"};
    uint16_t target_fps{60};
    float delta_time{1.0f};
};


class Game {
private:

    GP params;

    std::string error{};
    int CONTINUE_FLAG{0};

    Window *window;
    Engine *engine;
    SettingsController *settings_controller;
    UI *ui;
    
public:

    Game(GP params = GP());
    
    int Start(int fps);

    void stop();

    void pass();

    void Exit();

    ~Game();

private: // workers

    LARGE_INTEGER g_qpc_frequency{0};

    int initialize_timing();

    uint64_t get_monotonic_time_ns();

    void precise_sleep_ns(uint64_t nanoseconds);

};


#endif