#include "../include/console.h"

/**
 * Muda a posi��o do cursor no console

 *
 * @param x Posi��o x no console
 * @param y Posi��o y no console
 */
void gotoxy(int x, int y){

    /* Cria uma estrutura COORD e define seus membros x y com as novas posi��es */
    COORD coord = {0, 0};
    coord.X = x;
    coord.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

/**
 * Limpa tudo que est� escrito no console.
 */
void clearConsole(){
    system("cls");
}

/**
 * Ajusta o tamanho da janela do console
 */
void adjustWindowSize(){

    char command[50];
    sprintf(command, "mode con: cols=%d lines=%d", CONSOLE_WIDTH, CONSOLE_HEIGHT);
    system(command);

}

/**
 * Torna o cursor do console invis�vel
 */
void hideCursor(){
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}
