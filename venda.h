/* venda.h
 *
 * Defininição de tipos e protótipos das funções
 *
 * Ciro Cirne Trindade
 * 19/11/2020
 * 
 * Artur Freire dos Santos
 * Lucas Silva dos Anjos
 * 
 * Ciências da Computação
 * 
 * 24/11/2020
 */
#ifndef _VENDA_H
#define _VENDA_H
#include "vendedor.h"
#include "automovel.h"
#define ARQ_VENDAS "vendas.dat"

typedef struct data{
    int dia;
    int mes;
    int ano;
} data;

typedef struct venda {
    int cod_automovel;
    int cod_vendedor;
    data dt;
} venda;

/* função que cadastra uma venda no arquivo */
void cadastrar_venda(void);

/* função que lista todas as vendas realizadas em um mês/ano */
void listar_vendas_mes(void);

/* função que lista todas as vendas realizadas por um vendedor */
void listar_vendas_vendedor(void);

/* função que ordena um vetor de venda pela data da venda */
void ordenar_vendas(int, venda []);

int compara(data a, data b);

void quicksortVendas(venda vendas[], int e, int d);

#endif