//
//  main.c
//  tan
//
//  Created by BoBo W on 2025/4/3.
//
#include <stdio.h>
#include <stdbool.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include "stb_image.h"
#include "shader.h"
#include <cglm/cglm.h>
#include "CAMERA.h"
#include "cube.h"
#include "snake.h"
#include "food.h"
#include "texture.h"
#include "light.h"
#include "note.h"
#include "NPC_config.h"
#include "audio.h"
#include "record.h"
#include "score.h"

#define _windSpeed 0.05
#define NPC_num 5
#define MAX_deltatime 0.01
//#define debuging

void processInput(GLFWwindow *window);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
#ifdef _WIN32
#include <windows.h>
#include <shellscalingapi.h>
#pragma comment(lib, "Shcore.lib")
#endif
// DPI处理状态
typedef struct {
    GLFWwindow* window;
    int logical_width;
    int logical_height;
    int framebuffer_width;
    int framebuffer_height;
    float content_scale;
} DPIContext;
DPIContext ctx;

void init_dpi_awareness(void);
float get_content_scale(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void window_size_callback(GLFWwindow* window, int width, int height);
void content_scale_callback(GLFWwindow* window, float xscale, float yscale);
void create_dpi_context(GLFWwindow* window);
void get_dpi_state(int* fb_width, int* fb_height, float* scale);



//camera
Camera camera;
Camera* pcam=&camera;
vec3 position = {0.0f, 0.0f, 3.0f};

bool firstMouse = true;
float lastX = 800/2.0f, lastY = 600/2.0f;

// stores how much we're seeing of either texture
float mixValue = 0.2f;

float deltaTime = 0.0f; // 当前帧与上一帧的时间差
float lastFrame = 0.0f; // 上一帧的时间

//0diffuse 1specular
int Cube_textureU[2] = {1,2};
//head body tail
//int Snake_diffuse_textureU[3] = {0,1,2};
//int specular_textureU[3] = {12,13,14};
//head body tail
//int Rot_diffuse_textureU[3][3] = {3,4,5,6,7,8,9,10,11};
//const int Rot_specular_textureU[3] = {9,10,11};
int collapse[]={};

//0dir 1spot
int depth_textureU[2] = {15,16};

bool spaceKey=0;
bool directionKey=0;

//unsigned int snakeDiffuseTexture[3];
//unsigned int rotDiffuseTexture[3][3];
unsigned int SpecularTexture[3];

////[0-head;1-body;2-tail][face;end;left;up;right]
//unsigned int snakeDiffuseTexture[3][5];
//unsigned int snakeSpecularTexture[3][5];
////[0-stat0;1-1;2-2][face;end;left;up;right]
//unsigned int rotDiffuseTexture[3][5];
//unsigned int rotSpecularTexture[3][5];

//0Ver 1model 2shininess 3diffuse --4specular--
unsigned int VAO_SR, VAO_SR_depth, VBO_SR[4];

//0Ver 1model
unsigned int VAO_F, VAO_F_depth, VBO_F[2];

unsigned int cubeVAO, cubeVAO_depth;

int Max;
int foodN=0;
//bool newgame=0;
void RenderSrc(Shader *cubeShader,Shader *snakeShader,Shader *foodShader,float cubeOffSet, float cubeOffSet2, bool *f);

float mixure(float m1,float tempr,float n,float color,int i){
    return color*m1+(1-m1)*((warmFilter[i]*tempr+coolFilter[i]*(1-tempr))*(1-n)*0.8+noon[i]*n*0.2);
}
float windSpeed=_windSpeed;

int main(void)
{
    
    srand((unsigned)time(NULL));
    
    IniCub(&Cube);
    
    // 初始化 GLFW
    glfwInit();
    // 配置 OpenGL 上下文
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
#ifdef __APPLE__
    glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_TRUE); // macOS Retina支持
    //for apple
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    
    init_dpi_awareness();
    
    // 创建窗口
    GLFWwindow* window = glfwCreateWindow(800, 600, "first", NULL, NULL);
    if (window==NULL) {
        printf("Failed to creat GLFW window");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window); // 必须先设置上下文
    // 创建DPI上下文
    create_dpi_context(window);
    
    //隐藏鼠标
    //    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    //注册鼠标回调函数
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    //    glfwSetCursorPosCallback(window, cursor_position_callback);
    
    //    // 初始设置视口
    //    glViewport(0, 0, ctx.framebuffer_width, ctx.framebuffer_height);
    
    // 初始化 GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("Failed to initialize GLAD\n");
        return -1;
    }
    
    init_scoreprinting();
    
    init_audio("tan/res/SnakeBgm.WAV");
    
    //启用深度缓冲
    glEnable(GL_DEPTH_TEST);
    
    //使用封装的Shader
    Shader cubeShader=IniSha("tan/vshader.vs", "tan/fshader.fs");
    Shader snakeShader=IniSha("tan/vshader_snake.vs", "tan/fshader_snake.fs");
    Shader foodShader=IniSha("tan/vshader_food.vs", "tan/fshader_food.fs");
    Shader simpleDepthShader=IniSha("tan/vDepth.vs", "tan/fDepth.fs");
    Shader simpleDepthShader_SR=IniSha("tan/vDepth_snake.vs", "tan/fDepth.fs");
    snakeShader.use(&snakeShader);
    
    //使图像不上下颠倒
    stbi_set_flip_vertically_on_load(true);
    
    //生成纹理
    unsigned int texture1,texture2;
    load_texture(&texture1, "tan/res/gr.jpeg", GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_NEAREST, GL_NEAREST, Cube_textureU[0]);
    load_texture(&texture2, "tan/res/sh.PNG", GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_NEAREST, GL_NEAREST, Cube_textureU[1]);
    
    //注意颜色通道
    geterro(main122)
    geterro(main123)
    
    setCubeMaterial(&cubeShader, Cube_textureU[0], Cube_textureU[1], 1.0);
    
    rotHandle->post=NULL;
    //camera初始化
    IniCam_vec(&camera, &position, &_UP, YAW, PITCH, 3);
    
    IniLight(&camera, depth_textureU[0], depth_textureU[1]);

    debugp(main114, &snakeTransFinalH);
    debugp(main115, snakeH.headMat)
    
    Max=FragmentMax;
    geterro(main135)
    //for cube
    //创建顶点数组对象(VAO)
    
    glGenVertexArrays(1, &cubeVAO);
    glGenVertexArrays(1, &cubeVAO_depth);
    //创建顶点缓冲对象(VBO)
    unsigned int cubeVBO;
    glGenBuffers(1, &cubeVBO);
    //绑定cubeVBO
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    //传输ARRAY_BUFFER数据
    glBufferData(GL_ARRAY_BUFFER, sizeof(_cubeVertices), _cubeVertices, GL_STATIC_DRAW);
    //绑定cubeVAO
    glBindVertexArray(cubeVAO);
    //绑定cubeVBO
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    geterro(main151)
    //如何解析顶点数据
    /*每个顶点属性从一个VBO管理的内存中获得它的数据，而具体是从哪个VBO（程序中可以有多个VBO）获取则是通过在调用glVertexAttribPointer时绑定到GL_ARRAY_BUFFER的VBO决定的。*/
    //位置属性
    //注意某次更新后移除了颜色属性, 对应的步长也应该修改(原来是12)(还有offset)还有depth的也要改
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    //颜色属性
    //    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(3*sizeof(float)));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6*sizeof(float)));
    geterro(main160)
    glEnableVertexAttribArray(0);
    //    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    //解绑cubeVAO
    glBindVertexArray(0);
    
    glBindVertexArray(cubeVAO_depth);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
    
    //解绑
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    
    debugi(170, Max)
    geterro(main174)
    generateVAOVBO_SR(&VBO_SR[0], &VBO_SR[1], &VBO_SR[2], &VBO_SR[3], /*&VBO_SR[4],*/ &VAO_SR, Max);
    generateVAOVBO_SR_forDepth(&VBO_SR[0], &VBO_SR[1], &VAO_SR_depth, Max);
    geterro(main175)
    
    
    generateVAOVBO_F(&VBO_F[0], &VBO_F[1], &VAO_F, foodNum);
    generateVAOVBO_F_forDepth(&VBO_F[0], &VBO_F[1], &VAO_F_depth, foodNum);
    
    
    
    //面剔除
    glEnable(GL_CULL_FACE);
    
    
    //    debugmat3(main170,facingMatX)
    //    glm_mat4_mul(facingMatZ4, facingMatZ4, test);
    //    glm_mat4_mul(test, facingMatX4, test);
    //    glm_mat4_mul(test, facingMatX4, test);
    //    glm_mat4_mul(test, facingMatX4, test);
    //    debugmat4(main175, test)
    //    glm_mat4_copy(facingMatY, test);
    
    
    
    //    float vertices1[] = {
    //        -0.4f,-0.3f,-1.0f,0.0f,0.0f,
    //        -0.4f,0.3f,-1.0f,0.0f,1.0f,
    //        0.4f,0.3f,-1.0f,1.0f,1.0f,
    //
    //        0.4f,-0.3f,-1.0f,1.0f,0.0f,
    //        -0.4f,-0.3f,-1.0f,0.0f,0.0f,
    //        0.4f,0.3f,-1.0f,1.0f,1.0f
    //    };
    
    //    unsigned int VAOID,VBOID;
    //    glGenVertexArrays(1,&VAOID);
    //    glBindVertexArray(VAOID);
    //    glGenBuffers(1,&VBOID);
    //    glBindBuffer(GL_ARRAY_BUFFER,VBOID);
    //    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
    //    glBindVertexArray(VAOID);
    //    glBindBuffer(GL_ARRAY_BUFFER,VBOID);
    //    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    //    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
    //    glEnableVertexAttribArray(0);
    //    glEnableVertexAttribArray(1);
    //    glBindVertexArray(0);
    //    Shader testS = IniSha("tan/test.vs", "tan/test.fs");
    //    testS.use(&testS);
    //    testS.setInt(&testS,"depthMap",depth_textureU[0]);
    //    debug(main287)
    //
    //NewGame:
    //    printf("Newgame!\n");
    //    if(newgame){
    //        noteClean();
    //        while (snakeDel_withHead(snakeH.others)!=-1);
    //        rotFree();
    //        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //        newgame=0;
    //    }
    //trans
    mat4 View,Proj;
    glm_perspective(glm_rad(45.0f), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f, Proj);
    camera.GetViewMatrix(&camera, &View);
    glm_mat4_copy(GLM_MAT4_IDENTITY, View);
    
    cubeDrawSetting(&cubeShader, cubeVAO, (float*)View, (float*)Proj);
    
    setLight(&cubeShader, &camera);
    setLight(&snakeShader, &camera);
    setLight(&foodShader, &camera);
    int i=-1;
    float fpstemp=0;
    int angle=0.001;
    //    PrintS_Ini(4, B, C, 0.5, 0.5, 0.5, D(u(4)), _snakeV);
    //    script(-1, "SNAKE", 0.2, D(u(70)), B, C, 0.3, 0.7, _snakeV*0.5, 0.05);
    creatSnake(0, _snakeWIDTH, D(u(80)), 0.5, cube->margin+0.1, B, 5-A, _snakeV, NULL, 0, D(u(20)), 1);
    //    debug(testing)snakeH.stall=1;
    //    creatSnake(0, D(u(100)), D(u(100)), 0.5, 0.5, C, B, _snakeV, NULL, 0, D(u(80)), 1);
    foodIni();
    
    bool f=0;
    float sun=0.0f;
    int iniTimer=0;
    float wind=0.0f;
    float wind2=0.0f;
    snakeH.stall=1;
    bool iniWasted = 1;
    GameScores score={0,0};
    init_scores(&score);
//    bool NPCINI=0;
    
    printf("MAX%d\n",FragmentMax);
    glPolygonOffset(2.0f, 4.0f);
    glEnable(GL_POLYGON_OFFSET_FILL);
    while (!glfwWindowShouldClose(window)) {
        SCR_WIDTH=ctx.framebuffer_width;
        SCR_HEIGHT=ctx.framebuffer_height;
        
        while (STATE<=0&&!glfwWindowShouldClose(window)) {
            //            glDisable(GL_POLYGON_OFFSET_FILL);
            //            glPolygonOffset(2.0f, 4.0f);
            //            if(ppp==1)break;
            SCR_WIDTH=ctx.framebuffer_width;
            SCR_HEIGHT=ctx.framebuffer_height;
            if(STATE==0)snakeH.stall=1;
            else snakeH.stall=0;
            f=0;
            wind+=deltaTime*windSpeed;
            wind2+=deltaTime*_windSpeed;
            if(wind>=1.0)wind-=1;
            if(wind2>=1.0)wind2-=1;
            float currentFrame = (float)glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            if(deltaTime>MAX_deltatime)deltaTime=MAX_deltatime;
//                        deltaTime=0.01;
            lastFrame = currentFrame;
            if(STATE!=-3)Orth=1;
            if(snakeH.up==B&&snakeH.advance<=cube->margin){
                STATE=-2;
                Orth=0;
            }
            if(snakeH.up!=B&&STATE==-2){
                if(nHd->others!=NULL){
                    struct note *not=nHd->others;
                    Npc[0]=iniNPC(0, not->s, npc_fc, npc_rc, npc_oc, npc_sc, npc_randm, npc_ts, npc_bs, npc_es_sl, npc_apAdv, npc_rps, npc_perFrame, npc_rigor, npc_bumping);
                    not->s->ID=1; not=not->others;
                    Npc[1]=iniNPC(1, not->s, npc_fc, npc_rc, npc_oc, npc_sc, npc_randm, npc_ts, npc_bs, npc_es_sl, npc_apAdv, npc_rps, npc_perFrame, npc_rigor, npc_bumping);
                    not->s->ID=2; not=not->others;
                    Npc[2]=iniNPC(2, not->s, npc_fc, npc_rc, npc_oc, npc_sc, npc_randm, npc_ts, npc_bs, npc_es_sl, npc_apAdv, npc_rps, npc_perFrame, npc_rigor, npc_bumping);
                    not->s->ID=3; not=not->others;
                    Npc[3]=iniNPC(3, not->s, npc_fc, npc_rc, npc_oc, npc_sc, npc_randm, npc_ts, npc_bs, npc_es_sl, npc_apAdv, npc_rps, npc_perFrame, npc_rigor, npc_bumping);
                    not->s->ID=4; not=not->others;
                    Npc[4]=iniNPC(4, not->s, npc_fc, npc_rc, npc_oc, npc_sc, npc_randm, npc_ts, npc_bs, npc_es_sl, npc_apAdv, npc_rps, npc_perFrame, npc_rigor, npc_bumping);
                    not->s->ID=5;
                    noteRelease_ID(-3);
                    //                    snakeCrush(Npc[0]->H);
                    //                    snakeCrush(Npc[1]->H);
                    //                    snakeCrush(Npc[2]->H);
                    //                    snakeCrush(Npc[3]->H);
                    //                    snakeCrush(Npc[4]->H);
                    noteClean();
                    startTimer();
                }
//                NPCINI=1;
                STATE=-3;
                Orth=0;
                snakeH.stall=1;
            }
            //            printf("%d\n",Orth);
            if(kkk>=kkk_max/*&&NPCINI*/&&STATE==-3){
                snakeH.stall=0;
                STATE=1;
                break;
            }
            if((!Orth||STATE==-3)&&kkk<kkk_max){
                //                printf("kkk:%f\n",kkk);
                glm_perspective(glm_rad(kkk), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.01, 100.0, Proj);
//                                glm_perspective(glm_rad(kkk), (float)SCR_WIDTH/(float)SCR_HEIGHT, near, far, Proj);
                camera.distance=(cube->size*(1-2*cube->margin)/(float)SCR_WIDTH*(float)SCR_HEIGHT/2/tanf(glm_rad(kkk/2))+cube->size/2);
//                                printf("k:%f tan:%f\n",kkk,tanf(glm_rad(kkk/2)));
//                printf("%f\n",camera.distance);
//                                camera.distance=2;
                updateDistance(&camera);
                
                kkk+=0.1;
                //                if(kkk>=kkk_max)kkk=kkk_max;
            }else{
                glm_ortho(-cube->size*(0.5-cube->margin), cube->size*(0.5-cube->margin), (-cube->size*(0.5-cube->margin))/(float)SCR_WIDTH*(float)SCR_HEIGHT, (cube->size*(0.5-cube->margin))/(float)SCR_WIDTH*(float)SCR_HEIGHT, -100, 100, Proj);
            }
            updateLight(&camera,&simpleDepthShader,&simpleDepthShader_SR, &VBO_SR[1], &VBO_SR[2], &VBO_SR[3],/* &VBO_SR[4], Snake_diffuse_textureU, Rot_diffuse_textureU, specular_textureU,*/ &VAO_SR_depth, &f, &VBO_F[1], &VAO_F_depth, &foodN,&cubeVAO_depth);
            glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
            glClearColor(0.5f, 0.8f, 1.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            updateLightShader(&cubeShader, &camera);
            updateLightShader(&snakeShader, &camera);
            updateLightShader(&foodShader, &camera);
            cubeDraw(&cubeShader, &camera,cubeVAO, (float*)Proj,wind,wind2);
            if(iniTimer==50){
                script(-3, "SNAKE", 0.1, D(u(80)), B, C, 0.3, 0.4, _snakeV, 0.1);
                
                char ta[14];
                snprintf(ta, 14, "%012ld",score.score%10000000000000);
                //                    printf("%s\n",ta);
                script(-4, ta, 0.1, D(u(20)), B, C, 0.6, 0.7, _snakeV, 0.1);
                snprintf(ta, 14, "%012ld",score.length%10000000000000);
                //                    sprintf(ta, "%012ld",1234567890%10000000000000);
                //                    printf("%s\n",ta);
                script(-5, ta, 0.1, D(u(20)), B, C, 0.7, 0.7, _snakeV, 0.1);
                iniTimer++;
            }
            if(iniTimer<50)iniTimer++;
            else PrintS_Print(deltaTime);
            struct snakeHead *sn = &snakeH;
            snakeUpdate(sn/*, sn->velocity*/, deltaTime);

            rotUpdate();
            drawSR(&snakeShader, &VBO_SR[1], &VBO_SR[2], &VBO_SR[3]/*, &VBO_SR[4], Snake_diffuse_textureU, Rot_diffuse_textureU, specular_textureU*/, &VAO_SR, &camera, &Proj, &f);
            
            //                if(newgame)goto NewGame;
            // 交换缓冲并查询IO事件
            glfwSwapBuffers(window);
            glfwPollEvents();
            processInput(window);
        }
        camera.distance=1.7;
        //        if(ppp==1)break;
        f=0;
        Orth=0;
        wind+=deltaTime*windSpeed;
        wind2+=deltaTime*_windSpeed*(cosf(glm_rad(sun))+2)/1.5;
        if(wind>1.0)wind-=1;
        if(wind2>1.0)wind2-=1;
        //        if(wind<-1.0)wind=1.0;
        float currentFrame = (float)glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        if(deltaTime>MAX_deltatime)deltaTime=MAX_deltatime;
        //        deltaTime=0.01;
        lastFrame = currentFrame;
        //printf("deltaTime%f\n",deltaTime);
        sun+=0.08;
        windSpeed=_windSpeed+cosf(sun+72)/10;
        debugf(main378, windSpeed)
        if(sun>=360)sun=0.0f;
        dirLight.dir[0]=cosf(glm_rad(sun));
        dirLight.dir[1]=-cosf(glm_rad(sun));
        dirLight.dir[2]=sinf(glm_rad(sun));
        
        vec3 pos;
        struct snakeHead *targ=&snakeH;
        if(!snakeH.snakeAlive)targ=snakeH.others;
        if(targ!=NULL)getAbsPos(targ->up, targ->direction, targ->advance+getLength(targ->eatProcess[0])/cube->size, targ->position, targ->mesa, pos);
        debugvec3(main260, pos)
        setTargetPos(&camera, pos);
        if(firstMouse)cameraUpdate(&camera, pos, angle, deltaTime);
        debugvec3(main262, camera.targetPosition)
        debugvec3(main262, camera.Position)
        debugvec3(main262, camera.Front)
        
        debugf(main193, getLength(snakeH.length));
        
        if(pause==1)snakeH.velocity=0;
        
        foodRefreshAll();
        
        //        PrintS_Print(deltaTime);
        
        debugp(main184, snakeH.headMat)
        rotUpdate();
        snakeUpdate(&snakeH/*, snakeH.velocity*/, deltaTime);
        if(!snakeH.snakeAlive){
            if(iniWasted){
                script(-6, "WASTED", 0.1, D(u(20)), snakeH.up, snakeH.direction, snakeH.advance, 0.7, _snakeV, 0.1);
                printf("TIME:%lf, SCORE:%ld, LENGTH:%f", endTime-startTime, snakeH.score, getLength(endLength));
                
                GameScores newScore={0,endLength};
                if(snakeH.score>0){
                    if(snakeH.score<10000000000000)newScore.score=snakeH.score;
                    else newScore.score=10000000000000-1;
                }
                update_scores(&score, newScore);
                save_scores(&score);
                iniWasted=0;
            }
            PrintS_Print(deltaTime);
        }
        if(!starting){
            //            startingRobot(Npc[0]);
            //            startingRobot(Npc[1]);
            //            startingRobot(Npc[2]);
            //            startingRobot(Npc[3]);
            //            startingRobot(Npc[4]);
            //        }else{
            roboting(Npc[0]);
            roboting(Npc[1]);
            roboting(Npc[2]);
            roboting(Npc[3]);
            roboting(Npc[4]);
        }
        if(!ppp){
            if(starting&&(Npc[0]->H->up!=B||!Npc[0]->H->snakeAlive)&&(Npc[1]->H->up!=B||!Npc[1]->H->snakeAlive)&&(Npc[2]->H->up!=B||!Npc[2]->H->snakeAlive)&&(Npc[3]->H->up!=B||!Npc[3]->H->snakeAlive)&&(Npc[4]->H->up!=B||!Npc[4]->H->snakeAlive)){
                starting = 0;
            }
            snakeUpdate(Npc[0]->H/*, Npc[0]->H->velocity*/, deltaTime);
            snakeUpdate(Npc[1]->H/*, Npc[1]->H->velocity*/, deltaTime);
            snakeUpdate(Npc[2]->H/*, Npc[2]->H->velocity*/, deltaTime);
            snakeUpdate(Npc[3]->H/*, Npc[3]->H->velocity*/, deltaTime);
            snakeUpdate(Npc[4]->H/*, Npc[4]->H->velocity*/, deltaTime);
        }
        
        //        printf("score %ld\n",snakeH.score);
        
        debugf(main161,getLength(snakeH.toBeElongation))
        debugSnakePos(main224, (&snakeH))
        
        //        glCullFace(GL_FRONT);
        updateLight(&camera,&simpleDepthShader,&simpleDepthShader_SR, &VBO_SR[1], &VBO_SR[2], &VBO_SR[3], /*&VBO_SR[4], Snake_diffuse_textureU, Rot_diffuse_textureU, specular_textureU,*/&VAO_SR_depth, &f, &VBO_F[1], &VAO_F_depth, &foodN,&cubeVAO_depth);
        //        glCullFace(GL_BACK);
        updateLightShader(&cubeShader, &camera);
        updateLightShader(&snakeShader, &camera);
        updateLightShader(&foodShader, &camera);
        
        if(i<fpscon){
            fpstemp+=deltaTime;
            i++;
        }else if(i==fpscon){
            fps=fpscon/fpstemp;
            fpstemp=0;
            i=0;
        }
        //        printf("%lf\n",glfwGetTime()-startTime);
        //        angle++;
        //        angle=angle%360;
        
        glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
        float tempr = 0.5-d*0.5;
        float non = 1.0-fabsf(d);
        
        
        
        glClearColor(mixure(0.7, tempr, non, 0.5, 0), mixure(0.7, tempr, non, 0.8, 1), mixure(0.7, tempr, non, 1.0, 2),1.0);
        //glClear(GL_COLOR_BUFFER_BIT);
        //清除深度缓冲
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        //        mat4 view;
        //        camera.GetViewMatrix(&camera, &view);
        //        testS.setMat4fv(&testS, "view", (float *)view);
        //        testS.use(&testS);
        //        testS.setMat4fv(&testS,"proj",Proj[0]);
        //        glBindVertexArray(VAOID);
        //        glBindVertexArray(VAOID);
        ////        glDrawArrays(GL_TRIANGLES, 0, 6);
        //        glBindVertexArray(0);
        
        debugvec3(main351, *(cube->position))
        RenderSrc(&cubeShader, &snakeShader, &foodShader,wind,wind2,&f);
        drawScoreAndTime(mixure(0.7, non, tempr, 1.0, 0), mixure(0.7, non, tempr, 0.64, 1), mixure(0.7, non, tempr, 0, 2));
        
        debugi(main355, foodN)
        
        // 交换缓冲并查询IO事件
        glfwSwapBuffers(window);
        glfwPollEvents();
        //        printf("fps%f\n",fps);
        processInput(window);
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(textShaderProgram);
    for (int i = 0; i < 128; i++) {
        glDeleteTextures(1, &Characters[i].TextureID);
    }
    noteClean();
    cleanup_audio();
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS||ppp==1){
        if(snakeH.snakeAlive){
            endLength=getTotalLength(&snakeH);
            endTime=glfwGetTime();
        }
        ppp=1;
        debug(main477)
        noteClean();
        while (snakeDel_withHead(snakeH.others)!=-1);
        rotFree();
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS && directionKey==0){
        snakeKeyBoard(&snakeH, _RIGHT);
        directionKey=1;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_RELEASE){
        directionKey=0;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS && directionKey==0){
        snakeKeyBoard(&snakeH, _LEFT);
        directionKey=1;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_RELEASE){
        directionKey=0;
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && spaceKey==0){
        if(STATE==1){
            snakeKeyBoard(&snakeH, _SPACE);
            //            snakeH.score*=10;
            spaceKey=1;
        }
    }
    if(STATE==0&&glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
        STATE=-1;
        snakeH.stall=0;
        spaceKey=1;
        startTime=glfwGetTime();
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE && spaceKey==1){
        spaceKey=0;
    }
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
        snakeH.velocity=0;
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
        snakeH.velocity=_snakeV;
}
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    //    printf("mouse\n");
    if(glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_LEFT)==GLFW_PRESS&&STATE>=0){
        float xpos = (float) trunc(xposIn), ypos = (float) trunc(yposIn);
        if(firstMouse)
        {
            glm_vec3_copy(camera.Up, camera.WorldUp);
            firstMouse = false;
            lastX = xpos;
            lastY = ypos;
        }
        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos;
        lastX = xpos;
        lastY = ypos;
        //        printf("mouse\n");
        camera.ProcessMouseMovement(&camera,xoffset,yoffset,1);
    }
    if(STATE<=0){
        float x = (xposIn/SCR_WIDTH*ctx.content_scale-0.5)*cube->size;
        float y = -(yposIn/SCR_HEIGHT*ctx.content_scale-0.5)*cube->size/SCR_WIDTH*SCR_HEIGHT;
        mouseLight(x,y);
    }
    if(glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_LEFT)==GLFW_RELEASE){
        firstMouse = true;
    }
}
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
    //    printf("(%f,%f)\n",xpos/SCR_WIDTH,ypos/SCR_HEIGHT);
    if(STATE<=0){
        float x = (xpos/SCR_WIDTH*ctx.content_scale-0.5)*cube->size;
        float y = -(ypos/SCR_HEIGHT*ctx.content_scale-0.5)*cube->size/SCR_WIDTH*SCR_HEIGHT;
        mouseLight(x,y);
    }
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(&camera, (float)trunc(yoffset));
}
void RenderSrc(Shader *cubeShader,Shader *snakeShader,Shader *foodShader,float cubeOffSet, float cubeOffSet2, bool *f){
    mat4 Proj;
    if(!Orth)glm_perspective(glm_rad(45.0f), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f, Proj);
    //    else glm_ortho(-cube->size*(0.5-cube->margin), cube->size*(0.5-cube->margin), (-cube->size*(0.5-cube->margin))/4*3, (cube->size*(0.5-cube->margin))/4*3, near, far, Proj);
    
    updateLightShader(cubeShader, &camera);
    updateLightShader(snakeShader, &camera);
    updateLightShader(foodShader, &camera);
    cubeDraw(cubeShader, &camera,cubeVAO, (float*)Proj, cubeOffSet, cubeOffSet2);
    drawSR(snakeShader, &VBO_SR[1], &VBO_SR[2], &VBO_SR[3],/* &VBO_SR[4], Snake_diffuse_textureU, Rot_diffuse_textureU, specular_textureU,*/&VAO_SR, &camera, &Proj, f);
    drawF(foodShader, &VBO_F[1], &VAO_F, &camera, &Proj, &foodN);
}
// 初始化DPI感知
void init_dpi_awareness(void) {
#ifdef _WIN32
    // 尝试设置Per-Monitor DPI感知
    if (SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE) != S_OK) {
        // 回退到系统DPI感知
        SetProcessDPIAware();
    }
#endif
}

// 获取内容缩放因子v
float get_content_scale(GLFWwindow* window) {
    float xscale, yscale;
    glfwGetWindowContentScale(window, &xscale, &yscale);
    return xscale; // 通常x和y相同
}

// 帧缓冲大小回调
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    DPIContext* ctx = (DPIContext*)glfwGetWindowUserPointer(window);
    if (ctx) {
        ctx->framebuffer_width = width;
        ctx->framebuffer_height = height;
        ctx->content_scale = get_content_scale(window);
        
        // 基于物理像素设置视口
        glViewport(0, 0, width, height);
        
        //        printf("帧缓冲尺寸变化: %dx%d (缩放因子: %.1f)\n",
        //               width, height, ctx->content_scale);
    }
}

// 窗口大小回调
void window_size_callback(GLFWwindow* window, int width, int height) {
    DPIContext* ctx = (DPIContext*)glfwGetWindowUserPointer(window);
    if (ctx) {
        ctx->logical_width = width;
        ctx->logical_height = height;
        
        // 更新帧缓冲尺寸
        glfwGetFramebufferSize(window, &ctx->framebuffer_width, &ctx->framebuffer_height);
        
        //        printf("窗口尺寸变化: %dx%d\n", width, height);
    }
}

// 内容缩放回调
void content_scale_callback(GLFWwindow* window, float xscale, float yscale) {
    DPIContext* ctx = (DPIContext*)glfwGetWindowUserPointer(window);
    if (ctx) {
        ctx->content_scale = xscale;
        
        // 更新帧缓冲尺寸
        glfwGetFramebufferSize(window, &ctx->framebuffer_width, &ctx->framebuffer_height);
        
        //        printf("缩放因子变化: %.1f\n", xscale);
        
        // 更新视口
        glViewport(0, 0, ctx->framebuffer_width, ctx->framebuffer_height);
    }
}
// 创建DPI处理上下文
void create_dpi_context(GLFWwindow* window) {
    
    ctx.window = window;
    glfwGetWindowSize(window, &ctx.logical_width, &ctx.logical_height);
    glfwGetFramebufferSize(window, &ctx.framebuffer_width, &ctx.framebuffer_height);
    ctx.content_scale = get_content_scale(window);
    
    // 设置窗口用户指针
    glfwSetWindowUserPointer(window, &ctx);
    
    // 注册回调
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetWindowSizeCallback(window, window_size_callback);
    glfwSetWindowContentScaleCallback(window, content_scale_callback);
    
}

// 获取当前DPI状态
void get_dpi_state(int* fb_width, int* fb_height, float* scale) {
    *fb_width = ctx.framebuffer_width;
    *fb_height = ctx.framebuffer_height;
    *scale = ctx.content_scale;
}
