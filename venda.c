/* venda.c
 *
 * Modulo de implementação das funções de venda
 *
 * Artur Freire dos Santos
 * Lucas Silva dos Anjos
 * 
 * Ciências da Computação
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
        printf("\n\n\tERRO: O arquivo %s NAO pode ser encontrado!\n", ARQ_VENDAS);
        pausarTela();
        return;
    }

    // Move o ponteiro de posição para o final do arquivo
    fseek(vendaFile, 0, SEEK_END);
    printf("- CADASTRANDO UMA VENDA\n\n");
    printf("Nao deseja estar aqui? Entre com '-1' para voltar ao menu principal.\n\n");
    printf("Codigo do automovel: ");
    read_int(&v.cod_automovel);
    if (v.cod_automovel == -1) {
      fclose(vendaFile);
      return;
    }

    automovel c;
    if (!automovel_valido(v.cod_automovel, &c)) {
        printf("\tERRO: Carro com codigo invalido. Compra NAO cadastrada.\n");
        fclose(vendaFile);
        pausarTela();
        return;
    } else {
        printf("\n\tMarca\t\tModelo\t\tAno\tPreco\n");
        printf("\t------------------------------------------------------------------------\n");
        printf("\t%-16s%s\t\t%4d\t%.2f\n", 
          c.marca, c.modelo, c.ano, c.preco
        );
        printf("\t------------------------------------------------------------------------\n");
    }

    printf("Codigo do vendedor: ");
    read_int(&v.cod_vendedor);
    vendedor vendedorV;
    if (!vendedor_valido(v.cod_vendedor, &vendedorV)) {
        printf("\tERRO: Vendedor com codigo invalido. Compra NAO cadastrada.\n");
        fclose(vendaFile);
        pausarTela();
        return;
    } else {
        printf("\tNome\n");
        printf("\t---------------------------------------\n");
        printf("\t%s\n", vendedorV.nome);
        printf("\t---------------------------------------\n");
    }

    printf("Data da venda (yyyy/mm/dd): ");
    scanf("%d/%d/%d", &v.dt.ano, &v.dt.mes, &v.dt.dia);
    
    vender_automovel(v.cod_automovel); // Altera o status de vendido desse automovel

    fwrite(&v, sizeof(venda), 1, vendaFile);
    fclose(vendaFile);

    printf("\nVenda realizada com sucesso!\n");
    pausarTela();getchar();
}

void listar_vendas_vendedor(void) {
    int codigo, i, TAMANHO_CARROS, TAMANHO_VENDAS, TAMANHO_VENDEDORES;
    FILE * automoveisFile, * vendasFile, * vendedoresFile;
    
    printf("\n\n\tINFORME O CODIGO DO VENDEDOR: ");
    read_int(&codigo);
    vendedor vendedorV;
    if (!vendedor_valido(codigo, &vendedorV)) {
      printf("\tERRO: O codigo digitado e' invalido. Listagem NAO pode ser concluida.\n");
      pausarTela();
      return;
    }
    
    if ((vendasFile = fopen(ARQ_VENDAS, "rb")) == NULL) {
        printf("\n\n\tERRO: O arquivo %s NAO pode ser encontrado!\n", ARQ_VENDAS);
        pausarTela();
        return;
    }
    if ((automoveisFile = fopen(ARQ_AUTOMOVEIS, "rb")) == NULL) {
        printf("\n\n\tERRO: O arquivo %s NAO pode ser encontrado!\n", ARQ_AUTOMOVEIS);
        fclose(vendasFile);
        pausarTela();
        return;
    }

    if ((vendedoresFile = fopen(ARQ_VENDEDORES, "rb")) == NULL) {
      printf("\n\n\tERRO: O arquivo %s NAO pode ser encontrado!\n", ARQ_AUTOMOVEIS);
      fclose(vendasFile);
      pausarTela();
      return;
    }

    // Move o ponteiro de posição para o final do arquivo
    fseek(vendasFile, 0, SEEK_END);
    // Calcula-se o tamanha do vetor de vendas cadastrados
    TAMANHO_VENDAS = ftell(vendasFile) / sizeof(venda);
    venda vendas[TAMANHO_VENDAS];

    fseek(automoveisFile, 0, SEEK_END);
    TAMANHO_CARROS = ftell(automoveisFile) / sizeof(automovel);
    automovel carros[TAMANHO_CARROS];

    fseek(vendedoresFile, 0, SEEK_END);
    TAMANHO_VENDEDORES = ftell(vendedoresFile) / sizeof(vendedor);
    vendedor vendedores[TAMANHO_VENDEDORES];

    // Retornar o ponteiro de leitura para o começo do arquivo
    rewind(vendasFile);
    fread(vendas, sizeof(venda), TAMANHO_VENDAS, vendasFile);
    fclose(vendasFile);

    rewind(automoveisFile);
    fread(carros, sizeof(automovel), TAMANHO_CARROS, automoveisFile);
    fclose(automoveisFile);

    rewind(vendedoresFile);
    fread(vendedores, sizeof(vendedores), TAMANHO_VENDEDORES, vendedoresFile);
    fclose(vendedoresFile);

    ordenar_vendas(TAMANHO_VENDAS, vendas);

    float valorVendasTotais = 0.0;
    printf("\n\tDATA DA VENDA\tMARCA\t\tMODELO\t\tPRECO\t\tVENDEDOR\n");
    printf("\t---------------------------------------------------------------------------------------\n");
    for (i = 0; i < TAMANHO_VENDAS; i++) {
        if (vendas[i].cod_vendedor == codigo) {
            int id_carro = vendas[i].cod_automovel-1; 
            int id_vendedor = vendas[i].cod_vendedor-1;

            printf("\t%02d/%02d/%d", vendas[i].dt.dia, vendas[i].dt.mes, vendas[i].dt.ano);            
            printf("\t%-15s %s\t\t%-11.2f\t%-21s\n", 
              carros[id_carro].marca, 
              carros[id_carro].modelo, 
              carros[id_carro].preco,
              vendedores[id_vendedor].nome
            );
            printf("\t---------------------------------------------------------------------------------------\n");
            valorVendasTotais += carros[id_carro].preco;
        }
    }
    printf("\tTOTAL DO MES\t\t\t\t\t%.2f\n\n", valorVendasTotais);
    pausarTela();
}

void listar_vendas_mes(void) {
    printf("Informe o mes e ano da venda (yyyy/mm): ");
    int i, mes, ano, TAMANHO_VENDAS, TAMANHO_VENDEDORES, TAMANHO_CARROS;

    // READ_INT alterado para formato necessário
    char line[MAX_LENGTH+1];
    read_line(line, MAX_LENGTH);
    sscanf(line, "%d/%d", &ano, &mes);

    if (mes < 1 || mes > 12 || ano > 2020) {
        printf("\tERRO: Data invalida! A listagem NAO pode ser concluida.\n");
        pausarTela();
        return;
    }

    FILE * vendasFile, * automoveisFile, * vendedoresFile;
    if ((vendasFile = fopen(ARQ_VENDAS, "rb")) == NULL) {
        printf("\tERRO: O arquivo %s NAO pode ser encontrado!\n", ARQ_VENDAS);
        pausarTela();
        return;
    }
    if ((vendedoresFile = fopen(ARQ_VENDEDORES, "rb")) == NULL) {
        printf("\tERRO: O arquivo %s NAO pode ser encontrado!\n", ARQ_VENDEDORES);
        fclose(vendasFile);
        pausarTela();
        return;
    }
    if ((automoveisFile = fopen(ARQ_AUTOMOVEIS, "rb")) == NULL) {
        printf("\tERRO: O arquivo %s NAO pode ser encontrado!\n", ARQ_AUTOMOVEIS);
        fclose(vendasFile);
        fclose(vendedoresFile);
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
    fclose(vendasFile);
    
    rewind(vendedoresFile);
    fread(vendedores, sizeof(vendedor), TAMANHO_VENDEDORES, vendedoresFile);
    fclose(vendedoresFile);
    
    rewind(automoveisFile);
    fread(carros, sizeof(automovel), TAMANHO_CARROS, automoveisFile);
    fclose(automoveisFile);

    ordenar_vendas(TAMANHO_VENDAS, vendas);

    float vendasTotaisMes = 0.0;
    printf("\n\tDATA DA VENDA\tMARCA\t\tMODELO\t\tPRECO\t\tVENDEDOR\n");
    printf("\t---------------------------------------------------------------------------------------\n");
    for (i = 0; i < TAMANHO_VENDAS; i++) {
        if (mes == vendas[i].dt.mes && ano == vendas[i].dt.ano) {
            int id_carro = vendas[i].cod_automovel-1;
            int id_vendedor = vendas[i].cod_vendedor-1;

            printf("\t%02d/%02d/%d", vendas[i].dt.dia, vendas[i].dt.mes, vendas[i].dt.ano);
            
            printf("\t%-16s%s\t\t%-11.2f\t%-21s\n",
              carros[id_carro].marca, 
              carros[id_carro].modelo, 
              carros[id_carro].preco,
              vendedores[id_vendedor].nome
            );
            printf("\t---------------------------------------------------------------------------------------\n");
            vendasTotaisMes += carros[id_carro].preco;
        }
    }
    printf("\tTOTAL DO MES\t\t\t\t\t%.2f\n\n", vendasTotaisMes);
    pausarTela();
}

void ordenar_vendas(int tamanho, venda v[]) {
    quicksortVendas(v, 0, tamanho);
}

int compara(data a, data b) {
    // Transforma a data em um numero inteiro para melhor comparação
    int dtA = ( ( (a.dia * 100) + a.mes) * 10000) + a.ano;
    int dtB = ( ( (b.dia * 100) + b.mes) * 10000) + b.ano;

    if (dtA < dtB) return -1;
    if (dtA == dtB) return (dtB - dtA);
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
