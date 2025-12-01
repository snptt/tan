//
//  light.h
//  op
//
//  Created by BoBo W on 2025/4/21.
//
#ifndef LIGHT_H
#define LIGHT_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct dirLight{
    vec3 dir;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    GLuint depthMapFBO;
    GLuint depthMap;
    mat4 lightSpaceMatrix;
    int textureU;
};
struct spotLight{
    vec3 pos;
    vec3 dir;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float constant;
    float linear;
    float quadratic;
    float cutOff;
    float outerCutOff;
    GLuint depthMapFBO;
    GLuint depthMap;
    mat4 lightSpaceMatrix;
    int textureU;
};
struct dirLight dirLight;
struct spotLight spotLight;
void setLight(Shader *ourShader, Camera *camera){
    ourShader->use(ourShader);
    // directional light
    ourShader->setVec3f(ourShader,"dirLight.direction", dirLight.dir[0],dirLight.dir[1],dirLight.dir[2]);
    ourShader->setVec3f(ourShader,"dirLight.ambient", dirLight.ambient[0], dirLight.ambient[1],dirLight.ambient[2]);
    ourShader->setVec3f(ourShader,"dirLight.diffuse", dirLight.diffuse[0], dirLight.diffuse[1],dirLight.diffuse[2]);
    ourShader->setVec3f(ourShader,"dirLight.specular", dirLight.specular[0],dirLight.specular[1],dirLight.specular[2]);
    ourShader->setInt(ourShader,"dirLight.shadowMap",dirLight.textureU);
    
    // spotLight
    ourShader->setVec3f(ourShader,"spotLight.position", spotLight.pos[0],spotLight.pos[1],spotLight.pos[2]);
    ourShader->setVec3f(ourShader,"spotLight.direction", spotLight.dir[0],spotLight.dir[1],spotLight.dir[2]);
    ourShader->setVec3f(ourShader,"spotLight.ambient", spotLight.ambient[0],spotLight.ambient[1],spotLight.ambient[2]);
    ourShader->setVec3f(ourShader,"spotLight.diffuse", spotLight.diffuse[0],spotLight.diffuse[1],spotLight.diffuse[2]);
    ourShader->setVec3f(ourShader,"spotLight.specular",spotLight.specular[0],spotLight.specular[1],spotLight.specular[2]);
    ourShader->setFloat(ourShader,"spotLight.constant", spotLight.constant);
    ourShader->setFloat(ourShader,"spotLight.linear", spotLight.linear);
    ourShader->setFloat(ourShader,"spotLight.quadratic", spotLight.quadratic);
    ourShader->setFloat(ourShader,"spotLight.cutOff", spotLight.cutOff);
    ourShader->setFloat(ourShader,"spotLight.outerCutOff", spotLight.outerCutOff);
    ourShader->setInt(ourShader,"spotLight.shadowMap",spotLight.textureU);
    debugi(light61, spotLight.textureU)
}
void updateLightShader(Shader *ourShader, Camera *camera){
    ourShader->use(ourShader);
    ourShader->setVec3f(ourShader,"viewPos",camera->Position[0],camera->Position[1],camera->Position[2]);
    
    // directional light
    ourShader->setVec3f(ourShader,"dirLight.direction", dirLight.dir[0],dirLight.dir[1],dirLight.dir[2]);
    ourShader->setMat4fv(ourShader,"lightSpaceMatrixD", dirLight.lightSpaceMatrix[0]);
    
    
    ourShader->setFloat(ourShader,"spotLight.cutOff", spotLight.cutOff);
    // spotLight
    ourShader->setVec3f(ourShader,"spotLight.position", spotLight.pos[0],spotLight.pos[1],spotLight.pos[2]);
    ourShader->setVec3f(ourShader,"spotLight.direction", spotLight.dir[0],spotLight.dir[1],spotLight.dir[2]);
    ourShader->setMat4fv(ourShader,"lightSpaceMatrixS", spotLight.lightSpaceMatrix[0]);
    ourShader->setVec3f(ourShader,"spotLight.specular",spotLight.specular[0],spotLight.specular[1],spotLight.specular[2]);
    ourShader->setVec3f(ourShader,"spotLight.ambient", spotLight.ambient[0],spotLight.ambient[1],spotLight.ambient[2]);
}
vec3 warmFilter = {1.0, 0.64, 0.0}; // 暖色滤镜（黄色）
vec3 coolFilter = {0.0, 0.1, 0.6};
vec3 noon = {0.9,0.2,0.0};
float d;
GLuint SHADOW_WIDTH = 2048, SHADOW_HEIGHT = 2048;
float kkk=10,kkk_max=45;
void mouseLight(float x, float y){
    spotLight.pos[0]=x;
    spotLight.pos[1]=y;
//    printf("x:%f,y:%f\n",x,y);
}
void updateLight(Camera *camera, Shader *depthShader,Shader *depthShader_SR,unsigned int *VBO_model, unsigned int *VBO_shininess, unsigned int *VBO_diffuse, /*unsigned int *VBO_specular, int Snake_diffuse_textureU[3], int Rot_diffuse_textureU[3][3], int specular_textureU[3],*/unsigned int *VAO_SR_depth,bool *f,unsigned int *VBO_model_f, unsigned int *VAO_F_depth, int *foodnum, unsigned int *cubeVAO_depth){
//    dirLight.dir[0]=0.0f;
//    dirLight.dir[1]=0.0f;
//    dirLight.dir[2]=-3.0f;
    
//    spotLight.pos[0]=1.0;
//    spotLight.pos[1]=1.0;
//    spotLight.pos[2]=1.0;
//    spotLight.dir[0]=-1.0;
//    spotLight.dir[1]=-1.0;
//    spotLight.dir[2]=-1.0;
    if(STATE<=0){
        spotLight.ambient[0]=-1.0f;
//        spotLight.pos[0]=0.01;
//        spotLight.pos[1]=0.01;
        spotLight.pos[2]=cube->size*(1-2*cube->margin)/4*3/2/tanf(glm_rad(80/2))+cube->size/2+0.8;
//        spotLight.dir[0]=-spotLight.pos[0];
//        spotLight.dir[1]=-spotLight.pos[1];
//        spotLight.dir[2]=-spotLight.pos[2];
        spotLight.dir[0]=0.0;
        spotLight.dir[1]=0.0;
        spotLight.dir[2]=-1.0;
    }else if(STATE==1){
        glm_vec3_scale_as(camera->Position, 1.5, spotLight.pos);
        glm_vec3_copy(camera->Front, spotLight.dir);
        debugvec3(light94, spotLight.pos)
        debugvec3(light94, camera->Position)
        
        vec3 t1,t2,t3;
        glm_normalize_to(spotLight.pos, t1);
        glm_normalize_to(dirLight.dir, t2);
        d = glm_vec3_dot(t1, t2);
        glm_vec3_scale(warmFilter, 0.7-0.25*d, t3);
        glm_vec3_scale(coolFilter, 0.7+0.25*d, spotLight.ambient);
        debugf(light101, d)
        spotLight.cutOff=cos(glm_rad(15.0f+d*9.0f));
    }
    
    //depth
    //dirLight
    mat4 lightProjection, lightView;
    GLfloat near_plane = 0.1f, far_plane = 20.0f;
    glm_ortho(-1.0f, 1.0f, -1.0f, 1.0f, near_plane, far_plane, lightProjection);
    //lightProjection = glm::perspective(45.0f, (GLfloat)SHADOW_WIDTH / (GLfloat)SHADOW_HEIGHT, near_plane, far_plane); // Note that if you use a perspective projection matrix you'll have to change the light position as the current light position isn't enough to reflect the whole scene.
    vec3 temp={-dirLight.dir[0]*3,-dirLight.dir[1],-dirLight.dir[2]*3},temp2,left,up={0.0f,1.0f,0.0f};
    glm_cross(up, dirLight.dir, left);
    glm_cross(dirLight.dir, left, temp2);
    glm_lookat(temp, cubePosition, temp2, lightView);
    glm_mat4_mul(lightProjection, lightView, dirLight.lightSpaceMatrix);
    depthShader_SR->use(depthShader_SR);
    depthShader_SR->setMat4fv(depthShader_SR,"lightSpaceMatrix",dirLight.lightSpaceMatrix[0]);
    glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
    glBindFramebuffer(GL_FRAMEBUFFER, dirLight.depthMapFBO);
    glClear(GL_DEPTH_BUFFER_BIT);
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindVertexArray(*VAO_F_depth);
    int t=updateVBO_F(VBO_model_f);
    if(t!=-1)*foodnum=t;
    glDrawArraysInstanced(GL_TRIANGLES, 0, 36, *foodnum);
    int num = countingSR();
    glBindVertexArray(*VAO_SR_depth);
    updateVBO_SR(VBO_model, VBO_shininess, VBO_diffuse,/* VBO_specular, Snake_diffuse_textureU, Rot_diffuse_textureU, specular_textureU,*/ f);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 36, num);
//    mat4 test_v,test_p;
//    camera->GetViewMatrix(camera,&test_v);
//    if(!Orth)glm_perspective(glm_rad(45.0f), (float)800/(float)600, 0.1f, 100.0f, test_p);
//    else glm_ortho(-cube->size/2+cube->margin, cube->size/2-cube->margin, (-cube->size/2+cube->margin)/4*3, (cube->size/2-cube->margin)/4*3, -100.0f, 100.0f, test_p);
//    glm_mat4_mul(test_p,test_v,dirLight.lightSpaceMatrix);
    depthShader->use(depthShader);
    depthShader->setMat4fv(depthShader,"lightSpaceMatrix",dirLight.lightSpaceMatrix[0]);
    glBindVertexArray(*cubeVAO_depth);
    mat4 cubeModel;
    glm_translate_make(cubeModel, cubePosition);
    depthShader->setMat4fv(depthShader,"model",(float*)cubeModel);
    glDrawArrays(GL_TRIANGLES, 0, 180);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
    //spotLight
//    if((!Orth||STATE==-2)&&kkk<=kkk_max)glm_perspective(glm_rad(kkk), (GLfloat)SHADOW_WIDTH / (GLfloat)SHADOW_HEIGHT, near_plane, far_plane, lightProjection);
    if(Orth||STATE==-2){
//        glm_ortho(-1.0f, 1.0f, -1.0f, 1.0f, near_plane, far_plane, lightProjection);
        glm_perspective(80.f, (GLfloat)SHADOW_WIDTH / (GLfloat)SHADOW_HEIGHT, near_plane, far_plane, lightProjection);
    }else{
        glm_perspective(45.0f, (GLfloat)SHADOW_WIDTH / (GLfloat)SHADOW_HEIGHT, near_plane, far_plane, lightProjection);
    }
    glm_cross(up, spotLight.dir, left);
    glm_cross(spotLight.dir, left, temp2);
    glm_lookat(spotLight.pos, cubePosition, temp2, lightView);
    glm_mat4_mul(lightProjection, lightView, spotLight.lightSpaceMatrix);
    // - now render scene from light's point of view
    depthShader_SR->use(depthShader_SR);
    depthShader_SR->setMat4fv(depthShader_SR,"lightSpaceMatrix",spotLight.lightSpaceMatrix[0]);
    glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
    glBindFramebuffer(GL_FRAMEBUFFER, spotLight.depthMapFBO);
    glClear(GL_DEPTH_BUFFER_BIT);
    glBindVertexArray(*VAO_SR_depth);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 36, num);
    glBindVertexArray(*VAO_F_depth);
    if(STATE>=1)glDrawArraysInstanced(GL_TRIANGLES, 0, 36, *foodnum);
    
    depthShader->use(depthShader);
    depthShader->setMat4fv(depthShader,"lightSpaceMatrix",spotLight.lightSpaceMatrix[0]);
    glBindVertexArray(*cubeVAO_depth);
    glDrawArrays(GL_TRIANGLES, 0, 180);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void generateDepthTexture(GLuint *depthMapFBO, GLuint *depthMap, int textureUnit){
    //阴影
    glGenFramebuffers(1, depthMapFBO);
    glActiveTexture(GL_TEXTURE0+textureUnit);
    glGenTextures(1, depthMap);
    glBindTexture(GL_TEXTURE_2D, *depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    GLfloat borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

    glBindFramebuffer(GL_FRAMEBUFFER, *depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, *depthMap, 0);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)printf("Framebuffer not complete!\n");
    else printf("light162\n");
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void IniLight(Camera *camera, int depth_textureU_dir, int depth_textureU_spot){
    dirLight.dir[0]=cubePosition[0]-camera->Position[0];
    dirLight.dir[1]=cubePosition[1]-camera->Position[1];
    dirLight.dir[2]=cubePosition[2]-camera->Position[2];
    dirLight.ambient[0]=0.8f;
    dirLight.ambient[1]=0.8f;
    dirLight.ambient[2]=0.8f;
    dirLight.diffuse[0]=0.8f;
    dirLight.diffuse[1]=0.8f;
    dirLight.diffuse[2]=0.8f;
    dirLight.specular[0]=0.5f;
    dirLight.specular[1]=0.5f;
    dirLight.specular[2]=0.5f;
    dirLight.textureU=depth_textureU_dir;
    generateDepthTexture(&dirLight.depthMapFBO, &dirLight.depthMap, depth_textureU_dir);
    
    spotLight.pos[0]=camera->Position[0];
    spotLight.pos[1]=camera->Position[1];
    spotLight.pos[2]=camera->Position[2];
    spotLight.dir[0]=camera->Front[0];
    spotLight.dir[1]=camera->Front[1];
    spotLight.dir[2]=camera->Front[2];
    spotLight.ambient[0]=0.2f;
    spotLight.ambient[1]=0.2f;
    spotLight.ambient[2]=0.2f;
    spotLight.diffuse[0]=0.3f;
    spotLight.diffuse[1]=0.3f;
    spotLight.diffuse[2]=0.3f;
    spotLight.specular[0]=0.5f;
    spotLight.specular[1]=0.5f;
    spotLight.specular[2]=0.5f;
    spotLight.constant=1.0f;
    spotLight.linear=0.09f;
    spotLight.quadratic=0.032f;
    spotLight.cutOff=cos(glm_rad(14.5f));
    spotLight.outerCutOff=cos(glm_rad(25.0f));
    spotLight.textureU=depth_textureU_spot;
    generateDepthTexture(&spotLight.depthMapFBO, &spotLight.depthMap, depth_textureU_spot);
}


#endif
