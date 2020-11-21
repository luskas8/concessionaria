/* venda.h
 *
 * Define o tipo venda e os protótipos das operações realizadas sobre
 * esse tipo.
 *
 * Ciro Cirne Trindade
 * 19/11/2020
 */
#ifndef _VENDA_H
#define _VENDA_H
#define ARQ_VENDAS "vendas.dat"

typedef struct {
    int dia;
    int mes;
    int ano;
} data;

typedef struct {
    int cod_automovel; // código do automóvel
    int cod_vendedor; // código do vendedor
    data dt; // data da venda
} venda;

/* função que cadastra uma venda no arquivo */
void cadastrar_venda(void);
/* função que lista todas as vendas realizadas em um mês/ano */
// void listar_vendas_mes(void);
/* função que lista todas as vendas realizadas por um vendedor */
void listar_vendas_vendedor(void);
/* função que ordena um vetor de venda pela data da venda */
// void ordenar_vendas(int, venda []);

#endif