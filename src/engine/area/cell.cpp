#include "cell.hpp"


// CellSystem::CellSystem(uint8_t radius, uint8_t depth, glm::dvec3 central_cell) {

//}


// void CellSystem::resize(uint16_t radius, uint16_t depth) {
//     if (radius == 0) {
//         this->depth = depth;
//     }
//     else if (depth == 0) {
//         this->radius = radius;
//     }
//     else {
//         this->depth = depth;
//         this->radius = radius;
//     }
// }

int CellSystem::centralCell(glm::dvec3 central_cell) {
    return SUCCESS;
}

// int CellSystem::render(Camera *CAMERA){
//     shader.use();
//     shader.setMat4("projection", CAMERA->GetProjectionMatrix());
//     shader.setMat4("view", CAMERA->GetViewMatrix());

//     shader.setVec3("objectColor", glm::vec3(0.25f, 0.6f, 0.1f)); 
//     shader.setVec3("skyColor", glm::vec3(0.8f, 0.8f, 0.9f));    
//     shader.setVec3("groundColor", glm::vec3(0.6f, 0.2f, 0.0f)); 
//     shader.setFloat("intensity", 1.2f); 

//     int diameter = (int)radius * 2 + 1;
//     for (int i = 0; i < diameter; i++){
//         for (int j = 0; j < diameter; j++){
//             if (space[i][j] != nullptr) {
//                 glm::vec3 translation= glm::vec3(space[i][j]->cellPos - CAMERA->Position);
//                 glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
//                 shader.setMat4("model", model);
//                 space[i][j]->render();
//             }
//             else {
//                 printf("Not all Cells loadeded Cell: (%d, %d)\n", i, j);
//             }
//         }
//     }
//     return SUCCESS;
// }

// The Z shift now is not avalible
