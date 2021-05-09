#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#include "../include/console.h"
#include "../include/menu.h"

#define NUM_OPTIONS 3 /** Quantidade de op��es dispon�veis no menu */
#define NUM_LAST_OPTION ((OPT_NEW_GAME + NUM_OPTIONS) - 1) /** �ltima op��o dispon�vel no menu */
#define CHAR_ENTER 13 /** C�digo ASCII do caractere "Carriage Return", recebido quando o usu�rio pressiona "Enter" no teclado */
#define CHAR_SPACE 32 /** C�digo ASCII do caractere " " (espa�o) */
#define SETA_POS_X 3 /** Posi��o no eixo X do console onde a seta deve ser posicionada */

/**
 * Atualiza a "seta" ( > ) que indica qual op��o do menu est�
 * sendo selecionada e remove a seta da �ltima op��o selecionada.
 *
 * @param last_opt  �ltima op��o selecionada
 * @param opt       Nova op��o selecionada
 */
static void updateSeta(int last_opt, int opt){

    /* Limpa a seta da �tlima op��o selecionada */
    gotoxy(SETA_POS_X, last_opt);
    printf("%c", (char) CHAR_SPACE);

    /* Imprime a seta na nova op��o selecionada */
    gotoxy(SETA_POS_X, opt);
    printf("%c", '>');

    gotoxy(0,0);

}

/**
 * Mostra o menu. Espera at� que o usu�rio
 * escolha uma op��o para tomar uma a��o.
*/
int renderMenu(){

    int option = OPT_NEW_GAME; /** Op��o atual do menu selecionada pelo usu�rio. Inicializada como a primeira op��o */
    int last_option = NULL; /** �ltima op��o do menu selecionada pelo usu�rio */
    char carac; /** Caractere do teclado pressionado pelo usu�rio */

    /* Limpa o console */
    clearConsole();

    /* Imprime o t�tulo do jogo */
    printf("\n");
    printf( "      _____     _______   _______   _______   __    _   _____     _______   ______   \n"
            "     |     |   |       | |       | |       | |  |  | | |     |   |       | |    _ |  \n"
            "     |  __  |  |    ___| |    ___| |    ___| |   |_| | |  __  |  |    ___| |   | ||  \n"
            "     | |  |  | |   |___  |   |___  |   |___  |       | | |  |  | |   |___  |   |_||_ \n"
            "     | |__|  | |    ___| |    ___| |    ___| |  _    | | |__|  | |    ___| |    __  |\n"
            "     |      |  |   |___  |   |     |   |___  | | |   | |      |  |   |___  |   |  | |\n"
            "     |_____|   |_______| |___|     |_______| |_|  |__| |_____|   |_______| |___|  |_|\n\n\n"
            "     Novo jogo\n"
            "     Continuar jogo\n"
            "     Sair\n");

    /* Loop do menu que l� as entradas do teclado at� o usu�rio escolher uma op��o */
    do{
        carac = (char) 0; /* Reseta o �ltimo caractere lido */

        /* L� o caractere do teclado e armazena em carac */
        if(kbhit()) carac = getch();

        switch(carac){
            /* Caso o usu�rio pressione w, atualiza option para a op��o ligerimaente acima */
            case 'w':
            case 'W':
                if(option != OPT_NEW_GAME){
                    option--;
                }
            break;

            /* Caso o usu�rio pressione s, atualiza option para a op��o ligerimaente abaixo */
            case 's':
            case 'S':
                if(option != NUM_LAST_OPTION){
                    option++;
                }
        }

        /* Caso tenha ocorrido uma atualiza��o na op��o selecionada, atualiza a seta */
        if(last_option != option){
            updateSeta(last_option, option);
            last_option = option;
        }

        /* Atraso para o pr�ximo loop */
        Sleep(100);

    }while(carac != (char) CHAR_ENTER);

    return option;
}
