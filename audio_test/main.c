//
//  main.c
//  audio_test
//
//  Created by BoBo W on 2025/5/31.
//

#include <portaudio.h>
#include <sndfile.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

int main() {
    // 1. 初始化PortAudio
    Pa_Initialize();
    
    // 2. 加载音频文件
    const char* filename = "audio_test/demo3.WAV";
    SF_INFO sfinfo;
    SNDFILE* file = sf_open(filename, SFM_READ, &sfinfo);
    
    if (!file) {
        printf("无法打开音频文件: %s\n", filename);
        return 1;
    }
    
    // 创建音频数据
    AudioData audioData;
    audioData.totalFrames = sfinfo.frames;
    audioData.channels = sfinfo.channels;
    audioData.position = 0;
    audioData.buffer = malloc(sfinfo.frames * sfinfo.channels * sizeof(float));
    sf_readf_float(file, audioData.buffer, sfinfo.frames);
    sf_close(file);
    
    // 3. 设置输出流
    PaStream* stream;
    PaStreamParameters outputParams = {
        .device = Pa_GetDefaultOutputDevice(),
        .channelCount = audioData.channels,
        .sampleFormat = paFloat32,
        .suggestedLatency = Pa_GetDeviceInfo(Pa_GetDefaultOutputDevice())->defaultLowOutputLatency,
        .hostApiSpecificStreamInfo = NULL
    };
    
    // 4. 打开音频流
    Pa_OpenStream(&stream,
                  NULL,     // 无输入
                  &outputParams,
                  sfinfo.samplerate,
                  512,      // 缓冲区大小
                  paClipOff,
                  audioCallback,
                  &audioData);
    
    // 5. 开始播放
    Pa_StartStream(stream);
    printf("循环播放中... 按Enter键退出\n");
    getchar();  // 等待用户输入
    
    // 6. 停止播放并清理
    Pa_StopStream(stream);
    Pa_CloseStream(stream);
    free(audioData.buffer);
    Pa_Terminate();
    
    return 0;
}
