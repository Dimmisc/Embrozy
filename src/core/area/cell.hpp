#ifndef _CELL_HPP_
#define _CELL_HPP_

#define CELL_STANDART_SIZE 16
#define CELL_BIG_SIZE 32
#define CELL_SMALL_SIZE 8

#include <iostream>
#include <DS>
#include "cube.hpp"

uint8_t quantityLayots = 0;

typedef struct {
    int32_t x, y, z;
} CellPos;

class Cell 
{
public:
    CubeGrid *cubeLayots;
    Surface *cellFace;
    CellPos cellPos;

    Cell(const CellPos ABSOLUTE_POSITION);
    
    Cell(const CellPos ABSOLUTE_POSITION, FILE *UPLOAD_FILE = nullptr);

    ~Cell() {
        for (int i = 0; i < quantityLayots;i++){
            delete &cubeLayots[i];
        }
        delete cellFace;
    }
};

typedef struct CellGrid {
    Cell **grid;
    static uint8_t quantityXY;
} CellGrid;

class CellSystem {

    // Get argument from DS | namespace(directions)
    int Free_CellLine(uint8_t DIRECTION) {
        switch (DIRECTION) {
        case directions::FORWARD:
            break;
        case directions::BACKWARD:
            break;
        case directions::LEFT:
            break;
        case directions::RIGHT:
            break;
        default:
            break;
        }
        return -1;
    }

    //  Will be avalible latter 
    int Free_CellGrid(Cell **Grid) {
        return 0;
    }

public:
    Cell **space;
    int8_t  quantity {}; // Calculated by radius
    int8_t depthQ {}; // 

    // It take radius and depth in cells
    CellSystem(uint8_t radius, uint8_t depth, CellPos central_cell);

    // It take radius and depth in cells
    CellSystem(uint8_t radius, uint8_t depth);

    // It resize radius in cells
    int resize(int radius);

    // Set central chunk position
    int centralCell(CellPos central_cell);

    // It Follow on player coordinates offset
    int central_shift(int x, int y, int z);
};


#endif // _CELL_HPP_