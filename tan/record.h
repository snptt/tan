//
//  record.h
//  op
//
//  Created by BoBo W on 2025/5/31.
//
#ifndef record_H
#define record_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SCORE_FILE "game_scores.bin"
#define ENCRYPT_KEY "MySecretKey123!" // º”√‹√‹‘ø
//char ENCRYPT_KEY[]="MySecretKey123!";

typedef struct {
    long score;
    long length;
} GameScores;

// XORº”√‹/Ω‚√‹∫Ø ˝
void xor_encrypt(void* data, size_t data_len, const char* key) {
    unsigned char* data_ptr = (unsigned char*)data;
    size_t key_len = strlen(key);
    
    for(size_t i = 0; i < data_len; i++) {
        data_ptr[i] ^= key[i % key_len];
    }
}

void init_scores(GameScores* scores) {
    FILE* file = fopen(SCORE_FILE, "rb");
    if (file) {
        // ∂¡»°º”√‹ ˝æ›
        fread(scores, sizeof(GameScores), 1, file);
        // Ω‚√‹ ˝æ›
        xor_encrypt(scores, sizeof(GameScores), ENCRYPT_KEY);
        fclose(file);
    } else {
        printf("No record\n");
        scores->length=0;
        scores->score=0;
    }
}

void save_scores(const GameScores* scores) {
    GameScores encrypted = *scores;
    // º”√‹ ˝æ›
    xor_encrypt(&encrypted, sizeof(GameScores), ENCRYPT_KEY);
    
    FILE* file = fopen(SCORE_FILE, "wb");
    if (file) {
        fwrite(&encrypted, sizeof(GameScores), 1, file);
        fclose(file);
    }
}

void update_scores(GameScores* scores, GameScores new_score) {
//    scores->last_score = new_score;
    if (new_score.score >= scores->score) {
        *scores = new_score;
    }
}

//void show_scores(const GameScores* scores) {
//    printf("=== ∑÷ ˝º«¬º ===\n");
//    printf("Last turn: %d\n", scores->last_score);
//    printf("Best turn: %d\n\n", scores->high_score);
//}
//
//int main() {
//    GameScores scores;
//    int current_score;
//
//    // ∂¡»°≤¢Ω‚√‹¿˙ ∑º«¬º
//    init_scores(&scores);
//    show_scores(&scores);
//
//    // ”Œœ∑µ√∑÷ ‰»Î
//    scanf("%d", &current_score);
//
//    // ∏¸–¬≤¢º”√‹±£¥Ê
//    update_scores(&scores, current_score);
//    save_scores(&scores);
//
//    printf("\n∑÷ ˝“—±£¥Ê£°\n");
//    show_scores(&scores);
//
//    return 0;
//}
#endif
