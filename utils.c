/* utils.c
 *
 * Implementação de funções utilitárias para o sistema
 * 
 * Artur Freire dos Santos
 * Lucas Silva dos Anjos
 * 
 * Ciências da Computação
 * 
 * 27/11/2020
*/

#include <stdio.h>
#include "utils.h"

bool isThisChooseMistaken(char header[], char idOwner[], int * typedId) {
  printf("%s", header);
  printf("Nao deseja estar aqui? Entre com '-1' para voltar ao menu principal.\n\n");
  printf("Informe o codigo do %s: ", idOwner);
  read_int(typedId);
  return (*typedId == -1);
}


void pausarTela(char message[]) {
    printf("%s", message);
    printf("\tPressione ENTER para voltar ao menu...\n");
    char ch;
    read_line(&ch, 1);
}

void read_line(char line[], int max_length) {
    int i = 0;
    char ch;

    while ((ch = getchar()) != '\n') {
        if (i < max_length)
            line[i++] = ch;
    }
    line[i] = '\0';
}

bool read_int (int * var) {
    int result;

    char line[MAX_LENGTH + 1];
    read_line(line, MAX_LENGTH);
    result = sscanf(line, "%d", var);
    return (result == 1);
}

bool read_float (float * var) {
    int result;

    char line[MAX_LENGTH + 1];
    read_line(line, MAX_LENGTH);
    result = sscanf(line, "%f", var);
    return (result == 1);
}