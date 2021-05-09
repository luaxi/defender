#include "../include/game.h"

/**
 * Controla a execução do jogo.
 *
 * @param save  Estrutura que armazena os estados do jogo
 */
 int renderGame(save_t *save){

    char map[MAP_LIN][MAP_COL] = {0}; /** Matriz onde o mapa será armazenado */

    enemy_t enemies[MAX_ENEMIES] = {0}; /** Vetor de enemy_t que armazena os inimigos do jogo*/
    int num_enemies = 0; /** Quantidade de inimigos vivos */

    player_t player; /** Jogador */

    playerShot_t player_shots[MAX_PLAYER_SHOTS]; /** Vetor que armazena os tiros do jogador */
    int num_player_shots = 0; /** Quantidade de tiros no vetor */

    int coluna_inicial = 0; /** Coluna inicial a partir da qual o jogo será recortado */
    checkpoint_t check_point; /** Coluna que o jogo irá reiniciar quando o jogador perder uma vida */

    int game_return = 0; /** Retorno do jogo */

    int player_delay = PLAYER_MOVE_DELAY_MAX; /** Delay de movimentação do jogador (representa sua velocidade) */
    static int loop;

    /* Limpa o console */
    clearConsole();

    /* Lê o mapa */
    if(readMap(save, map, &player, enemies, &num_enemies) == SUCCESS){

        char carac, last_carac = '\0'; /** Caractere lido do teclado */

        char level_title[50];
        sprintf(level_title, "Level %d", save->level);

        renderScreen(level_title);

        /* Seta a posição inicial do jogador (recém lida do mapa) como o check point */
        check_point.x = player.position_x;
        check_point.y = player.position_y;

        /* Preenche as paredes do mapa */
        fillMap(map);

        /* Seta a coluna inicial a partir da posição do jogador */
        if(player.position_x <= 0 && player.position_x < COLUMN_PLAYER_DISTANCE){
            coluna_inicial = player.position_x + MAP_COL - COLUMN_PLAYER_DISTANCE;
        }else{
            coluna_inicial = player.position_x - COLUMN_PLAYER_DISTANCE;
        }

        do{
            /* Reseta o caractere */
            last_carac = carac;
            carac = 0;

            /* Seta a posição atual do jogador como sua última posição */
            player.last_x = player.position_x;
            player.last_y = player.position_y;

            /* Lê o caractere do teclado e armazena em carac */
            if(kbhit()) carac = getch();

            switch(carac){

                /* Caso o usuário aperte A (comando para a esquerda) */
                case 'a':
                case 'A':
                    /* Diminui a velocidade do jogador */
                    if(player_delay < PLAYER_MOVE_DELAY_MAX){
                        player_delay++;
                    }
                    break;

                /* Caso o usuário aperte D (comando para a direita) */
                case 'd':
                case 'D':
                    /* Aumenta a velocidade do jogador */
                    if(player_delay > PLAYER_MOVE_DELAY_MIN){
                        player_delay--;
                    }
                    break;

                /* Caso o usuário aperte W (comando para cima) */
                case 'w':
                case 'W':
                    /* Movimenta o jogador uma posição acima */
                    player.position_y = (player.position_y - 1) % MAP_LIN;
                    break;

                /* Caso o usuário aperte S (comando para baixo) */
                case 's':
                case 'S':
                    /* Movimenta o jogador uma posição abaixo */
                    player.position_y = (player.position_y + 1) % MAP_LIN;
                    break;

                /* Caso o usuário aperte " " (barra de espaço) */
                case CHAR_EMPTY_SPACE:

                    makePlayerShot(map, &player, player_shots, &num_player_shots);

                    break;
            }

            /* Atualiza a coluna*/
            if(loop >= player_delay){
                coluna_inicial = (coluna_inicial + 1) % MAP_COL;
                player.position_x = (player.position_x + 1) % MAP_COL;
                loop = 0;
            }else{
                loop++;
            }

            /* Verifica colisões do jogador */
            if(playerCollisions(map, &player) == 1){

                save->lives--;

                player.position_x = check_point.x;
                player.position_y = check_point.y;

                /* Seta a coluna inicial a partir da posição do jogador */
                if(player.position_x <= 0 && player.position_x < COLUMN_PLAYER_DISTANCE){
                    coluna_inicial = player.position_x + MAP_COL - COLUMN_PLAYER_DISTANCE;
                }else{
                    coluna_inicial = player.position_x - COLUMN_PLAYER_DISTANCE;
                }

                /* Seta a velocidade mais lenta do jogador */
                player_delay = PLAYER_MOVE_DELAY_MAX;

                Sleep(500);

            }

            /* Atualiza os tiros do jogador */
            updatePlayerShotsPositions(map, player_shots, &num_player_shots);

            /* Atualiza a posição do jogador */
            updatePlayerPosition(map, &player);

            /* Atualiza a posição dos inimigos */
            updateEnemiesPositions(map, enemies, &num_enemies, save);

            /* Imprime o mapa */
            printMap(map, coluna_inicial);

            /* Imprime a linha da vida e pontuação */
            gotoxy(0, 0);
            printf("Pontos: %d                            "
                   "Vidas: %d", save->score, save->lives);

            /* Altera a velocidade */
            //Sleep(101 - game_speed);
            Sleep(5);

        }while((carac != 'g' && carac != 'G') &&
               (save->lives > 0)              &&
               (num_enemies > 0));

        /* Caso não haja mais inimigos */
        if(num_enemies == 0){
            /* Incrementa o nível */
            save->level++;
            save->flag_new_game = 1;

            game_return = GAME_RETURN_NEXT_LEVEL;

        /* Caso o jogador tenha pressionado a tecla 'G' */
        }else if(toupper(carac) == 'G'){

            int i;

            save->coluna_inicial    = coluna_inicial;
            save->flag_new_game     = 0;
            save->num_enemies       = num_enemies;
            save->num_player_shots  = num_player_shots;
            save->player            = player;

            for(i = 0; i < MAX_ENEMIES; i++){
                save->enemies[i] = enemies[i];
            }

            for(i = 0; i < MAX_PLAYER_SHOTS; i++){
                save->player_shots[i] = player_shots[i];
            }

            game_return = GAME_RETURN_SAVE;

        /* Caso as vidas do jogador tenham acabado */
        }else if(save->lives == 0){
            game_return = GAME_RETURN_OVER;
        }

    }else{ /* Erro ao ler o arquivo */

        game_return = GAME_RETURN_FINISHED;

    }

    return game_return;

 }

///-------------------///
/// MAP
///-------------------///

/**
 * Busca e lê o mapa que está em um arquivo de texto.
 *
 * @param level         Fase do mapa
 * @param map           Ponteiro da matriz onde será armazeado o mapa
 * @param num_enemies   Número de inimigos no vetor
 */
int readMap(save_t *save, char map[][MAP_COL], player_t *player, enemy_t enemies[MAX_ENEMIES], int *num_enemies){

    char c; /** Caractere lido */
    char level_name[50]; /** Nome do arquivo do mapa */
    int i = 0, j = 0;
    FILE *arq;

    /* Formata nome do arquivo e salva em level_name */
    sprintf(level_name, "levels/level_%d.txt", save->level);

    /* Abre o arquivo */
    arq = fopen(level_name, "r");

    /* Caso haja erro na abertura */
    if(arq == NULL){
        return ERROR_LER_ARQUIVO;
    }

    /* Lê o arquivo (caractere por caractere) */
    while((c = fgetc(arq)) != EOF){

        /* Caso encontre uma quebra de linha */
        if(c == '\n'){
            i++;
            j = 0;
            continue;
        }

        /* Caso não seja um espaço em branco */
        if(c != ' '){

            if(save->flag_new_game == 1){
                /* Caso seja o caractere do jogador */
                if(c == MAP_CHAR_PLAYER){
                    /* Seta a posição do '@' para o jogador */
                    player->position_x = j;
                    player->position_y = i;
                    player->last_x = j;
                    player->last_y = i;

                /* Caso seja o caractere do inimigo */
                }else if(c == MAP_CHAR_ENEMY){

                    if(*num_enemies < 20){
                        /* Cria um novo inimigo e insere no vetor de inimigos */
                        enemy_t enemy;

                        enemy.position_x = j;
                        enemy.position_y = i;
                        enemy.last_x = j;
                        enemy.last_y = i;
                        enemy.move_delay = 0;

                        enemies[*num_enemies] = enemy;

                        *num_enemies += 1;
                    }
                }else if(c == MAP_CHAR_WALL){
                    map[i][j] = c;
                }
            }else{
                /// @todo buscar posicoes do save
            }
        }

        j++;
    }

    fclose(arq);

    return SUCCESS;

}

/**
 * Imprime o mapa no console a partir de uma coluna inicial.
 *
 * @param mapa              Matriz com os caracteres do mapa
 * @param coluna_inicial    Coluna inicial do recorte do mapa
 */
void printMap(char map[][MAP_COL], int coluna_inicial){

    int i, j;
    char recorte[MAP_LIN * (SCREEN_COL + 1)]; /** Recorte do mapa que será exibido na tela */

    for(i = 0; i < MAP_LIN; i++){
        for(j = 0; j < SCREEN_COL; j++){
           recorte[(i * (SCREEN_COL + 1)) + j] = map[i][(coluna_inicial + j) % MAP_COL];
        }
        recorte[(i * (SCREEN_COL + 1)) + j] = '\n';
    }
    recorte[(MAP_LIN * (SCREEN_COL + 1)) - 1] = '\0';

    gotoxy(0, 1);
    printf("%s", recorte);

}

/**
 * Preenche o mapa com os caracteres especiais
 * e encontra as posições do jogador e dos inimigos
 *
 * @param player_position   Ponteiro onde a posição do jogador será armazenada
 * @param enemies_positions Matriz onde as posições dos inimigos serão armazenadas
 */
int fillMap(char map[][MAP_COL]){

    int i, j;
    int flag_fill;
    char actual_char, last_char = '\0';

    /* Percorre a matriz do mapa */
    for(i = 0; i < MAP_COL; i++){

        flag_fill = 1;

        for(j = 0; j < MAP_LIN; j++){

            actual_char = map[j][i];

            /* Caso o caractere seja C */
            if(map[j][i] == MAP_CHAR_WALL){

                /* Caso não seja para preencher, começa a preencher */
                if(last_char != MAP_CHAR_WALL){
                    if(flag_fill == 0){
                        flag_fill = 1;
                    }else{ /* Caso seja para preencher, para de preencher */
                        flag_fill = 0;
                    }
                }

                /* Substitui o caractere */
                map[j][i] = (char) CHAR_WALL;

            /* Caso o caractere seja um elemento vazio */
            }else if(map[j][i] == '\0'){

                /* Caso seja para preencher, preenche */
                if(flag_fill == 1){
                    map[j][i] = (char) CHAR_WALL;
                }else{
                    map[j][i] = CHAR_EMPTY_SPACE;
                }

            }

            last_char = actual_char;

        }
    }

    return 0;
}

///-------------------///
/// PLAYER
///-------------------///

/**
 * Desenha o jogador no mapa com o formato:
 * "@  "
 * "@@@"
 *
 * @param map       Matriz com os caracteres do mapa
 * @param player    Estrutura que armazena as informações do jogador
 */
void drawPlayer(char map[][MAP_COL], player_t *player){

    map[player->position_y][player->position_x]                 = MAP_CHAR_PLAYER;
    map[player->position_y][(player->position_x + 1) % MAP_COL] = MAP_CHAR_PLAYER;
    map[player->position_y][(player->position_x + 2) % MAP_COL] = MAP_CHAR_PLAYER;
    map[player->position_y - 1][player->position_x]             = MAP_CHAR_PLAYER;
}

/**
 * Apaga o jogador no mapa.
 *
 * @param map       Matriz com os caracteres do mapa
 * @param player    Estrutura que armazena as informações do jogador
 */
void erasePlayer(char map[][MAP_COL], player_t *player){

    map[player->last_y][player->last_x]                 = CHAR_EMPTY_SPACE;
    map[player->last_y][(player->last_x + 1) % MAP_COL] = CHAR_EMPTY_SPACE;
    map[player->last_y][(player->last_x + 2) % MAP_COL] = CHAR_EMPTY_SPACE;
    map[player->last_y - 1][player->last_x]             = CHAR_EMPTY_SPACE;
}

/**
 * Atualiza a posição do jogador no mapa.
 *
 * @param map       Matriz com os caracteres do mapa
 * @param player    Estrutura que armazena as informações do jogador
 */
void updatePlayerPosition(char map[][MAP_COL], player_t *player){
    erasePlayer(map, &*player);
    drawPlayer(map, &*player);
}

/**
 * Verifica se houve colisão entre o jogador e uma parede ou um inimigo
 *
 * @param map       Matriz com os caracteres do mapa
 * @param player    Estrutura que armazena as informações do jogador
 */
int playerCollisions(char map[][MAP_COL], player_t *player){

    int collision = 0;

    if(checkPlayerCollision(map, player, CHAR_WALL) == 1 ||
        checkPlayerCollision(map, player, MAP_CHAR_ENEMY) == 1){
        collision = 1;
    }

    return collision;
}

/**
 * Verifica se houve colisão entre o jogador e um dado caractere
 *
 * @param map       Matriz com os caracteres do mapa
 * @param player    Estrutura que armazena as informações do jogador
 * @param carac     Caractere para a ser comparado
 */
int checkPlayerCollision(char map[][MAP_COL], player_t *player, char carac){

    int flag_collision = 0;

    if(map[player->position_y][player->position_x]                   == carac ||
        map[player->position_y][(player->position_x + 1) % MAP_COL]  == carac ||
        map[player->position_y][(player->position_x + 2) % MAP_COL]  == carac ||
        map[player->position_y - 1][player->position_x]              == carac){
        flag_collision = 1;
    }

    return flag_collision;
}

///-------------------///
/// ENEMY
///-------------------///

/**
 * Desenha o inimigo no mapa com o formato:
 * "XX"
 * "XX"
 *
 * @param map   Matriz com os caracteres do mapa
 * @param enemy Estrutura que armazena as informações do inimigo
 */
void drawEnemy(char map[][MAP_COL], enemy_t *enemy){

    map[enemy->position_y]      [enemy->position_x]                 = MAP_CHAR_ENEMY;
    map[enemy->position_y - 1]  [enemy->position_x]                 = MAP_CHAR_ENEMY;
    map[enemy->position_y - 1]  [(enemy->position_x + 1) % MAP_COL] = MAP_CHAR_ENEMY;
    map[enemy->position_y]      [(enemy->position_x + 1) % MAP_COL] = MAP_CHAR_ENEMY;
}

/**
 * Apaga o inimigo do mapa.
 *
 * @param map   Matriz com os caracteres do mapa
 * @param enemy Estrutura que armazena as informações do inimigo
 */
void eraseEnemy(char map[][MAP_COL], enemy_t *enemy){

    map[enemy->last_y]      [enemy->last_x]                       = CHAR_EMPTY_SPACE;
    map[enemy->last_y - 1]  [enemy->last_x]                   = CHAR_EMPTY_SPACE;
    map[enemy->last_y - 1]  [(enemy->last_x + 1) % MAP_COL]   = CHAR_EMPTY_SPACE;
    map[enemy->last_y]      [(enemy->last_x + 1) % MAP_COL]       = CHAR_EMPTY_SPACE;
}

/**
 * Atualiza as posições dos inimigos no mapa.
 *
 * @param map               Matriz com os caracteres do mapa
 * @param enemies_positions Matriz onde as posições dos inimigos serão armazenadas
 * @param num_enemies       Número de inimigos no vetor
 */
void updateEnemiesPositions(char map[][MAP_COL], enemy_t enemies[MAX_ENEMIES], int *num_enemies, save_t *save){

    int i, k;

    srand(time(NULL));


    /* Percorre os inimigos no vetor */
    for(i = 0; i < *num_enemies; i++){

        /* Armazena a posição anterior */
        enemies[i].last_x = enemies[i].position_x;
        enemies[i].last_y = enemies[i].position_y;

        /* Verifica as colisões do inimigo */
        if(checkEnemyCollision(map, &enemies[i], CHAR_PLAYER_SHOT)){

            /* Apaga o inimigo */
            eraseEnemy(map, &enemies[i]);

            *num_enemies -= 1;

            save->score += 10;

            /* Remove o inimigo do vetor */
            for(k = i; k < (MAX_ENEMIES - 1); k++){
                enemies[k] = enemies[k + 1];
            }

        }else{

            int rx = -1 + (rand() % (1 - (-1) + 1));
            int ry = -1 + (rand() % (1 - (-1) + 1));

            /* Apaga o inimigo */
            eraseEnemy(map, &enemies[i]);

            if(enemies[i].move_delay == ENEMY_MOVE_DELAY){
                enemies[i].position_x = (enemies[i].position_x + rx) % MAP_COL;
                enemies[i].position_y =  enemies[i].position_y + ry;

                /* Caso a nova posição colida em uma parede, retorna à posição anterior */
                if(checkEnemyCollision(map, &enemies[i], CHAR_WALL)){
                    enemies[i].position_x = enemies[i].last_x;
                    enemies[i].position_y = enemies[i].last_y;
                }
                enemies[i].move_delay = 0;
            }else{
                enemies[i].move_delay++;
            }

            /* Desenha o inimigo na nova posição */
            drawEnemy(map, &enemies[i]);
        }

    }
}

/**
 * Verifica se houve colisão entre um inimigo e um dado caractere
 *
 * @param map       Matriz com os caracteres do mapa
 * @param enemy     Estrutura que armazena as informações do inimigo
 * @param carac     Caractere para a ser comparado
 */
int checkEnemyCollision(char map[][MAP_COL], enemy_t *enemy, char carac){

    int flag_collision = 0;

    if(map[enemy->position_y][enemy->position_x]                        == carac ||
        map[enemy->position_y][(enemy->position_x + 1) % MAP_COL]       == carac ||
        map[enemy->position_y - 1][enemy->position_x]                   == carac ||
        map[enemy->position_y - 1][(enemy->position_x + 1) % MAP_COL]   == carac){
        flag_collision = 1;
    }

    return flag_collision;
}

///-------------------///
/// PLAYER SHOT
///-------------------///

/**
 * Cria um novo tiro do jogador e o insere no vetor de tiros.
 *
 * @param map               Matriz com os caracteres do mapa
 * @param player            Estrutura que armazena as informações do jogador
 * @param player_shots      Vetor que armazena os tiros do jogador
 * @param num_player_shots  Número de tiros no vetor
 */
void makePlayerShot(char map[][MAP_COL], player_t *player, playerShot_t player_shots[MAX_PLAYER_SHOTS], int *num_player_shots){

    if(*num_player_shots < MAX_PLAYER_SHOTS){

        playerShot_t new_shot;
        new_shot.position_x = player->position_x + 4;
        new_shot.position_y = player->position_y;
        new_shot.last_x     = player->position_x + 4;
        new_shot.last_y     = player->position_y;
        new_shot.limit      = 0;

        player_shots[*num_player_shots] = new_shot;

        *num_player_shots += 1;

    }

}

/**
 * Desenha o tiro do jogador no mapa com o formato:
 * "--"
 *
 * @param map           Matriz com os caracteres do mapa
 * @param player_shot   Estrutura que armazena as informações do jogador
 */
void drawPlayerShot(char map[][MAP_COL], playerShot_t *player_shot){

    map[player_shot->position_y][player_shot->position_x]                 = CHAR_PLAYER_SHOT;
    map[player_shot->position_y][(player_shot->position_x + 1) % MAP_COL] = CHAR_PLAYER_SHOT;

}

/**
 * Apaga o tiro do jogador do mapa.
 *
 * @param map           Matriz com os caracteres do mapa
 * @param player_shot   Estrutura que armazena as informações do jogador
 */
void erasePlayerShot(char map[][MAP_COL], playerShot_t *player_shot){

    map[player_shot->last_y][player_shot->last_x]                 = CHAR_EMPTY_SPACE;
    map[player_shot->last_y][(player_shot->last_x + 1) % MAP_COL] = CHAR_EMPTY_SPACE;
}

/**
 * Atualiza as posições dos inimigos no mapa.
 *
 * @param map               Matriz com os caracteres do mapa
 * @param enemies_positions Matriz onde as posições dos inimigos serão armazenadas
 * @param num_enemies       Número de inimigos no vetor
 */
void updatePlayerShotsPositions(char map[][MAP_COL], playerShot_t player_shots[MAX_PLAYER_SHOTS], int *num_player_shots){

    int i, k;

    for(i = 0; i < *num_player_shots; i++){

       // if(player_shots[i].is_active){

            /* Armazena a posição anterior do tiro */
            player_shots[i].last_x = player_shots[i].position_x;
            player_shots[i].last_y = player_shots[i].position_y;

            /* Apaga o tiro */
            erasePlayerShot(map, &player_shots[i]);

            /* Caso o limite de percorrimento do tiro não tenha sido alcançado */
            if(player_shots[i].limit < PLAYER_SHOT_LIMIT){


                /* Move o tiro */
                player_shots[i].position_x = (player_shots[i].position_x + 2) % MAP_COL;

                /* Desenha o tiro na nova posição */
                drawPlayerShot(map, &player_shots[i]);
                player_shots[i].limit++;

            }else{
                /* Decrementa o número de tiros */
                *num_player_shots -= 1;

                /* Remove o tiro do vetor */
                for(k = i; k < (MAX_PLAYER_SHOTS - 1); k++){
                    player_shots[k] = player_shots[k + 1];
                }

            }
       // }
    }
}
