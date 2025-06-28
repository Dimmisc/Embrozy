#ifndef _CELL_HPP_
#define _CELL_HPP_

#define CELL_STANDART_SIZE 16
#define CELL_BIG_SIZE 32
#define CELL_SMALL_SIZE 8

//h

#include "cube.hpp"


class Cell 
{
public:
    static uint8_t quantityLayots;
    CubeGrid *cubeLayots;
    Surface *cellFace;
    int32_t x{0}, y{0}, z{0};
};

typedef struct CellGrid {
    Cell **grid;
    static uint8_t quantityXYZ;
} CellGrid;


#endif // _CELL_HPP_