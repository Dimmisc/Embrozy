#ifndef _AREA_HPP_
#define _AREA_HPP_

#include "player/player.hpp"
#include "cell.hpp"


#include <string>
#include <cstdint>
#include "pcg/world-gen.hpp"


class Area {
    
public:
    std::string name;
    uint64_t seed;
    
    bool local_world;

    Camera MainPlayer;
    Generator *generator;
    CellSystem terrain;
    
    Player *players;

    Area(std::string name, bool LOCALWORLD): name(name), local_world(LOCALWORLD), terrain(1, 1) {
        generator = Init_PCG(seed);
         // Cellsystem Will be changed, but not now
    }

    int upload(std::string name);

    int save();

    int EXIT();

};

#endif 