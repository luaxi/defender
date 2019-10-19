#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "../include/console.h"

#define OPT_1 10
#define OPT_2 11
#define OPT_SAIR 12
#define NUM_OPTIONS 3
#define LAST_OPTION ((OPT_1 + NUM_OPTIONS) - 1)

#define ENTER 13

#define SETA_POS_X 3

/**
    PROTOTYPES
*/
void updateSeta(int last_opt, int opt);


void renderMenu(){

    int option = OPT_1;
    int last_option = NULL;
    char char_opt;

    clearConsole();

    // título
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


    do{
        char_opt = 0;

        if(kbhit()) char_opt = getch();

        switch(char_opt){
            case 'w':
            case 'W':
                if(option != OPT_1){
                    option--;
                }
            break;

            case 's':
            case 'S':
                if(option != LAST_OPTION){
                    option++;
                }
        }
        /*
        if((char_opt == 'w' || char_opt == 'W') && option != OPT_1){
            option--;
        }else if((char_opt == 's' || char_opt == 'S') && option != LAST_OPTION){
            option++;
        }*/


        if(last_option != option){
            updateSeta(last_option, option);
            last_option = option;
        }

    }while((option != OPT_SAIR) || (char_opt != 13));

}

void updateSeta(int last_opt, int opt){

    gotoxy(SETA_POS_X, last_opt);
    printf(" ");

    gotoxy(SETA_POS_X, opt);
    printf("%c", '>');

    gotoxy(0,0);

}
