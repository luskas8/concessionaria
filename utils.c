/* utils.c
 *
 * Implementação de funções uteis para o sistema usadas
 * com frequência
 * 
 * Lucas Silva dos Anjos
 * 
 * Ciência da Computação
 * 
 * 21/11/2020
*/

#include <stdio.h>
#include "utils.h"

void pausarTela(void) {
    printf("\tPressione qualquer tecla para continuar...\n");
    getch();
}