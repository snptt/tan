//
//  cube.h
//  op
//
//  Created by BoBo W on 2025/4/3.
//


#ifndef cube_H
#define cube_H
#include <glad/glad.h>
#include <cglm/cglm.h>
#include "CAMERA.h"
#define u(x) (x*unit)
#define unit 0.001f

#define rdf(x) 1.0f*(x), -1.0f*(x), 1.0f*(x)
#define rdfr(x,y) 1.0f*(y), -1.0f*(x), 1.0f*(x)
#define rdfd(x,y) 1.0f*(x), -1.0f*(y), 1.0f*(x)
#define rdff(x,y) 1.0f*(x), -1.0f*(x), 1.0f*(y)

#define rdb(x) 1.0f*(x), -1.0f*(x), -1.0f*(x)
#define rdbr(x,y) 1.0f*(y), -1.0f*(x), -1.0f*(x)
#define rdbd(x,y) 1.0f*(x), -1.0f*(y), -1.0f*(x)
#define rdbb(x,y) 1.0f*(x), -1.0f*(x), -1.0f*(y)

#define ruf(x) 1.0f*(x), 1.0f*(x), 1.0f*(x)
#define rufr(x,y) 1.0f*(y), 1.0f*(x), 1.0f*(x)
#define rufu(x,y) 1.0f*(x), 1.0f*(y), 1.0f*(x)
#define ruff(x,y) 1.0f*(x), 1.0f*(x), 1.0f*(y)

#define rub(x) 1.0f*(x), 1.0f*(x), -1.0f*(x)
#define rubr(x,y) 1.0f*(y), 1.0f*(x), -1.0f*(x)
#define rubu(x,y) 1.0f*(x), 1.0f*(y), -1.0f*(x)
#define rubb(x,y) 1.0f*(x), 1.0f*(x), -1.0f*(y)

#define lub(x) -1.0f*(x), 1.0f*(x), -1.0f*(x)
#define lubl(x,y) -1.0f*(y), 1.0f*(x), -1.0f*(x)
#define lubu(x,y) -1.0f*(x), 1.0f*(y), -1.0f*(x)
#define lubb(x,y) -1.0f*(x), 1.0f*(x), -1.0f*(y)

#define luf(x) -1.0f*(x), 1.0f*(x), 1.0f*(x)
#define lufl(x,y) -1.0f*(y), 1.0f*(x), 1.0f*(x)
#define lufu(x,y) -1.0f*(x), 1.0f*(y), 1.0f*(x)
#define luff(x,y) -1.0f*(x), 1.0f*(x), 1.0f*(y)

#define ldf(x) -1.0f*(x), -1.0f*(x), 1.0f*(x)
#define ldfl(x,y) -1.0f*(y), -1.0f*(x), 1.0f*(x)
#define ldfd(x,y) -1.0f*(x), -1.0f*(y), 1.0f*(x)
#define ldff(x,y) -1.0f*(x), -1.0f*(x), 1.0f*(y)

#define ldb(x) -1.0f*(x), -1.0f*(x), -1.0f*(x)
#define ldbl(x,y) -1.0f*(y), -1.0f*(x), -1.0f*(x)
#define ldbd(x,y) -1.0f*(x), -1.0f*(y), -1.0f*(x)
#define ldbb(x,y) -1.0f*(x), -1.0f*(x), -1.0f*(y)

#define normr 1.0f, 0.0f, 0.0f
#define norml -1.0f,0.0f,0.0f
#define normu 0.0f,1.0f,0.0f
#define normd 0.0f,-1.0f,0.0f
#define normf 0.0f,0.0f,1.0f
#define normb 0.0f,0.0f,-1.0f

#define cubeColor 0.03f,0.6f,0.36f,1.0f

#define _textCoordsP1 -5.0f,-5.0f
#define _textCoordsP2 5.0f,-5.0f
#define _textCoordsP4 -5.0f,5.0f
#define _textCoordsP3 5.0f,5.0f

#define _textCoordsP10 -5.0f,-5.0f
#define _textCoordsP20 5.0f,-5.0f
#define _textCoordsP40 -5.0f,10*MARGIN/2-5
#define _textCoordsP30 5.0f,10*MARGIN/2-5

const float SIZE=u(800),MARGIN=0.1;
const float SIZE_2 = SIZE/2.0;
vec3 cubePosition = {0.0f,0.0f,0.0f};

enum surFace{
    A,
    C,
    B,
    E,
    D,
    F,
    er
};

struct Cube{
    //定义时如u(800), 前面的数值应位于0-1000
    float size;
    //边缘宽度为占size的比例, 0-0.5
    float margin;
    float *vertices;
    vec3 *position;
};

struct Cube Cube;
struct Cube *cube=&Cube;

float _cubeVertices[]={
    rdfr(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normr,_textCoordsP1,
    rdbr(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normr,_textCoordsP2,
    rufr(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normr,_textCoordsP4,
    rdbr(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normr,_textCoordsP2,
    rubr(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normr,_textCoordsP3,
    rufr(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normr,_textCoordsP4,
    
    rdfd(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normd,_textCoordsP1,
    ldfd(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normd,_textCoordsP4,
    rdbd(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normd,_textCoordsP2,
    rdbd(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normd,_textCoordsP2,
    ldfd(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normd,_textCoordsP4,
    ldbd(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normd,_textCoordsP3,
    
    rdff(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normf,_textCoordsP1,
    ruff(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normf,_textCoordsP4,
    ldff(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normf,_textCoordsP2,
    ldff(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normf,_textCoordsP2,
    ruff(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normf,_textCoordsP4,
    luff(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normf,_textCoordsP3,
    
    lubb(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normb,_textCoordsP1,
    rubb(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normb,_textCoordsP2,
    ldbb(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normb,_textCoordsP4,
    rubb(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normb,_textCoordsP2,
    rdbb(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normb,_textCoordsP3,
    ldbb(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normb,_textCoordsP4,
    
    lubl(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,norml,_textCoordsP1,
    ldbl(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,norml,_textCoordsP4,
    lufl(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,norml,_textCoordsP2,
    lufl(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,norml,_textCoordsP2,
    ldbl(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,norml,_textCoordsP4,
    ldfl(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,norml,_textCoordsP3,
    
    lubu(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normu,_textCoordsP1,
    lufu(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normu,_textCoordsP4,
    rubu(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normu,_textCoordsP2,
    rubu(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normu,_textCoordsP2,
    lufu(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normu,_textCoordsP4,
    rufu(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normu,_textCoordsP3,
    //r
    rdf(SIZE_2-SIZE*MARGIN),cubeColor,normf,_textCoordsP10,
    rufr(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normf,_textCoordsP30,
    ruf(SIZE_2-SIZE*MARGIN),cubeColor,normf,_textCoordsP20,
    rdf(SIZE_2-SIZE*MARGIN),cubeColor,normf,_textCoordsP10,
    rdfr(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normf,_textCoordsP40,
    rufr(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normf,_textCoordsP30,
    
    ruf(SIZE_2-SIZE*MARGIN),cubeColor,normu,_textCoordsP10,
    rufr(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normu,_textCoordsP40,
    rub(SIZE_2-SIZE*MARGIN),cubeColor,normu,_textCoordsP20,
    rufr(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normu,_textCoordsP40,
    rubr(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normu,_textCoordsP30,
    rub(SIZE_2-SIZE*MARGIN),cubeColor,normu,_textCoordsP20,
    
    rdb(SIZE_2-SIZE*MARGIN),cubeColor,normb,_textCoordsP10,
    rub(SIZE_2-SIZE*MARGIN),cubeColor,normb,_textCoordsP20,
    rubr(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normb,_textCoordsP30,
    rdb(SIZE_2-SIZE*MARGIN),cubeColor,normb,_textCoordsP10,
    rubr(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normb,_textCoordsP30,
    rdbr(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normb,_textCoordsP40,
    
    rdb(SIZE_2-SIZE*MARGIN),cubeColor,normd,_textCoordsP10,
    rdfr(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normd,_textCoordsP30,
    rdf(SIZE_2-SIZE*MARGIN),cubeColor,normd,_textCoordsP20,
    rdb(SIZE_2-SIZE*MARGIN),cubeColor,normd,_textCoordsP10,
    rdbr(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normd,_textCoordsP40,
    rdfr(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normd,_textCoordsP30,
    //d
    rdb(SIZE_2-SIZE*MARGIN),cubeColor,normb,_textCoordsP10,
    ldbd(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normb,_textCoordsP30,
    ldb(SIZE_2-SIZE*MARGIN),cubeColor,normb,_textCoordsP20,
    rdb(SIZE_2-SIZE*MARGIN),cubeColor,normb,_textCoordsP10,
    rdbd(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normb,_textCoordsP40,
    ldbd(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normb,_textCoordsP30,
    
    rdb(SIZE_2-SIZE*MARGIN),cubeColor,normr,_textCoordsP10,
    rdf(SIZE_2-SIZE*MARGIN),cubeColor,normr,_textCoordsP20,
    rdfd(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normr,_textCoordsP30,
    rdb(SIZE_2-SIZE*MARGIN),cubeColor,normr,_textCoordsP10,
    rdfd(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normr,_textCoordsP30,
    rdbd(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normr,_textCoordsP40,
    
    rdf(SIZE_2-SIZE*MARGIN),cubeColor,normf,_textCoordsP10,
    ldf(SIZE_2-SIZE*MARGIN),cubeColor,normf,_textCoordsP20,
    ldfd(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normf,_textCoordsP30,
    rdf(SIZE_2-SIZE*MARGIN),cubeColor,normf,_textCoordsP10,
    ldfd(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normf,_textCoordsP30,
    rdfd(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normf,_textCoordsP40,
    
    ldf(SIZE_2-SIZE*MARGIN),cubeColor,norml,_textCoordsP10,
    ldb(SIZE_2-SIZE*MARGIN),cubeColor,norml,_textCoordsP20,
    ldbd(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,norml,_textCoordsP30,
    ldf(SIZE_2-SIZE*MARGIN),cubeColor,norml,_textCoordsP10,
    ldbd(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,norml,_textCoordsP30,
    ldfd(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,norml,_textCoordsP40,
    //f
    ldf(SIZE_2-SIZE*MARGIN),cubeColor,normd,_textCoordsP10,
    rdf(SIZE_2-SIZE*MARGIN),cubeColor,normd,_textCoordsP20,
    rdff(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normd,_textCoordsP30,
    ldf(SIZE_2-SIZE*MARGIN),cubeColor,normd,_textCoordsP10,
    rdff(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normd,_textCoordsP30,
    ldff(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normd,_textCoordsP40,
    
    ldf(SIZE_2-SIZE*MARGIN),cubeColor,norml,_textCoordsP10,
    luff(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,norml,_textCoordsP30,
    luf(SIZE_2-SIZE*MARGIN),cubeColor,norml,_textCoordsP20,
    ldf(SIZE_2-SIZE*MARGIN),cubeColor,norml,_textCoordsP10,
    ldff(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,norml,_textCoordsP40,
    luff(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,norml,_textCoordsP30,
    
    luf(SIZE_2-SIZE*MARGIN),cubeColor,normu,_textCoordsP10,
    ruff(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normu,_textCoordsP30,
    ruf(SIZE_2-SIZE*MARGIN),cubeColor,normu,_textCoordsP20,
    luf(SIZE_2-SIZE*MARGIN),cubeColor,normu,_textCoordsP10,
    luff(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normu,_textCoordsP40,
    ruff(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normu,_textCoordsP30,
    
    ruf(SIZE_2-SIZE*MARGIN),cubeColor,normr,_textCoordsP10,
    rdff(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normr,_textCoordsP30,
    rdf(SIZE_2-SIZE*MARGIN),cubeColor,normr,_textCoordsP20,
    ruf(SIZE_2-SIZE*MARGIN),cubeColor,normr,_textCoordsP10,
    ruff(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normr,_textCoordsP40,
    rdff(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normr,_textCoordsP30,
    //u
    ruf(SIZE_2-SIZE*MARGIN),cubeColor,normf,_textCoordsP10,
    lufu(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normf,_textCoordsP30,
    luf(SIZE_2-SIZE*MARGIN),cubeColor,normf,_textCoordsP20,
    ruf(SIZE_2-SIZE*MARGIN),cubeColor,normf,_textCoordsP10,
    rufu(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normf,_textCoordsP40,
    lufu(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normf,_textCoordsP30,
    
    ruf(SIZE_2-SIZE*MARGIN),cubeColor,normr,_textCoordsP10,
    rub(SIZE_2-SIZE*MARGIN),cubeColor,normr,_textCoordsP20,
    rubu(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normr,_textCoordsP30,
    ruf(SIZE_2-SIZE*MARGIN),cubeColor,normr,_textCoordsP10,
    rubu(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normr,_textCoordsP30,
    rufu(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normr,_textCoordsP40,
    
    rub(SIZE_2-SIZE*MARGIN),cubeColor,normb,_textCoordsP10,
    lub(SIZE_2-SIZE*MARGIN),cubeColor,normb,_textCoordsP20,
    lubu(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normb,_textCoordsP30,
    rub(SIZE_2-SIZE*MARGIN),cubeColor,normb,_textCoordsP10,
    lubu(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normb,_textCoordsP30,
    rubu(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normb,_textCoordsP40,
    
    lub(SIZE_2-SIZE*MARGIN),cubeColor,norml,_textCoordsP10,
    luf(SIZE_2-SIZE*MARGIN),cubeColor,norml,_textCoordsP20,
    lufu(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,norml,_textCoordsP30,
    lub(SIZE_2-SIZE*MARGIN),cubeColor,norml,_textCoordsP10,
    lufu(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,norml,_textCoordsP30,
    lubu(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,norml,_textCoordsP40,
    //b
    lub(SIZE_2-SIZE*MARGIN),cubeColor,normu,_textCoordsP10,
    rub(SIZE_2-SIZE*MARGIN),cubeColor,normu,_textCoordsP20,
    rubb(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normu,_textCoordsP30,
    lub(SIZE_2-SIZE*MARGIN),cubeColor,normu,_textCoordsP10,
    rubb(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normu,_textCoordsP30,
    lubb(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normu,_textCoordsP40,
    
    rub(SIZE_2-SIZE*MARGIN),cubeColor,normr,_textCoordsP10,
    rdb(SIZE_2-SIZE*MARGIN),cubeColor,normr,_textCoordsP20,
    rdbb(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normr,_textCoordsP30,
    rub(SIZE_2-SIZE*MARGIN),cubeColor,normr,_textCoordsP10,
    rdbb(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normr,_textCoordsP30,
    rubb(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normr,_textCoordsP40,
    
    ldb(SIZE_2-SIZE*MARGIN),cubeColor,normd,_textCoordsP10,
    rdbb(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normd,_textCoordsP30,
    rdb(SIZE_2-SIZE*MARGIN),cubeColor,normd,_textCoordsP20,
    ldb(SIZE_2-SIZE*MARGIN),cubeColor,normd,_textCoordsP10,
    ldbb(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normd,_textCoordsP40,
    rdbb(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normd,_textCoordsP30,
    
    lub(SIZE_2-SIZE*MARGIN),cubeColor,norml,_textCoordsP10,
    ldbb(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,norml,_textCoordsP30,
    ldb(SIZE_2-SIZE*MARGIN),cubeColor,norml,_textCoordsP20,
    lub(SIZE_2-SIZE*MARGIN),cubeColor,norml,_textCoordsP10,
    lubb(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,norml,_textCoordsP40,
    ldbb(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,norml,_textCoordsP30,
    //l
    ldb(SIZE_2-SIZE*MARGIN),cubeColor,normb,_textCoordsP10,
    lubl(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normb,_textCoordsP30,
    lub(SIZE_2-SIZE*MARGIN),cubeColor,normb,_textCoordsP20,
    ldb(SIZE_2-SIZE*MARGIN),cubeColor,normb,_textCoordsP10,
    ldbl(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normb,_textCoordsP40,
    lubl(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normb,_textCoordsP30,
    
    ldb(SIZE_2-SIZE*MARGIN),cubeColor,normd,_textCoordsP10,
    ldf(SIZE_2-SIZE*MARGIN),cubeColor,normd,_textCoordsP20,
    ldfl(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normd,_textCoordsP30,
    ldb(SIZE_2-SIZE*MARGIN),cubeColor,normd,_textCoordsP10,
    ldfl(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normd,_textCoordsP30,
    ldbl(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normd,_textCoordsP40,
    
    ldf(SIZE_2-SIZE*MARGIN),cubeColor,normf,_textCoordsP10,
    luf(SIZE_2-SIZE*MARGIN),cubeColor,normf,_textCoordsP20,
    lufl(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normf,_textCoordsP30,
    ldf(SIZE_2-SIZE*MARGIN),cubeColor,normf,_textCoordsP10,
    lufl(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normf,_textCoordsP30,
    ldfl(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normf,_textCoordsP40,
    
    lub(SIZE_2-SIZE*MARGIN),cubeColor,normu,_textCoordsP10,
    lufl(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normu,_textCoordsP30,
    luf(SIZE_2-SIZE*MARGIN),cubeColor,normu,_textCoordsP20,
    lub(SIZE_2-SIZE*MARGIN),cubeColor,normu,_textCoordsP10,
    lubl(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normu,_textCoordsP40,
    lufl(SIZE_2-SIZE*MARGIN,SIZE_2),cubeColor,normu,_textCoordsP30
};

void IniCub(struct Cube *cube){
    cube->size=SIZE;
    cube->margin=MARGIN;
    cube->vertices=_cubeVertices;
    cube->position=&cubePosition;
}

void setCubeMaterial(Shader *cubeShader, int diffuse_texture, int specular_texture, float shininess){
    cubeShader->use(cubeShader);
    cubeShader->setInt(cubeShader,"material.diffuse", diffuse_texture);
    cubeShader->setInt(cubeShader,"material.specular", specular_texture);
    cubeShader->setFloat(cubeShader,"material.shininess", 1);
}

void cubeDrawSetting(Shader *cubeShader, unsigned int cubeVAO, float *view, float *proj){
    mat4 cubeModel;
    glm_translate_make(cubeModel, cubePosition);
    cubeShader->use(cubeShader);
    vec4 color = {cubeColor};
    glBindVertexArray(cubeVAO);
    cubeShader->setMat4fv(cubeShader,"view",view);
    cubeShader->setMat4fv(cubeShader,"proj",proj);
    cubeShader->setMat4fv(cubeShader,"model",(float*)cubeModel);
    cubeShader->setVec4v(cubeShader,"ourColor",color[0],color[1],color[2],color[3]);
    glBindVertexArray(0);
}

void cubeUpdate(Shader *cubeShader, Camera *camera, float *proj, float offset, float offset2){
    mat4 view;
    camera->GetViewMatrix(camera, &view);
    cubeShader->setMat4fv(cubeShader, "view", (float*)view);
    cubeShader->setMat4fv(cubeShader,"proj",proj);
    cubeShader->setFloat(cubeShader,"offset",offset);
    cubeShader->setFloat(cubeShader,"offset2",offset2);
}

void cubeDraw(Shader *cubeShader, Camera *camera ,unsigned int cubeVAO, float *proj, float offset,float offset2){
    cubeShader->use(cubeShader);
    glBindVertexArray(cubeVAO);
    cubeUpdate(cubeShader, camera, proj, offset, offset2);
    glDrawArrays(GL_TRIANGLES, 0, 180);
    glBindVertexArray(0);
}

#endif
