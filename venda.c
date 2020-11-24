/* venda.c
 *
 * Modulo de imprementação das funções de venda
 *
 * Artur Freire
 * Lucas Silva dos Anjos
 * 
 * Ciência da Computação
 * 
 * 24/11/2020
*/

#include <stdio.h>
#include "utils.h"
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

    printf("Codigo do automovel: ");
    scanf("%d", &v.cod_automovel);
    if (!automovel_valido(v.cod_automovel)) {
        fclose(vendaFile);
        return;
    }

    printf("Codigo do vendedor: ");
    scanf("%d", &v.cod_vendedor);
    if (!vendedor_valido(v.cod_vendedor)) {
        fclose(vendaFile);
        return;
    }

    printf("Data da venda: <dd/mm/aaaa>\n");
    scanf("%d/%d/%d", &v.dt.dia, &v.dt.mes, &v.dt.ano);

    fwrite(&v, sizeof(venda), 1, vendaFile);
    fclose(vendaFile);
}