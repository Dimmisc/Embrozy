#include "cell.hpp"


CellSystem::CellSystem(uint8_t radius, uint8_t depth, glm::dvec3 central_cell) {

}

CellSystem::CellSystem(uint8_t radius, uint8_t depth) {

}

void CellSystem::resize(uint16_t radius, uint16_t depth) {
    if (radius == 0) {
        this->depth = depth;
    }
    else if (depth == 0) {
        this->radius = radius;
    }
    else {
        this->depth = depth;
        this->radius = radius;
    }
}

int CellSystem::centralCell(glm::dvec3 central_cell) {
    return SUCCESS;
}

// The Z shift now is not avalible
int CellSystem::systemShift(glm::dvec3 camera_position) {
    return SUCCESS;
}