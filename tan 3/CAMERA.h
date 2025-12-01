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

#ifndef debuging
#define debugvec3(x,y) //printf(#x#y":\n");\
glm_vec3_print(y, stdout);
#define debugf(x,y) //printf(#x#y":%.12f\n",y);
#endif
#ifdef debuging
#define debugvec3(x,y) printf(#x#y":\n");\
glm_vec3_print(y, stdout);
#define debugf(x,y) printf(#x#y":%.12f\n",y);
#endif


//0begin 1gaming
int STATE = 0;

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
const float YAW         = -90.0f;// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
const float PITCH       =  0.0f;
const float SPEED       =  2.5f;
const float SENSITIVITY =  0.006f;
const float ZOOM        =  45.0f;
vec3 _POSITION = {0.0f, 0.0f, 0.0f};
vec3 _UP = {0.0f,1.0f,0.0f};
vec3 _FRONT = {0.0f, 0.0f, -1.0f};

struct Camera{
    // camera Attributes
    float distance;
    vec3 Position;
    vec3 Front;
    vec3 Up;
    vec3 Right;
    vec3 WorldUp;
    vec3 targetPosition;

    // euler Angles
    float Yaw;
    float Pitch;
    // camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;
    
    void (*ProcessKeyboard)(struct Camera *cam, enum Camera_Movement direction, float deltaTime);
    
    void (*ProcessMouseMovement)(struct Camera *cam, float xoffset, float yoffset, GLboolean constrainPitch);
    
    void (*ProcessMouseScroll)(struct Camera *cam, float yoffset);
    
    void (*updateCameraVectors)(struct Camera *cam);
    
    void (*GetViewMatrix)(struct Camera *cam, mat4 *result);
};
typedef struct Camera Camera;

void updateCameraVectors(Camera *cam){
    vec3 offsetY,offsetP,temp;
//    pos[0] = -cos(glm_rad(cam->Yaw)) * cos(glm_rad(cam->Pitch));
//    pos[1] = -sin(glm_rad(cam->Pitch));
//    pos[2] = -sin(glm_rad(cam->Yaw)) * cos(glm_rad(cam->Pitch));
    glm_vec3_scale_as(cam->Right, -cam->Yaw, offsetY);
    glm_vec3_scale_as(cam->Up, -cam->Pitch, offsetP);
    glm_vec3_addadd(offsetP,offsetY,cam->Position);
    glm_normalize(cam->Position);
    glm_vec3_scale_as(cam->Position, (cam->distance), cam->Position);
    glm_vec3_negate_to(cam->Position, cam->Front);
    glm_vec3_cross(cam->Front, cam->WorldUp, temp);
    glm_normalize_to(temp, cam->Right);
    glm_vec3_cross(cam->Right, cam->Front, temp);
    glm_vec3_normalize_to(temp, cam->Up);
}

int Orth=1;

void GetViewMatrix(struct Camera *cam, mat4 *result){
    if(Orth){
        glm_mat4_copy(GLM_MAT4_IDENTITY, *result);
        return;
    }
    vec3 temp;
    glm_normalize_to(cam->Position, temp);
    glm_vec3_add(temp, cam->Front, temp);
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

//    cam->Yaw   += xoffset;
//    cam->Pitch += yoffset;
    cam->Yaw   = xoffset;
    cam->Pitch = yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
//    if (constrainPitch)
//    {
//        if (cam->Pitch > 89.0f)
//            cam->Pitch = 89.0f;
//        if (cam->Pitch < -89.0f)
//            cam->Pitch = -89.0f;
//    }

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
void IniCam_vec(Camera *temp, vec3* position/*=_POSITION*/, vec3* up/*_UP*/, float yaw/*=YAW*/, float pitch/*=PITCH*/, float distance){
    glm_vec3_copy(_FRONT, temp->Front);
    glm_vec3_copy(*position, temp->Position);
    glm_vec3_copy(*up, temp->WorldUp);
    temp->MovementSpeed = SPEED;
    temp->MouseSensitivity = SENSITIVITY;
    temp->Zoom = ZOOM;
    temp->Yaw = 0;
    temp->Pitch = 0;
    temp->ProcessKeyboard=ProcessKeyboard;
    temp->ProcessMouseMovement=ProcessMouseMovement;
    temp->ProcessMouseScroll=ProcessMouseScroll;
    temp->updateCameraVectors=updateCameraVectors;
//    temp->updateCameraVectors(temp);
    glm_vec3_copy(*up, temp->Up);
    temp->GetViewMatrix=GetViewMatrix;
    temp->distance=distance;
}

//constructor with scalar values
void IniCam_scl(Camera *temp, float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch, float distance){
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
    temp->Yaw = 0;
    temp->Pitch = 0;
    temp->ProcessKeyboard=ProcessKeyboard;
    temp->ProcessMouseMovement=ProcessMouseMovement;
    temp->ProcessMouseScroll=ProcessMouseScroll;
    temp->updateCameraVectors=updateCameraVectors;
//    temp->updateCameraVectors(temp);
    glm_vec3_copy(temp->WorldUp, temp->Up);
    temp->GetViewMatrix=GetViewMatrix;
    temp->distance=distance;
}

void setTargetPos(Camera *cam, float *pos){
    vec3 temp;
    temp[0]=pos[0];
    temp[1]=pos[1];
    temp[2]=pos[2];
    glm_vec3_normalize(temp);
    debugvec3(CAMERA183, temp)
    glm_vec3_scale(temp, (cam->distance), cam->targetPosition);
    debugf(CAMERA187, cam->distance)
    debugvec3(CAMERA187, cam->targetPosition)
}

void cameraUpdate(Camera *cam, float *pos, int angle, float deltaTime){
    vec3 front,temp;
    debugvec3(CAMERA195, cam->Position)
    temp[0]=cam->targetPosition[0]-cam->Position[0];
    temp[1]=cam->targetPosition[1]-cam->Position[1];
    temp[2]=cam->targetPosition[2]-cam->Position[2];
    debugvec3(CAMERA198, temp)
    cam->Position[0]+=temp[0]*deltaTime;
    cam->Position[1]+=temp[1]*deltaTime;
    cam->Position[2]+=temp[2]*deltaTime;
    front[0]=-cam->Position[0];
    front[1]=-cam->Position[1];
    front[2]=-cam->Position[2];
    vec3 v;
    glm_vec3_normalize(front);
    glm_vec3_copy(front, cam->Front);
    glm_vec3_cross(cam->Front, cam->Up, v);
    glm_vec3_rotate(v, glm_rad(angle*deltaTime), front);
    glm_vec3_normalize(v);
    glm_vec3_copy(v, cam->Right);
    glm_vec3_cross(cam->Right, cam->Front, v);
    glm_vec3_normalize(v);
    glm_vec3_copy(v, cam->Up);
}
void updateDistance(Camera *cam){
    glm_normalize(cam->Position);
    glm_vec3_scale_as(cam->Position, (cam->distance), cam->Position);
//    glm_vec3_print(cam->Position, stdout);
//    printf("distance:%f\n",cam->distance);
}

#endif
