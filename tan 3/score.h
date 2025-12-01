#ifndef SCORE_H
#define SCORE_H

#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "stb_image.h"
#include "shader.h"
#include <ft2build.h>
#include FT_FREETYPE_H
#include "food.h" 

// 窗口尺寸
//const GLuint WIDTH = 800, HEIGHT = 600;
int SCR_WIDTH=800, SCR_HEIGHT=600;
float correctRatio=1.0;

// 存储每个字符信息的结构体
typedef struct {
    GLuint     TextureID;   // 字形纹理 ID
    GLint      SizeX;       // 字形宽度
    GLint      SizeY;       // 字形高度
    GLint      BearingX;    // 字形左侧基线偏移
    GLint      BearingY;    // 字形上侧基线偏移
    GLuint     Advance;     // 字形游标距离（以 1/64 px 为单位）
} Character;

// 用于保存 ASCII 前 128 个字符信息
Character Characters[128];

// 文本渲染用的 VAO、VBO
GLuint VAO, VBO;

// 文本渲染着色器程序 ID
GLuint textShaderProgram;

// 顶点着色器源码
const GLchar* vertexShaderSource =
"#version 330 core\n"
"layout (location = 0) in vec4 vertex; // <pos.x, pos.y, tex.x, tex.y>\n"
"out vec2 TexCoords;\n"
"uniform mat4 projection;\n"
//"uniform float correct;\n"
"void main() {\n"
//"    gl_Position = projection * vec4(vertex.x, vertex.y*correct, 0.0, 1.0);\n"
"    gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);\n"
"    TexCoords = vertex.zw;\n"
"}\n";

// 片段着色器源码
const GLchar* fragmentShaderSource =
"#version 330 core\n"
"in vec2 TexCoords;\n"
"out vec4 color;\n"
"uniform sampler2D text;\n"
"uniform vec3 textColor;\n"
"void main() {\n"
"    float alpha = texture(text, TexCoords).r;\n"
"    color = vec4(textColor, alpha);\n"
"}\n";



// 检查着色器编译错误
void checkShaderCompileStatus(GLuint shader, const char* type) {
    GLint success;
    GLchar infoLog[1024];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 1024, NULL, infoLog);
        fprintf(stderr, "ERROR::SHADER_COMPILATION_ERROR of type: %s\n%s\n", type, infoLog);
    }
}

// 检查程序链接错误
void checkProgramLinkStatus(GLuint program) {
    GLint success;
    GLchar infoLog[1024];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 1024, NULL, infoLog);
        fprintf(stderr, "ERROR::PROGRAM_LINKING_ERROR:\n%s\n", infoLog);
    }
}

// 初始化并编译着色器程序
GLuint InitTextShader(void) {
    // 顶点着色器
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    checkShaderCompileStatus(vertexShader, "VERTEX");

    // 片段着色器
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    checkShaderCompileStatus(fragmentShader, "FRAGMENT");

    // 链接程序
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    checkProgramLinkStatus(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return shaderProgram;
}

// 初始化 FreeType，加载字体并生成 ASCII 字符
void LoadFontCharacters(const char* fontPath) {
    FT_Library ft;
    if (FT_Init_FreeType(&ft)) {
        fprintf(stderr, "ERROR::FREETYPE: 无法初始化 FreeType 库\n");
        exit(EXIT_FAILURE);
    }

    FT_Face face;
    if (FT_New_Face(ft, fontPath, 0, &face)) {
        fprintf(stderr, "ERROR::FREETYPE: 无法加载字体: %s\n", fontPath);
        exit(EXIT_FAILURE);
    }

    FT_Set_Pixel_Sizes(face, 0, 48);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for (GLubyte c = 0; c < 128; c++) {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            fprintf(stderr, "ERROR::FREETYPE: 无法加载字形: %c\n", c);
            continue;
        }
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        Character ch = {
            texture,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            face->glyph->bitmap_left,
            face->glyph->bitmap_top,
            (GLuint)face->glyph->advance.x
        };
        Characters[c] = ch;
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

// 初始化 VAO、VBO，用于渲染字形四边形
void InitTextRenderBuffers(void) {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

    // layout(location = 0) vec4 vertex: (x, y, u, v)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

// 在屏幕上渲染文本
void RenderText(const char* text, GLfloat x, GLfloat y, GLfloat scale, GLfloat r, GLfloat g, GLfloat b) {
    glUseProgram(textShaderProgram);
    GLint colorLoc = glGetUniformLocation(textShaderProgram, "textColor");
    glUniform3f(colorLoc, r, g, b);
//    if((float)SCR_WIDTH/4/(float)SCR_HEIGHT*3!=correctRatio){
//        correctRatio=(float)SCR_WIDTH/4/(float)SCR_HEIGHT*3;
//        GLint correctLoc = glGetUniformLocation(textShaderProgram, "correct");
//        glUniform1f(correctLoc,correctRatio);
//    }
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    for (const char* p = text; *p; p++) {
        Character ch = Characters[(GLubyte)*p];

        GLfloat xpos = x + ch.BearingX * scale;
        GLfloat ypos = y - (ch.SizeY - ch.BearingY) * scale;
        GLfloat w = ch.SizeX * scale;
        GLfloat h = ch.SizeY * scale;

        GLfloat vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }
        };
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glDrawArrays(GL_TRIANGLES, 0, 6);
        x += (ch.Advance >> 6) * scale;
    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

static float timeStart = 0.0f;
// 启动计时器
void startTimer(void) {
    
    timeStart = (float)glfwGetTime();
}

void drawScoreAndTime(GLfloat r, GLfloat g, GLfloat b) {
//	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//    glClear(GL_COLOR_BUFFER_BIT);
    float time_total;
    if(snakeH.snakeAlive)time_total = (float)glfwGetTime() - timeStart;
    else time_total=endTime-timeStart;
    int minutes = (int)(time_total / 60);
    int seconds = (int)(time_total) % 60;
    char buffer[100];
    snprintf(buffer, sizeof(buffer), "Score: %ld  Time: %02d:%02d", snakeH.score, minutes, seconds);

     // 渲染参数设置
    GLfloat scale = 0.5f;
    GLfloat x = SCR_WIDTH*(800.0/SCR_WIDTH) - 14.0f*strlen(buffer); // 调整为更安全的右边距
    GLfloat y = 20.0f*(600.0/SCR_HEIGHT);
    
    RenderText(buffer, x, y, scale, r, g, b);

	
}

void init_scoreprinting(void){
	// 开启混合，使用预乘 alpha
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // 2. 初始化文本渲染着色器
    textShaderProgram = InitTextShader();
    // 配置正交投影：左下角为 (0,0)，右上角为 (WIDTH, HEIGHT)
    // 这里直接手动构造正交矩阵
    GLfloat ortho[16] = {
        2.0f / (SCR_WIDTH*(800.0/SCR_WIDTH)), 0,            0, 0,
        0,            2.0f / (SCR_HEIGHT*(600.0/SCR_HEIGHT)), 0, 0,
        0,            0,           -1, 0,
       -1,           -1,            0, 1
    };
    glUseProgram(textShaderProgram);
    GLint projLoc = glGetUniformLocation(textShaderProgram, "projection");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, ortho);

    // 3. 加载字体，生成字符纹理
    const char* fontPath = "tan/res/DejaVuSans.ttf";
    LoadFontCharacters(fontPath);

    // 4. 初始化 VAO/VBO
    InitTextRenderBuffers();
	
}


# endif
