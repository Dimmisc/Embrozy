#ifndef _CELL_HPP_
#define _CELL_HPP_

#define CELL_STANDART_SIZE 16
#define CELL_BIG_SIZE 32
#define CELL_SMALL_SIZE 8

//h

#include "cube.hpp"


class cell 
{
public:
    static uint8_t quantityXYZ;
    cubeGrid *cubeLayots;
    uint8_t quantityLayots;
    int32_t x;
    int32_t y;
    int32_t z;
};


#endif // _CELL_HPP_