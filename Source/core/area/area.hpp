#ifndef _AREA_HPP_
#define _AREA_HPP_


#include "cell.hpp"
#include "player/player.hpp"


class Area 
{
public:
    Player *players;
    CellGrid map;

};


#endif //_AREA_HPP_