//
//  food.h
//  op
//
//  Created by BoBo W on 2025/4/7.
//

#ifndef food_H
#define food_H
#include <glad/glad.h>
#include <cglm/cglm.h>
#include "cube.h"
#include "snake.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define foodNum 12
#define foodScore u(70)
#define foodcolor 1.0f,1.0f,1.0f

float food_IniVer[] = {
    //b
    ruf(1),foodcolor,normf,
    ldf(1),foodcolor,normf,
    rdf(1),foodcolor,normf,
    ruf(1),foodcolor,normf,
    luf(1),foodcolor,normf,
    ldf(1),foodcolor,normf,
    //e
    lub(1),foodcolor,normb,
    rub(1),foodcolor,normb,
    ldb(1),foodcolor,normb,
    rub(1),foodcolor,normb,
    rdb(1),foodcolor,normb,
    ldb(1),foodcolor,normb,
    //a
    rdf(1),foodcolor,normr,
    rdb(1),foodcolor,normr,
    ruf(1),foodcolor,normr,
    rub(1),foodcolor,normr,
    ruf(1),foodcolor,normr,
    rdb(1),foodcolor,normr,
    //c
    lub(1),foodcolor,normu,
    luf(1),foodcolor,normu,
    rub(1),foodcolor,normu,
    rub(1),foodcolor,normu,
    luf(1),foodcolor,normu,
    ruf(1),foodcolor,normu,
    //f
    lub(1),foodcolor,norml,
    ldb(1),foodcolor,norml,
    luf(1),foodcolor,norml,
    luf(1),foodcolor,norml,
    ldb(1),foodcolor,norml,
    ldf(1),foodcolor,norml,
    //d
    rdf(1),foodcolor,normd,
    ldf(1),foodcolor,normd,
    rdb(1),foodcolor,normd,
    rdb(1),foodcolor,normd,
    ldf(1),foodcolor,normd,
    ldb(1),foodcolor,normd
};

float foodSize = u(20);
struct food{
    float size;
    float position;
    float advance;
    enum surFace direction;
    //以所在平面的法向量决定
    enum surFace up;
    float score;
    //valid==0将不会绘制
    bool mesa;
    bool valid;
    mat4 *mat;
};
struct food food[foodNum];
mat4 foodMat[foodNum];
bool foodBe[foodNum];
bool refresh=1;

void getMatFood(struct food *f){
//    vec3 transU,transL,transF;
//    transU[0] = _norVec[f->up][0];
//    transU[1] = _norVec[f->up][1];
//    transU[2] = _norVec[f->up][2];
//    glm_translate_make(*(f->mat), cubePosition);
//    glm_vec3_scale(transU, (cube->size/2+f->size/2), transU);
//    glm_translate(*(f->mat), transU);
//    transL[0] = _norVec[map[f->up][f->direction]][0];
//    transL[1] = _norVec[map[f->up][f->direction]][1];
//    transL[2] = _norVec[map[f->up][f->direction]][2];
//    glm_vec3_scale(transL, (cube->size*(0.5-f->position)), transL);
//    glm_translate(*(f->mat), transL);
//    transF[0] = _norVec[f->direction][0];
//    transF[1] = _norVec[f->direction][1];
//    transF[2] = _norVec[f->direction][2];
//    glm_vec3_scale(transF, (cube->size*(0.5-f->advance)-f->size/2), transF);
//    glm_translate(*(f->mat), transF);
//    //大小缩放
//    vec3 sclW={1.0f,1.0f,1.0f};
//    glm_vec3_scale(sclW, f->size, sclW);
//    glm_scale(*(f->mat), sclW);
    getTrans1Mat(f->up, map[f->up][f->direction], f->size, f->size, f->advance, f->position, f->mesa, f->mat);
    getTrans2Mat(f->mat, f->direction, f->size, f->advance, f->mat);
}

void eatTest(struct snakeHead *s, struct food *f){
    if(!f->valid)return;
    float temp = distanceMeasure(f->up, f->direction, f->position, f->advance, D(f->size), D(f->size), f->mesa, s->up, s->direction, s->position, s->advance, s->width, s->mesa);
    if(temp>0&&s->advance_neareatFood<temp){
        s->advance_neareatFood = temp;
        s->nearestFood=f;
    }
}

void robotEatTest(struct robot *s, struct food *f){
    if(!f->valid)return;
    float temp = distanceMeasure(f->up, f->direction, f->position, f->advance, D(f->size), D(f->size), 1, s->up, s->direction, s->position, s->advance, s->width, s->mesa);
    if(temp>0&&s->advance_neareatFood<temp){
        s->advance_neareatFood = temp;
        s->nearestFood=f;
    }
}

//f==NULL 检查全部
void robotFindNearestfood(struct robot *s){
    if(s==NULL)return;
    s->advance_neareatFood=-1;
    s->nearestFood=NULL;
    for(int i=0;i<foodNum;i++){
        robotEatTest(s, &food[i]);
    }
}


//f==NULL 检查全部
void findNearestfood(struct snakeHead *s){
    s->advance_neareatFood=-1;
    s->nearestFood=NULL;
    for(int i=0;i<foodNum;i++){
        eatTest(s, &food[i]);
    }
}

//检测两个物体是否重叠
bool overLap(enum surFace u1, enum surFace d1, float length1, float width1, float a1, float p1, enum surFace u2, enum surFace d2, float length2, float width2, float a2, float p2){
    if(u1!=u2) return 0;
    float w1=width1/ cube->size/2;
    float l1=length1/ cube->size;
    float w2=width2/ cube->size /2;
    float l2=length2/ cube->size;
    if(d2==d1){
        if(fabs(p1-p2)<=w2+w1 && (a1+l1>=a2&&a1<=a2+l2)){
            return 1;
        }
    }
    if(d2==5-d1){
        if(fabs(p1-p2)<=w1+w2 && 1-a1-a2<=l1+l2){
            return 1;
        }
    }
    if(d2==map[u1][d1]){
        if(a1+l1>=1-p2-w2 && a1<=1-p2+w2 && a2<=p1+w1 && a2+l2>=p1-w1){
            return 1;
        }
    }
    if(d2==5-map[u1][d1]){
        if(a1<=p2+w2 && a1+l1>=p2-w2 && 1-a2>=p1-w1 && 1-a2-l2<=p1+w1){
            return 1;
        }
    }
    return 0;
}

//检测一个食物位置与snakeH或snakeB或snakeT或rot是否冲突, 0代表冲突
bool foodPositionTest(float a, float p, float size, enum surFace foodUp, enum surFace foodDir){
//    return 1;
    //与snakeH
    struct snakeHead *H = &snakeH;
    while(H!=NULL){
        if(overLap(foodUp, foodDir, size, size, a, p, H->up, H->direction, getLength(H->length), getLength(H->width), H->advance, H->position)) return 0;
        
        //与body
        struct snakeBody *b=H->post;
        while (b!=NULL) {
            if(overLap(foodUp, foodDir, size, size, a, p, b->up, b->direction, getLength(b->length), getLength(b->width), b->advance, b->position)) return 0;
            b=b->post;
        }
        //与tail
        if(!H->noTail){
            struct snakeTail *T=H->tail;
            if(overLap(foodUp, foodDir, size, size, a, p, T->up, T->direction, getLength(T->length), getLength(T->width), T->advance, T->position)) return 0;
        }
        H=H->others;
    }
    //与rot
    struct rot *r = rotHandle->post;
    while(r!=NULL){
        if(overLap(foodUp, foodDir, size, size, a, p, r->up, r->direction, getLength(r->length), getLength(r->width), r->advance, r->position)) return 0;
        r=r->post;
    }
    return 1;
}

//food只出现在高台上
void foodRefresh(struct food *f){
    refresh=1;
    f->valid=0;
    f->mesa=1;
//    srand((unsigned)time(NULL));
    int asf = rand() % 6;
    f->size = foodSize;
    f->direction = asf;
//    srand((unsigned)time(NULL));
    asf = rand() % 6;
    while (asf==f->direction||asf==5-f->direction) {
//        srand((unsigned)time(NULL));
        asf = rand() % 6;
    }
    f->up = asf;
    debugi(food201, f->up)
    debugi(food201, f->direction)
    float a, p;
    int i=6;
    do{
//        srand((unsigned)time(NULL));
        a = rand() % 1001;
        a=a*0.001*(1-cube->margin*2)+cube->margin;
//        srand((unsigned)time(NULL));
        p = rand()%1001;
        p=p*0.001*(1-cube->margin*2)+cube->margin;
        debugf(food212, a)
        debugf(food213, p)
        if(foodPositionTest(a, p, f->size, f->up, f->position)){
            f->valid=1;
            break;
        }
        i--;
    }while(i>=0);
    f->advance = a;
    f->position = p;
    if(f->valid)getMatFood(f);
    f->score = foodScore;
}

//每一帧调用一次
void foodRefreshAll(void){
    for (int i=0; i<foodNum; i++) {
        if(food[i].valid==0) foodRefresh(&food[i]);
    }
}

void gotEaten(struct food *f){
    foodRefresh(f);
}

void eat(struct snakeHead *s){
    debugf(food239, s->advance_neareatFood)
    if(s->advance<=s->advance_neareatFood){
        if(s->eatRange>0){
            s->toBeElongation += D(s->nearestFood->score);
            //        s->eatRange=-s->width/2;
            s->score+=(s->nearestFood->score)*1000;
            gotEaten(s->nearestFood);
            s->velocity=_snakeV/(NEWHEADWIDTH(s)/_snakeWIDTH);
            struct snakeHead *temp=&snakeH;
            while (temp!=NULL) {
                findNearestfood(temp);
                temp=temp->others;
            }
        }else{
            struct food* f=s->nearestFood;
            if(f->mesa){
                if(s->direction==f->direction){
                    float p=f->position>s->position?s->position+(getLength(s->width+5)/2+f->size/2)/cube->size:s->position-(getLength(s->width+5)/2+f->size/2)/cube->size;
                    float a=f->advance-0.005;
                    if(p>1||p<0||a<0||a>1){
                        foodRefresh(f);
                        return;
                    }else{
                        if(p>1-cube->margin||p<cube->margin||a<cube->margin)f->mesa=0;
                        f->position=p;
                        f->advance=a;
                    }
                }else if(s->direction==5-f->direction){
                    float p=f->position>1-s->position?1-s->position+(getLength(s->width+5)/2+f->size/2+5)/cube->size:1-s->position-(getLength(s->width+5)/2+f->size/2)/cube->size;
                    float a=f->advance+0.005;
                    if(p>1||p<0||a<0||a>1){
                        foodRefresh(f);
                        return;
                    }else{
                        if(p>1-cube->margin||p<cube->margin||a>1-cube->margin)f->mesa=0;
                        f->position=p;
                        f->advance=a;
                    }
                }else if(f->direction==s->dirLEFT){
                    float a=(f->advance+f->size/2/cube->size>s->position)?s->position+(getLength(s->width+5)/2)/cube->size:s->position-(getLength(s->width+5)/2+f->size)/cube->size;
                    float p=f->position+0.005;
                    if(p>1||p<0||a<0||a>1){
                        foodRefresh(f);
                        return;
                    }else{
                        if(p>1-cube->margin||a>1-cube->margin||a<cube->margin)f->mesa=0;
                        f->position=p;
                        f->advance=a;
                    }
                }else if(f->direction==s->dirRIGHT){
                    float a=(f->advance+f->size/2/cube->size>1-s->position)?1-s->position+(getLength(s->width+5)/2)/cube->size:1-s->position-(getLength(s->width+5)/2+f->size)/cube->size;
                    float p=f->position-0.005;
                    if(p>1||p<0||a<0||a>1){
                        foodRefresh(f);
                        return;
                    }else{
                        if(p>1-cube->margin||p<cube->margin||a>1-cube->margin)f->mesa=0;
                        f->position=p;
                        f->advance=a;
                    }
                }
                getMatFood(f);
                refresh=1;
            }else{
                foodRefresh(f);
            }
        }
    }
}

void foodIni(void){
    debug(food247)
    srand((unsigned)time(NULL));
    for(int i=0;i<foodNum;i++){
        food[i].mat=&foodMat[i];
        foodRefresh(&food[i]);
        debugi(food251 food No., i)
        debugi(valid:, food[i].valid)
    }
}

void generateVAOVBO_F(unsigned int *VBO_Ver, unsigned int *VBO_model, unsigned int *VAO_F, int MAX){
    glGenVertexArrays(1, VAO_F);
    glGenBuffers(1, VBO_Ver);
    glGenBuffers(1, VBO_model);
    glBindBuffer(GL_ARRAY_BUFFER, *VBO_Ver);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(snake_IniVer)+(sizeof(mat4)+sizeof(int)*2+sizeof(float))*Max, NULL, GL_STREAM_DRAW);
//    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(snake_IniVer), snake_IniVer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(food_IniVer), food_IniVer, GL_STATIC_DRAW);
    //model
    glBindBuffer(GL_ARRAY_BUFFER, *VBO_model);
    glBufferData(GL_ARRAY_BUFFER, sizeof(mat4)*MAX, NULL, GL_DYNAMIC_DRAW);
    glBindVertexArray(*VAO_F);
    glBindBuffer(GL_ARRAY_BUFFER, *VBO_Ver);
    //位置属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
    //颜色属性
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3*sizeof(float)));
    //法线
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6*sizeof(float)));
    //model
    glBindBuffer(GL_ARRAY_BUFFER, *VBO_model);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)0);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)(4*sizeof(float)));
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)(8*sizeof(float)));
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)(12*sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    glEnableVertexAttribArray(4);
    glEnableVertexAttribArray(5);
    glEnableVertexAttribArray(6);
    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);
    glVertexAttribDivisor(6, 1);
    glBindVertexArray(0);
}
void generateVAOVBO_F_forDepth(unsigned int *VBO_Ver, unsigned int *VBO_model, unsigned int *VAO_F, int MAX){
    glGenVertexArrays(1, VAO_F);
    glBindVertexArray(*VAO_F);
    glBindBuffer(GL_ARRAY_BUFFER, *VBO_Ver);
    //位置属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
    //model
    glBindBuffer(GL_ARRAY_BUFFER, *VBO_model);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)0);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)(4*sizeof(float)));
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)(8*sizeof(float)));
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)(12*sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    glEnableVertexAttribArray(4);
    glVertexAttribDivisor(1, 1);
    glVertexAttribDivisor(2, 1);
    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glBindVertexArray(0);
}

int updateVBO_F(unsigned int *VBO_model){
    if(refresh==0)return-1;
    refresh=0;
    glBindBuffer(GL_ARRAY_BUFFER, *VBO_model);
    mat4 *m=(mat4*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    int j=0;
    for(int i=0;i<foodNum;i++){
        if(food[i].valid){
            glm_mat4_copy(*(food[i].mat), m[j++]);
        }
    }
    glBindBuffer(GL_ARRAY_BUFFER, *VBO_model);
    glUnmapBuffer(GL_ARRAY_BUFFER);
    return j;
}

void drawF(Shader *shader, unsigned int *VBO_model, unsigned int *VAO_F, Camera *camera, mat4 *proj, int *num){
    shader->use(shader);
    glBindVertexArray(*VAO_F);
    mat4 view;
    camera->GetViewMatrix(camera, &view);
    shader->setMat4fv(shader, "view", (float *)view);
    shader->setMat4fv(shader,"proj",(float*)proj[0]);
    int temp=updateVBO_F(VBO_model);
    if(temp!=-1)*num=temp;
    glDrawArraysInstanced(GL_TRIANGLES, 0, 36, *num);
}

#endif

