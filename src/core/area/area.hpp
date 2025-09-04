#ifndef _AREA_HPP_
#define _AREA_HPP_

#include "player/player.hpp"
#include "cell.hpp"


#include <string>
#include <cstdint>
#include <glm/glm.hpp>

class Area {
    
    std::string name;
    uint64_t seed;

    Player *players;
    Camera MainPlayer;
    CellSystem world;

    Area(std::string name, const bool LOCALWORLD);

    int upload(std::string name);

    int save();

    int EXIT();

};

#endif 