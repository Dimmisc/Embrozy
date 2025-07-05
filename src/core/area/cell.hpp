#ifndef _CELL_HPP_
#define _CELL_HPP_

#define CELL_STANDART_SIZE 16
#define CELL_BIG_SIZE 32
#define CELL_SMALL_SIZE 8

//h

#include "cube.hpp"

typedef struct {
    int32_t x, y, z;
}CellPos;
class Cell 
{
public:
    static uint8_t quantityLayots;
    CubeGrid *cubeLayots;
    Surface *cellFace;
    CellPos cellPos;
};

typedef struct CellGrid {
    Cell **grid;
    static uint8_t quantityXY;
} CellGrid;

class CellSystem {
    
    int Free_CellLine(Cell *Line);

    int Free_CellGrid(Cell **Grid);
public:
    Cell **space;
    int8_t *maspos;
    int8_t  quantity;
    int8_t *deeppos;
    
    CellSystem(int raadius, CellPos central_cell);
    
    CellSystem(int radius);
    
    int resize(int radius);

    int central_shift(int x, int y, int z);
};
#endif // _CELL_HPP_