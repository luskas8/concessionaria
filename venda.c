/* venda.c
 *
 * Modulo de imprementação das funções de venda
 *
 * Artur Freire
 * Lucas Silva dos Anjos
 * 
 * Ciência da Computação
 * 
 * 27/11/2020
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
    read_int(&v.cod_automovel);
    if (!automovel_valido(v.cod_automovel)) {
        fclose(vendaFile);
        return;
    }

    printf("Codigo do vendedor: ");
    read_int(&v.cod_vendedor);
    if (!vendedor_valido(v.cod_vendedor)) {
        fclose(vendaFile);
        return;
    }

    printf("\tData da venda\n");
    printf("Dia: "); read_int(&v.dt.dia);
    printf("Mes: "); read_int(&v.dt.mes);
    printf("Ano: "); read_int(&v.dt.ano);
    
    vender_automovel(v.cod_automovel); // Altera o status de vendido desse automovel

    fwrite(&v, sizeof(venda), 1, vendaFile);
    fclose(vendaFile);
}

void listar_vendas_vendedor(void) {

}

void listar_vendas_mes(void) {
    printf("Informe o mes e ano da venda: <mm/aaaa>\n");
    int i, mes, ano, TAMANHO_VENDAS, TAMANHO_VENDEDORES, TAMANHO_CARROS;

    // READ_INT alterado para formato necessário
    char line[MAX_LENGTH+1];
    read_line(line, MAX_LENGTH);
    sscanf(line, "%d/%d", &mes, &ano);

    if (mes < 1 || mes > 12) {
        printf("\n\n\tERRO: Mes invalido, por favor verifique e tente novamente!\n");
        pausarTela();
        return;
    }

    FILE * vendasFile, * automoveisFile, * vendedoresFile;
    if ((vendasFile = fopen(ARQ_VENDAS, "rb")) == NULL) {
        printf("\n\n\tERRO: Algo de errado com seu arquivo %s, por favor verifique e tente novamente!\n", ARQ_VENDAS);
        pausarTela();
        return;
    }
    if ((automoveisFile = fopen(ARQ_AUTOMOVEIS, "rb")) == NULL) {
        printf("\n\n\tERRO: Algo de errado com seu arquivo %s, por favor verifique e tente novamente!\n", ARQ_AUTOMOVEIS);
        fclose(vendasFile);
        pausarTela();
        return;
    }
    if ((vendedoresFile = fopen(ARQ_VENDEDORES, "rb")) == NULL) {
        printf("\n\n\tERRO: Algo de errado com seu arquivo %s, por favor verifique e tente novamente!\n", ARQ_VENDEDORES);
        pausarTela();
        return;
    }

    // Move o ponteiro de posição para o final do arquivo
    fseek(vendasFile, 0, SEEK_END);
    // Calcula-se o tamanha do vetor de vendas cadastrados
    TAMANHO_VENDAS = ftell(vendasFile) / sizeof(venda);
    venda vendas[TAMANHO_VENDAS];

    fseek(vendedoresFile, 0, SEEK_END);
    TAMANHO_VENDEDORES = ftell(vendedoresFile) / sizeof(vendedor);
    vendedor vendedores[TAMANHO_VENDEDORES];

    fseek(automoveisFile, 0, SEEK_END);
    TAMANHO_CARROS = ftell(automoveisFile) / sizeof(automovel);
    automovel carros[TAMANHO_CARROS];

    // Retornar o ponteiro de leitura para o começo do arquivo
    rewind(vendasFile);
    fread(vendas, sizeof(venda), TAMANHO_VENDAS, vendasFile);
    fclose(vendedoresFile);
    
    rewind(vendedoresFile);
    fread(vendedores, sizeof(vendedor), TAMANHO_VENDEDORES, vendedoresFile);
    fclose(vendedoresFile);
    
    rewind(automoveisFile);
    fread(carros, sizeof(automovel), TAMANHO_CARROS, automoveisFile);
    fclose(automoveisFile);

    ordenar_vendas(TAMANHO_VENDAS, vendas);

    for (i = 0; i < TAMANHO_VENDEDORES; i++) {
        printf("%d %s\n", vendedores[i].codigo, vendedores[i].nome);
    }

    float vendasTotaisMes = 0.0;
    printf("\tDATA DA VENDA\t\tMARCA\t\t\t\tMODELO\t\t\t\tPRECO\t\tVENDEDOR\n");
    printf("\t------------------------------------------------------------------------------------------------------------------------------------\n");
    for (i = 0; i < TAMANHO_VENDAS; i++) {
        if (mes == vendas[i].dt.mes && ano == vendas[i].dt.ano) {
            int id_carro = vendas[i].cod_automovel-1, id_vendedor = vendas[i].cod_vendedor-1; // Pega a posição do carro segundo o que foi cadastrado na venda

            // Informações da venda
            printf("\t%02d/%02d/%d", vendas[i].dt.dia, vendas[i].dt.mes, vendas[i].dt.ano);
            
            // Informações do carro
            printf("\t\t%-21s\t\t%-21s\t\t%.2f", carros[id_carro].marca, carros[id_carro].modelo, carros[id_carro].preco);
            
            // Informações do vendedor
            printf("\t\t%d\t\t%s\t|\t%s\n", vendas[i].cod_vendedor-1, vendedores[vendas[i].cod_vendedor].nome, vendedores[id_vendedor].nome);
            printf("\t------------------------------------------------------------------------------------------------------------------------------------\n");
            vendasTotaisMes += carros[id_carro].preco;
        }
    }
    printf("\tTOTAL\t\t\t\t\t\t\t\t\t\t\t%.2f\n\n", vendasTotaisMes);
    pausarTela();
}

void ordenar_vendas(int tamanho, venda v[]) {
    quicksortVendas(v, 0, tamanho);
}

int compara(data a, data b) {
    // Transforma a data em um numero inteiro para melhor comparação
    int fimA = ( ( (a.dia * 100) + a.mes) * 10000) + a.ano;
    int fimB = ( ( (b.dia * 100) + b.mes) * 10000) + b.ano;

    if (fimA < fimB) return -1;
    if (fimA == fimB) return 0;
    return 1;
}

void quicksortVendas(venda vendas[], int e, int d) {
    int i = e, j = d-1;
    venda aux, x = vendas[(e + d) / 2];
    while (i <= j) {
        while (compara(vendas[i].dt, x.dt) < 0) i++;
        while (compara(vendas[j].dt, x.dt) > 0) j--;
        if (i <= j) {
            aux = vendas[i];
            vendas[i++] = vendas[j];
            vendas[j--] = aux;
        }
    }
    if (j > e) quicksortVendas(vendas, e, j);
    if (i < d) quicksortVendas(vendas, i, d);
}
