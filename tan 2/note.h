//
//  note.h
//  op
//
//  Created by BoBo W on 2025/5/24.
//
#ifndef note_H
#define note_H
#include "snake.h"
#include "cube.h"

//#define NoteDebuging

#ifdef NoteDebuging
#define notedegub ;
#endif
#ifndef NoteDebuging
#define notedebug //;
#endif

struct note{
    int ID;
    int note;
    float correct;
    long width;
    struct snakeHead* s;
    int step;
    struct note* others;
};
struct note nHandel;
struct note* nHd=&nHandel;

enum alphabet{
    _s,
    _n,
    _a,
    _k,
    _e,
    _0,
    _1,
    _2,
    _3,
    _4,
    _5,
    _6,
    _7,
    _8,
    _9,
    _w,
    _t,
    _d,
    __
};

//0,1起笔位置, 3宽度 4长度
int _widNum[18]={
    3,//s
    3,//n
    4,//a
    5,//k
    3,//e
    4,//0
    2,//1
    4,
    4,
    3,
    4,
    4,
    6,
    4,
    4,//9
    4,//w
    2,//T
    3//D
};
/*
 float advS[20][25]={
 //起始点x轴比例，起始点y轴比例，总x轴比例，总y轴比例，各笔画比例，-1终止
     {15.5,25,18.5,31,3.25,12.25,7.5,17,12.25,17,17,17,12.25,12.25,7.5,7.5,2.5,-1},
 //    s
     {0,0,18.5,31,30.25,4.75,29.25,14.75,29.25,8.25,-1},
 //    N
     {0,30.25,18.5,31,30.25,19.5,29.5,4.75,16.5,9.75,-1},
 //    A
     {0,0,1.675,18.5,31,4.75,12,5,12.25,12,4.75,7.25,19.5,7.25,5,12,12,4.75,-1},
 //    K
     {5,25.25,18.5,31,3.75,12,7.25,17,29.25,16.75,5,12,7,9.5,5,9.5,-1},
 //    E
     {3.5,5.5,18.5,31,3.5,5,17.5,30,5,-1},
 //    1
     {17,27.5,18.5,31,3.5,17.5,7.5,17.5,22.5,17.5,12.5,12.5,7.5,7.5,2.5,-1},
 //    2
     {4.5,22.5,18.5,31,3.5,7.5,7.5,12.5,12.5,17.5,30,17.5,12.5,12.5,12.5,12.5,2.5,-1},
 //    3
     {4.5,3.5,18.5,31,3.5,5,17.5,7.5,12.5,5,12.5,5,5,10,-1},
 //    4
     {18,3.5,18.5,31,3.5,17.5,7.5,17.5,22.5,17.5,12.5,12.5,7.5,7.5,2.5,-1},
 //    5
     {18,3.5,18.5,31,3.5,17.5,30,17.5,12.5,12.5,7.5,7.5,2.5,-1},
 //    6
     {3.5,5.5,18.5,31,3.5,5,10,10,5,7.5,10,5,10,5,5,2.5,15,-1},
 //    7
     {12,7.5,18.5,31,3.5,7.5,7.5,12.5,12.5,17.5,30,17.5,12.5,12.5,7.5,7.5,2.5,-1},
 //    8
     {12,7.5,18.5,31,3.5,7.5,7.5,12.5,12.5,17.5,17.5,17.5,12.5,17.5,2.5,-1},
 //    9
     {18.5,30.5,18.5,31,18.5,30,17.5,25,12.5,20,7.5,15,2.5,-1},
 //    0
     {0,0,18.5,31,30.5,7,15,5,15,7.5,29.5,-1},
 //    W
     {23,0,18.5,31,23,5,12,27,7.5,-1},
 //    T
     {0,0,18.5,31,30.5,5,30,12.5,30,8.5,-1}
 //    D
     };
 //第一位：0向上，1向左，2向下，3向右；后面： 0:_LEFT, 1:_RIGHT, 2:end
 int turnS[20][15]={
     {0,0,0,0,0,0,1,1,1,1,1,1,1,2},
 //    S
     {1,0,1,1,1,2},
 //    N
     {0,1,1,1,1,0,0,0},
 //    A
     {2,0,0,1,1,0,0,0,1,1,0,0,0,0,2},
 //    K
     {0,1,1,1,1,1,1,1,0,0,1,1,2},
 //    E
     {3,0,0,0,0,2},
 //    1
     {2,1,1,1,0,0,0,0,0,0,0,2},
 //    2
     {2,0,0,0,0,0,0,0,0,0,0,0,0,2},
 //    3
     {0,0,0,0,1,0,0,1,0,0,2},
 //    4
     {0,0,0,0,1,1,1,1,1,1,1,2},
 //    5
     {0,0,0,0,0,0,0,0,0,2},
 //    6
     {1,1,1,1,1,0,0,1,0,0,1,0,0,1,2},
 //    7
     {0,0,0,0,0,0,0,0,0,0,0,0,0,2},
 //    8
     {0,0,0,0,0,0,0,0,0,0,0,2},
 //    9
     {1,1,1,1,1,1,1,1,1,2},
 //    0
     {2,0,0,1,1,0,0,2},
 //    W
     {1,0,0,1,1,2},
 //    T
     {2,0,0,1,1,1,2}
 //    D
     };
 */

float _advS[18][20]=/*{{0,0,30.25,4.75,29.25,14.75,29.25,8.25,-1}};*/
{
 {15.5,25,19,0,3.25,12.25,7.5,17,12.25,17,17,17,12.25,12.25,7.5,7.5,2.5,-1},//S
 {0,0,19,0,30.25,4.75,29.25,14.75,29.25,8.25,-1},//N
 {0,30.25,19,0,30.25,19.5,29.5,4.75,16.5,9.75,-1},//A
 {0,0,21,0,30.25,4.75,12,5,12.25,12,4.75,7.25,19.5,7.25,5,12,12,4.75,-1},//K
 {5,25.25,19,0,3.75,12,7.25,17,29.25,16.75,5,12,7,9.5,5,9.5,-1},//E
//    {15.5,25,18.5,31,3.25,12.25,7.5,17,12.25,17,17,17,12.25,12.25,7.5,7.5,2.5,-1},
////    s
//    {0,0,18.5,31,30.25,4.75,29.25,14.75,29.25,8.25,-1},
////    N
//    {0,30.25,18.5,31,30.25,19.5,29.5,4.75,16.5,9.75,-1},
////    A
//    {0,0,1.675,18.5,31,4.75,12,5,12.25,12,4.75,7.25,19.5,7.25,5,12,12,4.75,-1},
////    K
//    {5,25.25,18.5,31,3.75,12,7.25,17,29.25,16.75,5,12,7,9.5,5,9.5,-1},
////    E
//    {3.5,5.5,18.5,31,3.5,5,17.5,30,5,-1},
    
    {18.5,30.5,18.5,31,18.5,30,17.5,25,12.5,20,7.5,15,2.5,-1},
//    0
    {3.5,5.5,18.5,31,3.5,5,17.5,30,5,-1},
//    1
    {17,27.5,18.5,31,3.5,17.5,7.5,17.5,22.5,17.5,12.5,12.5,7.5,7.5,2.5,-1},
//    2
    {4.5,22.5,18.5,31,3.5,7.5,7.5,12.5,12.5,17.5,30,17.5,12.5,12.5,7.5,7.5,3.5,-1},
//    3
    {4.5,3.5,18.5,31,3.5,5,17.5,7.5,12.5,5,12.5,5,5,10,-1},
//    4
    {18,3.5,18.5,31,3.5,17.5,7.5,17.5,22.5,17.5,12.5,12.5,7.5,7.5,2.5,-1},
//    5
    {18,3.5,18.5,31,3.5,17.5,30,17.5,12.5,12.5,7.5,7.5,2.5,-1},
//    6
    {3,5.5,18.5,31,2,4,8,12.5,8,4,6,8,4.5,8,4,4,2,12.5,-1},
    // 7
    {12,7.5,18.5,31,3.5,7.5,7.5,12.5,12.5,17.5,30,17.5,12.5,12.5,7.5,7.5,2.5,-1},
//    8
    {12,7.5,18.5,31,3.5,7.5,7.5,12.5,12.5,17.5,17.5,17.5,12.5,17.5,2.5,-1},
//    9
    {0,0,18.5,31,30.5,7,15,5,15,7.5,29.5,-1},
//    W
    {23,0,24,31,23,5,12,27,7.5,-1},
//    T
    {0,0,18.5,31,30.5,4,29.5,10,6,6,18.5,6,6,4,-1}
   // D

 };

//第一位：0向上，1向左，2向下，3向右；后面： 0:_LEFT, 1:_RIGHT, 2:end
int _turnS[18][15]=/*{{2,0,0,1,1,1,2}};*/
{
 {0,0,0,0,0,0,1,1,1,1,1,1,1,2},
 {2,0,0,1,1,1,2},
 {0,1,1,1,1,0,0,0,2},
 {2,0,0,1,1,0,0,0,1,1,0,0,0,1,2},
 {0,1,1,1,1,1,1,1,0,0,1,1,2},
//    {0,0,0,0,0,0,1,1,1,1,1,1,1,2},
////    S
//    {2,0,0,1,1,1,2},
////    N
//    {0,1,1,1,1,0,0,0,2},
////    A
//    {2,0,0,1,1,0,0,0,1,1,0,0,0,1,2},
////    K
//    {0,1,1,1,1,1,1,1,0,0,1,1,2},
////    E

    {1,1,1,1,1,1,1,1,1,2},
//    0
    {1,1,1,1,1,2},
//    1
    {2,1,1,1,0,0,0,0,0,0,0,2},
//    2
    {2,0,0,0,0,0,0,0,0,0,0,0,0,2},
//    3
    {0,0,0,0,1,0,0,1,0,0,2},
//    4
    {0,0,0,0,1,1,1,1,1,1,1,2},
//    5
    {0,0,0,0,0,0,0,0,0,2},
//    6
    {1,1,1,1,1,0,0,1,0,0,1,0,0,1,2},
   // 7

    {0,0,0,0,0,0,0,0,0,0,0,0,0,2},
//    8
    {0,0,0,0,0,0,0,0,1,1,1,2},
//    9
    {2,0,0,1,1,0,0,2},
    //    W
        {1,0,0,1,1,2},
    //    T
    {2,0,0,1,1,0,1,1,0,1,2}
   // D



 };
//posl水平 posu竖直方向
struct note* PrintS_Ini(int note_value, enum surFace sur, enum surFace up, float pos_l,float pos_u,float correct,long width,float velocity, int ID){
    if(note_value==__)return NULL;
    struct note* n = (struct note*)  malloc(sizeof(struct note));
    struct note* temp=nHd;
    while(temp->others!=NULL){
        temp=temp->others;
    }
    long tobE =  width*_advS[note_value][4]*correct;
    if(tobE<width) correct=1/_advS[note_value][4];
    temp->others=n;
    n->others=NULL;
    n->note=note_value;
    n->correct=correct;
    n->step=0;
    n->width=width;
    n->ID=ID;
    enum surFace dir;
    float l=getLength(_advS[note_value][0]*correct*width)/cube->size+pos_l,u=getLength(_advS[note_value][1]*correct*width)/cube->size+pos_u;
//    notedebug printf("p1:%f,a1:%f\n",l,u);
    float t = l;
    if(_turnS[note_value][0]==0){
        dir=up;
    }
    else if(_turnS[note_value][0]==1){
        dir=map[sur][up];
//        t=l;
        l=1-u;
        u=t;
    }
    else if(_turnS[note_value][0]==2){
        dir=5-up;
        l=1-l;
        u=1-u;
    }
    else if(_turnS[note_value][0]==3){
        dir=5-map[sur][up];
//        t=l;
        l=u;
        u=1-t;
    }
    else dir=er;
//    notedebug printf("p2:%f,a2:%f\n",l,u);
    n->s=creatSnake(ID, width, 1, l, u, dir, sur, velocity, NULL, 0, width*_advS[note_value][4]*correct, 1);
//    notedebug printf("%d %p\n",note_value,n->s);
    return n;
}
void script(int ID, char *c, float gap, long width, enum surFace sur, enum surFace up,float pos_u,float correct,float velocity, float margin){
    if(c==NULL||*c=='\0')return;
    
    //gap:几倍的S的宽度
    float sum=0,wn=0;
    int i=0;
    while (*(c+i)!='\0') {
        int t=0;
        if(*(c+i)=='S')t=_s;
        else if(*(c+i)=='N')t=_n;
        else if(*(c+i)=='A')t=_a;
        else if(*(c+i)=='K')t=_k;
        else if(*(c+i)=='E')t=_e;
        else if(*(c+i)>='0'&&*(c+i)<='9')t=*(c+i)-'0'+_0;
        else if(*(c+i)=='W')t=_w;
        else if(*(c+i)=='T')t=_t;
        else if(*(c+i)=='D')t=_d;
        else t=__;
//        notedebug printf("note %d\n",t);
        if(t!=__){
            sum+=_advS[t][2]+_advS[_s][2]*gap-_widNum[t];
            wn+=_widNum[t];
        }else{
            sum+=_advS[_s][2]+_advS[_s][2]*gap;
        }
        i++;
    }
    sum-=_advS[_s][2]*gap;
    float k=getLength(sum*width*correct+wn*width)/cube->size/(1-2*cube->margin-2*margin);
//    if(k<1)k=1;
//    printf("k:%f",k);
    i=0;
    float acc=getLength(width/k)/cube->size+cube->margin+margin;
    while (*(c+i)!='\0') {
        int t=0;
        if(*(c+i)=='S')t=_s;
        else if(*(c+i)=='N')t=_n;
        else if(*(c+i)=='A')t=_a;
        else if(*(c+i)=='K')t=_k;
        else if(*(c+i)=='E')t=_e;
        else if(*(c+i)>='0'&&*(c+i)<='9')t=*(c+i)-'0'+_0;
        else if(*(c+i)=='W')t=_w;
        else if(*(c+i)=='T')t=_t;
        else if(*(c+i)=='D')t=_d;
        else t=__;
        PrintS_Ini(t, sur, up, acc, pos_u, correct, width/k, velocity,ID);
//        notedebug printf("No.%d,value%d,acc:%f\n",i,t,acc);
//        printf("width:%f\n",getLength(width*correct/k));
        acc+=getLength(width*correct/k*(_advS[t][2]-_widNum[t]+_advS[_s][2]*gap)+_widNum[t]*width/k)/cube->size;
        
        i++;
    }
//    notedebug printf("acc:%f",acc);

}
void PrintS_Print(float deltaTime){
    debug(note48)
    struct note* temp=nHd->others;
//    int i=0;
    while(temp!=NULL){
        struct snakeHead* s=temp->s;
        if(s->stall){
            temp=temp->others;
            continue;
        }
        snakeUpdate(s, s->velocity, deltaTime);
//        notedebug printf("%d %d up:%c dir:%c adv:%.12f pos:%.12f len:%.12f wid:%.12f mesa:%d \n",i++,temp->note,enumtest[s->up],enumtest[s->direction],s->advance,s->position,getLength(s->length),getLength(s->width),s->mesa);
        debugSnakePos(note72, s)
        debugp(note73, s)
        if(s->toBeElongation<=0){
            if(_advS[temp->note][5+temp->step]<=0){
                s->stall=1;
                s->toBeElongation=0;
            }else{
                s->advance-=getLength(s->toBeElongation)/cube->size;
                s->length+=s->toBeElongation;
                getTrans2MatH(s);
                s->toBeElongation=_advS[temp->note][5+temp->step]*temp->correct*temp->width;
                if(!snakeTurn(s,_turnS[temp->note][1+temp->step])){
                    debug(note83)
                }
                debugf(note85,_advS[temp->note][5+temp->step]*temp->correct*temp->width)
                debugi(note85,_turnS[temp->note][1+temp->step])
                if(temp->ID==-1&&(s->advance-s->advance_end<getLength(s->toBeElongation))){
                    s->toBeElongation=D(s->advance-s->advance_end)+1;
                }
                temp->step++;
            }
        }
//        if(s->advance-s->advance_end<getLength(s->toBeElongation)){
//            s->toBeElongation=D(s->advance-s->advance_end);
//        }
        temp=temp->others;
    }
    debug(note68)
}

void noteClean(void){
    struct note *n = nHd->others;
    while(n!=NULL){
        struct note *t=n;
        snakeDel_withHead(n->s);
        n=n->others;
        free(t);
    }
    nHd->others=NULL;
}

void noteClean_ID(int ID){
    struct note *n = nHd;
    while(n->others!=NULL){
        if(n->others->s->ID==ID){
            struct note *t=n->others;
            snakeDel(t->s);
            free(t);
            n->others=n->others->others;
        }else n=n->others;
    }
}

void noteRelease_ID(int ID){
    struct note *n = nHd;
    while(n->others!=NULL){
        if(n->others->ID==ID){
            struct note *t=n->others;
            t->s->stall=0;
            t->s=NULL;
            n->others=n->others->others;
            free(t);
        }else n=n->others;
    }
}

#endif
