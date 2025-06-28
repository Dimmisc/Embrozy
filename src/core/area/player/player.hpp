#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_


#include "../dust.hpp"
#include "../../render/camera.hpp"



class Player 
{
public: 
    int64_t x, y, z;
    Camera camera;
    
};

#endif //_PLAYER_HPP_