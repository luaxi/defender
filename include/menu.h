#ifndef MENU_H
#define MENU_H

/**
 * Os números das opções representam a sua posição no eixo Y do console.
 *
 * Cada opção é definidas por "OPT_", seguido do número da opção, em
 * ordem crescente.
 *
 * A única opção que difere é a opção de saída, que está definida por "OPT_SAIR".
 */
#define OPT_NEW_GAME 10
#define OPT_CONTINUE 11
#define OPT_EXIT 12

int renderMenu();

#endif
