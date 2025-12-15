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
// #include "cube.hpp"
// #include "pcg/world-gen.hpp"
// #include "../render/shaders.hpp"
// #include "../render/camera.hpp"

using std::vector;

static uint8_t quantityLayots = 0;


class Cell 
{
public:
    uint8_t CELL_SIZE;
    
    int16_t **face{nullptr};
    glm::dvec3 cellPos;
    unsigned int VBO;
    unsigned int VAO;
    // unsigned int EBO;
    int vertexCount{0};
    glm::mat4 model_matrix;

    Cell(const glm::dvec3 ABSOLUTE_POSITION, Generator *GEN): cellPos(ABSOLUTE_POSITION) {

        this->CELL_SIZE = CELL_STANDART_SIZE;
        
        const int gridSize = static_cast<int>(this->CELL_SIZE * CUBE_SIZE_STANDART / DUST_SIZE_STANDART);
        const float worldOffsetX = static_cast<float>(gridSize * (int)this->cellPos.x);
        const float worldOffsetZ = static_cast<float>(gridSize * (int)this->cellPos.z);
        cellPos.x *= 16;
        cellPos.z *= 16;
        face = (int16_t**)malloc(sizeof(*face) * gridSize);
        for (int local_i = 0; local_i < gridSize; local_i++) {
            face[local_i] = (int16_t*)malloc(sizeof(*face) * gridSize);
            for (int local_j = 0; local_j < gridSize; local_j++) {
                float world_x = worldOffsetX + local_i;
                float world_z = worldOffsetZ + local_j;
                int16_t noise_value = (int16_t)std::round(GEN->world_generator.GetNoise(world_x, world_z) * 1024);
                face[local_i][local_j] = noise_value;
            }
        }
        printf("TerraStartHeight: %d\n", (int)face[0][0]);
        
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        // glGenBuffers(1, &EBO);
        glBindVertexArray(VAO);
        
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        vector<float> vertices(0);
        float s = 1.0f/16 * CELL_STANDART_SIZE / (CUBE_SIZE_STANDART / DUST_SIZE_STANDART);
        const int FLOATS_PER_FACE = 18;
        vertices.reserve(gridSize * gridSize * 3 * FLOATS_PER_FACE);
        for (int i = 0; i < gridSize; i++) {
            for (int j = 0; j < gridSize; j++) {
                int16_t current_cell_height = face[i][j]; 
                float offsetX = i * s;
                float offsetY = (float)current_cell_height * s; 
                float offsetZ = j * s; 
                for(int k = 0; k < FLOATS_PER_FACE / 3; ++k) {
                        vertices.push_back(DUST_VERTICES.top[k*3 + 0] * s + offsetX);
                        vertices.push_back(DUST_VERTICES.top[k*3 + 1] * s + offsetY);
                        vertices.push_back(DUST_VERTICES.top[k*3 + 2] * s + offsetZ);
                    }
                this->vertexCount += 6;
                if (i != 0 && face[i - 1][j] <= (current_cell_height - 1)) {
                    for(int k = 0; k < FLOATS_PER_FACE / 3; ++k) {
                        vertices.push_back(DUST_VERTICES.left[k*3 + 0] * s + offsetX);
                        vertices.push_back(DUST_VERTICES.left[k*3 + 1] * s + offsetY);
                        vertices.push_back(DUST_VERTICES.left[k*3 + 2] * s + offsetZ);
                    }
                    this->vertexCount += 6;
                }
                if (i != gridSize - 1 && face[i + 1][j] <= (current_cell_height - 1)) {
                     for(int k = 0; k < FLOATS_PER_FACE / 3; ++k) {
                        vertices.push_back(DUST_VERTICES.right[k*3 + 0] * s + offsetX);
                        vertices.push_back(DUST_VERTICES.right[k*3 + 1] * s + offsetY);
                        vertices.push_back(DUST_VERTICES.right[k*3 + 2] * s + offsetZ);
                    }
                    this->vertexCount += 6;
                }
                if (j != 0 && face[i][j - 1] <= (current_cell_height - 1)) {
                     for(int k = 0; k < FLOATS_PER_FACE / 3; ++k) {
                        vertices.push_back(DUST_VERTICES.forward[k*3 + 0] * s + offsetX);
                        vertices.push_back(DUST_VERTICES.forward[k*3 + 1] * s + offsetY);
                        vertices.push_back(DUST_VERTICES.forward[k*3 + 2] * s + offsetZ);
                    }
                    this->vertexCount += 6;
                }
                if (j != gridSize - 1 && face[i][j + 1] <= (current_cell_height - 1)) {
                     for(int k = 0; k < FLOATS_PER_FACE / 3; ++k) {
                        vertices.push_back(DUST_VERTICES.backward[k*3 + 0] * s + offsetX);
                        vertices.push_back(DUST_VERTICES.backward[k*3 + 1] * s + offsetY);
                        vertices.push_back(DUST_VERTICES.backward[k*3 + 2] * s + offsetZ);
                    }
                    this->vertexCount += 6;
                }
            }
        }
        // printf("%f, %f, %f, %f, %f, %f\n %f, %f, %f, %f, %f, %f, %f\n", vertices[0], vertices[1], vertices[2], vertices[3], vertices[4], vertices[5],
            //  vertices[6], vertices[7], vertices[8], vertices[9], vertices[10], vertices[11]);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }
    
    // Cell(const glm::dvec3 ABSOLUTE_POSITION, FILE *UPLOAD_FILE = nullptr, Generator *GEN);

    glm::mat4 GetModelMat4(glm::dvec3 camera_position){
        return glm::mat4();
    }

    void render(){
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0,  vertexCount);
        GLenum error = glGetError();
        if (error != GL_NO_ERROR) {
            switch (error) {
                case GL_INVALID_ENUM:
                    printf("Invalid enum passed to glDrawArrays\n");
                    break;
                case GL_INVALID_VALUE:
                    printf("Invalid first or count parameter\n");
                    break;
                case GL_INVALID_OPERATION:
                    printf("Invalid operation - check shader program, VAO, etc.\n");
                    break;
            }
        }
    }

    ~Cell() {
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
    bool alocated_cells;
    int radius; // int rounded radius
    int depth; // depth attached cells 
    // Get argument from DS | namespace(directions)
    void Free_CellLine(uint8_t DIRECTION) {
        int diameter = radius * 2 + 1;
        int p = 0;
        bool orient = false; // false x : true y
        switch (DIRECTION) {
            case directions::FORWARD: 
                p = radius - 1;
                break;
            case directions::BACKWARD: 
                break;
            case directions::LEFT: 
                orient = true;
                break;
            case directions::RIGHT: 
                p = radius - 1;
                orient = true;
                break;
            default:
                return ;
        }
        for (int g = 0; g < radius; g++){
            if (orient){
                delete space[g][p];
                space[g][p] = nullptr;
            }
            else {
                delete space[p][g];
                space[p][g] = nullptr;
            }
        }
    }

    //  Will be avalible latter 
    void Allocate_And_Populate_Grid() {
        int diameter = radius * 2 + 1;
        printf("%d", radius);
        // 1. Выделяем память под массив строк
        space = new Cell**[diameter];
        for (int i = 0; i < diameter; ++i) {
            // 2. Выделяем память под столбцы и инициализируем nullptr
            space[i] = new Cell*[diameter];
            for (int j = 0; j < diameter; ++j) {
                space[i][j] = nullptr;
            }
        }

        // 3. Заполняем сетку новыми ячейками
        for (int i = 0; i < diameter; ++i) {
            for (int j = 0; j < diameter; ++j) {
                // Рассчитываем абсолютную позицию ячейки в мире
                long long cell_x = (long long)central_cell.x + (i - radius);
                long long cell_z = (long long)central_cell.z + (j - radius);
                
                // Создаем новую ячейку
                printf("Position new cell:%lf, %lf\n", cell_x, cell_z);
                space[i][j] = new Cell(glm::dvec3(cell_x, 0, cell_z), &generator);
            }
        }
        printf("%d", radius);
    }

public:
    Generator generator;    
    Shader shader;
    glm::dvec3 central_cell; // The Cell where is player
    Cell ***space; 


    // It take radius and depth in cells
    CellSystem(int radius, int depth, glm::dvec3 central_cell, Generator GEN) :
    radius(radius), depth(depth), central_cell(central_cell), generator(GEN), shader("assets/shaders/main.vs", "assets/shaders/main.fs") {
        // this->uploadMap = vector<vector<bool>> (radius, vector<bool>(radius));
        printf("Terrarian Init: rad:%d, dep:%d\n", this->depth, this->radius);
        Allocate_And_Populate_Grid();
    }

    int render(Camera *CAMERA){
        shader.use();
        shader.setMat4("projection", CAMERA->GetProjectionMatrix());
        shader.setMat4("view", CAMERA->GetViewMatrix());
        shader.setVec3("objectColor", glm::vec3(0.25f, 0.6f, 0.1f)); 

        shader.setVec3("skyColor", glm::vec3(0.8f, 0.8f, 0.9f));    
        shader.setVec3("groundColor", glm::vec3(0.6f, 0.2f, 0.0f)); 
        shader.setFloat("intensity", 1.2f); 

        int diameter = (int)radius * 2 + 1;
        for (int i = 0; i < diameter; i++){
            for (int j = 0; j < diameter; j++){
                if (space[i][j] != nullptr) {
                    glm::vec3 translation= glm::vec3(space[i][j]->cellPos - CAMERA->Position);
                    glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
                    shader.setMat4("model", model);
                    space[i][j]->render();
                }
                else {
                    printf("Not all Cells loadeded Cell: (%d, %d)\n", i, j);
                }
            }
        }
        return SUCCESS;
    }

    // It take radius and depth in cells
    CellSystem(uint8_t radius, uint8_t depth);

    // It resize radius in cells
    // if it get 0 value, value not changed 
    // void resize(uint16_t radius, uint16_t depth);

    // Set central chunk position, when you load map with player position
    int centralCell(glm::dvec3 central_cell);

    // Follow on player coordinates offset
    int systemShift(glm::dvec3 camera_position);

    ~CellSystem() {
        if (space == nullptr) return;
        int diameter = radius * 2 + 1;
        for (int i = 0; i < diameter; ++i) {
            if (space[i] != nullptr) {
                for (int j = 0; j < diameter; ++j) {
                    delete space[i][j]; 
                }
                delete[] space[i]; 
            }
        }
        delete[] space; 
        space = nullptr;
    }

};

#endif // _CELL_HPP_