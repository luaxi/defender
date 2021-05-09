#ifndef MENU_H
#define MENU_H

/**
 * Os n�meros das op��es representam a sua posi��o no eixo Y do console.
 *
 * Cada op��o � definidas por "OPT_", seguido do n�mero da op��o, em
 * ordem crescente.
 *
 * A �nica op��o que difere � a op��o de sa�da, que est� definida por "OPT_SAIR".
 */
#define OPT_NEW_GAME 10
#define OPT_CONTINUE 11
#define OPT_EXIT 12

int renderMenu();

#endif
