#ifndef CONSOLE_H
#define CONSOLE_H

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define CONSOLE_WIDTH 106 /** Largura da janela do console */
#define CONSOLE_HEIGHT 37 /** Altura da janela do console */

void gotoxy(int x, int y);
void clearConsole();
void adjustWindowSize();
void hideCursor();

#endif
