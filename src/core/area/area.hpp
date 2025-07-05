#ifndef _AREA_HPP_
#define _AREA_HPP_

#include <cstdint>

#include <glm/glm.hpp>

class Area {
    
    std::string name;
    uint64_t seed;

    Player *players;
    Camera MainPlayer;
    CellSystem world;

    int Area(std::string name, const bool LOCALWORLD);

    int upload(std::string name);

    int save();

    int EXIT();

};

#endif 