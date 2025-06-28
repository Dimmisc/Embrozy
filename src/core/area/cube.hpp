#ifndef _CUBE_HPP_
#define _CUBE_HPP_


#include "surfaces/surface.hpp"
#include "dust.hpp"

#include <cstdint>

#define CUBE_SIZE_STANDART 32


class Сube
{   
    Surface cubeFace;
public:
    static uint8_t QUANTITY_LEN_XYZ;
    
    DustCube *dustConsist;
    uint16_t cubeType;
    int8_t x{0};
    int8_t y{0};
};

typedef struct СubeGrid 
{   
    Сube **grid;
    uint16_t quantityLenXY;
} CubeGrid;


#endif // _CUBE_HPP_