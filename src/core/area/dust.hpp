#ifndef _DUST_HPP_
#define _DUST_HPP_


#include <cstdint> 

#include "types/dustType.hpp"   


#define DUST_SIZE_STANDART 2
#define DUST_SIZE_SMALL 1 // Use small size for very efficient computer
#define DUST_SIZE_BIG 4 // Use big size for not efficient computer
#define DUST_SIZE_CHECK 8 // Using in debugging and testing features


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