#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "../include/menu.h"
#include "../include/console.h"

#define CONSOLE_WIDTH 105 /** Largura da janela do console */
#define CONSOLE_HEIGHT 36 /** Altura da janela do console */

int main()
{

    /** @todo inicialização do programa */

    /* Seta o título do console */
    SetConsoleTitle("Defender");

    /* Redimensiona a janela */
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT windowSize = {0, 0, CONSOLE_HEIGHT, CONSOLE_WIDTH};
    SetConsoleWindowInfo(hStdout, 1, &windowSize);

    /* Renderiza o menu */
    renderMenu();

    /* Limpa o console */
    clearConsole();

    return 0;
}
