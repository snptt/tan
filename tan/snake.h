//
//  snake.h
//  op
//
//  Created by BoBo W on 2025/4/3.
//

#ifndef snake_H
#define snake_H
#include <glad/glad.h>
#include <cglm/cglm.h>
#include "cube.h"
#include <math.h>
#include "texture.h"
#define snakecolor 1.0f,0.48f,0.0f,1.0f
#define snakeMax 200
#define dingdian 1000000.0
#define D(x) (x*dingdian)
#define _snakeWIDTH D(u(20))
#define _snakeV D(u(80))
#define decayT 100
#define NEWHEADWIDTH(h) (h->ID>=0? D((2.5*_snakeWIDTH/dingdian-1.5/(getTotalLength(h)/dingdian*10+1/_snakeWIDTH*dingdian))) : h->width)
#define _EatRange(x) ((x))
#define FragmentMax (int)ceil(cube->size*cube->size/getLength(_snakeWIDTH)/getLength(_snakeWIDTH)*6)
#define height(x) ((x)*0.6)

#ifndef debuging
#define debug(x) //printf(#x"\n");
#define debugi(x,y) //printf(#x#y" %d\n",y);
#define debugl(x,y) //printf(#x#y" %ld\n",y);
#define debugp(x,y) //printf(#x#y"%p%s\n",y,y==NULL?"NULL":"");
#define debugf(x,y) //printf(#x#y":%.12f\n",y);
#define debugmat4(x,y) //printf(#x#y":\n");\
glm_mat4_print(y, stdout);
#define debugmat3(x,y) //printf(#x#y":\n");\
glm_mat3_print(y, stdout);
#define debugvec3(x,y) //printf(#x#y":\n");\
glm_vec3_print(y, stdout);
#define debugSnakePos(y,x) //printf(#y#x" up:%c dir:%c adv:%.12f pos:%.12f len:%.12f wid:%.12f mesa:%d \n",enumtest[x->up],enumtest[x->direction],x->advance,x->position,getLength(x->length),getLength(x->width),x->mesa);
//#define geterro(x) \/\/printf("glGetErro"#x" %d\n",glad_glGetError());
#endif
#ifdef debuging
#define debug(x) printf(#x"\n");
#define debugi(x,y) printf(#x#y" %d\n",y);
#define debugl(x,y) printf(#x#y" %ld\n",y);
#define debugp(x,y) printf(#x#y"%p%s\n",y,y==NULL?"NULL":"");
#define debugf(x,y) printf(#x#y":%.12f\n",y);
#define debugmat4(x,y) printf(#x#y":\n");\
glm_mat4_print(y, stdout);
#define debugmat3(x,y) printf(#x#y":\n");\
glm_mat3_print(y, stdout);
#define debugvec3(x,y) printf(#x#y":\n");\
glm_vec3_print(y, stdout);
#define debugSnakePos(y,x) printf(#y#x" up:%c dir:%c adv:%.12f pos:%.12f len:%.12f wid:%.12f mesa:%d \n",enumtest[x->up],enumtest[x->direction],x->advance,x->position,getLength(x->length),getLength(x->width),x->mesa);
#define geterro(x) \/\/printf("glGetErro"#x" %d\n",glad_glGetError());
#endif

float fps=0.0f;
#define fpscon 5

//testing
char enumtest[7]={'A','C','B','E','D','F','e'};
bool pause=0;

bool pauseEvent=1;
bool RpauseEvent=0;
#define pausing(x) //if(x)pause=1;

#define text00 0.0f,0.0f
#define text10 1.0f,0.0f
#define text01 0.0f,1.0f
#define text11 1.0f,1.0f

mat4 test;

float snake_IniVer[]={
    //b
    ruf(1)/*,snakecolor*/,normf,
    ldf(1)/*,snakecolor*/,normf,
    rdf(1)/*,snakecolor*/,normf,
    ruf(1)/*,snakecolor*/,normf,
    luf(1)/*,snakecolor*/,normf,
    ldf(1)/*,snakecolor*/,normf,
    //e
    lub(1)/*,snakecolor*/,normb,
    rub(1)/*,snakecolor*/,normb,
    ldb(1)/*,snakecolor*/,normb,
    rub(1)/*,snakecolor*/,normb,
    rdb(1)/*,snakecolor*/,normb,
    ldb(1)/*,snakecolor*/,normb,
    //a
    rdf(1)/*,snakecolor*/,normr,
    rdb(1)/*,snakecolor*/,normr,
    ruf(1)/*,snakecolor*/,normr,
    rub(1)/*,snakecolor*/,normr,
    ruf(1)/*,snakecolor*/,normr,
    rdb(1)/*,snakecolor*/,normr,
    //c
    lub(1)/*,snakecolor*/,normu,
    luf(1)/*,snakecolor*/,normu,
    rub(1)/*,snakecolor*/,normu,
    rub(1)/*,snakecolor*/,normu,
    luf(1)/*,snakecolor*/,normu,
    ruf(1)/*,snakecolor*/,normu,
    //f
    lub(1)/*,snakecolor*/,norml,
    ldb(1)/*,snakecolor*/,norml,
    luf(1)/*,snakecolor*/,norml,
    luf(1)/*,snakecolor*/,norml,
    ldb(1)/*,snakecolor*/,norml,
    ldf(1)/*,snakecolor*/,norml,
    //d
    rdf(1)/*,snakecolor*/,normd,
    ldf(1)/*,snakecolor*/,normd,
    rdb(1)/*,snakecolor*/,normd,
    rdb(1)/*,snakecolor*/,normd,
    ldf(1)/*,snakecolor*/,normd,
    ldb(1)/*,snakecolor*/,normd
};

//六个平面的法向量
const vec3 _norVec[6] = {
    {1.0f,0.0f,0.0f},//a-right
    {0.0f,1.0f,0.0f},//c-up
    {0.0f,0.0f,1.0f},//b-front
    {0.0f,0.0f,-1.0f},//e-back
    {0.0f,-1.0f,0.0f},//d-down
    {-1.0f,0.0f,0.0f}//f-left
};
const vec3 neg_norVec[6] = {
    {0.0f,1.0f,1.0f},//a-right
    {1.0f,0.0f,1.0f},//c-up
    {1.0f,1.0f,0.0f},//b-front
    {1.0f,1.0f,0.0f},//e-back
    {1.0f,0.0f,1.0f},//d-down
    {0.0f,1.0f,1.0f}//f-left
};
const vec3 abs_norVec[6] = {
    {1.0f,0.0f,0.0f},//a-right
    {0.0f,1.0f,0.0f},//c-up
    {0.0f,0.0f,1.0f},//b-front
    {0.0f,0.0f,1.0f},//e-back
    {0.0f,1.0f,0.0f},//d-down
    {1.0f,0.0f,0.0f}//f-left
};
enum surFace map[6][6]={
    {er,B,D,C,E,er},//A 以[A]为顶[某]元素左侧的方向
    {E,er,A,F,er,B},//C
    {C,F,er,er,A,D},//B
    {D,A,er,er,F,C},//E
    {B,er,F,A,er,E},//D
    {er,E,C,D,B,er}//f
};

enum turn{
    turnLEFT,
    turnRIGHT
};

//mat4 snakeMatTemp[snakeMax];
//bool snakeMatUsed[snakeMax];
mat4 snakeTrans1H, snakeTransFinalH;
mat4 snakeTrans1T, snakeTransFinalT;
int snakeNum=0;

double NPC_startTime[5], NPC_endTime[5], NPC_endLength[5];
struct NPC *Npc[5];

float velocity=0;

float getLength(long length){
    return length/dingdian;
}

//每次新生成(转弯、到新的平面上)的头的width为_snakeWIDTH+(_snakeWIDTH-1/(getTotalLength()+1/_snakeWIDTH)
struct snakeHead{
    long eatProcess[3];
    //绝对数值
    long width;
    long length;
    long velocity;
    
    long eatRange;
    
    long toBeElongation;
    long score;
    //中心位于平面左右的相对距离, 0.0f-1.0f
    float position;
    //到前面的比例, 0.0f,1.0f
    float advance;
    
    
    float advance_end;
    float advance_neareatFood;
    //以面对的平面的法向量决定
    enum surFace direction;
    //以所在平面的法向量决定
    enum surFace up;
    //LEFT: map[.up][.direction]
    enum surFace dirLEFT;
    enum surFace dirRIGHT;
    
    struct snakeBody *post;
    struct snakeTail *tail;
    
    int counter;
    
    float eatAdv;
    
    //按下空格后=width/2, 在eatProcess中减小; 如果advance+width/2超出边界, 设为advance到边界的距离. 每次触发吞咽后设为-width/2, 随update+=movement, <0时禁用eat.
    
    struct food *nearestFood;
    struct snakeHead* advEndH;
    struct snakeBody* advEndB;
    struct snakeTail* advEndT;
    struct rot* advEndDy;
    
//    //ID==0代表是其他小蛇; >0代表是角色
    int ID;
    struct snakeHead *others;
    //初始化其他小蛇时要分配头尾结构体的内存, 和头尾各两个mat的内存
    int bodyNum;
    
    bool mesa:1;

    bool snakeAlive:1;
    
    //==1时意味着没有尾, 此时蛇只有头
    bool noTail:1;
    
    bool stall:1;

    mat4 *headMat;
    mat4 *headTrans1Mat;
};

struct snakeBody{
    //绝对数值
    long width;
    long length;
    //中心位于平面左右的相对距离, 0.0f-1.0f
    float position;
    //到前面的比例, 0.0f,1.0f
    float advance;
    //以面对的平面的法向量决定
    bool mesa;
    
    enum surFace direction;
    //以所在平面的法向量决定
    enum surFace up;
    
    struct snakeBody *pre;
    struct snakeBody *post;
    struct snakeHead *head;
    
    mat4 *snakeMat;
};

struct snakeTail{
    //绝对数值
    long width;
    long length;
    //中心位于平面左右的相对距离, 0.0f-1.0f
    float position;
    //到前面的比例, 0.0f,1.0f
    float advance;
    
    bool mesa;
    //以面对的平面的法向量决定
    enum surFace direction;
    //以所在平面的法向量决定
    enum surFace up;
    
    struct snakeBody *pre;
    struct snakeHead *head;
    
    bool stat;//toBeElongation不为0时, stat=1, 不再缩短
    
    mat4 *tailMat;
    mat4 *tailTran1Mat;
};

struct rot{
    //绝对数值
    long width,length;
    //中心位于平面左右的相对距离, 0.0f-1.0f
    float position;
    //到前面的比例, 0.0f,1.0f
    float advance;
    
    bool mesa;
    //以面对的平面的法向量决定
    enum surFace direction;
    //以所在平面的法向量决定
    enum surFace up;
    
    //0 head; 1 body; 2 tail
    int type;
    
    struct rot *pre;
    struct rot *post;
    
    // <=0为正常,对应蛇的ID, 1为腐烂第一阶段, 2为腐烂第二阶段
    int state;
    //倒计时 length/width*decayT+1
    long clock;
    
    mat4 *rotMat;
};

//作为所有rot的一个全局的“handle”
struct rot Handle;
struct rot *rotHandle=&Handle;

struct snakeHead snakeH;
//struct snakeBody snakeB[snakeMax];
//bool snakeUsed[snakeMax];
struct snakeTail snakeT;

double startTime,endTime;
long Score=0;
long endLength;

//vec3 sclW={1.0f,1.0f,0.0f},sclL={0.0f,0.0f,1.0f};

//不涉及前后位置和长度
void transScaleMake(float *v, float value){
    vec3 temp={0,0,0};
    if(v[0]==0)temp[0]=1.0f;
    if(v[1]==0)temp[1]=1.0f;
    if(v[2]==0)temp[2]=1.0f;
    v[0]=value*v[0]+temp[0];
    v[1]=value*v[1]+temp[1];
    v[2]=value*v[2]+temp[2];
}

//不涉及前后位置和长度
void getTrans1Mat(enum surFace up, enum surFace dirLEFT, float width, float length, float advance, float position, bool mesa, mat4 *result){
    debug(getTrans1Mat)
    //将躯体移到适当位置; translate是右乘
    vec3 transU,transL;
    transU[0] = _norVec[up][0];
    transU[1] = _norVec[up][1];
    transU[2] = _norVec[up][2];
    glm_translate_make(*result, cubePosition);
    debugvec3(279, transU)
//    if(advance<(cube->margin)||advance>(1-cube->margin)||position<(cube->margin)||position>(1-cube->margin)){
    if(!mesa){
//        transMake(transU, ((cube->size/2.0*(1-cube->margin))+width/2));
        glm_vec3_scale(transU, ((cube->size*(0.5-cube->margin))+height(width)/2), transU);
        debug(277)
    }
    else{
//        transMake(transU, (cube->size/2+width/2));
        glm_vec3_scale(transU, (cube->size/2+height(width)/2), transU);
        debug(280)
    }
    debugvec3(285,transU)
    glm_translated(*result, transU);
    transL[0] = _norVec[dirLEFT][0];
    transL[1] = _norVec[dirLEFT][1];
    transL[2] = _norVec[dirLEFT][2];
//    transMake(transL, (cube->size*(0.5-position)));
    glm_vec3_scale(transL, (cube->size*(0.5-position)), transL);
    glm_translated(*result, transL);
    debugmat4(296,*result)
//    glm_mat4_mul(*result, facingMat4[up][map[dirLEFT][up]],*result);
    debugmat4(516, test)
    //粗细缩放
//    vec3 sclW={width/2,height(width)/2,1.0f};
    debugvec3(306, sclW)
    vec3 sclW={abs_norVec[dirLEFT][0]*width/2+neg_norVec[dirLEFT][0],abs_norVec[dirLEFT][1]*width/2+neg_norVec[dirLEFT][1],abs_norVec[dirLEFT][2]*width/2+neg_norVec[dirLEFT][2]},sclH={abs_norVec[up][0]*height(width)/2+neg_norVec[up][0],abs_norVec[up][1]*height(width)/2+neg_norVec[up][1],abs_norVec[up][2]*height(width)/2+neg_norVec[up][2]};
    glm_scale(*result, sclW);
    glm_scale(*result, sclH);
    debugmat4(307,*result)
}
void getTrans2Mat(mat4 *Trans1Mat, enum surFace direction, float length, float advance, mat4 *result){
    debugp(560, result)
    debug(getTrans2Mat)
    debugp(294Trans1Mat, Trans1Mat)
    //将躯体移到适当的前后位置; translated是右乘
    if(Trans1Mat!=NULL&&Trans1Mat!=result)glm_mat4_copy(*Trans1Mat, *result);
    vec3 transF;
    transF[0] = _norVec[direction][0];
    transF[1] = _norVec[direction][1];
    transF[2] = _norVec[direction][2];
//    transMake(transF, (cube->size*(0.5-advance)-length/2));
    glm_vec3_scale(transF, (cube->size*(0.5-advance)-length/2), transF);
    glm_translated(*result, transF);
    //debugmat4(373, *result)
    //长度缩放
    vec3 sclL={abs_norVec[direction][0]*length/2+neg_norVec[direction][0],abs_norVec[direction][1]*length/2+neg_norVec[direction][1],abs_norVec[direction][2]*length/2+neg_norVec[direction][2]};
    glm_scale(*result, sclL);
    debugmat4(381, *result)
}

void getFinalMat(enum surFace up, enum surFace direction, long width, long length, float advance, float position, bool mesa, mat4 *result){
    getTrans1Mat(up, map[up][direction], getLength(width), getLength(length), advance, position, mesa, result);
    getTrans2Mat(NULL, direction, getLength(length), advance, result);
}

void getTrans1MatH(struct snakeHead *s){
    getTrans1Mat(s->up, s->dirLEFT, getLength(s->width), getLength(s->length), s->advance, s->position, s->mesa, s->headTrans1Mat);
}
void getTrans2MatH(struct snakeHead *s){
    getTrans2Mat(s->headTrans1Mat, s->direction, getLength(s->length), s->advance, s->headMat);
}
void getTrans1MatT(struct snakeTail *s){
    enum surFace dirLEFT = map[s->up][s->direction];
    getTrans1Mat(s->up, dirLEFT, getLength(s->width), getLength(s->length), s->advance, s->position, s->mesa, s->tailTran1Mat);
}
void getTrans2MatT(struct snakeTail *s){
    getTrans2Mat(s->tailTran1Mat, s->direction, getLength(s->length), s->advance, s->tailMat);
}

void headMove(struct snakeHead *h, long movement){
    debug(headMove)
    if(!h->snakeAlive) return;
    if(h->eatRange<0){
        h->eatRange+=movement;
        if(h->eatRange>=0) h->eatRange=0;
    }
    if(h->eatRange<=0){
        if((!h->noTail)||((h->noTail)&&(h->tail->stat))){
            h->length+=movement;
        }
        h->advance-=getLength(movement)/ cube->size;
        debugp(339, h->headMat)
        getTrans2MatH(h);
        debugp(341, h->headMat)
    }
    
}
void tailMove(struct snakeTail *s, long movement){
    debug(tailMove)
    if(s->stat||!s->head->snakeAlive||s->head->noTail){
        if(s->stat)s->stat=0;
        return;
    }
    //float scal = 1.0f-movement/s->length;
    s->length-=movement;
    getTrans2MatT(s);
}
void bodyScal(struct snakeBody *s, float width_scal){
    s->width = s->width*width_scal;
    vec3 sclL={1.0*getLength(s->width),1.0*getLength(s->width),1.0};
    glm_scale(*(s->snakeMat), sclL);
}

long getTotalLength(struct snakeHead *s){
    long sum=s->length;
    if(!s->noTail){ sum+=s->tail->length;
        struct snakeBody *b=s->post;
        while (b!=NULL) {
            sum+=b->length;
            b=b->post;
        }
    }
    return sum+s->toBeElongation;
}

//实现蛇探头觅食的效果 static用于计数, 每次更新head的长、宽, 整个过程在pic帧内完成.
//[0]-lengthChange;[1]-initialLength;[2]initialWidth;
void eatProcess(struct snakeHead *s, int pic, long movement){
    debugi(556,pic)
    debugf(553, getLength(s->eatRange))
    debugf(553, getLength(s->eatProcess[0]))
    debugf(553, getLength(s->eatProcess[1]))
    debugf(553, getLength(s->eatProcess[2]))
    if(s->counter>=pic){
        s->eatRange=-(_EatRange(s->width));
        s->length=s->eatProcess[1];
        s->advance=s->eatAdv;
        s->width=s->eatProcess[2];
        s->counter=0;
        s->eatProcess[0]=0;
        s->eatProcess[1]=0;
        s->eatProcess[2]=0;
        s->eatAdv=0;
//        s->tail->length+=movement;
        return;
    }
    s->eatProcess[0]+=movement;
    if(s->counter==0){
        s->eatProcess[0]=0;
        s->eatProcess[1]=s->length;
        s->eatAdv=s->advance;
        s->eatProcess[2]=s->width;
    }
    s->counter++;
    if(s->counter<=pic/2){
        long temp = s->eatRange*0.5;
        s->length+=temp;
//        s->width=(double)s->eatProcess[1]/(double)s->length*s->eatProcess[2];
        s->eatRange-=temp;
        s->advance-=getLength(temp)/(cube->size);
        debugf(603,getLength(temp)/(cube->size))
        debugf(604,getLength(s->width))
//        pause=1;
//        float correct = s->eatRange /(pic*pic/4.0);
//        float temp=(s->counter)*(pic-s->counter)*correct;
//        s->length+=temp;
//        s->advance-=temp/(cube->size);
//        s->eatRange-=temp;
//        s->width=(s->eatProcess[3])*(s->eatProcess[1])/s->length;
    }else{
        float temp = (getLength(s->length+s->eatRange-s->eatProcess[0])+1)*movement;
        
        if(s->length+s->eatRange-s->eatProcess[0]-s->eatProcess[1]<0){
            s->eatRange=-(_EatRange(s->width));
            s->length=s->eatProcess[1];
            s->advance=s->eatAdv;
            s->width=s->eatProcess[2];
            s->counter=0;
            s->eatProcess[0]=0;
            s->eatProcess[1]=0;
            s->eatProcess[2]=0;
            s->eatAdv=0;
//            s->tail->length+=movement;
            getTrans1MatH(s);
            getTrans2MatH(s);
            return;
        }
        
        s->length-=temp;
//        s->width=(double)s->eatProcess[1]/(double)s->length*s->eatProcess[2];
        s->eatRange+=temp;
        s->advance+=getLength(temp)/(cube->size);
        
//        float correct = (s->length+s->eatRange-(s->eatProcess[0])-(s->eatProcess[1])) /(pic*pic/4.0);
//        float temp=correct-(s->counter)*(pic-s->counter)*correct;
//        s->length-=temp;
//        s->advance+=temp/(cube->size);
//        s->eatRange+=temp;
//        s->width=(s->eatProcess[3])*(s->eatProcess[1])/s->length;
    }
    getTrans1MatH(s);
    getTrans2MatH(s);
    debugf(593, (getLength(s->length)))
}

void snakeCrush(struct snakeHead *s);
//eat 更新nearestFood
void findNearestfood(struct snakeHead *s);
//检测有没有吃
void eat(struct snakeHead *s);

void iniBody(struct snakeBody *b, long width, long length, float position, float advance, bool mesa, enum surFace direction, enum surFace up, struct snakeBody *pre, struct snakeBody *post, struct snakeHead *head, bool allocMat, mat4 *mat, bool getMat){
    debug(iniBody)
    b->width=width;
    b->length=length;
    b->position=position;
    b->advance=advance;
    b->mesa=mesa;
    b->direction=direction;
    b->up=up;
    b->pre=pre;
    b->post=post;
    b->head=head;
    b->snakeMat=mat;
    if(allocMat&&mat==NULL){
        b->snakeMat=(mat4*)malloc(sizeof(mat4));
    }
    if(getMat&&b->snakeMat!=NULL){
        getFinalMat(up, direction, width, length, advance, position,mesa, b->snakeMat);
    }
}

void iniHead(struct snakeHead *H, int ID,long width, long length, float position, float advance, enum surFace direction, enum surFace up, bool mesa, float velocity,int bodyNum, struct snakeBody *post, struct snakeTail *tail, long eatRange, bool noTail, long toBeElongation, long score, bool allocMat, mat4 *TMat, mat4 *FMat, bool getMat){
    pausing(1)
    debug(iniHead)
    H->mesa=mesa;
    H->velocity=velocity;
    H->bodyNum=bodyNum;
    H->snakeAlive=1;
    H->width=width;
    H->length=length;
    H->position=position;
    H->advance=advance;
    H->advance_end=-1;
    H->advance_neareatFood=-1;
    H->direction=direction;
    H->up=up;
    H->dirLEFT=map[up][direction];
    H->dirRIGHT=5-H->dirLEFT;
    H->post=post;
    H->tail=tail;
    H->counter=0;
    H->eatProcess[0]=0;
    H->eatProcess[1]=0;
    H->eatProcess[2]=0;
    H->eatAdv=0;
    H->eatRange=eatRange;
    H->nearestFood=NULL;
    H->advEndB=NULL;
    H->advEndH=NULL;
    H->advEndT=NULL;
    H->advEndDy=NULL;
    H->ID=ID;
    H->others=H->others;
    H->noTail=noTail;
    H->toBeElongation=toBeElongation;
    H->stall=0;
    H->score=score;
    if(ID!=0){
        H->headMat=FMat;
        H->headTrans1Mat=TMat;
        if(allocMat&&TMat==NULL){
            H->headTrans1Mat=(mat4*)malloc(sizeof(mat4));
        }
        if(allocMat&&FMat==NULL){
            H->headMat=(mat4*)malloc(sizeof(mat4));
        }
    }else{
        H->headMat=&snakeTransFinalH;
        H->headTrans1Mat=&snakeTrans1H;
    }
    if(getMat&&H->headTrans1Mat!=NULL&&H->headMat!=NULL){
        getTrans1MatH(H);
        getTrans2MatH(H);
    }
}

void iniTail(struct snakeTail *T, long width, long length, float position, float advance, bool mesa, enum surFace direction, enum surFace up, struct snakeBody *pre, struct snakeHead *head, bool stat, bool allocMat, mat4 *TMat, mat4 *FMat, bool getMat){
    debug(iniTail)
    T->width=width;
    T->length=length;
    T->position=position;
    T->advance=advance;
    T->direction=direction;
    T->mesa=mesa;
    T->up=up;
    T->pre=pre;
    T->head=head;
    T->stat=stat;
    T->tailMat=FMat;
    T->tailTran1Mat=TMat;
    if(T->head->ID==0){
        T->tailMat=&snakeTransFinalT;
        T->tailTran1Mat=&snakeTrans1T;
    }
    if(allocMat&&TMat==NULL){
        T->tailTran1Mat=(mat4*)malloc(sizeof(mat4));
    }
    if(allocMat&&FMat==NULL){
        T->tailMat=(mat4*)malloc(sizeof(mat4));
    }
    if(getMat&&T->tailTran1Mat!=NULL&&T->tailMat!=NULL){
        getTrans1MatT(T);
        getTrans2MatT(T);
    }
    
}

//新head
void snakeExchangeH(struct snakeHead *s, long width, float position, float advance, enum surFace direction, enum surFace up, bool mesa){
    pausing(1)
    debug(snakeExchangeH)
    struct snakeBody *temp;
    getTrans1MatH(s);
    getTrans2MatH(s);
    if(s->noTail){
        temp=NULL;
        iniTail(s->tail, s->width, s->length, s->position, s->advance, s->mesa, s->direction, s->up, NULL, s, s->tail->stat, 1, s->tail->tailTran1Mat, s->tail->tailMat, 0);
        debug(508);
        glm_mat4_copy(*(s->headTrans1Mat), *(s->tail->tailTran1Mat));
        glm_mat4_copy(*(s->headMat), *(s->tail->tailMat));
        debugp(517, s->headMat)
        s->noTail=0;
    }else{
        if(s->post!=NULL){
            s->post->pre = (struct snakeBody * ) malloc(sizeof(struct snakeBody));
            struct snakeBody * b = s->post->pre;
            iniBody(b, s->width, s->length, s->position, s->advance, s->mesa, s->direction, s->up, NULL, s->post, s, 1, NULL, 0);
            temp = b;
            debug(517)
            glm_mat4_copy(*(s->headMat), *(b->snakeMat));
            s->bodyNum++;
        }else{
            s->post = (struct snakeBody * ) malloc(sizeof(struct snakeBody));
            struct snakeBody * b = s->post;
            temp = b;
            iniBody(b, s->width, s->length, s->position, s->advance, s->mesa, s->direction, s->up, NULL, NULL, s, 1, NULL, 0);
            debug(525)
            glm_mat4_copy(*(s->headMat), *(b->snakeMat));
            s->bodyNum++;
            s->tail->pre = b;
        }
    }
    iniHead(s, s->ID, width, 0, position, advance, direction, up, mesa, s->velocity, s->bodyNum, temp, s->tail, s->eatRange, 0, s->toBeElongation, s->score, 0, s->headTrans1Mat, s->headMat, 1);
    snakeCrush(s);
    findNearestfood(s);
}

//新尾
void snakeTailUpdate(struct snakeTail *T,int cornerTail){
    if(T->head->noTail)return;
    debug(snakeTailUpdate)
    struct snakeBody *b=T->pre;
    //平面上
    if(cornerTail==1){
        if(T->pre==NULL){
            if(T->head->width<=T->width){
                T->head->length+=T->length;
            }else{
                if(T->length-T->width<0){
                    T->head->length+=T->length;
                }else{
                    T->head->length+=T->width;
                    T->head->toBeElongation+=T->length-T->width;
                }
//                if(T->head->toBeElongation<0){
//                    debug(tobeelongation<0)
//                    snakeH.velocity=0;
//                }
            }
            T->head->noTail=1;
            return;
        }
        if(b->pre!=NULL){
            if(b->width<=T->width){
                iniTail(T, b->width, b->length+T->length, b->position, b->advance, b->mesa, b->direction, b->up, b->pre, T->head, 0, 0, T->tailTran1Mat, T->tailMat, 1);
            }else{
                if(T->length-T->width<0){
                    iniTail(T, b->width, b->length+T->length, b->position, b->advance, b->mesa, b->direction, b->up, b->pre, T->head, 0, 0, T->tailTran1Mat, T->tailMat, 1);
                }else{
                    iniTail(T, b->width, b->length+T->width, b->position, b->advance, b->mesa, b->direction, b->up, b->pre, T->head, 0, 0, T->tailTran1Mat, T->tailMat, 1);
                    T->head->toBeElongation+=T->length-T->width;
                }
            }
            b->pre->post=NULL;
        }else{
            if(b->width<=T->width){
                iniTail(T, b->width, b->length+T->length, b->position, b->advance, b->mesa, b->direction, b->up, NULL, T->head, 0, 0, T->tailTran1Mat, T->tailMat, 1);
            }else{
                if(T->length-T->width<0){
                    iniTail(T, b->width, b->length+T->length, b->position, b->advance, b->mesa, b->direction, b->up, NULL, T->head, 0, 0, T->tailTran1Mat, T->tailMat, 1);
                }else{
                    iniTail(T, b->width, b->length+T->width, b->position, b->advance, b->mesa, b->direction, b->up, NULL, T->head, 0, 0, T->tailTran1Mat, T->tailMat, 1);
                    T->head->toBeElongation+=T->length-T->width;
                }
//                if(T->head->toBeElongation<0){
//                    debug(tobeelongation<0)
//                    snakeH.velocity=0;
//                }
            }
            T->head->post=NULL;
        }
        free(b->snakeMat);
        free(b);
        T->head->bodyNum--;
    }else if(cornerTail==2){
        if(T->pre==NULL){
            if(T->head->width<=T->width){
                T->head->length+=T->length;
            }else{
                if(T->length<height(T->width)){
                    T->head->length+=T->length;
                }else{
                    T->head->length+=height(T->width);
                    T->head->toBeElongation+=T->length-height(T->width);
                }
//                if(T->head->toBeElongation<0){
//                    debug(tobeelongation<0)
//                    snakeH.velocity=0;
//                }
            }
            T->head->noTail=1;
            return;
        }
        if(b->pre!=NULL){
            if(b->width<=T->width){
                iniTail(T, b->width, b->length+T->length, b->position, b->advance, b->mesa, b->direction, b->up, b->pre, T->head, 0, 0, T->tailTran1Mat, T->tailMat, 1);
            }else{
                if(T->length-height(T->width)<0){
                    iniTail(T, b->width, b->length+T->length, b->position, b->advance, b->mesa, b->direction, b->up, b->pre, T->head, 0, 0, T->tailTran1Mat, T->tailMat, 1);
                }else{
                    iniTail(T, b->width, b->length+height(T->width), b->position, b->advance, b->mesa, b->direction, b->up, b->pre, T->head, 0, 0, T->tailTran1Mat, T->tailMat, 1);
                    T->head->toBeElongation+=T->length-height(T->width);
                }
            }
            b->pre->post=NULL;
        }else{
            if(b->width<=T->width){
                iniTail(T, b->width, b->length+T->length, b->position, b->advance, b->mesa, b->direction, b->up, NULL, T->head, 0, 0, T->tailTran1Mat, T->tailMat, 1);
            }else{
                if(T->length-height(T->width)<0){
                    iniTail(T, b->width, b->length+T->length, b->position, b->advance, b->mesa, b->direction, b->up, NULL, T->head, 0, 0, T->tailTran1Mat, T->tailMat, 1);
                }else{
                    iniTail(T, b->width, b->length+height(T->width), b->position, b->advance, b->mesa, b->direction, b->up, NULL, T->head, 0, 0, T->tailTran1Mat, T->tailMat, 1);
                    T->head->toBeElongation+=T->length-height(T->width);
                }
            }
            T->head->post=NULL;
        }
        free(b->snakeMat);
        free(b);
        T->head->bodyNum--;
    }else{
        if(T->pre==NULL){
            T->head->noTail=1;
            return;
        }
        if(b->pre!=NULL){
            iniTail(T, b->width, b->length, b->position, b->advance, b->mesa, b->direction, b->up, b->pre, T->head, 0, 0, T->tailTran1Mat, T->tailMat, 1);
            b->pre->post=NULL;
        }else{
            iniTail(T, b->width, b->length, b->position, b->advance, b->mesa, b->direction, b->up, NULL, T->head, 0, 0, T->tailTran1Mat, T->tailMat, 1);
            T->head->post=NULL;
        }
        free(b->snakeMat);
        free(b);
        T->head->bodyNum--;
    }
}

int cornerTail(struct snakeHead *s){
    struct snakeTail *T = s->tail;
    if(T->pre==NULL){
        if(T->up==s->up&&T->length<=s->width)return 1;
        else if (T->up==s->direction&&T->length<=height(s->width))return 2;
    }else{
        if(T->up==T->pre->up&&T->length<=T->pre->width)return 1;
        else if (T->up==T->pre->direction&&T->length<=height(T->pre->width))return 2;
    }
    return 0;
}

void snakeTailTransform(struct snakeTail* T, long width, long length, float position, float advance, bool mesa, enum surFace direction, enum surFace up, struct snakeBody *pre){
    debug(snakeTailTransform)
    iniTail(T, width, length, position, advance, mesa, direction, up, pre, T->head, T->stat, 0, T->tailTran1Mat, T->tailMat, 0);
    if(length<=0){
        snakeTailUpdate(T,0);
    }else{
        getTrans1MatT(T);
        getTrans2MatT(T);
    }
}

//检测与一个长方体是否发生碰撞, 不碰撞返回-1
float distanceMeasure(enum surFace objUp, enum surFace objDir, float objPosition, float objAdvance, long objLength, long objWidth, bool objmesa, enum surFace vUp, enum surFace vDir, float vP, float vA, long vW, bool vmesa){
    debug(distanceMeasure)
    float widthRe = getLength(vW)/ cube->size/2;
    float lengthRe = getLength(objLength)/ cube->size;
    float widthReObj = getLength(objWidth)/ cube->size/2;
    if(objUp!=vUp){
        if(!vmesa&&!objmesa&&5-vDir==objUp&&fabs(objPosition-vP)<widthRe+widthReObj&&lengthRe+height(widthRe*2)>cube->margin){
            return cube->margin-1+vA-height(widthReObj*2);
        }else{
            return -1;
        }
    }
    if(vmesa!=objmesa)return -1;
    if(objDir==vDir){
        //同向
        if(fabs(objPosition-vP)<widthRe+widthReObj&&vA>objAdvance){
            debugf(909, objAdvance + lengthRe)
            return objAdvance + lengthRe;
        }
    }else if (objDir==map[vUp][vDir]){
        //向左
        if(((vP+widthRe)>objAdvance)&&((vP-widthRe)<(objAdvance+lengthRe))&&vA>1-objPosition-widthReObj){
//        if(((vP+widthRe)>objAdvance)&&((vP-widthRe)<(objAdvance+lengthRe))&&vA>1-objPosition){
            debugf(915,1.0-objPosition + widthRe)
            return 1.0-objPosition + widthReObj;
        }
    }else if (objDir==(5-map[vUp][vDir])){
        //向右
        if(((vP+widthRe)>(1.0-(objAdvance+lengthRe)))&&((vP-widthRe)<(1.0-objAdvance))&&vA>objPosition-widthReObj){
//        if(((vP+widthRe)>(1.0-(objAdvance+lengthRe)))&&((vP-widthRe)<(1.0-objAdvance))&&vA>objPosition){
            debugf(921, objPosition+widthRe)
            return objPosition+widthReObj;
        }
    }else{
        //反向
        if(fabs(1.0-objPosition-vP)<widthRe+widthReObj&&vA>1-objAdvance-lengthRe){
            debugf(927, 1.0-objAdvance)
            return 1.0-objAdvance;
        }
    }
    return -1;
}

//是否发生碰撞且更近
bool bumpTest(struct snakeHead *s, enum surFace up, enum surFace direction, long length, long width, float position, float advance, bool mesa){
    //debug(bumptest)return 0;
    float temp=distanceMeasure(up, direction, position, advance, length, width, mesa, s->up, s->direction, s->position, s->advance, s->width, s->mesa);
    debugf(745bump,temp)
    if(temp>0){
        if(s->advance_end<temp){
            s->advance_end=temp;
            return 1;
        }
    }
    return 0;
}

//当头改变或是边界事件,slice事件触发后, 需要进行彻底的碰撞更新. 否则只需要更新尾部.
//碰撞更新 储存在advance_end. j==-1时检测全部, j==0时只需要检测头尾部. 并且标记了最近碰撞的类型.
void snakeCrush(struct snakeHead *s){
    debug(snakeCrush)
    debugf(638,s->advance)
    s->advance_end=-1;
    s->advEndH=NULL;
    s->advEndB=NULL;
    s->advEndT=NULL;
    s->advEndDy=NULL;
    struct snakeHead *H=&snakeH;
    
    while (H!=NULL) {
        //检测其他的head
        if(s!=H){
            if(H->up==s->up){
                if(bumpTest(s, H->up, H->direction, H->length, H->width, H->position, H->advance, H->mesa)){
                    debug(959)
                    s->advEndH=H;
                    s->advEndB=NULL;
                    s->advEndT=NULL;
                    s->advEndDy=NULL;
                }
            }
        }
        
        //检测body和tail
        if(!H->noTail){
            struct snakeTail *T = H->tail;
            if(T->up==s->up){
                if(bumpTest(s, T->up, T->direction, T->length, T->width, T->position, T->advance, T->mesa)){
                    debug(973)
                    s->advEndH=NULL;
                    s->advEndB=NULL;
                    s->advEndT=T;
                    s->advEndDy=NULL;
                }
            }
            if(H->post!=NULL){
                debug(811body)
                struct snakeBody *b=H->post;
                while (b!=NULL) {
                    if(bumpTest(s, b->up, b->direction, b->length, b->width, b->position, b->advance, b->mesa)){
                        debug(986)
                        s->advEndH=NULL;
                        s->advEndB=b;
                        s->advEndT=NULL;
                        s->advEndDy=NULL;
                    };
                    b=b->post;
                }
            }
        }
        
        H=H->others;
        debugp(823,s->advEndH)
        debugp(824,s->advEndB)
        debugp(825,s->advEndT)
        debugp(826,s->advEndDy)
    }
    //检测rot
    if(rotHandle->post!=NULL){
        struct rot *r=rotHandle->post;
        while (r!=NULL) {
            if(bumpTest(s, r->up, r->direction, r->length, r->width, r->position, r->advance, r->mesa)){
                debug(1006)
                s->advEndH=NULL;
                s->advEndB=NULL;
                s->advEndT=NULL;
                s->advEndDy=r;
            }
            r=r->post;
        }
    }
}



//边界事件
void snakeBorder(struct snakeHead *s){
    debug(snakeBorder)
    long w= NEWHEADWIDTH(s);
    if (s->advance<0){
        debug(704)
        debugf(adv706, s->advance)
        debugSnakePos(818,s)
        snakeExchangeH(s, w, s->position, (1.0-cube->margin), (5-s->up), s->direction, 1);
        debugSnakePos(820,s)
    }
    else if(!s->mesa&& s->advance<(1.0-cube->margin)&&s->advance>cube->margin&&s->position<=1-cube->margin&&s->position>=cube->margin){
        debugSnakePos(821,s)
        debug(adv708)
        snakeExchangeH(s, w, s->position, cube->margin-height(getLength(s->width)/cube->size), s->up, (5-s->direction),0);
        debugSnakePos(825,s)
    }
    else if(s->advance<(cube->margin)){
        debugSnakePos(827,s)
        if(!s->mesa&&(s->position<=cube->margin||s->position>=1-cube->margin)){
            snakeExchangeH(s, w, s->position, 1-cube->margin, (5-s->up), s->direction, 0);
        }else if(s->mesa){
            snakeExchangeH(s, w, s->position, 1.0, (5-s->up), s->direction,0);
        }
        debugSnakePos(831,s)
    }
    else ;
//    snakeCrush(s);
    findNearestfood(s);
}



//getMat为1则生成Mat
void iniRot(struct rot *r, long lenght, long width, float position, float advance, bool mesa, enum surFace direction, enum surFace up, long clock, int type, struct rot *pre, struct rot *post, int snakeId, bool allocMat, mat4 *rotMat, bool getMat){
    debug(iniRot)
    r->length=lenght;
    r->width=width;
    r->position=position;
    r->advance=advance;
    r->mesa=mesa;
    r->direction=direction;
    r->up=up;
    r->pre=pre;
    r->post=post;
    r->state=-snakeId;
    r->clock=clock;
    r->rotMat=rotMat;
    r->type=type;
    if(allocMat&&rotMat==NULL){
        r->rotMat=(mat4*)malloc(sizeof(mat4));
    }
    if(getMat&&r->rotMat!=NULL){
        getFinalMat(up, direction, width, lenght, advance, position, mesa, r->rotMat);
    }
}

mat4 * useBodyMat(struct snakeBody *b){
    debug(useBodyMat)
    mat4 *temp = b->snakeMat;
    b->snakeMat=NULL;
    return temp;
}

mat4 * useHeadMat(struct snakeHead *b){
    debug(useHeadMat)
    if(b==&snakeH){
        debugp(738, b->headMat)
        mat4 *m = (mat4*)malloc(sizeof(mat4));
        debug(736)
        glm_mat4_copy(*(b->headMat), *m);
        return m;
    }
    mat4 *temp = b->headMat;
    b->headMat=NULL;
    return temp;
}

mat4 * useTailMat(struct snakeTail *b){
    debug(useTailMat)
    if(b->head==&snakeH){
        mat4 *m = (mat4*)malloc(sizeof(mat4));
        debug(748)
        glm_mat4_copy(*(b->tailMat), *m);
        return m;
    }
    mat4 *temp = b->tailMat;
    b->tailMat=NULL;
    return temp;
}

void rotDel(struct rot *r){
    debug(rotDel)
    if(r!=NULL){
        if(r->post!=NULL)r->post->pre=r->pre;
        if(r->pre!=NULL)r->pre->post=r->post;
        free(r->rotMat);
        free(r);
    }
}

//释放某一条蛇的内存, 注意并没有改变others指针
void snakeFree(struct snakeHead *s);
void snakeFree_notHead(struct snakeHead *s);
void die(struct snakeHead *H);

//抹除某一条蛇
int snakeDel(struct snakeHead *h){
    if(h==NULL)return-1;
    h->snakeAlive=0;
    h->length=getTotalLength(h);
    if(h==&snakeH){
        endTime=glfwGetTime();
    }else{
        if(h->ID>=0&&h->ID<=4)NPC_endLength[h->ID]=getTotalLength(h);
    }
    debug(snakeDel)
    if(h!=&snakeH){
        struct snakeHead *temp=&snakeH;
        while (temp->others!=NULL) {
            if(temp->others==h) break;
            temp=temp->others;
        }
        temp->others=h->others;
        snakeFree_notHead(h);
    }else{
        snakeFree_notHead(h);
    }
    return 0;
}
int snakeDel_withHead(struct snakeHead *h){
    if(h==NULL)return-1;
//    h->snakeAlive=0;
//    h->length=getTotalLength(h);
//    if(h==&snakeH){
//        endTime=glfwGetTime();
//    }else{
//        if(h->ID>=0&&h->ID<=4)NPC_endLength[h->ID]=getTotalLength(h);
//    }
    debug(snakeDel)
    if(h!=&snakeH){
        struct snakeHead *temp=&snakeH;
        while (temp->others!=NULL) {
            if(temp->others==h) break;
            temp=temp->others;
        }
        if(temp->others!=NULL) temp->others=h->others;
        snakeFree(h);
    }else{
        snakeFree(h);
    }
    return 0;
}

void sliceH(struct snakeHead *H, struct snakeHead *s){
    debug(sliceH)
    long l,w=s->width;
    float a,p=s->position;
    long length;
    bool notail=s->noTail;
    if(H->direction==s->direction){
        if(H->eatRange<=0){
            length=D((s->advance-H->advance)*cube->size);
        }else{
            length=s->length-H->eatRange;
        }
        l=0;
        a=0;
    }else if(H->direction==5-s->direction){
        if(H->width>s->width){
            s->snakeAlive=0;
            return;
        }else{
            H->snakeAlive=0;
            return;
        }
    }else if(H->dirLEFT==s->direction){
        length=D((H->position-s->advance)*(cube->size))-H->width/2-1;
        notail=1;
        l=s->length-length-H->width-11;
        a=H->position+getLength(H->width+20)/2/ cube->size;
//        if(l<0)length=s->length-H->width-l-1;
//        else length=s->length-l-H->width-1;
    }else if(H->dirRIGHT==s->direction){
        length=D((1-H->position-s->advance)*(cube->size))-H->width/2-1;
        notail=1;
        l=s->length-length-H->width-11;
        a=1-H->position+getLength(H->width+20)/2/ cube->size;
//        if(l<0)length=s->length-H->width-l-1;
//        else length=s->length-l-H->width-1;
    }else{
        length=s->length;
        l=0;
        a=0;
    }
    
    int cl=1;
    struct rot *temp=rotHandle;
    while (temp->post!=NULL) {
        temp=temp->post;
    }
    struct rot *r;
    if(l<=0||a<=0||a>=1){
        r=temp;
    }else{
        r=(struct rot *)malloc(sizeof(struct rot));
        temp->post=r;
        cl+=l/w*decayT;
        iniRot(r, l, w, p, a, s->mesa,s->direction, s->up, cl, 1, temp, NULL, s->ID, 1, NULL, 1);
    }
    //遍历剩余躯体和尾, 变成rot
    if(s->post!=NULL){
        struct snakeBody *b=s->post;
        while (b!=NULL) {
            cl+=(b->length)/(b->width)*decayT;
            struct rot *newR = (struct rot *)malloc(sizeof(struct rot));
            iniRot(newR, b->length, b->width, b->position, b->advance, s->mesa, b->direction, b->up, cl, 1, r, NULL, s->ID,0 ,useBodyMat(b) ,0);
            r->post=newR;
            r=r->post;
            b=b->post;
        }
    }
    s->post=NULL;
    if(!s->noTail){
        struct rot *newR = (struct rot *)malloc(sizeof(struct rot));
        struct snakeTail *t = s->tail;
        cl+=(t->length)/(t->width)*decayT;
        iniRot(newR, t->length, t->width, t->position, t->advance, t->mesa, t->direction, t->up, cl, 2, r, NULL, s->ID, 1, NULL, 0);
        debug(845)
        glm_mat4_copy(*(t->tailMat), *(newR->rotMat));
        r->post=newR;
    }
    
    if(length<=0){
        s->snakeAlive=0;
        die(s);
    }else{
        iniHead(s, s->ID, w, length, p, s->advance, s->direction, s->up, s->mesa, s->velocity,0, NULL, s->tail, s->eatRange, notail, s->toBeElongation, s->score, 0, s->headTrans1Mat, s->headMat, 1);
    }
}

void sliceR(struct snakeHead *H, struct rot *r){
    debug(sliceR)
//    if(r->state>0){
//        H->snakeAlive=0;
//        return;
//    }
    long l,w=r->width;
    float a,p=r->position;
    long length;
    float advance;
    if(H->direction==r->direction){
        debug(1360)
        if(H->eatRange<=0){
            length=D((r->advance-H->advance)*cube->size);
        }else{
            length=r->length-H->eatRange;
        }
        advance=r->advance;
        l=-1;
        a=-1;
    }else if(H->direction==5-r->direction){
        debug(1366)
        if(H->eatRange<=0){
            length=r->length-D(fabsf(1-H->advance-r->advance)*cube->size);
            advance=1-H->advance;
        }else{
            length=r->length-H->eatRange;
            advance=r->advance+getLength(H->eatRange)/ cube->size;
        }
        l=-1;
        a=-1;
    }else if(H->dirLEFT==r->direction){
        debug(1372)
        length=D((H->position-r->advance)*(cube->size))-H->width/2-1;
        advance=r->advance;
        l=r->length-length-H->width-2;
        a=H->position+getLength(H->width+2)/ cube->size/2;
    }else if(H->dirRIGHT==r->direction){
        debug(1378)
        length=D((1-H->position-r->advance)*(cube->size))-H->width/2-1;
        advance=r->advance;
        l=r->length-length-H->width-2;
        a=1-H->position+getLength(H->width+2)/ cube->size/2;
    }else{
        debug(1384)
        length=r->length;
        advance=r->advance;
        l=-1;
        a=-1;
    }
    debugf(1385,getLength(l))
    debugf(1385,a)
    debugf(1385,getLength(length))
    debugf(1385,advance)
    if(l>0&&a>=0&&a<=1){
        struct rot *newR=(struct rot*)malloc(sizeof(struct rot));
        iniRot(newR, l, w, p, a, r->mesa, r->direction, r->up, r->clock, r->type, r, r->post, -r->state, 1, NULL, 1);
        if(r->post!=NULL){
            r->post->pre=newR;
            r->post=newR;
        }else{
            r->post=newR;
        }
    }
    if(length>0&&advance>0){
        r->length=length;
        r->advance=advance;
        getFinalMat(r->up, r->direction, r->width, r->length, r->advance, r->position, r->mesa, r->rotMat);
    }else{
        rotDel(r);
    }
}

void sliceB(struct snakeHead *H, struct snakeBody *s){
    debug(sliceB)
    s->head->bodyNum--;
    struct rot *temp=rotHandle;
    while (temp->post!=NULL) {
        temp=temp->post;
    }
    struct rot *r;
    long l,w=s->width;
    float a,p=s->position;
    long length;
    //s->direction==H->direction实际上是不会发生的
    if(s->direction==5-H->direction){
        if(H->eatRange<=0){
            l=s->length-D(fabsf(1-H->advance-s->advance)*cube->size);
            a=1-H->advance;
        }else{
            l=s->length-H->eatRange;
            a=s->advance+(getLength(H->eatRange)/ cube->size);
        }
        length=0;
    }else if(s->direction==H->dirLEFT){
        l=s->length-D((H->position-s->advance)*(cube->size))-H->width/2-1;
        a=H->position+(getLength(H->width+2)/2/ cube->size);
        length=s->length - l - H->width-2;
    }else if(s->direction==H->dirRIGHT){
        l=s->length-D((1-s->advance-H->position)*(cube->size))-H->width/2-1;
        a=1-H->position+(getLength(H->width+2)/2/ cube->size);
        length=s->length - l - H->width-2;
    }else{
        a=0;
        l=0;
        length=s->length;
    }
    int cl=1;
    if(l<=0||a<=0||a>=1){
        r=temp;
    }
    else{
        r=(struct rot *)malloc(sizeof(struct rot));
        temp->post=r;
        cl+=l/w*decayT;
        iniRot(r, l, w, p, a, s->mesa, s->direction, s->up, cl, 1, temp, NULL, s->head->ID, 1, NULL, 1);
    }
    //遍历剩余躯体和尾, 变成rot
    if(s->post!=NULL){
        struct snakeBody *b=s->post;
        while (b!=NULL) {
            cl+=(b->length)/(b->width)*decayT;
            struct rot *newR = (struct rot *)malloc(sizeof(struct rot));
            iniRot(newR, b->length, b->width, b->position, b->advance, b->mesa, b->direction, b->up, cl, 1, r, NULL, s->head->ID, 0 ,useBodyMat(b) ,0);
            r->post=newR;
            r=r->post;
            b=b->post;
        }
    }
    if(!s->head->noTail){
        struct rot *newR = (struct rot *)malloc(sizeof(struct rot));
        struct snakeTail *t = s->head->tail;
        cl+=(t->length)/(t->width)*decayT;
        iniRot(newR, t->length, t->width, t->position, t->advance, t->mesa, t->direction, t->up, cl, 2, r, NULL, s->head->ID, 1, NULL, 0);
        debug(956)
        glm_mat4_copy(*(t->tailMat), *(newR->rotMat));
        r->post=newR;
    }
    
    //清理body
    struct snakeBody *d = s;
    if(s->pre!=NULL){
        s->pre->post=NULL;
        s->head->tail->pre=s->pre;
    }else {
        s->head->post=NULL;
        s->head->tail->pre=NULL;
    }
//    if(length<=0)length=0;
    struct snakeTail *t=s->head->tail;
    snakeTailTransform(t, s->width, length, s->position, s->advance, s->mesa, s->direction, s->up, s->pre);
//    if(s->head->post==s)s->head->post=NULL;
    
    while (d!=NULL) {
        d->head->bodyNum--;
        struct snakeBody *d1 = d->post;
        free(d->snakeMat);
        free(d);
        d=d1;
    }
}

void sliceT(struct snakeHead *H, struct snakeTail *s){
    debug(sliceT)
    long l,w=s->width;
    float a,p=s->position;
    long length;
    if(s->direction==H->direction){
        a=-1;
        l=-1;
        if(H->eatRange<=0)length=D((s->advance-H->advance)*cube->size);
        else length=s->length-H->eatRange;
        debugf(1416, getLength(length))
    }else if(s->direction==5-H->direction){
        if(H->eatRange<=0){
            a=1-H->advance+0.0001;
            l=D(s->advance-1+H->advance);
        }
        else{
            a=s->advance+getLength(H->eatRange+1)/ cube->size;
            l=s->length-H->eatRange;
        }
        length=0;
        debugf(1422, a)
        debugf(1422, getLength(l))
    }else if(s->direction==H->dirLEFT){
        a=H->position+getLength(H->width+20)/ cube->size/2;
        l=s->length-D((H->position-s->advance)*(cube->size))-H->width/2-10;
//        if(l<0)length=s->length-H->width-l-1;
//        else length=s->length-l-H->width-1;
        length=s->length-l-H->width-11;
        debugf(1428, a)
        debugf(1428, getLength(l))
        debugf(1428, getLength(length))
    }else if(s->direction==H->dirRIGHT){
        a=1-H->position+getLength(H->width)/ cube->size/2+0.001;
        l=s->length-D((1-s->advance-H->position)*(cube->size))-H->width/2-10;
//        if(l<0)length=s->length-H->width-l-1;
//        else length=s->length-l-H->width-1;
        length=s->length-l-H->width-11;
        debugf(1435, a)
        debugf(1435, getLength(l))
        debugf(1435, getLength(length))
    }else{
        a=-1;
        l=-1;
        length=s->length;
        debugl(1442, length)
    }
    if(a>=0&&a<=1&&(l>0)){
        struct rot *temp=rotHandle;
        while (temp->post!=NULL) {
            temp=temp->post;
        }
        struct rot *r=(struct rot *)malloc(sizeof(struct rot));
        temp->post=r;
        iniRot(r, l, w, p, a, s->mesa, s->direction, s->up, ((int)(l/w)*decayT+1), 2, temp, NULL, s->head->ID, 1, NULL, 1);
    }
    debugi(1455, s->stat)
    snakeTailTransform(s, s->width, length, s->position, s->advance, s->mesa, s->direction, s->up, s->pre);
    debugi(1456, s->stat)
}
bool starting = 1;
//die
void snakeBump(struct snakeHead *s){
    debug(snakeBump)
    debugf(1384, getLength(s->length))
    if(s->advance<=s->advance_end){
        if((starting&&s->ID>0)||s->ID<0){
            if(s->advEndB!=NULL){
                sliceB(s,s->advEndB);
            }else if(s->advEndT!=NULL){
                sliceT(s,s->advEndT);
            }else if(s->advEndDy!=NULL){
                sliceR(s,s->advEndDy);
            }else if(s->advEndH!=NULL){
                sliceH(s, s->advEndH);
            }
        }else{
            if(s->eatRange<=0){
                debugf(1387, getLength(s->length))
                s->snakeAlive = 0;
                if(s->advEndB!=NULL)debugSnakePos(1450, s->advEndB);
                if(s->advEndT!=NULL)debugSnakePos(1450, s->advEndT);
                if(s->advEndDy!=NULL)debugSnakePos(1450, s->advEndDy);
                if(s->advEndH!=NULL)debugSnakePos(1450, s->advEndH);
            }else{
                debugf(1390, getLength(s->length))
                if(s->advEndB!=NULL){
                    debugSnakePos(1453, s->advEndB)
                    sliceB(s,s->advEndB);
                }else if(s->advEndT!=NULL){
                    debugSnakePos(1453, s->advEndT)
                    sliceT(s,s->advEndT);
                }else if(s->advEndDy!=NULL){
                    debugSnakePos(1453, s->advEndDy)
                    if(s->advEndDy->state<=0){
                        sliceR(s,s->advEndDy);
                    }else{
                        s->snakeAlive=0;
                    }
                }else if(s->advEndH!=NULL){
                    debugSnakePos(1453, s->advEndH)
                    sliceH(s, s->advEndH);
                }
            }
        }
    }
}

//将蛇放进rot
void die(struct snakeHead *H){
    debug(die)
    struct rot *temp=rotHandle;
    debugp(1413, temp->post)
    while (temp->post!=NULL) {
        temp=temp->post;
    }
    int cl = 1;
    struct rot *r=(struct rot *)malloc(sizeof(struct rot));
    temp->post=r;
    cl+=H->length/H->width*decayT;
    debugmat4(1420, *(H->headMat))
    iniRot(r, H->length, H->width, H->position, H->advance, H->mesa, H->direction, H->up, cl, 0, temp, NULL, H->ID, 0, useHeadMat(H), 0);
    debugp(1422, rotHandle->post)
    debugf(1424, getLength(r->length))
    debugmat4(1425, *(r->rotMat))
    struct snakeBody *b=H->post;
    debugp(1423, b)
    while (b!=NULL) {
        debug(1416)
        debugp(1417, r)
        cl+=(b->length)/(b->width)*decayT;
        struct rot *newR = (struct rot *)malloc(sizeof(struct rot));
        iniRot(newR, b->length, b->width, b->position, b->advance, b->mesa, b->direction, b->up, cl, 1, r, NULL, H->ID, 0 ,useBodyMat(b) ,0);
        debugf(1424, getLength(newR->length))
        r->post=newR;
        r=r->post;
        b=b->post;
    }
    if(!H->noTail){
        temp=(struct rot *)malloc(sizeof(struct rot));
        cl+=H->tail->length/H->tail->width*decayT;
        iniRot(temp, H->tail->length, H->tail->width, H->tail->position, H->tail->advance, H->tail->mesa, H->tail->direction, H->tail->up, cl, 2, r, NULL, H->ID, 0, useTailMat(H->tail), 0);
        debugf(1432, getLength(temp->length))
        r->post=temp;
    }
    debugp(1445, rotHandle->post)
    debugp(1445, rotHandle->post->post)
    snakeDel(H);
}

//update 每一帧更新
void snakeUpdate(struct snakeHead *H/*, float velocity*/, float deltaTime){
    if(H->stall){
//        snakeCrush(H);
        return;
    }
    
    if(!H->snakeAlive)return;
    if(!H->noTail)debugi(1542, H->tail->stat);
        debugSnakePos(snake1627, H)
        debugp(snake1627, H)
    debug(snakeUpdate)
    debugf(1087,H->advance)
    debugp(1071, H->headMat)
    debugf(1090,H->advance)
    snakeCrush(H);
    if(H->ID>=0)snakeBump(H);
    if(!H->snakeAlive){
        if(H==&snakeH){
            endLength=getTotalLength(H);
        }
        die(H);
        return;
    }
    struct snakeTail *T = H->tail;
    if(H->ID>=0&&STATE>0/*&&!starting*/){
        if(H->noTail){
            if(H->toBeElongation==0&&H->length<(NEWHEADWIDTH(H))&&H->noTail){
                H->toBeElongation+=(NEWHEADWIDTH(H)-H->length);
            }else if(H->toBeElongation==0&&H->length<H->width&&H->noTail){
                H->toBeElongation+=H->width-H->length;
            }
        }
        findNearestfood(H);
        eat(H);
    }
    long velocity = H->velocity;
    long movement = velocity*deltaTime;
    
    if(H->toBeElongation>0&&H->eatRange<=0){
        if(H->noTail){
            H->length+=movement;
            H->toBeElongation-=movement;
            if(H->toBeElongation<0){
                H->length+=H->toBeElongation;
                H->toBeElongation=0;
            }
        }else{
            T->stat=1;
            H->toBeElongation-=movement;
            if(H->toBeElongation<=0){
                T->length+=movement;
                T->stat=0;
            }
        }
    }else if(H->toBeElongation<0&&H->eatRange<=0){
        long mt=movement;
        H->toBeElongation+=mt;
        if(H->toBeElongation>0){
            mt-=H->toBeElongation;
            H->toBeElongation=0;
        }
        if(!H->noTail){
            H->tail->length-=mt;
        }else{
            H->length-=mt;
        }
    }
    //move 更新头和尾的矩阵
    debug(1088)
    debugf(1107, H->advance)
    if(H->eatRange>0){
        eatProcess(H, (float)_EatRange(((H->eatProcess[2]==0?(H->width):(H->eatProcess[2])))/(float)velocity*fps), movement);
//        debugf(1356, H->width/2/velocity*fps)
//        eatProcess(H, (H->width/2/velocity*fps), movement);
        debugf(1110, H->advance)
    }else{
        headMove(H, movement);
        debugf(1115, H->advance)
        tailMove(T, movement);
    }
    snakeBorder(H);
    if(!H->noTail){
        int i=cornerTail(H);
        if(i!=0)snakeTailUpdate(T,i);
        if(T->length<=0){
            H->toBeElongation+=T->length;
            snakeTailUpdate(T,0);
        }
    }
    if(!H->noTail)debugi(1609, H->tail->stat);
    
}

void getAbsPos(enum surFace up, enum surFace dir, float a, float p, bool mesa, float *result){
    vec3 v1;
    if(mesa){
        v1[0] = _norVec[up][0]*cube->size/2;
        v1[1] = _norVec[up][1]*cube->size/2;
        v1[2] = _norVec[up][2]*cube->size/2;
    }else{
        v1[0] = _norVec[up][0]*cube->size*(0.5-cube->margin);
        v1[1] = _norVec[up][1]*cube->size*(0.5-cube->margin);
        v1[2] = _norVec[up][2]*cube->size*(0.5-cube->margin);
    }
    vec3 v2;
    v2[0] = _norVec[dir][0]*(0.5-a)*cube->size;
    v2[1] = _norVec[dir][1]*(0.5-a)*cube->size;
    v2[2] = _norVec[dir][2]*(0.5-a)*cube->size;
    vec3 v3;
    v3[0] = _norVec[map[up][dir]][0]*(0.5-p)*cube->size;
    v3[1] = _norVec[map[up][dir]][1]*(0.5-p)*cube->size;
    v3[2] = _norVec[map[up][dir]][2]*(0.5-p)*cube->size;
    result[0]=v1[0]+v2[0]+v3[0];
    result[1]=v1[1]+v2[1]+v3[1];
    result[2]=v1[2]+v2[2]+v3[2];
}

void rotUpdate(void){
    debug(rotUpdate)
    struct rot *r = rotHandle->post;
    while (r!=NULL) {
        if(r->length<=0){
            struct rot *temp=r->pre;
            rotDel(r);
            r=temp;
        }
        r->clock--;
        if(r->clock<0){
            if(r->state<=0){
                r->state=1;
                r->clock=(float)r->length/(float)r->width*decayT+1;
            }else if(r->state==1){
                r->state=2;
                r->clock=(float)r->length/(float)r->width*decayT+1;
            }else{
                struct rot *temp=r->pre;
                rotDel(r);
                r=temp;
            }
        }
        r=r->post;
    }
}

//dir==0左转, dir==1右转
bool snakeTurn(struct snakeHead *H, enum turn dir){
    debug(snakeTurn)
    if(!H->snakeAlive||H->eatRange>0||H->eatProcess[0]!=0||H->eatProcess[1]!=0||H->eatProcess[2]!=0)return 0;
    float p,a;
    long w;
    enum surFace d=H->direction;
//    if(H->ID>=0)w=NEWHEADWIDTH(H);
//    else w=H->width;
    w=NEWHEADWIDTH(H);
    if(H->length>w){
        if(dir==turnLEFT){
            p=1-H->advance-getLength(w)/cube->size/2;
            a=H->position-getLength(H->width)/cube->size/2;
            d=H->dirLEFT;
        }else if(dir==turnRIGHT){
            p=H->advance+getLength(w)/2/ cube->size;
            a=1-H->position-getLength(H->width)/2/ cube->size;
            d=H->dirRIGHT;
        }else{
            return 0;
        }
        snakeExchangeH(H, w, p, a, d, H->up, H->mesa);
    }else{
        return 0;
    }
    return 1;
}
enum snakeKey{
    _LEFT,
    _RIGHT,
    _SPACE
};
//键盘事件 0-a/左箭头; 1-d/右箭头; 2-空格
void snakeKeyBoard(struct snakeHead *h, int type){
    if(type==_LEFT&&h->eatRange<=0){
        snakeTurn(h, turnLEFT);
    }else if(type==_RIGHT&&h->eatRange<=0){
        snakeTurn(h, turnRIGHT);
    }else if(type==_SPACE){
        long range=_EatRange(h->width);
        if(h->eatRange==0){
            if(h->mesa&&(h->advance-cube->margin)*(cube->size)<getLength(range)){
                h->eatRange=D((h->advance-cube->margin)*(cube->size));
                debugf(1520, getLength(h->eatRange))
            }else if(!h->mesa&&h->advance<cube->margin&&h->advance*cube->size<getLength(range)){
                h->eatRange=D(h->advance*(cube->size));
                debugf(1523, getLength(h->eatRange))
            }else if(!h->mesa&&h->advance>1-cube->margin&&(h->advance-1+cube->margin)*cube->margin<getLength(range)){
                h->eatRange=D((h->advance-1+cube->margin)*cube->margin);
                debugf(1526, getLength(h->eatRange))
            }else if((h->position<=cube->margin||h->position>=1-cube->margin)&&(h->advance-cube->margin)*cube->size<getLength(range)){
                h->eatRange=D((h->advance-cube->margin)*cube->size);
                debugf(1529, getLength(h->eatRange))
            }else{
                h->eatRange=range;
                debugf(1532, getLength(h->eatRange))
            }
        }
    }
}

//释放内存!!!
void snakeFree(struct snakeHead *s){
    debug(snakeFree)
    struct snakeBody *b = s->post;
    while (b!=NULL) {
        struct snakeBody *b1=b->post;
        free(b->snakeMat);
        free(b);
        b=b1;
    }
    if(s!=&snakeH){
        free(s->headMat);
        free(s->headTrans1Mat);
        if(s->tail!=NULL){
            free(s->tail->tailMat);
            free(s->tail->tailTran1Mat);
            free(s->tail);
        }
        free(s);
    }
}
void snakeFree_notHead(struct snakeHead *s){
    debug(snakeFree)
    struct snakeBody *b = s->post;
    while (b!=NULL) {
        struct snakeBody *b1=b->post;
        free(b->snakeMat);
        free(b);
        b=b1;
    }
    s->post=NULL;
    s->tail->pre=NULL;
    s->noTail=1;
    if(s!=&snakeH){
        free(s->headMat);
        free(s->headTrans1Mat);
        free(s->tail->tailMat);
        free(s->tail->tailTran1Mat);
        free(s->tail);
        s->tail=NULL;
        s->headMat=NULL;
        s->headTrans1Mat=NULL;
//        free(s);
    }
}

void rotFree(void){
    struct rot *r=rotHandle->post;
    while (r!=NULL) {
        struct rot *r1=r->post;
        free(r);
        r=r1;
    }
    rotHandle->post=NULL;
}

//void creatSnake(int ID,float width, float length, float position, float advance, enum surFace direction, enum surFace up, float velocity,struct snakeBody *post, float eatRange, float toBeElongation, bool mesa){
//    if(ID==0){
//        iniHead(&snakeH, 0, width, length, position, advance, direction, up, mesa, velocity, 0, post, &snakeT, eatRange, 1, toBeElongation, 0, &snakeTrans1H, &snakeTransFinalH, 1);
//        iniTail(&snakeT, width, length, position, advance, mesa, direction, up, NULL, &snakeH, 0, 0, &snakeTrans1T, &snakeTransFinalT, 1);
//    }else{
//        struct snakeHead *h=(struct snakeHead*)malloc(sizeof(struct snakeHead));
//        struct snakeTail *t=(struct snakeTail*)malloc(sizeof(struct snakeTail));
//        iniHead(h, ID, width, length, position, advance, direction, up, mesa, velocity, 0, post, t, eatRange, 1, toBeElongation, 1, NULL, NULL, 1);
//        iniTail(t, width, length, position, advance, mesa, direction, up, NULL, &snakeH, 0, 1, &snakeTrans1T, &snakeTransFinalT, 1);
//        struct snakeHead *temp=&snakeH;
//        while (temp->others!=NULL) {
//            temp=temp->others;
//        }
//        temp->others=h;
//    }
//}
struct snakeHead* creatSnake(int ID,long width, long length, float position, float advance, enum surFace direction, enum surFace up, float velocity,struct snakeBody *post, long eatRange, long toBeElongation, bool mesa){
    if(ID==0){
        snakeH.others=NULL;
        iniHead(&snakeH, 0, width, length, position, advance, direction, up, mesa, velocity, 0, post, &snakeT, eatRange, 1, toBeElongation, 0, 0, &snakeTrans1H, &snakeTransFinalH, 1);
        iniTail(&snakeT, width, length, position, advance, mesa, direction, up, NULL, &snakeH, 0, 0, &snakeTrans1T, &snakeTransFinalT, 1);
        return NULL;
    }else{
        struct snakeHead *h=(struct snakeHead*)malloc(sizeof(struct snakeHead));
        h->others=NULL;
        struct snakeTail *t=(struct snakeTail*)malloc(sizeof(struct snakeTail));
        iniHead(h, ID, width, length, position, advance, direction, up, mesa, velocity, 0, post, t, eatRange, 1, toBeElongation, 0, 1, NULL, NULL, 1);
        iniTail(t, width, length, position, advance, mesa, direction, up, NULL, h, 0, 1, NULL, NULL, 0);
        struct snakeHead *temp=&snakeH;
        while (temp->others!=NULL) {
            temp=temp->others;
        }
        temp->others=h;
        return h;
    }
}
int ccc=0,ppp=0;
int countingSR(void){
//    int j=0;
    int i=0;
    struct snakeHead *snake=&snakeH;
//    if(STATE==0)snake=snake->others;
    if(!snakeH.snakeAlive)snake=snakeH.others;
    while (snake!=NULL) {
//        j++;
        debugp(snake1880,snake)
        debugp(snake1880,snake->others)
        if(snake->snakeAlive){
            i++;
            if(!snake->noTail){
                struct snakeBody *b=snake->post;
                while (b!=NULL) {
                    i++;
                    b=b->post;
                }
                i++;
            }
        }
        snake=snake->others;
    }
    struct rot *r=rotHandle->post;
    while (r!=NULL) {
        i++;
        r=r->post;
    }
//    if(j>=ccc)ccc=j;
//    if(ccc>j)ppp=1;
    return i;
}

struct NPC{
    bool alive;
    struct snakeHead *H;
    int ID;
    float fc;
    //0self 1other 2rot(state>0)
    float cc[3];
    float randm;
    //提前多少转弯
    float ts;//0
    float bs;//0
    float es_sl;
    int rps;
    //每帧能进行多少次robotCrush检测
    float perFrame;
    int frameCounter;
    float averageMovement;
    int counting;
//    float agg;
    float apAdv;
    float rigor;

    float bumping;
//    float bumping1;
};



struct NPC *iniNPC(int ID, struct snakeHead* H, float fc, float rc, float oc, float sc, float randm, float ts, float bs, float es_sl, float apAdv, int rps, float perFrame, float rigor, float bumping/*, float bumping1*/){
    struct NPC* n = (struct NPC*)malloc(sizeof(struct NPC));
    n->H=H;
    n->fc=fc;
    n->ID=ID;
    n->alive=1;
    n->averageMovement=n->H->width;
    n->bs=bs;
    n->frameCounter=0;
    n->cc[1]=oc;
    n->perFrame=perFrame;
    n->cc[2]=rc;
    n->rps=rps;
    n->cc[0]=sc;
    n->ts=ts;
    n->es_sl=es_sl;
    n->randm=randm;
    n->counting=0;
    n->apAdv=apAdv;
    n->rigor=rigor;
    n->bumping=bumping;
//    n->bumping1=bumping1;
    return n;
}
struct robot{
    //绝对数值
    long width;
    //中心位于平面左右的相对距离, 0.0f-1.0f
    float position;
    //到前面的比例, 0.0f,1.0f
    float advance;
    
    int rps;
    
    long eatRange;
    
    float *advance_end;
    //0self 1other 2rot
    int *type;
    long *bumpingDir;
    float advance_neareatFood;
    //以面对的平面的法向量决定
    enum surFace direction;
    //以所在平面的法向量决定
    enum surFace up;
    //LEFT: map[.up][.direction]
    enum surFace dirLEFT;
    enum surFace dirRIGHT;
    
    struct food *nearestFood;
    struct snakeHead* advEndH;
    struct snakeBody* advEndB;
    struct snakeTail* advEndT;
    struct rot* advEndDy;

    bool mesa;
};
void iniRobot(struct robot *H,long width, float position, float advance, enum surFace direction, enum surFace up, bool mesa, int rps){
    H->mesa=mesa;
    H->width=width;
    H->position=position;
    H->advance=advance;
    H->advance_end=(float*)malloc(sizeof(float)*rps);
    H->type=(int*)malloc(sizeof(int)*rps);
    H->bumpingDir=(long*)malloc(sizeof(long)*rps);
    H->advance_neareatFood=-1;
    H->direction=direction;
    H->up=up;
    H->dirLEFT=map[up][direction];
    H->dirRIGHT=5-H->dirLEFT;
    H->eatRange=_EatRange(width);
    H->nearestFood=NULL;
    H->advEndB=NULL;
    H->advEndH=NULL;
    H->advEndT=NULL;
    H->advEndDy=NULL;
    H->rps=rps;
}
void deletRobot(struct robot *robot){
    if(robot==NULL)return;
    free(robot->advance_end);
    free(robot->type);
    free(robot->bumpingDir);
    free(robot);
}

//-1未进入rps, >=0:排第几位
int robotBumpTest(struct robot *s, enum surFace up, enum surFace direction, long length, long width, float position, float advance, bool mesa, int *counter){
    float temp=distanceMeasure(up, direction, position, advance, length, width, mesa, s->up, s->direction, s->position, s->advance, s->width, s->mesa);
//    printf("temp: %f\n",temp);
    if(temp>0){
        *counter=*counter+1;
        int returning=-1;
        int i=0;
        float t=temp;
        while (i<s->rps) {
            if(t<=0)break;
            if(s->advance_end[i]<t){
                float swap=s->advance_end[i];
                s->advance_end[i]=t;
                t=swap;
                if(returning==-1)returning=i;
            }
            i++;
        }
        if(returning!=-1){
            if(s->direction==direction||s->direction==5-direction)s->bumpingDir[returning]=length;
//            else s->bumpingDir[returning]=width;
            else s->bumpingDir[returning]=0;
        }
        return returning;
    }
    return -1;
}
void robotCrushTest(struct robot *s, struct NPC *N){
    if(s==NULL)return;
    int *counter = &(N->counting);
    int i=0;
    while (i++<s->rps) {
        s->advance_end[i]=-1;
        s->type[i]=-1;
    }
    s->advEndH=NULL;
    s->advEndB=NULL;
    s->advEndT=NULL;
    s->advEndDy=NULL;
    struct snakeHead *H=&snakeH;
    while (H!=NULL) {
        bool isSelf=0;
        if(H==N->H)isSelf=1;
        int temp;
        if(N->H!=H){
            if(H->up==s->up){
                temp = robotBumpTest(s, H->up, H->direction, H->length, H->width, H->position, H->advance, H->mesa, counter);
                if(temp>=0){
                    if(temp==0){
                        s->advEndH=H;
                        s->advEndB=NULL;
                        s->advEndT=NULL;
                        s->advEndDy=NULL;
                    }
                    if(isSelf)s->type[temp]=0;
                    else s->type[temp]=1;
                }
            }
        }
        //检测body和tail
        if(!H->noTail){
            struct snakeTail *T = H->tail;
            if(T->up==s->up){
                temp = robotBumpTest(s, T->up, T->direction, T->length, T->width, T->position, T->advance, T->mesa, counter);
                if(temp>=0){
                    if(temp==0){
                        s->advEndH=NULL;
                        s->advEndB=NULL;
                        s->advEndT=T;
                        s->advEndDy=NULL;
                    }
                    if(isSelf)s->type[temp]=0;
                    else s->type[temp]=1;
                }
            }
        }
        if(H->post!=NULL){
            struct snakeBody *b=H->post;
            while (b!=NULL) {
                temp = robotBumpTest(s, b->up, b->direction, b->length, b->width, b->position, b->advance, b->mesa, counter);
                if(temp>=0){
                    if(temp==0){
                        s->advEndH=NULL;
                        s->advEndB=b;
                        s->advEndT=NULL;
                        s->advEndDy=NULL;
                    }
                    if(isSelf)s->type[temp]=0;
                    else s->type[temp]=1;
                };
                b=b->post;
            }
        }
        H=H->others;
    }
    //检测rot
    if(rotHandle->post!=NULL){
        struct rot *r=rotHandle->post;
        while (r!=NULL) {
            int temp = robotBumpTest(s, r->up, r->direction, r->length, r->width, r->position, r->advance, r->mesa, counter);
            if(temp>=0){
                if(temp==0){
                    s->advEndH=NULL;
                    s->advEndB=NULL;
                    s->advEndT=NULL;
                    s->advEndDy=r;
                }
                if(r->state<=0)s->type[temp]=1;
                else s->type[temp]=2;
                
            }
            r=r->post;
        }
    }
}
void robotFindNearestfood(struct robot *s);

//dir==0左转, dir==1右转
struct robot* robotTurn(struct NPC *N, enum turn dir){
    struct snakeHead *H=N->H;
    if(N->H->eatRange>0)return NULL;
    struct robot *s=(struct robot * ) malloc(sizeof(struct robot));
    float p,a;
    long w;
    enum surFace d=H->direction;
//    if(H->ID>=0)w=NEWHEADWIDTH(H);
//    else w=H->width;
    w=NEWHEADWIDTH(H);
    if(H->length>=w){
        if(dir==turnLEFT){
            p=1-H->advance-getLength(w)/cube->size/2;
            a=H->position-getLength(H->width)/cube->size/2;
            d=H->dirLEFT;
        }else if(dir==turnRIGHT){
            p=H->advance+getLength(w)/2/ cube->size;
            a=1-H->position-getLength(H->width)/2/ cube->size;
            d=H->dirRIGHT;
        }else{
            deletRobot(s);
            return NULL;
        }
        iniRobot(s, w, p, a, d, H->up, H->mesa, N->rps);
    }else{
        deletRobot(s);
        return NULL;
    }
    return s;
}

//struct robot* robotBorder(struct NPC* N){
//    struct snakeHead* s=N->H;
//    struct robot *r=(struct robot * ) malloc(sizeof(struct robot));
//    long w= NEWHEADWIDTH(s);
//    if (s->advance<0){
//        iniRobot(r, w, s->position, (1.0-cube->margin), (5-s->up), s->direction, 1, N->rps);
////        snakeExchangeH(s, w, s->position, (1.0-cube->margin), (5-s->up), s->direction, 1);
//    }
//    else if(!s->mesa&& s->advance<(1.0-cube->margin)&&s->advance>cube->margin&&s->position<=1-cube->margin&&s->position>=cube->margin){
//        iniRobot(r, w, s->position, cube->margin-height(getLength(s->width)/cube->size), s->up, (5-s->direction),0, N->rps);
////        snakeExchangeH(s, w, s->position, cube->margin-height(getLength(s->width)/cube->size), s->up, (5-s->direction),0);
//    }
//    else if(s->advance<(cube->margin)){
//        if(!s->mesa&&(s->position<=cube->margin||s->position>=1-cube->margin)){
//            iniRobot(r, w, s->position, 1-cube->margin, (5-s->up), s->direction, 0, N->rps);
////            snakeExchangeH(s, w, s->position, 1-cube->margin, (5-s->up), s->direction, 0);
//        }else if(s->mesa){
//            iniRobot(r, w, s->position, 1.0, (5-s->up), s->direction,0,N->rps);
////            snakeExchangeH(s, w, s->position, 1.0, (5-s->up), s->direction,0);
//        }
//    }
//    else ;
//    return r;
//}
enum robotBorderR{
    Mm,
    mUm,
    mDm,
    mM
};
//struct robot* robotBorder_type(struct NPC* N, enum robotBorderR type){
//    struct snakeHead *s=N->H;
//    struct robot *r=(struct robot * ) malloc(sizeof(struct robot));
//    long w= NEWHEADWIDTH(s);
//    if (type==mM){
//        iniRobot(r, w, s->position, (1.0-cube->margin), (5-s->up), s->direction, 1, N->rps);
//    }else if(type==mUm){
//        iniRobot(r, w, s->position, cube->margin-height(getLength(s->width)/cube->size), s->up, (5-s->direction),0, N->rps);
//    }else if(type==mDm){
//        iniRobot(r, w, s->position, 1-cube->margin, (5-s->up), s->direction, 0, N->rps);
//    }else if(type==Mm){
//        iniRobot(r, w, s->position, 1.0, (5-s->up), s->direction,0, N->rps);
//    }else{
//        free(r);
//        return NULL;
//    }
//    return r;
//}
//int countingLB=0,countingRB=0,countingBB=0;
struct robot* robotBorderRobot(struct robot *s, enum robotBorderR type/*, float* reAdv*/){
    if(s==NULL)return NULL;
    struct robot *r=(struct robot * ) malloc(sizeof(struct robot));
    long w= s->width;
    if (type==mM){
//        if(reAdv!=NULL)*reAdv=s->advance;
        iniRobot(r, w, s->position, (1.0-cube->margin), (5-s->up), s->direction, 1, s->rps);
    }else if(type==mUm){
//        if(reAdv!=NULL)*reAdv=s->advance-1+cube->margin;
        iniRobot(r, w, s->position, cube->margin-height(getLength(s->width)/cube->size), s->up, (5-s->direction),0, s->rps);
    }else if(type==mDm){
//        if(reAdv!=NULL)*reAdv=s->advance-cube->margin;
        iniRobot(r, w, s->position, 1-cube->margin, (5-s->up), s->direction, 0, s->rps);
    }else if(type==Mm){
//        if(reAdv!=NULL)*reAdv=s->advance-cube->margin;
        iniRobot(r, w, s->position, 1.0, (5-s->up), s->direction,0, s->rps);
    }else{
        deletRobot(r);
        return NULL;
    }
    return r;
}
struct robot* creatRobotL(struct NPC* N){
    struct robot *r= robotTurn(N, turnLEFT);
    robotCrushTest(r,N);
    robotFindNearestfood(r);
    return r;
}

struct robot* creatRobotR(struct NPC* N){
    struct robot *r= robotTurn(N, turnRIGHT);
    robotCrushTest(r,N);
    robotFindNearestfood(r);
    return r;
}

struct robot* creatRobotSelf(struct NPC* N){
    struct robot *r = (struct robot*)malloc(sizeof(struct robot));
    iniRobot(r, N->H->width, N->H->position, N->H->advance, N->H->direction, N->H->up, N->H->mesa, N->rps);
    robotCrushTest(r,N);
    robotFindNearestfood(r);
    return r;
}

struct robot* creatRBR(struct NPC* N, struct robot *firstR, enum robotBorderR type/*, float *reAdv*/){
//    countingBB++;
    if(firstR==NULL)return NULL;
    struct robot *secondR = robotBorderRobot(firstR, type/*, reAdv*/);
    robotCrushTest(secondR,N);
    robotFindNearestfood(secondR);
    return secondR;
}

float HarMean(struct NPC *N, float* advance_end, int* type, long* bumpngDir, float advance){
    float sum=0;
    int i=0;
    while (i<N->rps) {
        if(advance_end[i]<=0){
            break;
        }
        if((advance-advance_end[i])<=0){
            return 0;
        }
        sum+=1/((advance-advance_end[i])*N->cc[type[i]]*(1-getLength(bumpngDir[i])/cube->size*N->bumping));
//        printf("sum %f\n",sum);
        i++;
    }
    if(sum<0||1/sum<0){
//        printf("sum:%f 1/sum%f adv_end0:%f adv_end1:%f adv_end2:%f advance%f",sum,1/sum,advance_end[0],advance_end[1],advance_end[2],advance);
    }
    if(sum==0)return 1;
    if(sum<0)return 0;
    return 1/sum;
}

float apcA(struct NPC *N, struct robot *robotSelf, struct robot *BB/*, float reAdv*/, float BB_a/*, float *F*/){
    if(robotSelf==NULL)return 0;
    float apBB=0, ap=0, apFBB=0, apF=0;
    ap=HarMean(N, robotSelf->advance_end, robotSelf->type, robotSelf->bumpingDir, robotSelf->advance);
    if(N->ID==0){
//        printf("%*s\n",(int)(ap*20),".");
//        printf("%*s %f\n",10,"---",ap);
    }
    if(robotSelf->nearestFood!=NULL){
//        *F=robotSelf->advance_neareatFood-robotSelf->advance_end[0];
        if(robotSelf->advance_end[0]<=0){
            apF=1/((robotSelf->advance-robotSelf->advance_neareatFood)<0?0.0001:(robotSelf->advance-robotSelf->advance_neareatFood))*N->fc;
        }else{
            
            //        printf("F%f\n",*F);
            apF = (robotSelf->advance>robotSelf->advance_end[0])?(robotSelf->advance-robotSelf->advance_end[0]):0/ ((robotSelf->advance-robotSelf->advance_neareatFood)<0?0.0001:(robotSelf->advance-robotSelf->advance_neareatFood))*N->fc;
        }
    }
    if(BB==NULL){
        return ap+apF;
    }else{
        apBB=HarMean(N, BB->advance_end, BB->type, BB->bumpingDir, BB->advance);
        if(BB->nearestFood!=NULL){
            if(BB->advance_end[0]<=0){
                apFBB=1/((BB->advance-BB->advance_neareatFood)<0?0.0001:(BB->advance-BB->advance_neareatFood))*N->fc;
            }else{
                apFBB = (BB->advance>BB->advance_end[0])?(BB->advance-BB->advance_end[0]):0/ ((BB->advance-BB->advance_neareatFood)<0?0.0001:(BB->advance-BB->advance_neareatFood))*N->fc;
            }
        }
    }
    return sqrtf((ap+apF)*(apBB+apFBB));
//    if(robotSelf->mesa||robotSelf->position<cube->margin||robotSelf->position>1-cube->margin){
//        return (robotSelf->advance-cube->margin)*(ap+apF)+(1+cube->margin-robotSelf->advance)*(apBB+apFBB);
//    }else{
//        return (robotSelf->advance-cube->margin<0)?(robotSelf->advance*(ap+apF)+(1-robotSelf->advance)*(apBB+apFBB)):(robotSelf->advance-1+cube->margin*(ap+apF)+(2-robotSelf->advance-cube->margin)*(apBB+apFBB));
//    }
    
}

float apcLR(struct NPC *N, struct robot *LR, struct robot *LRB/*, float reAdv*/, float LRB_wp){
    if(LR==NULL)return 0;
    float apLRB, apLR, apFLRB=0, apFLR=0;
    apLR=HarMean(N, LR->advance_end, LR->type, LR->bumpingDir, LR->advance);
//    if(N->ID==1)printf("apLR:%f\n",apLR);
    if(LR->nearestFood!=NULL){
        if(LR->advance_end[0]<=0){
            apFLR=1/((LR->advance-LR->advance_neareatFood)<0?0.0001:(LR->advance-LR->advance_neareatFood))*N->fc;
        }else{
            apFLR = (LR->advance>LR->advance_end[0])?(LR->advance-LR->advance_end[0]):0/ ((LR->advance-LR->advance_neareatFood)<0?0:(LR->advance-LR->advance_neareatFood))*N->fc;
        }
    }
    if(LRB==NULL){
        return apLR+apFLR;
    }else{
        apLRB=HarMean(N, LRB->advance_end, LRB->type, LRB->bumpingDir, LRB->advance);
        if(LRB->nearestFood!=NULL){
            if(LRB->advance_end[0]<=0){
                apFLRB=1/((LRB->advance-LRB->advance_neareatFood)<0?0.0001:(LRB->advance-LRB->advance_neareatFood))*N->fc;
            }else{
                apFLRB = (LRB->advance>LRB->advance_end[0])?(LRB->advance-LRB->advance_end[0]):0/ ((LRB->advance-LRB->advance_neareatFood)<0?0:(LRB->advance-LRB->advance_neareatFood))*N->fc;
            }
        }
    }
    return sqrtf((apLR+apFLR)*(apLRB+apFLRB));
//    if(LR->mesa||LR->position<cube->margin||LR->position>1-cube->margin){
//        return (LR->advance-cube->margin)*(apLR+apFLR)+(1+cube->margin-LR->advance)*(apLRB+apFLRB);
//    }else{
//        return (LR->advance-cube->margin<0)?(LR->advance*(apLR+apFLR)+(1-LR->advance)*(apLRB+apFLRB)):(LR->advance-1+cube->margin*(apLR+apFLR)+(2-LR->advance-cube->margin)*(apLRB+apFLRB));
//    }
}

int pfpf=50, testing_id=-1;
//#define RED "\033[0;32;31m"
//#define BLUE "\033[0;32;34m"
//#define GREEN "\033[0;32;32m"
#define RED "|"
#define BLUE "/"
#define GREEN "\\"

//0前 1左 2右
int decide(struct NPC *N, float A, float L, float R){
    float t1,t2,M1,M2,M3;
    bool rig = 0;
    if(A>L){
        if(A>R){
            if(L>R){
                //A>L>R
                t1=A-L;
                t2=L-R;
                M1=0;
                M2=1;
                M3=2;
                if(testing_id!=-1&&N->ID==testing_id){
                    printf(BLUE"%*s",(int)R*pfpf,BLUE);
                    printf(GREEN"%*s",(int)t2*pfpf,GREEN);
                    printf(RED"%*s\n",(int)t1*pfpf,RED);
                }
                if(A<N->rigor)rig=1;
            }else{
                //A>R>L
                t1=A-R;
                t2=R-L;
                M1=0;
                M2=2;
                M3=1;
                if(testing_id!=-1&&N->ID==testing_id){
                    printf(GREEN"%*s",(int)L*pfpf,GREEN);
                    printf(BLUE"%*s",(int)t2*pfpf,BLUE);
                    printf(RED"%*s\n",(int)t1*pfpf,RED);
                }
                if(A<N->rigor)rig=1;
            }
        }else{
            //R>A>L
            t1=R-A;
            t2=A-L;
            M1=2;
            M2=0;
            M3=1;
            if(testing_id!=-1&&N->ID==testing_id){
                printf(GREEN"%*s",(int)L*pfpf,GREEN);
                printf(RED"%*s",(int)t2*pfpf,RED);
                printf(BLUE"%*s\n",(int)t1*pfpf,BLUE);
            }
            if(R<N->rigor)rig=1;
        }
    }else{
        if(A>R){
            //L>A>R
            t1=L-A;
            t2=A-R;
            M1=1;
            M2=0;
            M3=2;
            if(testing_id!=-1&&N->ID==testing_id){
                printf(BLUE"%*s",(int)R*pfpf,BLUE);
                printf(RED"%*s",(int)t2*pfpf,RED);
                printf(GREEN"%*s\n",(int)t1*pfpf,GREEN);
            }
            if(L<N->rigor)rig=1;
        }else{
            if(L>R){
                //L>R>A
                t1=L-R;
                t2=R-A;
                M1=1;
                M2=2;
                M3=0;
                if(testing_id!=-1&&N->ID==testing_id){
                    printf(RED"%*s",(int)A*pfpf,RED);
                    printf(BLUE"%*s",(int)t2*pfpf,BLUE);
                    printf(GREEN"%*s\n",(int)t1*pfpf,GREEN);
                }
                if(L<N->rigor)rig=1;
            }else{
                //R>L>A
                t1=R-L;
                t2=L-A;
                M1=2;
                M2=1;
                M3=0;
                if(testing_id!=-1&&N->ID==testing_id){
                    printf(RED"%*s",(int)A*pfpf,RED);
                    printf(GREEN"%*s",(int)t2*pfpf,GREEN);
                    printf(BLUE"%*s\n",(int)t1*pfpf,BLUE);
                }
                if(R<N->rigor)rig=1;
            }
        }
    }
//    if(t1<N->randm&&!rig){
    if(!rig){
        if(t1<N->randm){
            if(t1+t2<N->randm){
                int r = rand()%(int)N->apAdv;
                if(r<=2){
                    printf("r : %d",r);
                    r = rand()%99;
                    if(r>=50)return 1;
                    else return 2;
                }
                return 0;
            }
            if(M1==0){
                int r = rand()%(int)N->apAdv;
                if(r<=2){
                    printf("r : %d",(int)N->apAdv);
                    return M2;
                }
                return M1;
            }else if(M2==0){
                int r = rand()%(int)N->apAdv;
                if(r<=2){
                    printf("r : %d",(int)N->apAdv);
                    return M1;
                }
                return M2;
            }else{
                int r = rand()%100;
                if(r>=50)return M2;
                return M1;
            }
        }
    }
    return M1;
}

void roboting(struct NPC *N){
//    countingLB=0;countingRB=0;countingBB=0;
    if(!N->alive)return;
    if(!N->H->snakeAlive){
        NPC_endTime[N->ID]=glfwGetTime();
        NPC_endLength[N->ID]=N->H->length;
        N->alive=0;
        snakeDel_withHead(N->H);
        return;
    }
    N->frameCounter--;
    if(N->frameCounter>=0)return;
    N->counting=0;
    struct snakeHead* s=N->H;
    struct robot *Self = creatRobotSelf(N);
    struct robot *L = creatRobotL(N);
    struct robot *R = creatRobotR(N);
    struct robot *LB = NULL;
    struct robot *RB = NULL;
    struct robot *BB = NULL;
    float LB_wp;
    if(L==NULL)LB_wp=getLength(s->width)*1.5+N->bs;
    else LB_wp=getLength(L->width)+getLength(s->width)*0.5+N->bs;
//    float RB_wp=getLength(R->width)+getLength(s->width)*0.5;
    float RB_wp=LB_wp;
    float BB_a;
    if(L==NULL)BB_a=getLength(N->H->width)+N->ts;
    else BB_a=getLength(L->width)+N->ts;
    if(s->mesa){
        if(s->position<=cube->margin+LB_wp){
            LB = creatRBR(N, L, Mm/*, &reAdvLB*/);
        }else if(s->position>=1-cube->margin-RB_wp){
            RB = creatRBR(N, R, Mm/*, &reAdvRB*/);
        }
        if(s->advance<=cube->margin+BB_a){
//            BB = robotBorder_type(N, Mm);
            BB = creatRBR(N, Self, Mm/*, &reAdvBB*/);
        }
    }else{
        if(s->position<cube->margin||s->position>1-cube->margin){
            if(s->position<=LB_wp){
                LB = creatRBR(N, L, mM/*, &reAdvLB*/);
            }else if(s->position>=1-RB_wp){
                RB = creatRBR(N, R, mM/*, &reAdvRB*/);
            }else{
                if(s->position>=cube->margin-RB_wp){
                    RB = creatRBR(N, R, mUm/*, &reAdvRB*/);
                }else if(s->position<=1-cube->margin+LB_wp){
                    LB = creatRBR(N, L, mUm/*, &reAdvLB*/);
                }
            }
            if(s->advance<=cube->margin+BB_a){
//                BB = robotBorder_type(N, mDm);
                BB = creatRBR(N, Self, mDm/*, &reAdvBB*/);
            }
        }else{
            if(s->position<=cube->margin+LB_wp){
                LB = creatRBR(N, L, mDm/*, &reAdvLB*/);
            }else if(s->position>=1-cube->margin-RB_wp){
                RB = creatRBR(N, R, mDm/*, &reAdvRB*/);
            }
            if(s->advance<=BB_a){
//                BB = robotBorder_type(N, mM);
                BB = creatRBR(N, Self, mM/*, &reAdvBB*/);
            }else if(s->advance>=cube->margin&&s->advance<=1-cube->margin+BB_a){
//                BB = robotBorder_type(N, mUm);
                BB = creatRBR(N, Self, mUm/*, &reAdvBB*/);
            }
        }
    }
    float apA=apcA(N, Self, BB/*, reAdvBB*/, BB_a/*, &F*/);
    float apL=apcLR(N, L, LB/*, reAdvLB*/, LB_wp);
    float apR=apcLR(N, R, RB/*, reAdvRB*/, RB_wp);
    int d = decide(N, apA, apL, apR);
    if(d==0){
        if(N->H->advance-getLength(Self->eatRange)/cube->size<=N->H->advance_end||N->H->advance-getLength(Self->eatRange)/cube->size<=N->H->advance_neareatFood){
            if((N->H->advEndB!=NULL||N->H->advEndH!=NULL||N->H->advEndT!=NULL||N->H->advEndDy!=NULL)&&apA>N->rigor){
                d = decide(N, apA*N->es_sl, apL, apR);
//                printf("2535\n");
            }
//            printf("2537\n");
            if(d==0)snakeKeyBoard(N->H, _SPACE);
        }
    }
    if(d==1){
        snakeTurn(N->H, turnLEFT);
    }else if(d==2){
        snakeTurn(N->H, turnRIGHT);
    }
    N->frameCounter=N->counting/N->perFrame;
    deletRobot(Self);
    deletRobot(BB);
    deletRobot(L);
    deletRobot(R);
    deletRobot(LB);
    deletRobot(RB);
}

void startingRobot(struct NPC* N){
    if(N->H->advance+getLength(N->H->eatRange)<=N->H->advance_end){
        snakeKeyBoard(N->H, _SPACE);
    }
}


void generateVAOVBO_SR(unsigned int *VBO_Ver, unsigned int *VBO_model, unsigned int *VBO_shininess, unsigned int *VBO_diffuse/*, unsigned int *VBO_specular*/, unsigned int *VAO_SR, int MAX){
    glGenVertexArrays(1, VAO_SR);
    geterro(1727)
    glGenBuffers(1, VBO_Ver);
    glGenBuffers(1, VBO_model);
    glGenBuffers(1, VBO_shininess);
    glGenBuffers(1, VBO_diffuse);
//    glGenBuffers(1, VBO_specular);
    glBindBuffer(GL_ARRAY_BUFFER, *VBO_Ver);
    geterro(1733)
//    glBufferData(GL_ARRAY_BUFFER, sizeof(snake_IniVer)+(sizeof(mat4)+sizeof(int)*2+sizeof(float))*Max, NULL, GL_STREAM_DRAW);
//    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(snake_IniVer), snake_IniVer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(snake_IniVer), snake_IniVer, GL_STATIC_DRAW);
    geterro(1737)
    glBindBuffer(GL_ARRAY_BUFFER, *VBO_diffuse);
    glBufferData(GL_ARRAY_BUFFER, sizeof(int)*MAX, NULL, GL_STREAM_DRAW);
    geterro(1740)
//    glBindBuffer(GL_ARRAY_BUFFER, *VBO_specular);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(int)*MAX, NULL, GL_STREAM_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, *VBO_shininess);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*MAX, NULL, GL_STREAM_DRAW);
    //model
    glBindBuffer(GL_ARRAY_BUFFER, *VBO_model);
    glBufferData(GL_ARRAY_BUFFER, sizeof(mat4)*MAX, NULL, GL_STREAM_DRAW);
    glBindVertexArray(*VAO_SR);
    glBindBuffer(GL_ARRAY_BUFFER, *VBO_Ver);
    //位置属性
    //注意某一次更新后移除了颜色数据, 修改了步长和offset
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
//    //颜色属性
//    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(3*sizeof(float)));
    //法线
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
    //diffuse
    glBindBuffer(GL_ARRAY_BUFFER, *VBO_diffuse);
    glVertexAttribPointer(3, 1, GL_INT, GL_FALSE, sizeof(int), (void*)0);
    //specular
//    glBindBuffer(GL_ARRAY_BUFFER, *VBO_specular);
//    glVertexAttribPointer(4, 1, GL_INT, GL_FALSE, sizeof(int), (void*)0);
    //shininess
    glBindBuffer(GL_ARRAY_BUFFER, *VBO_shininess);
    glVertexAttribPointer(5, 1, GL_FLOAT, GL_FALSE, sizeof(float), (void*)0);
    //model
    glBindBuffer(GL_ARRAY_BUFFER, *VBO_model);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)0);
    glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)(4*sizeof(float)));
    glVertexAttribPointer(8, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)(8*sizeof(float)));
    glVertexAttribPointer(9, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)(12*sizeof(float)));
    glEnableVertexAttribArray(0);
//    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
//    glEnableVertexAttribArray(4);
    glEnableVertexAttribArray(5);
    glEnableVertexAttribArray(6);
    glEnableVertexAttribArray(7);
    glEnableVertexAttribArray(8);
    glEnableVertexAttribArray(9);
    glVertexAttribDivisor(3, 1);
//    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);
    glVertexAttribDivisor(6, 1);
    glVertexAttribDivisor(7, 1);
    glVertexAttribDivisor(8, 1);
    glVertexAttribDivisor(9, 1);
    glBindVertexArray(0);
}

void generateVAOVBO_SR_forDepth(unsigned int *VBO_Ver, unsigned int *VBO_model, unsigned int *VAO_SR, int MAX){
    glGenVertexArrays(1, VAO_SR);
    glBindVertexArray(*VAO_SR);
    glBindBuffer(GL_ARRAY_BUFFER, *VBO_Ver);
    //位置属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
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


void updateVBO_SR(unsigned int *VBO_model, unsigned int *VBO_shininess, unsigned int *VBO_diffuse, /*unsigned int *VBO_specular, int Snake_diffuse_textureU[3], int Rot_diffuse_textureU[3][3], int specular_textureU[3], */bool *f){
    if(*f)return;
    glBindBuffer(GL_ARRAY_BUFFER, *VBO_model);
    geterro(1793)
    mat4 *m=(mat4*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    geterro(1795)
    debugp(1796, m)
    glBindBuffer(GL_ARRAY_BUFFER, *VBO_shininess);
    float *shininess=(float*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    geterro(1797)
    debugp(1800, shininess)
    glBindBuffer(GL_ARRAY_BUFFER, *VBO_diffuse);
    int *diffuse=(int*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
//    glBindBuffer(GL_ARRAY_BUFFER, *VBO_specular);
//    int *specular=(int*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    struct snakeHead *snake=&snakeH;
    if(!snake->snakeAlive)snake=snake->others;
//    if(STATE==0&&snake==&snakeH){
//        snake=snake->others;
//    }

//    struct snakeHead* testing=NULL;
//    if(Npc[0]!=NULL) testing=Npc[0]->H;
//    struct snakeHead* testing = NULL;
//    if(Npc[2]!=NULL) testing = Npc[0]->H;
//    if(Npc[0]!=NULL) testing=Npc[0]->H;
    
    int i=0;
    while (snake!=NULL) {
        if(snake->snakeAlive){
            debugi(snake2010, snake->ID)
            debugi(snake2010,i)
            debugmat4(1789, *(snake->headMat))
            geterro(1807)
            glm_mat4_copy(*(snake->headMat), m[i]);
            debugmat4(1813, *m)
            geterro(1809)
            shininess[i]=1.0f;
            //        diffuse[i]=Snake_diffuse_textureU[0];
            diffuse[i]=-snake->ID;
            //        if(testing!=NULL&&testing->advEndH==snake){
            //            diffuse[i]=-6;
            //        }
            //        debugi(1816, diffuse[i]);
            //        specular[i]=specular_textureU[0];
            i++;
            if(!snake->noTail){
                struct snakeBody *b=snake->post;
                while (b!=NULL) {
                    glm_mat4_copy(*(b->snakeMat), m[i]);
                    shininess[i]=1.0f;
                    //                diffuse[i]=Snake_diffuse_textureU[1];
                    diffuse[i]=-snake->ID;
                    //                if(testing!=NULL&&testing->advEndB==b){
                    //                    diffuse[i]=-1;
                    //                }
                    //                specular[i]=specular_textureU[1];
                    i++;
                    b=b->post;
                }
                glm_mat4_copy(*(snake->tail->tailMat), m[i]);
                shininess[i]=1.0f;
                //            diffuse[i]=Snake_diffuse_textureU[2];
                diffuse[i]=-snake->ID;
                //            if(testing!=NULL&&testing->advEndT==snake->tail){
                //                diffuse[i]=-6;
                //            }
                //            specular[i]=specular_textureU[2];
                i++;
            }
        }
        snake=snake->others;
    }
    struct rot *r=rotHandle->post;
    while (r!=NULL) {
//        memcpy(m++, *(r->rotMat), sizeof(mat4));
        glm_mat4_copy(*(r->rotMat), m[i]);
        shininess[i]=1.0f;
//        diffuse[i]=Rot_diffuse_textureU[r->state][r->type];
        diffuse[i]=r->state;
//        diffuse[i]=-6;
//        if(testing!=NULL&&testing->advEndDy==r){
//            diffuse[i]=-6;
//        }
//        if(r->state==0)diffuse[i]=-1;
//        specular[i]=specular_textureU[r->type];
        i++;
        r=r->post;
    }
//    debugi(1816, diffuse[0]);
    
    glBindBuffer(GL_ARRAY_BUFFER, *VBO_model);
    glUnmapBuffer(GL_ARRAY_BUFFER);
    glBindBuffer(GL_ARRAY_BUFFER, *VBO_shininess);
    glUnmapBuffer(GL_ARRAY_BUFFER);
    glBindBuffer(GL_ARRAY_BUFFER, *VBO_diffuse);
    glUnmapBuffer(GL_ARRAY_BUFFER);
//    glBindBuffer(GL_ARRAY_BUFFER, *VBO_specular);
//    glUnmapBuffer(GL_ARRAY_BUFFER);
    *f=1;
}

void rebindtextureU(int *collapse, int *textureU, int collapse_num, int textureU_num, unsigned int *texture, unsigned int textureType){
    for (int i=0; i<collapse_num; i++) {
        for (int j=0; j<textureU_num; j++) {
            if(*(textureU+j)==*(collapse+i)){
                glActiveTexture(GL_TEXTURE0+*(collapse+i));
                glBindTexture(textureType, *(texture+j));
            }
        }
    }
}

void drawSR(Shader *shader, unsigned int *VBO_model, unsigned int *VBO_shininess, unsigned int *VBO_diffuse,/* unsigned int *VBO_specular, int Snake_diffuse_textureU[3], int Rot_diffuse_textureU[3][3], int specular_textureU[3],*/unsigned int *VAO_SR, Camera *camera, mat4 *proj, bool *f){
    shader->use(shader);
    glBindVertexArray(*VAO_SR);
    mat4 view;
    camera->GetViewMatrix(camera, &view);
    shader->setMat4fv(shader, "view", (float *)view);
    debug(1241)
    shader->setMat4fv(shader,"proj",(float*)proj[0]);
    int num = countingSR();
    debugi(1864, num)
    updateVBO_SR(VBO_model, VBO_shininess, VBO_diffuse, /*VBO_specular, Snake_diffuse_textureU, Rot_diffuse_textureU, specular_textureU,*/ f);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 36, num);
//    printf("%d\n",num);
}

#endif
