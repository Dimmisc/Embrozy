#ifndef _CELL_HPP_
#define _CELL_HPP_

#define CELL_STANDART_SIZE 16
#define CELL_BIG_SIZE 32
#define CELL_SMALL_SIZE 8

#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <DS>
#include "cube.hpp"
#include "pcg/world-gen.hpp"

using std::vector;

static uint8_t quantityLayots = 0;

// struct CellPos {
//     int32_t x, y, z;
//     CellPos& operator+=(const CellPos& other) {
//         x += other.x;
//         y += other.y;
//         z += other.z;
//         return *this;
//     }

// } ;


class Cell 
{
public:
    static uint8_t CELL_SIZE;
    
    // vector<vector<vector<DustCube>>> cell;
    Surface cellFace;
    glm::dvec3 cellPos;
    unsigned int VBO;
    unsigned int VAO;
    // unsigned int EBO;
    int NumberDrawedTriangles{0};
    glm::mat4 model_matrix;

    Cell(const glm::dvec3 ABSOLUTE_POSITION, Generator *GEN): cellFace(CELL_STANDART_SIZE * DUST_SIZE_STANDART), cellPos(ABSOLUTE_POSITION) {
        this->CELL_SIZE = CELL_STANDART_SIZE;

        const int gridSize = static_cast<int>(this->CELL_SIZE * CUBE_SIZE_STANDART / DUST_SIZE_STANDART);
        const float worldOffsetX = static_cast<float>(gridSize * this->cellPos.x);
        const float worldOffsetZ = static_cast<float>(gridSize * this->cellPos.z);

        for (int local_i = 0; local_i < gridSize; local_i++) {
            for (int local_j = 0; local_j < gridSize; local_j++) {
                float world_x = worldOffsetX + local_i;
                float world_z = worldOffsetZ + local_j;
                int16_t noise_value = (int16_t)std::round(GEN->world_generator.GetNoise(world_x, world_z) * 1000);
                cellFace.surface[local_i][local_j] = noise_value;
            }
        }
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        // glGenBuffers(1, &EBO);
        glBindVertexArray(VAO);
        
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        vector<float> vertices(0);
        
        const int FLOATS_PER_FACE = 18;
        for (int i = 0; i < gridSize; i++) {
            for (int j = 0; j < gridSize; j++) {
                uint16_t current_cell_height = cellFace.surface[i][j]; 
                float offsetX = i * CUBE_SIZE_STANDART / DUST_SIZE_STANDART;
                float offsetY = current_cell_height * CUBE_SIZE_STANDART / DUST_SIZE_STANDART; 
                float offsetZ = j * CUBE_SIZE_STANDART / DUST_SIZE_STANDART; 
                for(int k = 0; k < FLOATS_PER_FACE / 3; ++k) {
                        vertices.push_back(DUST_VERTICES.top[k*3 + 0] * DUST_SIZE_STANDART + offsetX);
                        vertices.push_back(DUST_VERTICES.top[k*3 + 1] * DUST_SIZE_STANDART + offsetY);
                        vertices.push_back(DUST_VERTICES.top[k*3 + 2] * DUST_SIZE_STANDART + offsetZ);
                    }
                this->NumberDrawedTriangles += 2;
                if (i == 0 || cellFace.surface[i - 1][j] <= (current_cell_height - 1)) {
                    for(int k = 0; k < FLOATS_PER_FACE / 3; ++k) {
                        vertices.push_back(DUST_VERTICES.left[k*3 + 0] * DUST_SIZE_STANDART + offsetX);
                        vertices.push_back(DUST_VERTICES.left[k*3 + 1] * DUST_SIZE_STANDART + offsetY);
                        vertices.push_back(DUST_VERTICES.left[k*3 + 2] * DUST_SIZE_STANDART + offsetZ);
                    }
                    this->NumberDrawedTriangles += 2;
                }
                if (i == gridSize - 1 || cellFace.surface[i + 1][j] <= (current_cell_height - 1)) {
                     for(int k = 0; k < FLOATS_PER_FACE / 3; ++k) {
                        vertices.push_back(DUST_VERTICES.right[k*3 + 0] * DUST_SIZE_STANDART + offsetX);
                        vertices.push_back(DUST_VERTICES.right[k*3 + 1] * DUST_SIZE_STANDART + offsetY);
                        vertices.push_back(DUST_VERTICES.right[k*3 + 2] * DUST_SIZE_STANDART + offsetZ);
                    }
                    this->NumberDrawedTriangles += 2;
                }
                if (j == 0 || cellFace.surface[i][j - 1] <= (current_cell_height - 1)) {
                     for(int k = 0; k < FLOATS_PER_FACE / 3; ++k) {
                        vertices.push_back(DUST_VERTICES.forward[k*3 + 0] * DUST_SIZE_STANDART + offsetX);
                        vertices.push_back(DUST_VERTICES.forward[k*3 + 1] * DUST_SIZE_STANDART + offsetY);
                        vertices.push_back(DUST_VERTICES.forward[k*3 + 2] * DUST_SIZE_STANDART + offsetZ);
                    }
                    this->NumberDrawedTriangles += 2;
                }
                if (j == gridSize - 1 || cellFace.surface[i][j + 1] <= (current_cell_height - 1)) {
                     for(int k = 0; k < FLOATS_PER_FACE / 3; ++k) {
                        vertices.push_back(DUST_VERTICES.backward[k*3 + 0] * DUST_SIZE_STANDART + offsetX);
                        vertices.push_back(DUST_VERTICES.backward[k*3 + 1] * DUST_SIZE_STANDART + offsetY);
                        vertices.push_back(DUST_VERTICES.backward[k*3 + 2] * DUST_SIZE_STANDART + offsetZ);
                    }
                    this->NumberDrawedTriangles += 2;
                }
            }
        }
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    }
    
    // Cell(const CellPos ABSOLUTE_POSITION, FILE *UPLOAD_FILE = nullptr, Generator *GEN);

    ~Cell() {
        for (int i = 0; i < CELL_SIZE * CUBE_SIZE_STANDART / DUST_SIZE_STANDART;i++){
            for(int j = 0; j < CELL_SIZE * CUBE_SIZE_STANDART / DUST_SIZE_STANDART; j++){
                delete &cellFace.surface[i][j];
            }
            delete &cellFace.surface[i];
        }
        delete &cellFace;
        glDeleteVertexArrays(1, &VAO);
        //glDeleteVertexArrays(1, &EBO);
        glDeleteBuffers(1, &VBO);
    }
};

struct CellGrid {
    Cell **grid;
    static uint8_t quantityXY;
};

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
            return ERROR_UNCOMPATIBLE_DIRECTION;
        }
        return SUCCESS;
    }

    //  Will be avalible latter 
    int Free_CellGrid(Cell **Grid) {
        return FAIL;
    }

public:
    glm::dvec3 central_cell; // The Cell where is player
    Cell **space; 
    int8_t radius{}; // int rounded radius
    int8_t depth{}; // depth attached cells 

    // It take radius and depth in cells
    CellSystem(uint8_t radius, uint8_t depth, glm::dvec3 central_cell);

    // It take radius and depth in cells
    CellSystem(uint8_t radius, uint8_t depth);

    // It resize radius in cells
    // if it get 0 value, value not changed 
    void resize(uint16_t radius, uint16_t depth);

    // Set central chunk position
    int centralCell(glm::dvec3 central_cell);

    // It Follow on player coordinates offset
    int systemShift(glm::dvec3 camera_position);
};

#endif // _CELL_HPP_