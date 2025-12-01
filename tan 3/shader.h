//
//  Untitled.h
//  op
//
//  Created by BoBo W on 2025/3/29.
//

#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h> // 包含glad来获取所有的必须OpenGL头文件
#include <cglm/cglm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Shader{
    
    //程序ID
    unsigned int ID;
    
    void (*use)(struct Shader* p);
    
    void (*setBool)(struct Shader* p, char* const name, bool value);
    
    void (*setInt)(struct Shader* p, char* const name, int value);
    
    void (*set1iv)(struct Shader* p, char* const name, int num, int *value);
    
    void (*setFloat)(struct Shader* p, char* const name, float value);
    
    void (*checkCompileErrors)(unsigned int shader, char type);
    
    void (*setVec2fv)(struct Shader* p, char* const name, vec2* value);
    
    void (*setVec2f)(struct Shader* p, char* const name, float x, float y);
    // ------------------------------------------------------------------------
    void (*setVec3fv)(struct Shader* p, char* const name, vec3 *value);
    
    void (*setVec3f)(struct Shader* p, char* const name, float x, float y, float z);
    // ------------------------------------------------------------------------
    void (*setVec4fv)(struct Shader* p, char* const name, vec4 value);
    
    void (*setVec4v)(struct Shader* p, char* const name, float x, float y, float z, float w);
    // ------------------------------------------------------------------------
    void (*setMat2fv)(struct Shader* p, char* const name, mat2 *mat);
    // ------------------------------------------------------------------------
    void (*setMat3fv)(struct Shader* p, char* const name, float *mat);
    // ------------------------------------------------------------------------
    void (*setMat4fv)(struct Shader* p, char* const name, float *mat);
    
};

void use(struct Shader* p){
        glUseProgram(p->ID);
}

void setBool(struct Shader* p, char* const name, bool value){
    glUniform1i(glGetUniformLocation(p->ID, name), (int)value);
}

void setInt(struct Shader* p, char* const name, int value){
    glUniform1i(glGetUniformLocation(p->ID, name), value);
}

void set1iv(struct Shader* p, char* const name, int num, int *value){
    glUniform1iv(glGetUniformLocation(p->ID, name), num, value);
}

void setFloat(struct Shader* p, char* const name, float value){
    glUniform1f(glGetUniformLocation(p->ID, name), value);
}
// ------------------------------------------------------------------------
void setVec2fv(struct Shader* p, char* const name, vec2* value){
    glUniform2fv(glGetUniformLocation(p->ID, name), 1, *value);
}
void setVec2f(struct Shader* p, char* const name, float x, float y){
    glUniform2f(glGetUniformLocation(p->ID, name), x, y);
}
// ------------------------------------------------------------------------
void setVec3fv(struct Shader* p, char* const name, vec3* value){
    glUniform3fv(glGetUniformLocation(p->ID, name), 1, *value);
}
void setVec3f(struct Shader* p, char* const name, float x, float y, float z){
    glUniform3f(glGetUniformLocation(p->ID, name), x, y, z);
}
// ------------------------------------------------------------------------
void setVec4fv(struct Shader* p, char* const name, vec4 value){
    glUniform4fv(glGetUniformLocation(p->ID, name), 1, value);
}
void setVec4v(struct Shader* p, char* const name, float x, float y, float z, float w){
    glUniform4f(glGetUniformLocation(p->ID, name), x, y, z, w);
}
// ------------------------------------------------------------------------
void setMat2fv(struct Shader* p, char* const name, mat2 *mat){
    glUniformMatrix2fv(glGetUniformLocation(p->ID, name), 1, GL_FALSE, *mat[0]);
}
// ------------------------------------------------------------------------
void setMat3fv(struct Shader* p, char* const name, float *mat){
    glUniformMatrix3fv(glGetUniformLocation(p->ID, name), 1, GL_FALSE, mat);
}
// ------------------------------------------------------------------------
void setMat4fv(struct Shader* p, char* const name, float *mat){
    glUniformMatrix4fv(glGetUniformLocation(p->ID, name), 1, GL_FALSE, mat);
}

void checkCompileErrors(unsigned int shader, char type[])
    {
        int success;
        char infoLog[1024];
        if (strcmp(type,"PROGRAM"))
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                printf("ERROR::SHADER_COMPILATION_ERROR of type: %s\n%s\n -- --------------------------------------------------- -- ",type,infoLog);
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                printf("ERROR::PROGRAM_LINKING_ERROR of type: %s\n%s\n -- --------------------------------------------------- -- ",type,infoLog);
            }
        }
    }

typedef struct Shader Shader;

struct Shader IniSha(const char* vertexPath, const char* fragmentPath){
    
    //读取着色器代码
    FILE *vShaderFile = NULL;
    FILE *fShaderFile = NULL;
    
    char *vertexCode,*fragmentCode;
    
    vShaderFile = fopen(vertexPath,"rb");
    fShaderFile = fopen(fragmentPath,"rb");
    if (vShaderFile == NULL || fShaderFile == NULL){
            perror("ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ");
            exit(1);
    }
    fseek(vShaderFile,0,SEEK_END);
    fseek(fShaderFile,0,SEEK_END);
    long vLength = ftell(vShaderFile);
    long fLength = ftell(fShaderFile);
    vertexCode = (char*)malloc((vLength+1)*sizeof(char));
    fragmentCode = (char*)malloc((fLength+1)*sizeof(char));
    rewind(vShaderFile);
    rewind(fShaderFile);
    vLength=fread(vertexCode,1,vLength,vShaderFile);
    fLength=fread(fragmentCode,1,fLength,fShaderFile);
    vertexCode[vLength]='\0';
    fragmentCode[fLength]='\0';
    fclose(vShaderFile);
    fclose(fShaderFile);
    
    const char* vc = vertexCode,*fc = fragmentCode;
    
    //编译着色器
    unsigned int vertex, fragment;
    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vc, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");
    // fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fc, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");
    // shader Program
    unsigned int ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");
    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    
    free(vertexCode);
    free(fragmentCode);
    
    struct Shader temp;
    temp.ID = ID;
    temp.use=use;
    temp.setBool=setBool;
    temp.setInt=setInt;
    temp.set1iv=set1iv;
    temp.setFloat=setFloat;
    temp.setVec2f=setVec2f;
    temp.setVec3f=setVec3f;
    temp.setVec4v=setVec4v;
    temp.setMat2fv=setMat2fv;
    temp.setMat3fv=setMat3fv;
    temp.setMat4fv=setMat4fv;
    return temp;
    
}

/*
 着色器的创建方法:
 Shader ourShader=IniSha("path/to/shaders/shader.vs", "path/to/shaders/shader.fs");
 ourShader.use(&ourShader);
 ourShader.setFloat(&ourShader, "someUniform", 1.0f);
 */


#endif
