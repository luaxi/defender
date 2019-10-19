#include <conio.h>
#include <stdlib.h>
#include <Windows.h>

void gotoxy(int x, int y){
    COORD coord = {0, 0};
    coord.X = x;
    coord.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void clearConsole(){
    system("cls");
}
