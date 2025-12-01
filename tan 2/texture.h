//
//  texture.h
//  op
//
//  Created by BoBo W on 2025/4/21.
//
#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"
#define geterro(x) //printf("glGetErro"#x" %d\n",glad_glGetError());

void load_texture(unsigned int *texture, const char *path, const int WRAP_S, const int WRAP_T, const int MIN_FILTER, const int MAG_FILTER, int textureUnit){
    glGenTextures(1, texture);
    //激活纹理单元之后，接下来的glBindTexture函数调用会绑定这个纹理到当前激活的纹理单元，纹理单元GL_TEXTURE0默认总是被激活
    glActiveTexture(GL_TEXTURE0+textureUnit);
    glBindTexture(GL_TEXTURE_2D, *texture);
    // 为当前绑定的纹理对象设置环绕、过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, WRAP_S);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, WRAP_T);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, MIN_FILTER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, MAG_FILTER);
    // 加载并生成纹理
    int width, height, nrChannels;
    unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
    GLenum format = GL_RGB;
            if (nrChannels == 4) {
                format = GL_RGBA;
            } else if (nrChannels == 1) {
                format = GL_RED;
            }
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        printf("Failed to load texture Path:%s\n",path);
    }
    stbi_image_free(data);
}

//右左上下后前 path: left, right, up, down, end, face
void load_texture_cubeMap(unsigned int *texture, char (*path)[40], const int face_number, int textureUnit){
    glActiveTexture(GL_TEXTURE0+textureUnit);
    glGenTextures(1, texture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, *texture);
    int width, height, nrChannels;
    int widthE=-1, heightE=-1;
//    // 在代码中生成纯色纹理（例如红色）
//    unsigned char red[] = {0, 255, 0};
//    for (int i = 0; i < 6; i++) {
//        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, red);
//    }
    unsigned char *data;
    for(int i=0;i<face_number;i++){
        data = stbi_load(*(path+i), &width, &height, &nrChannels, 0);
        GLenum format = GL_RGB;
                if (nrChannels == 4) {
                    format = GL_RGBA;
                } else if (nrChannels == 1) {
                    format = GL_RED;
                }
        if(widthE==-1){
            widthE=width;
            heightE=height;
        }else if(widthE!=width||heightE!=height){
            printf("Invalid dimensions! Wrong width or height : %s\n",*(path+i));
        }
        if (data)
        {
            if(width!=height){
                printf("Invalid dimensions!: %s\n",*(path+i));
            }else{
                geterro(50)
                //            printf("%d %d",width,height);
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
                geterro(51)
            }
        }
        else
        {
            printf("Failed to load texture Path:%s\n",*(path+i));
        }
        stbi_image_free(data);
    }
    glGenerateMipmap(GL_TEXTURE_CUBE_MAP); // 生成Mipmap
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

#endif
