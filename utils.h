/* utils.h
 *
 * Protótipo das funções 'uteis' do sitema
 * 
 * Artur Freire dos Santos
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

/* Aguada o usuário pressionar qualquer tecla para continuar execução do programa */
void pausarTela(void);

/* Função recebe um vetor de caractere e seu inteiro de tamanho e lê as informações digitadas
   na linha */
void read_line (char line[], int max_length);

/* Função ecebe um inteiro para ser lido como entrada do teclado */
bool read_int (int * var);

/* Função recebe um ponto flutuante para ser lido como entrada do teclado */
bool read_float (float * var);

#endif