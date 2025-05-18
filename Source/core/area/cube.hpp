#ifndef _CUBE_HPP_
#define _CUBE_HPP_


#include "surfaces/surface.hpp"

#include "dust.hpp"

#include <cstdint>

#define CUBE_SIZE_STANDART 32


class cube
{
public:
    static uint8_t QUANTITY_LEN_XYZ;
    dustCube *dustConsist;
    Surface cubeFace;
    uint16_t cubeType;
    int8_t x;
    int8_t y;
    int8_t z;
};

typedef struct cubeGrid 
{   
    cube **grid;
    uint16_t quantityLenXY;
} cubeGrid;


#endif // _CUBE_HPP_