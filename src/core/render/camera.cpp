#include "Camera.hpp"

Camera::Camera(glm::dvec3 position, glm::vec3 up, float yaw, float pitch) 
    : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
    Position = position;
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) 
    : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
    Position = glm::vec3(posX, posY, posZ);
    WorldUp = glm::vec3(upX, upY, upZ);
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix()
{
    glm::vec3 Pos(0.0f);
    return glm::lookAt(Pos, Pos + Front, Up);
}

glm::mat4 Camera::GetProjectionMatrix() {
     return glm::perspective(glm::radians(Zoom), (float)this->SCREEN_HEIGHT/this->SCREEN_WIDTH, NORMAL_NEAR_PLANE, NORMAL_FAR_PLANE);
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
    float velocity = MovementSpeed * deltaTime;
    if (direction == FORWARD)
        Position += Front * velocity;
    if (direction == BACKWARD)
        Position -= Front * velocity;
    if (direction == LEFT)
        Position -= Right * velocity;
    if (direction == RIGHT)
        Position += Right * velocity;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch) {
    if (xoffset){
        xoffset *= this->MouseSensitivity;
        Yaw   += xoffset;
    }
    if (yoffset) {
        yoffset *= this->MouseSensitivity;
        Pitch += yoffset;
    }

    if (constrainPitch)
    {
        if (this->Pitch > 89.0f)
            this->Pitch = 89.0f;
        if (this->Pitch < -89.0f)
            this->Pitch = -89.0f;
    }

    // update vectors Front, Right и Up, using Eiler's angles
    updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset)
{
    Zoom -= (float)yoffset;
    if (Zoom < 0.001f)
        Zoom = 0.001f;
    if (Zoom > 45.0f)
        Zoom = 45.0f;
}

void Camera::updateCameraVectors()
{
    // update front     vector
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);
    // update right, up vectors
    Right = glm::normalize(glm::cross(Front, WorldUp));  // Нормализуем, потому что их длина может приближаться к 0, когда вы смотрите вверх или вниз, что приводит к замедлению движения.
    Up    = glm::normalize(glm::cross(Right, Front));
}
void Camera::ProcessScreen(int width, int height){
    this->SCREEN_HEIGHT = height, this->SCREEN_WIDTH = width;
}