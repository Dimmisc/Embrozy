#ifndef _AREA_HPP_
#define _AREA_HPP_

#include "player/player.hpp"
#include "cell.hpp"


#include <string>
#include <cstdint>
#include "pcg/world-gen.hpp"
#include <glm/glm.hpp>


class Area {
    
public:
    std::string name;
    uint64_t seed;
    
    bool local_world;

    Camera PlayerCamera;
    CellSystem *terrain{nullptr};

    Area(std::string name, bool LOCALWORLD) : 
    name(name), local_world(LOCALWORLD), PlayerCamera(glm::dvec3(0.0f)) {
        // printf("CameraCreated: height: %d, width: %d", PlayerCamera.SCREEN_WIDTH, PlayerCamera.SCREEN_HEIGHT);
    }

    void CreateTerrain(int depth, int radius, glm::dvec3 Position){
        terrain = new CellSystem(radius - 1, depth - 1, Position, Init_PCG(124851));
    }

    int render() {
        return this->terrain->render(&PlayerCamera);
    }

    int upload(std::string name);

    int save();

    int EXIT();

};

#endif 