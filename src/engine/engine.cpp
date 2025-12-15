#include "engine.hpp"

#include <stdio.h>

Engine::Engine(EP params) : params(params) {
    this->area = new Area(params.default_area_name, params.local_world);
    this->renderer = new Renderer();
    this->physics_engine = new PhysicsEngine();
    this->sound_engine = new SoundEngine();
}

void Engine::update(float delta_time) {

}

Engine::~Engine() {
    if (this->area) {
        delete this->area;
    }
    if (this->renderer) {
        delete this->renderer;
    }
    if (this->physics_engine) {
        delete this->physics_engine;
    }
    if (this->sound_engine) {
        delete this->sound_engine;
    }
}

