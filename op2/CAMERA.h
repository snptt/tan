//
//  CAMERA.h
//  op
//
//  Created by BoBo W on 2025/4/2.
//

#ifndef CAMERA_H
#define CAMERA_H
#include <glad/glad.h>
#include <cglm/cglm.h>
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
const float YAW         = -90.0f;// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
const float PITCH       =  0.0f;
const float SPEED       =  1.5f;
const float SENSITIVITY =  0.1f;
const float ZOOM        =  45.0f;
vec3 _POSITION = {0.0f, 0.0f, 0.0f};
vec3 _UP = {0.0f,1.0f,0.0f};
vec3 _FRONT = {0.0f, 0.0f, -1.0f};

struct Camera{
    // camera Attributes
    vec3 Position;
    vec3 Front;
    vec3 Up;
    vec3 Right;
    vec3 WorldUp;
    // euler Angles
    float Yaw;
    float Pitch;
    // camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;
    
    void (*ProcessKeyboard)(struct Camera *cam, enum Camera_Movement direction, float deltaTime);
    
    void (*ProcessMouseMovement)(struct Camera *cam, float xoffset, float yoffset, GLboolean constrainPitch = true);
    
    void (*ProcessMouseScroll)(struct Camera *cam, float yoffset);
    
    void (*updateCameraVectors)(struct Camera *cam);
    
    void (*GetViewMatrix)(struct Camera *cam, mat4 *result);
};

typedef struct Camera Camera;

void updateCameraVectors(Camera *cam){
    vec3 front,temp;
    front[0] = cos(glm_rad(cam->Yaw)) * cos(glm_rad(cam->Pitch));
    front[1] = sin(glm_rad(cam->Pitch));
    front[2] = sin(glm_rad(cam->Yaw)) * cos(glm_rad(cam->Pitch));
    glm_vec3_norm(front);
    glm_vec3_copy(front, cam->Front);
    glm_vec3_cross(cam->Front, cam->WorldUp, temp);
    glm_vec3_norm(temp);
    glm_vec3_copy(temp, cam->Right);
    glm_vec3_cross(cam->Right, cam->Front, temp);
    glm_vec3_norm(temp);
    glm_vec3_copy(temp, cam->Up);
}

void GetViewMatrix(struct Camera *cam, mat4 *result){
    vec3 temp;
    glm_vec3_add(cam->Position, cam->Front, temp);
    glm_lookat(cam->Position, temp, cam->Up, *result);
}

// processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
void ProcessKeyboard(struct Camera *cam, enum Camera_Movement direction, float deltaTime){
    float velocity = cam->MovementSpeed * deltaTime;
    //printf("%f\n",velocity);
    vec3 temp;
    if (direction == FORWARD){
        glm_vec3_scale(cam->Front, velocity, temp);
        glm_vec3_add(cam->Position, temp, cam->Position);
    }
    if (direction == BACKWARD){
        glm_vec3_scale(cam->Front, velocity, temp);
        glm_vec3_sub(cam->Position, temp, cam->Position);
    }
    if (direction == LEFT){
        glm_vec3_scale(cam->Right, velocity, temp);
        glm_vec3_sub(cam->Position, temp, cam->Position);
    }
    if (direction == RIGHT){
        glm_vec3_scale(cam->Right, velocity, temp);
        glm_vec3_add(cam->Position, temp, cam->Position);
    }
}

// processes input received from a mouse input system. Expects the offset value in both the x and y direction.
void ProcessMouseMovement(struct Camera *cam, float xoffset, float yoffset, GLboolean constrainPitch){
    xoffset *= cam->MouseSensitivity;
    yoffset *= cam->MouseSensitivity;

    cam->Yaw   += xoffset;
    cam->Pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
        if (cam->Pitch > 89.0f)
            cam->Pitch = 89.0f;
        if (cam->Pitch < -89.0f)
            cam->Pitch = -89.0f;
    }

    // update Front, Right and Up Vectors using the updated Euler angles
    updateCameraVectors(cam);
    }

// processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
void ProcessMouseScroll(struct Camera *cam, float yoffset)
{
    cam->Zoom -= (float)yoffset;
    if (cam->Zoom < 1.0f)
        cam->Zoom = 1.0f;
    if (cam->Zoom > 45.0f)
        cam->Zoom = 45.0f;
}

//constructor with vectors
void IniCam_vec(Camera *temp, vec3* position/*=_POSITION*/, vec3* up/*_UP*/, float yaw/*=YAW*/, float pitch/*=PITCH*/){
    glm_vec3_copy(_FRONT, temp->Front);
    glm_vec3_copy(*position, temp->Position);
    glm_vec3_copy(*up, temp->WorldUp);
    temp->MovementSpeed = SPEED;
    temp->MouseSensitivity = SENSITIVITY;
    temp->Zoom = ZOOM;
    temp->Yaw = yaw;
    temp->Pitch = pitch;
    temp->ProcessKeyboard=ProcessKeyboard;
    temp->ProcessMouseMovement=ProcessMouseMovement;
    temp->ProcessMouseScroll=ProcessMouseScroll;
    temp->updateCameraVectors=updateCameraVectors;
    temp->updateCameraVectors(temp);
    temp->GetViewMatrix=GetViewMatrix;
}

//constructor with scalar values
void IniCam_scl(Camera *temp, float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch){
    glm_vec3_copy(_FRONT, temp->Front);
    temp->Position[0] = posX;
    temp->Position[1] = posY;
    temp->Position[2] = posZ;
    temp->WorldUp[0] = upX;
    temp->WorldUp[1] = upY;
    temp->WorldUp[2] = upZ;
    temp->MovementSpeed = SPEED;
    temp->MouseSensitivity = SENSITIVITY;
    temp->Zoom = ZOOM;
    temp->Yaw = yaw;
    temp->Pitch = pitch;
    temp->ProcessKeyboard=ProcessKeyboard;
    temp->ProcessMouseMovement=ProcessMouseMovement;
    temp->ProcessMouseScroll=ProcessMouseScroll;
    temp->updateCameraVectors=updateCameraVectors;
    temp->updateCameraVectors(temp);
    temp->GetViewMatrix=GetViewMatrix;
}


#endif
