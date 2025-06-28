#ifndef _CAMERA_HPP_
#define _CAMERA_HPP_

#define NORMAL_FAR_PLANE 4096.0f
#define NORMAL_NEAR_PLANE 0.1f

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

// Определяет несколько возможных опций для движения камеры.
// Используется для абстракции, чтобы не зависеть от конкретных клавиш.
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Параметры камеры по умолчанию
const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  2.5f;    
const float SENSITIVITY =  0.1f;
const float ZOOM        =  45.0f;


// Класс камеры, который обрабатывает ввод и вычисляет
// соответствующие углы Эйлера, векторы и матрицы для использования в OpenGL
class Camera
{
public:
    // Атрибуты камеры
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    // Углы Эйлера
    float Yaw;
    float Pitch;
    // Настройки камеры
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    // Конструктор с векторами
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
    // Конструктор со скалярами
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

    // Возвращает матрицу вида, вычисленную с использованием углов Эйлера и матрицы LookAt
    glm::mat4 GetViewMatrix();

    void ProcessKeyboard(Camera_Movement direction, float deltaTime);

    void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);

    void ProcessMouseScroll(float yoffset);

private:
    void updateCameraVectors();
};

#endif // _CAMERA_HPP_