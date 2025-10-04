#ifndef _CAMERA_HPP_
#define _CAMERA_HPP_

#define NORMAL_FAR_PLANE 4096.0f
#define NORMAL_NEAR_PLANE 0.1f

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>


enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// the camera params defined
const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  2.5f;    
const float SENSITIVITY =  0.1f;
const float ZOOM        =  45.0f;

class Camera
{
public:

    glm::dvec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    float Yaw;
    float Pitch;

    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;


    Camera(glm::dvec3 position = glm::dvec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);

    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

    // give view matrix
    glm::mat4 GetViewMatrix();

    void ProcessKeyboard(Camera_Movement direction, float deltaTime);

    void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);

    void ProcessMouseScroll(float yoffset);

private:

    void updateCameraVectors();
};

#endif // _CAMERA_HPP_