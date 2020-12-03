/* vendedor.h
 *
 * Define o tipo vendedor o os protótipos das operações realizadas
 * sobre esse tipo. 
 *
 * Ciro Cirne Trindade
 * 19/11/2020
 * 
 * Artur Freire dos Santos
 * Lucas Silva dos Anjos
 * 
 * Ciências da Computação
 * 
 * 27/11/2020
 */
#ifndef _VENDEDOR_H
#define _VENDEDOR_H
#include <stdbool.h>
#include <string.h>
#include "utils.h"
#define ARQ_VENDEDORES "vendedores.dat"

typedef struct vendedor {
    int codigo; // código do vendedor
    char nome[41]; // nome do vendedor
} vendedor;

/* função que cadastra um vendedor no arquivo */
void cadastrar_vendedor(void);

/* função que altera um vendedor */
void alterar_vendedor(void);

/* função que lista todos os vendedores */
void listar_vendedores(void);

/* função que recebe um inteiro e um ponteiro de vendedor e retorna se é um código de vendedor cadastrado ou não */
bool vendedor_valido(int, vendedor *);

#endif
