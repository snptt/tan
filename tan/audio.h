//
//  audio.h
//  op
//
//  Created by BoBo W on 2025/5/31.
//
#ifndef audio_H
#define audio_H

#include <portaudio.h>
#include <sndfile.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <portaudio.h>
#include <sndfile.h>
#include <stdio.h>

// 音频数据结构
typedef struct {
    float* buffer;          // 音频数据
    sf_count_t totalFrames; // 总帧数
    sf_count_t position;    // 当前播放位置
    int channels;           // 声道数
} AudioData;

// PortAudio 回调函数
static int audioCallback(const void* input, void* output,
                        unsigned long frameCount,
                        const PaStreamCallbackTimeInfo* timeInfo,
                        PaStreamCallbackFlags statusFlags,
                        void* userData) {
    AudioData* data = (AudioData*)userData;
    float* out = (float*)output;
    unsigned long framesToCopy = frameCount;
    
    // 检查是否到达文件末尾
    if (data->position + frameCount > data->totalFrames) {
        framesToCopy = data->totalFrames - data->position;
    }
    
    // 复制音频数据到输出缓冲区
    memcpy(out, &data->buffer[data->position * data->channels],
           framesToCopy * data->channels * sizeof(float));
    
    // 更新播放位置
    data->position += framesToCopy;
    
    // 循环播放：回到开头
    if (data->position >= data->totalFrames) {
        data->position = 0;
        
        // 复制剩余部分（如果帧数超出文件结尾）
        if (framesToCopy < frameCount) {
            unsigned long remainingFrames = frameCount - framesToCopy;
            memcpy(&out[framesToCopy * data->channels],
                   data->buffer,
                   remainingFrames * data->channels * sizeof(float));
            data->position = remainingFrames;
        }
    }
    
    return paContinue;
}

// 全局音频数据
static AudioData bgMusic;
static PaStream* audioStream;

// 初始化音频系统
void init_audio(const char* filename) {
    // 初始化PortAudio
    Pa_Initialize();
    
    // 加载音频文件
    SF_INFO sfinfo;
    SNDFILE* file = sf_open(filename, SFM_READ, &sfinfo);
    if (!file) {
            printf("无法打开音频文件: %s\n", filename);
        }
    bgMusic.totalFrames = sfinfo.frames;
    bgMusic.channels = sfinfo.channels;
    bgMusic.position = 0;
    bgMusic.buffer = malloc(sfinfo.frames * sfinfo.channels * sizeof(float));
    sf_readf_float(file, bgMusic.buffer, sfinfo.frames);
    sf_close(file);
    
    // 设置输出流
    PaStreamParameters outputParams = {
        .device = Pa_GetDefaultOutputDevice(),
        .channelCount = bgMusic.channels,
        .sampleFormat = paFloat32,
        .suggestedLatency = Pa_GetDeviceInfo(Pa_GetDefaultOutputDevice())->defaultLowOutputLatency,
        .hostApiSpecificStreamInfo = NULL
    };
    
    // 打开音频流
    Pa_OpenStream(&audioStream,
                  NULL,
                  &outputParams,
                  sfinfo.samplerate,
                  512,
                  paClipOff,
                  audioCallback,
                  &bgMusic);
    
    // 开始播放
    Pa_StartStream(audioStream);
}

// 清理音频资源
void cleanup_audio(void) {
    Pa_StopStream(audioStream);
    Pa_CloseStream(audioStream);
    free(bgMusic.buffer);
    Pa_Terminate();
}

#endif
