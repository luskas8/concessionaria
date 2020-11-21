/* venda.c
 *
 * Modulo de imprementação das funções de venda
 *
 * Artur Freire
 * Lucas Silva dos Anjos
 * 
 * Ciência da Computação
 * 
 * 21/11/2020
*/

#include <stdio.h>
#include "venda.h"

void cadastrar_venda(void) {
    venda v;
    FILE * vendaFile;
    // Verifica se há algo de errado com o arquivo
    if ((vendaFile = fopen(ARQ_VENDAS, "r+b")) == NULL) {
        printf("\n\n\tERRO: Algo de errado com seu arquivo %s, por favor verifique e tente novamente!\n", ARQ_VENDAS);
        pausarTela();
        return;
    }

    // Move o ponteiro de posição para o final do arquivo
    fseek(vendaFile, 0, SEEK_END);

    printf("Codigo do vendedor: ");
    scanf("%d", &v.cod_vendedor);
    printf("Codigo do automovel: ");
    scanf("%d", &v.cod_automovel);

    fwrite(&v, sizeof(venda), 1, vendaFile);
    fclose(vendaFile);
}