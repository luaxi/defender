#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#include "../include/console.h"
#include "../include/menu.h"

#define NUM_OPTIONS 3 /** Quantidade de opções disponíveis no menu */
#define NUM_LAST_OPTION ((OPT_NEW_GAME + NUM_OPTIONS) - 1) /** Última opção disponível no menu */
#define CHAR_ENTER 13 /** Código ASCII do caractere "Carriage Return", recebido quando o usuário pressiona "Enter" no teclado */
#define CHAR_SPACE 32 /** Código ASCII do caractere " " (espaço) */
#define SETA_POS_X 3 /** Posição no eixo X do console onde a seta deve ser posicionada */

/**
 * Atualiza a "seta" ( > ) que indica qual opção do menu está
 * sendo selecionada e remove a seta da última opção selecionada.
 *
 * @param last_opt  Última opção selecionada
 * @param opt       Nova opção selecionada
 */
static void updateSeta(int last_opt, int opt){

    /* Limpa a seta da útlima opção selecionada */
    gotoxy(SETA_POS_X, last_opt);
    printf("%c", (char) CHAR_SPACE);

    /* Imprime a seta na nova opção selecionada */
    gotoxy(SETA_POS_X, opt);
    printf("%c", '>');

    gotoxy(0,0);

}

/**
 * Mostra o menu. Espera até que o usuário
 * escolha uma opção para tomar uma ação.
*/
int renderMenu(){

    int option = OPT_NEW_GAME; /** Opção atual do menu selecionada pelo usuário. Inicializada como a primeira opção */
    int last_option = NULL; /** Última opção do menu selecionada pelo usuário */
    char carac; /** Caractere do teclado pressionado pelo usuário */

    /* Limpa o console */
    clearConsole();

    /* Imprime o título do jogo */
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

    /* Loop do menu que lê as entradas do teclado até o usuário escolher uma opção */
    do{
        carac = (char) 0; /* Reseta o último caractere lido */

        /* Lê o caractere do teclado e armazena em carac */
        if(kbhit()) carac = getch();

        switch(carac){
            /* Caso o usuário pressione w, atualiza option para a opção ligerimaente acima */
            case 'w':
            case 'W':
                if(option != OPT_NEW_GAME){
                    option--;
                }
            break;

            /* Caso o usuário pressione s, atualiza option para a opção ligerimaente abaixo */
            case 's':
            case 'S':
                if(option != NUM_LAST_OPTION){
                    option++;
                }
        }

        /* Caso tenha ocorrido uma atualização na opção selecionada, atualiza a seta */
        if(last_option != option){
            updateSeta(last_option, option);
            last_option = option;
        }

        /* Atraso para o próximo loop */
        Sleep(100);

    }while(carac != (char) CHAR_ENTER);

    return option;
}
