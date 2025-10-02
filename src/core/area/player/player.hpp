#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_


#include "../dust.hpp"
#include "../../render/camera.hpp"



class Player 
{
public: 
    
    glm::vec3 pos;
    Camera camera;
    
};

#endif //_PLAYER_HPP_