#ifndef __ENGINE_HPP__
#define __ENGINE_HPP__

#include "area/area.hpp"
#include "renderer/renderer.hpp"
#include "physics/physics_engine.hpp"
#include "sound/sound_engine.hpp"

struct EP {
    std::string default_area_name{"DefaultArea"};
    bool local_world{false};
};

class Engine {
private:
    EP params;
    Area *area;
    Renderer *renderer;
    PhysicsEngine *physics_engine;
    SoundEngine *sound_engine;

public:
    inline Engine(EP params = EP()) :
        params(params),
        area(nullptr),
        renderer(nullptr),
        physics_engine(nullptr),
        sound_engine(nullptr) {
            area = new Area(this->params.default_area_name, this->params.local_world);
            renderer = new Renderer();
            physics_engine = new PhysicsEngine();
            sound_engine = new SoundEngine();
    }

    inline void update(float delta_time) {
        // Update area (e.g., physics/simulation step, render, etc.)
        if(area) area->render();
        // Update other subsystems (if they have update logic)
        // For now: stub (implement more if needed)
    }
    
    inline ~Engine() {
        if(area) delete area;
        if(renderer) delete renderer;
        if(physics_engine) delete physics_engine;
        if(sound_engine) delete sound_engine;
    }
};

#endif