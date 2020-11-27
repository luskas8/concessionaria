/* utils.h
 *
 * Protótipo das funções 'uteis' do sitema
 * 
 * Lucas Silva dos Anjos
 * 
 * Ciência da Computação
 * 
 * 27/11/2020
*/

#ifndef _UTILS_H
#define _UTILS_H
#include <stdbool.h>
#define MAX_LENGTH 120

/* Aguada o usuário pressionar qualquer tecla para continuar execussão do programa */
void pausarTela(void);

/* Função recebe um vetor de caracter e seu inteiro de tamanho e lê as informações digitadas
   na linha */
void read_line (char line[], int max_length);

bool read_int (int * var);

#endif