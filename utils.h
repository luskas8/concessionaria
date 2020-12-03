/* utils.h
 *
 * Protótipo das funções utilitárias do sitema
 * 
 * Artur Freire dos Santos
 * Lucas Silva dos Anjos
 * 
 * Ciências da Computação
 * 
 * 27/11/2020
*/

#ifndef _UTILS_H
#define _UTILS_H
#include <stdbool.h>
#define MAX_LENGTH 120
#define ERR_OPEN_ARC "\n\n\tERRO: NAO foi possivel criar/encontrar o arquivo %s no diretorio atual!\nPor favor crie-o ou mova o projeto para um diretorio que possua permissao de escrita.\n"
#define CURR_YEAR 2020

/* Função que aguada o usuário pressionar ENTER para continuar a 
execução do programa. */
void pausarTela(char []);

/* Função de apresentação da seção que possibilita o retorno do usuário para 
o menu principal caso tenha entrado na seção atual por engano. */
bool isThisChooseMistaken(char header[], char idOwner[], int * typedId);

/* Função recebe um vetor de caractere e seu inteiro de tamanho e lê as 
informações digitadas na linha. */
void read_line (char line[], int max_length);

/* Função ecebe um inteiro para ser lido como entrada do teclado. */
bool read_int (int * var);

/* Função recebe um ponto flutuante para ser lido como entrada do teclado. */
bool read_float (float * var);

#endif
