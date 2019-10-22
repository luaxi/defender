#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#include "../include/console.h"

/**
 * Os números das opções representam a sua posição no eixo Y do console.
 *
 * Cada opção é definidas por "OPT_", seguido do número da opção, em
 * ordem crescente.
 *
 * A única opção que difere é a opção de saída, que está definida por "OPT_SAIR".
 */
#define OPT_1 10
#define OPT_2 11
#define OPT_SAIR 12

#define NUM_OPTIONS 3 /** Quantidade de opções disponíveis no menu */
#define LAST_OPTION ((OPT_1 + NUM_OPTIONS) - 1) /** Última opção disponível no menu */
#define ENTER 13 /** Código ASCII do caractere "Carriage Return", recebido quando o usuário pressiona "Enter" no teclado */
#define SETA_POS_X 3 /** Posição no eixo X do console onde a seta deve ser posicionada */

/* PROTOTYPES */
void updateSeta(int last_opt, int opt);
void renderMenu();

/**
 * Mostra o menu. Espera até que o usuário
 * escolha  uma opção para tomar uma ação.
*/
void renderMenu(){

    int option = OPT_1; /** Opção atual do menu selecionada pelo usuário. Inicializada como a primeira opção */
    int last_option = NULL; /** Úlima opção do menu selecionada pelo usuário */
    char carac; /** Caractere do teclado pressionado pelo usuário */

    /* Limpa o console */
    clearConsole();

    /* Imprime o título do jogo */
    printf("\n");
    printf("      _____     _______   _______   _______   __    _   _____     _______   ______   \n");
    printf("     |     |   |       | |       | |       | |  |  | | |     |   |       | |    _ |  \n");
    printf("     |  __  |  |    ___| |    ___| |    ___| |   |_| | |  __  |  |    ___| |   | ||  \n");
    printf("     | |  |  | |   |___  |   |___  |   |___  |       | | |  |  | |   |___  |   |_||_ \n");
    printf("     | |__|  | |    ___| |    ___| |    ___| |  _    | | |__|  | |    ___| |    __  |\n");
    printf("     |      |  |   |___  |   |     |   |___  | | |   | |      |  |   |___  |   |  | |\n");
    printf("     |_____|   |_______| |___|     |_______| |_|  |__| |_____|   |_______| |___|  |_|\n\n\n");

    printf("     Novo jogo\n");
    printf("     Continuar jogo\n");
    printf("     Sair\n");

    /* Loop do menu que lê as entradas do teclado até o usuário escolher uma opção */
    do{
        carac = (char) 0; /* Reseta o último caractere lido */

        /* Lê o caractere do teclado e armazena em carac */
        if(kbhit()) carac = getch();

        switch(carac){
            /* Caso o usuário pressione w, atualiza option para a opção ligerimaente acima */
            case 'w':
            case 'W':
                if(option != OPT_1){
                    option--;
                }
            break;

            /* Caso o usuário pressione s, atualiza option para a opção ligerimaente abaixo */
            case 's':
            case 'S':
                if(option != LAST_OPTION){
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

    }while((option != OPT_SAIR) || (carac != ENTER));

}

/**
 * Atualiza a "seta" ( > ) que indica qual opção do menu está
 * sendo selecionada e remove a seta da última opção selecionada.
 *
 * @param last_opt  Última opção selecionada
 * @param opt       Nova opção selecionada
 */
void updateSeta(int last_opt, int opt){

    /* Limpa a seta da útlima opção selecionada */
    gotoxy(SETA_POS_X, last_opt);
    printf(" ");

    /* Imprime a seta na nova opção selecionada */
    gotoxy(SETA_POS_X, opt);
    printf("%c", '>');

    gotoxy(0,0);

}
