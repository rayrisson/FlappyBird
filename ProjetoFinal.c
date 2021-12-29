#include <raylib.h>
#include <stdio.h>
#include "score.h"

typedef struct _Personagem{
    int xSprite, ySprite;
    Texture2D sprite;
    Rectangle player;
}Personagem;

void propertiesPipe(Rectangle pipe1[], Rectangle pipe2[]){
    int spacing = 0;
    for (int i = 0; i < 1000; i++){
        pipe1[i].width = 100;
        pipe1[i].height = GetRandomValue(5, 307);
        pipe1[i].y = 0;
        pipe1[i].x = 400 + spacing;    
        pipe2[i].width = 100;
        pipe2[i].height = 350;
        pipe2[i].y = pipe1[i].height + 135;
        pipe2[i].x = pipe1[i].x;
        spacing += 230;
    }
}

void drawPipes(Rectangle pipe1[], Rectangle pipe2[]){
    for(int i = 0; i < 1000; i++){ 
        DrawRectangleRec(pipe1[i], (Color){38, 114, 76, 255});
        DrawRectangleRec(pipe2[i], (Color){38, 114, 76, 255});
    }
}

void pipeSlide(Rectangle pipe1[], Rectangle pipe2[]){
    for(int i = 0; i < 1000; i++){
        pipe1[i].x -= 1.5;
        pipe2[i].x -= 1.5;
    }
}

bool checkCollision(Rectangle pipe1[], Rectangle pipe2[], Rectangle player){
    for(int i = 0; i < 1000; i++){
        if(CheckCollisionRecs(player, pipe1[i]) || CheckCollisionRecs(player, pipe2[i]) || player.y == 0 || player.y >= 420)
            return true;
    }
    return false;
}

int main(){
    InitWindow(800, 450, "FlappyBird");
    InitAudioDevice();
    int score = 0, hiscore = 0, recentscore = 0;
    bool menu = true;
    FILE *armPontuacao;
    Personagem persona = {200, 200, LoadTexture("resources/sprite.png"), {200, 200, 40, 28}};
    Texture2D background = LoadTexture("resources/fundo.png");
    Texture2D menutexture = LoadTexture("resources/menu.png");
    Music musicGame = LoadMusicStream("resources/principal.ogg");
    Sound fxGameOver = LoadSound("resources/gameover.wav");
    Rectangle pipeTop[1000] = { 0 }, pipeDown[1000] = { 0 };
    SetTargetFPS(60);
    while(!WindowShouldClose()){
        if(menu){
            armPontuacao = fopen("score.txt", "a");
            hiscore = bestScore();
            recentscore = mostRecentScore();
            fclose(armPontuacao);
            propertiesPipe(pipeTop, pipeDown);
            PlayMusicStream(musicGame);
            UpdateMusicStream(musicGame);
            BeginDrawing();
            DrawTexture(menutexture, 0, 0, WHITE);
            DrawText("Pressione ENTER para jogar", 185, 395, 25, (Color){0, 53, 203, 255});
            DrawText(TextFormat("HI-SCORE: %08i", hiscore), 7, 280, 20, (Color){143, 197, 68, 255});
            DrawText(TextFormat("RECENT SCORE: %08i", recentscore), 525, 280, 20, (Color){143, 197, 68, 255});
            EndDrawing();
            if(IsKeyPressed(KEY_ENTER)){
                menu = false;
                armPontuacao = fopen("score.txt", "a");
            }
        }else{
            if(IsKeyDown(KEY_SPACE) || IsMouseButtonDown(MOUSE_LEFT_BUTTON)){
                persona.player.y -= 5;
                persona.ySprite -= 5;
            }else{
                persona.player.y += 5;
                persona.ySprite += 5;
            }
            score++;
            UpdateMusicStream(musicGame);
            pipeSlide(pipeTop, pipeDown);
            BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawTexture(background, 0, 0, RAYWHITE);
            drawPipes(pipeTop, pipeDown);
            DrawText(TextFormat("%08i", score), 5, 5, 50, WHITE);
            DrawTexture(persona.sprite, persona.xSprite, persona.ySprite, RAYWHITE);
            EndDrawing();
            if(checkCollision(pipeTop, pipeDown, persona.player)){
                SetSoundVolume(fxGameOver, 0.3); 
                PlaySound(fxGameOver);
                fprintf(armPontuacao,"%d\n", score);
                fclose(armPontuacao);
                score = 0;
                persona.player.y = 200;
                persona.ySprite = 200;
                menu = true;
            }
        }
    }
    UnloadTexture(background);
    UnloadTexture(persona.sprite);
    UnloadTexture(menutexture);
    UnloadMusicStream(musicGame); 
    CloseAudioDevice();
    CloseWindow();
}