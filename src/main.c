#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "../include/menu.h"
#include "../include/console.h"
#include "../include/game.h"

void renderScreen(char string[200]);

int main()
{

    save_t save; /** Dados iniciais do jogo */
    int menu_return = 0; /** Op��o retornada pelo menu */
    int game_return = 0;

    /** @todo inicializa��o do programa */

    /* Seta o t�tulo do console */
    SetConsoleTitle("Defender");

    /* Redimensiona a janela */
    adjustWindowSize();

    /* Invisibiliza o cursor */
    hideCursor();

    do{
        /* Renderiza o menu e verifica o retorno da op��o selecionada */
        if((menu_return = renderMenu()) == OPT_NEW_GAME ||
           menu_return == OPT_CONTINUE){/* Caso o usu�rio selecione a op��o "novo jogo" */

           if(menu_return == OPT_CONTINUE){

                FILE *arq = fopen(FILE_SAVE, "r");

                if(arq){

                    fread(&save, sizeof(save), 1, arq);
                    fclose(arq);

                }else{
                    /** @todo handle file error */
                }

           }else{
                /* Seta os dados iniciais do novo jogo */
                save.level = 1;
                save.lives = 3;
                save.score = 0;
                save.coluna_inicial = 0;
                save.flag_new_game = 1;
           }

            /* Renderiza os n�veis enquanto o jogo n�o terminar */
            do{

                game_return = renderGame(&save);

            }while(game_return == GAME_RETURN_NEXT_LEVEL);

            switch(game_return){
                case GAME_RETURN_OVER:

                    /** @todo gameover */

                    renderScreen("Voc� perdeu!");

                    break;

                case GAME_RETURN_SAVE:
                    /** @todo salvar */

                    {

                        FILE *arq = fopen(FILE_SAVE, "w");
                        if(arq){
                            fwrite(&save, sizeof(save), 1, arq);
                            fclose(arq);
                        }else{

                            /** @todo handle file error */
                        }


                        renderScreen("Jogo salvo!!");
                    }

                    break;

                case GAME_RETURN_FINISHED:
                    /** @todo fim de jogo */

                    renderScreen("Parabens, voce zerou o jogo!");

                    break;
            }

        }else if(menu_return == OPT_CONTINUE){

            /** @todo continuar jogo */

        }
    }while(menu_return != OPT_EXIT);

    /* Limpa o console */
    clearConsole();

    return 0;
}

void renderScreen(char string[200]){
    clearConsole();
    gotoxy(10, MAP_LIN/2);
    printf("%s", string);
    Sleep(2500);
}
