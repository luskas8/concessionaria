/* automovel.h
 *
 * Define o tipo automóvel e os protótipos das operações realizadas
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
 * 24/11/2020
 */

#ifndef _AUTOMOVEL_H
#define _AUTOMOVEL_H
#include <stdbool.h>
#include "utils.h"
#define ARQ_AUTOMOVEIS "automoveis.dat"
#define ARQ_A_VENDA "avenda.txt"

typedef struct automovel {
    int codigo;
    char marca[21];
    char modelo[21];
    int ano;
    float preco;
    bool vendido;
} automovel;

/* função que cadastra um automóvel no arquivo */
void cadastrar_automovel(void);

/* função que altera os dados de um automóvel cadastrado */
void alterar_automovel(void);

/* função que lista todos os automóveis cadastrados */
void listar_todos_automoveis(void);

/* função que lista os automóveis a venda */
void listar_automoveis_a_venda(void);

/* função que ordenada um vetor do tipo automovel pelo preço */
void ordenar_automoveis(int, automovel []);

/* função de quicksort para ordernar o vetor de tipo automovel */
void quicksort(automovel [], int, int);

/* função que recebe inteiro e um ponteiro de automovel e retornar se é um 
código de automovel válido */
bool automovel_valido(int, automovel *);

/* função que exibe os automoveis em formato de tabela, recebendo como 
parâmetro a própria lista, seu tamanho, seu título (opcional) e a Stream 
onde esses dados devem ser impressos */
void exibirFormatoTabela(automovel [], int, char [], FILE *);

/* função que recebe um inteiro e altera o status de vendido de um carro 
determinado por esse inteiro */
void vender_automovel(int);
#endif 
