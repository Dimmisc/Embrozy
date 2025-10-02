#include "cell.hpp"


CellSystem::CellSystem(uint8_t radius, uint8_t depth, CellPos central_cell) {

}

CellSystem::CellSystem(uint8_t radius, uint8_t depth) {

}

int CellSystem::resize(int radius, int depth) {
    return SUCCESS;
}

int CellSystem::centralCell(CellPos central_cell) {
    return SUCCESS;
}

// The Z shift now is not avalible
int CellSystem::central_shift(int x, int y, int z) {
    return SUCCESS;
}