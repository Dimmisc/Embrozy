#ifndef _DUST_HPP_
#define _DUST_HPP_


#include <cstdint> 

#include "types/dustType.hpp"   


#define DUST_SIZE_STANDART 2
#define DUST_SIZE_SMALL 1 // Use small size for very efficient computer
#define DUST_SIZE_BIG 4 // Use big size for not efficient computer
#define DUST_SIZE_CHECK 8 // Using in debugging and testing features

 struct DustVertices {
    float top[18], bottom[18], right[18], left[18], backward[18], forward[18];
} ;
const DustVertices DUST_VERTICES = {
    .top =      {0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,  0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f},
    .bottom =   {0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f},
    .right =    {1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f,  1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f},
    .left =     {0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f},
    .backward = {0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,  0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f},
    .forward =  {0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,  0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f}
};

class Dust {
public:
    float rotationX{0};
    float rotationY{0};
    float rotationZ{0};
    double x{0};
    double y{0};
    double z{0};
    _DustType *type{nullptr};
};

typedef struct DustLine {
    Dust *line;
    uint8_t quantity;
} DustLine;

typedef struct DustGrid {
    Dust **grid;
    uint8_t quantityLenXY;
} DustGrid;

typedef struct DustCube {
    uint16_t **dustLine;
    static uint8_t quantityLenXYZ;
} DustCube;

#endif // _DUST_HPP_