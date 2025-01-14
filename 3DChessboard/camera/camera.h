#ifndef CAMERA_H
#define CAMERA_H

#include "../libs.h"

class Camera {
public:

    // Camera Attributes
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    // Euler Angles
    float yaw;
    float pitch;

    // Camera options
    float movementSpeed;
    float mouseSensitivity;
    float zoom;

    // Constructor with vectors
    Camera(glm::vec3 startPosition, glm::vec3 upDirection, float startYaw, float startPitch)
        : front(glm::vec3(0.0f, 0.0f, -1.0f)), worldUp(upDirection), yaw(startYaw), pitch(startPitch), movementSpeed(2.5f), mouseSensitivity(0.1f), zoom(45.0f)
    {
        position = startPosition;
        updateCameraVectors();
    }

    glm::mat4 getViewMatrix() {
        return glm::lookAt(position, position + front, up);
    }

    //keyboard
    void processKeyboard(int direction, float deltaTime) {
        float velocity = movementSpeed * deltaTime;
        if (direction == GLFW_KEY_W) {
            position += front * velocity;
        }
        if (direction == GLFW_KEY_S) {
            position -= front * velocity;
        }
        if (direction == GLFW_KEY_A) {
            position -= right * velocity;
        }
        if (direction == GLFW_KEY_D) {
            position += right * velocity;
        }
    }


    //mouse

    void processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true) {
        xoffset *= mouseSensitivity;
        yoffset = -yoffset;
        yoffset *= mouseSensitivity;


        yaw += xoffset;
        pitch -= yoffset;

        if (constrainPitch) {
            if (pitch > 89.0f) pitch = 89.0f;
            if (pitch < -89.0f) pitch = -89.0f;
        }

        updateCameraVectors();
    }

    void processMouseScroll(float yoffset) {
        if (zoom >= 1.0f && zoom <= 45.0f) {
            zoom -= yoffset;
        }
        if (zoom <= 1.0f) {
            zoom = 1.0f;
        }
        if (zoom >= 45.0f) {
            zoom = 45.0f;
        }
    }



private:
    // Calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors() {
        glm::vec3 front;
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        this->front = glm::normalize(front);

        // Also re-calculate the Right and Up vector
        right = glm::normalize(glm::cross(front, worldUp));  // Normalize the vectors
        up = glm::normalize(glm::cross(right, front));
    }
};


#endif