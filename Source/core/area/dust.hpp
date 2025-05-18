#ifndef _DUST_HPP_
#define _DUST_HPP_


#include <cstdint> 

#include "types/dustType.hpp"   


#define DUST_SIZE_STANDART 2
#define DUST_SIZE_SMALL 1 // Use small size for very efficient computer
#define DUST_SIZE_BIG 4 // Use big size for not efficient computer
#define DUST_SIZE_CHECK 8 // Using in debugging and testing features


class dust 
{
public:
    float rotationX{0};
    float rotationY{0};
    float rotationZ{0};
    double x{0};
    double y{0};
    double z{0};
    _DustType *type{nullptr};
};

typedef struct dustLine
{
    dust *line;
    uint8_t quantity;
} dustLine;

typedef struct dustGrid
{
    dust **grid;
    uint8_t quantityLenXY;
} dustGrid;

typedef struct dustCube 
{
    dustLine **dustLineGrid;
    uint8_t quantityLenXY;
} dustCube;

#endif // _DUST_HPP_