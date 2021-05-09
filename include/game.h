#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "console.h"

#define SCREEN_COL 105 /** Número máximo de colunas exibidas do mapa */
#define MATRIX_COL 416 /** Número de colunas da matriz */
#define MAP_COL 415 /** Número de colunas do mapa */
#define MAP_LIN 35 /** Número de linhas do mapa */
#define MAX_ENEMIES 20 /** Quantidade máxima de inimigos em cada mapa */
#define MAP_CHAR_PLAYER '@' /** Caractere que representa a posição do jogador no arquivo do mapa */
#define MAP_CHAR_ENEMY 'X' /** Caractere que representa as posições dos inimigos no arquivo do mapa */
#define MAP_CHAR_WALL 'C' /** Caractere que representa as paredes no arquivo do mapa */
#define CHAR_PLAYER_SHOT '-' /** Caractere que representa o tiro do jogador */
#define CHAR_WALL 219 /** Caractere que representa as paredes na matriz do mapa */
#define CHAR_EMPTY_SPACE ' ' /** Caractere que representa o espaço em branco na matriz do mapa */
#define PLAYER_SPEED_MIN 0 /** Velocidade máxima do jogador */
#define PLAYER_SPEED_MAX 100 /** Velocidade mínima do jogador */
#define COLUMN_PLAYER_DISTANCE 10 /** Distância do jogador em relação a coluna da extremidade esquerda do mapa */
#define MAX_PLAYER_SHOTS 20 /** Máximo de tiros que o usuário pode dar simultaneamente */
#define PLAYER_SHOT_LIMIT 200 /** Limite de percorrimento do tiro no mapa */

#define FILE_SAVE "save.bin"

#define LOOPS_SHOT 2
#define ENEMY_MOVE_DELAY 10
#define PLAYER_MOVE_DELAY_MAX 5
#define PLAYER_MOVE_DELAY_MIN 0

#define NO_COLLISION 20
#define COLLISION_PLAYER_TO_WALL 21
#define COLLISION_PLAYER_TO_ENEMY 22
#define COLLISION_PLAYER_TO_SHOT 23

#define ERROR_LER_ARQUIVO -1
#define SUCCESS 1

/**
 * Códigos dos retornos do jogo
 */
#define GAME_RETURN_SAVE 11
#define GAME_RETURN_NEXT_LEVEL 12
#define GAME_RETURN_OVER 13
#define GAME_RETURN_FINISHED 14

typedef struct player{
    int position_x;
    int position_y;
    int last_x;
    int last_y;
} player_t;

typedef struct enemy{
    int position_x;
    int position_y;
    int last_x;
    int last_y;
    int move_delay;
} enemy_t;

typedef struct checkpoint{
    int x;
    int y;
} checkpoint_t;

typedef struct playerShot{
    int position_x;
    int position_y;
    int last_x;
    int last_y;
    int limit;
} playerShot_t;

typedef struct save{
    enemy_t enemies[MAX_ENEMIES];
    playerShot_t player_shots[MAX_PLAYER_SHOTS];
    player_t player;
    int level;
    int lives;
    int score;
    int coluna_inicial;
    int flag_new_game;
    int num_enemies;
    int num_player_shots;

} save_t;

int renderGame(save_t *save);
int readMap(save_t *save, char map[][MAP_COL], player_t *player, enemy_t enemies[MAX_ENEMIES], int *num_enemies);
void printMap(char mapa[][MAP_COL], int coluna_inicial);
int fillMap(char map[][MAP_COL]);
void drawPlayer(char map[][MAP_COL], player_t *player);
void erasePlayer(char map[][MAP_COL], player_t *player);
void updatePlayerPosition(char map[][MAP_COL], player_t *player);
void drawEnemy(char map[][MAP_COL], enemy_t *enemy);
void eraseEnemy(char map[][MAP_COL], enemy_t *enemy);
void updateEnemiesPositions(char map[][MAP_COL], enemy_t enemies[MAX_ENEMIES], int *num_enemies, save_t *save);
int playerCollisions(char map[][MAP_COL], player_t *player);
int checkPlayerCollision(char map[][MAP_COL], player_t *player, char carac);
void makePlayerShot(char map[][MAP_COL], player_t *player, playerShot_t player_shots[MAX_PLAYER_SHOTS], int *num_player_shots);
void drawPlayerShot(char map[][MAP_COL], playerShot_t *player_shot);
void erasePlayerShot(char map[][MAP_COL], playerShot_t *player_shot);
void updatePlayerShotsPositions(char map[][MAP_COL], playerShot_t player_shots[MAX_PLAYER_SHOTS], int *num_player_shots);
int checkEnemyCollision(char map[][MAP_COL], enemy_t *enemy, char carac);

#endif
