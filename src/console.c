#include <conio.h>
#include <stdlib.h>
#include <windows.h>

/**
 * Muda a posição do cursor no console
 *
 * @param x Posição x no console
 */
void gotoxy(int x, int y){

    /* Cria uma estrutura COORD e define seus membros x y com as novas posições */
    COORD coord = {0, 0};
    coord.X = x;
    coord.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

/**
 * Limpa tudo que está escrito no console.
 */
void clearConsole(){
    system("cls");
}
